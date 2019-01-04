#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
using namespace std;

#include "Any.h"
#include "NonCopyable.h"

class IocContainer :NonCopyable
{
public:
	IocContainer(void) {}
	~IocContainer(void) {}

	template<class T, typename Depend, typename... Args>
	typename enable_if<!is_base_of<T,Depend>::value>::type RegisterType(const string& strKey)
	{
		function<T*  (Args...)> func = [](Args... args) {return new T( new Depend(args...)); };//通过闭包擦除了参数类型
		RegisterType(strKey, func);
	}

	template<class T, typename Depend, typename... Args>
	typename enable_if<is_base_of<T,Depend>::value>::type RegisterType(const string& strKey)
	{
		function<T* (Args...)> function = [](Args...args) {return new Depend(args...);  };		//通过闭包擦除了参数类型
		RegisterType(strKey, function);
	}

	template<class T,typename...Args>
	void RegisterSimple(const string& strKey)
	{
		function<T* (Args...)> function = [](Args... args) {return new T(args...); };
		RegisterType(strKey, function);
	}

	template<class T,typename... Args>
	T* Resolve(const string& strKey, Args...args)
	{
		auto it = m_creatorMap.find(strKey);
		if (it == m_creatorMap.end())
			return nullptr;
		Any resolver = it->second;
		function<T* (Args...)> func = resolver.AnyCast<function<T* (Args...)>>();
		return func(args...);
	}

	template<class T,typename... Args>
	shared_ptr<T> ResolveShared(const string& strKey, Args...args)
	{
		T* t = Resolve<T>(strKey, args...);
		return shared_ptr<T>(t);
	}

private:
	void RegisterType(const string& strKey,Any constructor)
	{
		if (m_creatorMap.find(strKey) != m_creatorMap.end())
		{
			throw ::invalid_argument("this key has already exist!");
		}
		// 通过Any擦除了不同类型的构造器
		m_creatorMap.emplace(strKey, constructor);
	}

private:
	unordered_map<string, Any> m_creatorMap;
};