
#include "pch.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;
int main()
{
	/*
		emplace_back 能就地通过参数构造对象，不需要拷贝或者移动内存，
		相比push_back能更好地避免内存的拷贝与移动。
	*/
	{
		// 基本用法 
		struct A {
			int x;
			int y;
			A(int a, double b) :x(a), y(b) {}
		};

		vector<A> v;
		v.emplace_back(1, 2);
		cout << v.size() << endl;
	}
	/*
		emplace_back 和 push_back的比较
	*/
	{
		struct Complicated {
			int year;
			double country;
			string name;
			Complicated(int a,double b,string c):year(a),country(b),name(c)
			{
				cout << "is constructed" << endl;
			}
			Complicated(const Complicated& other):year(other.year),country(other.country),name(move(other.name))
			{
				cout << "is moved" << endl;
			}
		};

		map<int, Complicated> m;
		int anInt = 4;
		double aDouble = 5.0;
		string aString = "C++";
		cout << "--insert--" << endl;
		m.insert(make_pair(4, Complicated(anInt, aDouble, aString)));

		cout << "--emplace--" << endl; 
		m.emplace(4, Complicated(anInt,aDouble,aString));

		cout << "--emplace_back--" << endl;
		vector<Complicated> v;
		v.emplace_back(anInt, aDouble, aString);

		cout << "--push_back--" << endl;
		v.push_back(Complicated(anInt, aDouble, aString));
	}
}
