#pragma once
#include <string>
#include <functional>
#include <map>
#include "Any.h"
#include "function_traits.h"
#include "NonCopyable.h"

using namespace std;

class MessageBus :NonCopyable
{
public:
	//ע����Ϣ
	template<typename F>
	void Attach(F&& f, const string& strTopic = "")
	{
		auto func = to_function(forward<F>(f));
		Add(strTopic, move(func));
	}

	// ������Ϣ
	template<typename R>
	void SendReq(const string& strTopic = "")
	{
		using function_type = function<R()>;
		string strMsgType = strTopic + typeid(function_type).name();
		auto range = m_map.equal_range(strMsgType);
		for (Iterater it = range.first;it!= range.second;++it)
		{
			auto f = it->second.AnyCast<function_type>();
			f();
		}
	}

	template<typename R,typename... Args>
	void SendReq(Args&&...args, const string& strTopic = "")
	{
		using function_type = function<R(Args...)>;
		string strMsgType = strTopic + typeid(function_type).name();
		auto range = m_map.equal_range(strMsgType);
		for (Iterater it = range.first; it != range.second;++it)
		{
			auto f = it->second.AnyCast<function_type>();
			f(forward<Args>(args)...);
		}
	}

	//�Ƴ�ĳ�����⣬��Ҫ�������Ϣ����
	template<typename R,typename...Args>
	void Remove(const string& strTopic = "")
	{
		using function_type = function<R(Args...)>;//typename function_traits<void(Args)>::stl_function_type;

		string strMsgType = strTopic + typeid(function_type).name();
		int count = m_map.count(strMsgType);
		auto range = m_map.equal_range(strMsgType);
		m_map.erase(range.first, range.second);
	}
private:
	template<typename F>
	void Add(const string& strTopic, F&& f)
	{
		string strMsgType = strTopic + typeid(F).name();
		m_map.emplace(move(strMsgType), forward<F>(f));
	}
private:
	multimap<string, Any> m_map;
	typedef multimap<string, Any>::iterator Iterater;
};