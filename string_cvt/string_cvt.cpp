// string_cvt.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <codecvt>

using namespace std;
int main()
{
	wstring str = L"中国人";
	wstring_convert<codecvt<wchar_t, char, mbstate_t>> converter(new codecvt<wchar_t, char, mbstate_t>("CHS"));

	string narrowStr = converter.to_bytes(str);
	wstring wstr = converter.from_bytes(narrowStr);
	cout << narrowStr << endl;
	wcout.imbue(locale("chs"));
	wcout << wstr << endl;
}
