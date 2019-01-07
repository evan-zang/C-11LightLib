#pragma once
#include "sqlite/sqlite3.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "NonCopyable.h"
#include <string>

using namespace std;
class SmartDB :NonCopyable
{
public:
	SmartDB()
	{

	}
	/*
	*  创建或打开数据库
	*  如果数据库不存在，则数据库将被创建并打开，如果创建失败则设置失败标志
	*  @param[in] fileName:数据库文件的位置
	*/
	explicit SmartDB(const string& fileName) :m_dbHandle(nullptr), m_statement(0)
	{
		Open(fileName);
	}

	~SmartDB()
	{

	}

	/*
	*	打开数据库	
	*/
	bool Open(const string& fileName)
	{
		m_code = sqlite3_open(fileName.data(), &m_dbHandle);
		return (SQLITE_OK == m_code);
	}

	/*
	* 释放资源，关闭数据库
	*/
	bool Close()
	{
		if (nullptr == m_dbHandle)
			return true;
		sqlite3_finalize(m_statement);
		m_code = CloseDBHandle();
		m_statement = nullptr;
		m_dbHandle = nullptr;
		return (SQLITE_OK == m_code);
	}
	
private:
	/*BindParams*/
	int BindParams(sqlite3_stmt* statement, int current)
	{
		return SQLITE_OK;
	}

	template<typename T, typename... Args>
	int BindParams(sqlite3_stmt* statement, int current, T&&first, Args&&...args)
	{
		// 绑定基本类型
		BindValue(statement, current, first);
		if (m_code != SQLITE_OK)
		{
			return m_code;
		}
		BindParams(statement, current + 1, forward<Args>(args)...);
	}

	template<typename T>
	typename enable_if<is_floating_point<T>::value>::type BindValue(sqlite3_stmt* statement,int current,T t)
	{
		m_code = sqlite3_bind_double(statement, current, forward<T>(t));
	}

	template<typename T>
	typename enable_if<is_integral<T>::value>::type BindValue(sqlite3_stmt* statement, int current, T t)
	{
		BindIntValue(statement, current, t);
	}

	template<typename T>
	typename enable_if<is_same<T,int64_t>::value || is_same<T,uint64_t>::value>::type BindIntValue(sqlite3_stmt* statement, int current, T t)
	{
		m_code = sqlite3_bind_int64(statement, current, forward<T>(t));
	}

	template<typename T>
	typename enable_if<!is_same<T, int64_t>::value && !is_same<T, uint64_t>::value>::type BindIntValue(sqlite3_stmt* statement, int current, T t)
	{
		m_code = sqlite3_bind_int(statement, current, forward<T>(t));
	}

	template<typename T>
	typename enable_if<is_same<string,T>::value>::type BindValue(sqlite3_stmt* statement, int current,const T& t)
	{
		m_code = sqlite3_bind_text(statement, current, t.data(), t.length(), SQLITE_TRANSIENT);
	}

	template<typename T>
	typename enable_if<is_same<char*,T>::value || is_same<const char*,T>::value>::type BindValue(sqlite3_stmt* statement,int current,T t)
	{
		m_code = sqlite3_bind_text(statement, current, t, strlen(t) + 1, SQLITE_TRANSIENT);
	}
	template<typename T>
	typename enable_if<is_same<blob, T>::value >::type BindValue(sqlite3_stmt* statement, int current,const T&t)
	{
		m_code = sqlite3_bind_blob(statement, current, t.pBuf,t.size, SQLITE_TRANSIENT);
	}

	template<typename T>
	typename enable_if<is_same<nullptr_t, T>::value >::type BindValue(sqlite3_stmt* statement, int current, const T&t)
	{
		m_code = sqlite3_bind_null(statement, current);
	}
private:
	int CloseDBHandle()
	{
		int code = sqlite3_close(m_dbHandle);
		while (code==SQLITE_BUSY)
		{
			code = SQLITE_OK;
			sqlite3_stmt *stmt = sqlite3_next_stmt(m_dbHandle, nullptr);
			if (stmt==nullptr)
			{
				break;
			}
			code = sqlite3_finalize(stmt);
			if (code==SQLITE_OK)
			{
				code = sqlite3_close(m_dbHandle);
			}
		}
		return code;
	}
private:
	sqlite3* m_dbHandle;
	sqlite3_stmt* m_statement;
	int m_code;					//记录最近一次的错误码
};