
#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <map>
#include <functional>

using namespace std;
class DllParser
{
public:
	DllParser():m_hMod(nullptr)
	{
			
	}
	~DllParser()
	{
		UnLoad();
	}

	bool Load(const std::string & dllPath)
	{
		m_hMod = LoadLibraryA(dllPath.data());
		if (nullptr == m_hMod)
		{
			cout << "LoadLibrary failed" << endl;
		}
		return true;
	}

	bool UnLoad()
	{
		if (nullptr == m_hMod)
			return true;
		auto b = FreeLibrary(m_hMod);
		if (!b)
			return false;
		m_hMod = nullptr;
		return true;
	}

	template<typename T>
	function<T> GetFunction(const string& funcName)
	{
		auto it = m_map.find(funcName);
		if (it == m_map.end())
		{
			auto addr = GetProcAddress(m_hMod, funcName.c_str());
			if (!addr)
				return nullptr;
			m_map.insert(make_pair(funcName, addr));
			it = m_map.find(funcName);
		}
		return function<T>((T*)(it->second));
	}

	template<typename T,typename... Args>
	typename result_of<function<T>(Args...)>::type ExcecuteFunc(string& funcName,Args&&... args)
	{
		auto f = GetFunction<T>(funcName);
		if (nullptr==f)
		{
			string s = "can not find this function "+funcName;
			throw exception(s.c_str());
		}
		return f(forward<Args>(args)...);
	}
private:
	HMODULE m_hMod;
	map<string, FARPROC> m_map;
};

int main()
{
	/*
		类似于如下调用
		auto max = ExcecuteFunc<int(int,int)>("Max",5,8);
		auto ret = ExecuteFunc<int(int)><"Get",5);	
	*/
}

