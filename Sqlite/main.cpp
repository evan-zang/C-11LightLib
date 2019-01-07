#include "pch.h"
#include <iostream>
#include <string>
#include "sqlite/sqlite3.h"

using namespace std;
void doTest()
{
	//创建数据库
	sqlite3* conn = nullptr;
	int result = sqlite3_open("test.db", &conn);

	// 创建表
	const char* createTableSQL = "CREATE TABLE if not exists PersonTable(ID INTEGER NOT NULL,Name Text,Address BLOB);";
	sqlite3_exec(conn, createTableSQL, nullptr, nullptr, nullptr);
	// 插入数据
	const char* sqlinsert = "INSERT INTO PersonTable(ID,Name,Address) VALUES(?,?,?);";
	int id = 2;
	const char* name = "Peter";
	const char* city = "zhuhai";

	sqlite3_stmt* stmt2 = NULL;

	// 翻译SQL脚本
	sqlite3_prepare_v2(conn, sqlinsert, strlen(sqlinsert), &stmt2, nullptr);
	sqlite3_bind_int(stmt2, 1, id);
	sqlite3_bind_text(stmt2, 2, name, strlen(name), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt2, 2, city, strlen(city), SQLITE_TRANSIENT);

	//执行sql操作
	sqlite3_step(stmt2);
	// 释放句柄
	sqlite3_finalize(stmt2);
	sqlite3_close(conn);
}
int main()
{
	doTest();
}



