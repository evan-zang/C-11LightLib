// lambda.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace  std;


class A 
{
public:
	int i_ = 0;
	void func(int x, int y)
	{
		//auto x1 = [] {return i_; } ;// error,没有捕获外部变量
		auto x2 = [=] {i_ + x + y; };	//OK,捕获所有外部变量
		auto x3 = [&] {i_ + x + y; };	//OK，捕获所有外部变量
		auto x4 = [this] {return i_; };	//OK, 捕获所有外部变量
		//auto x5 = [this]{return i_+x+y;}; //error,没有捕获x,y
		auto x6 = [this, x, y] {return i_ + x + y; }; //OK,捕获this指针,x,y
		auto x7 = [this] {return i_++; };	//OK,捕获this指针，并修改成员的值
	}
};
int main()
{
    // 优点：
	// 1）就地匿名定义目标函数或函数对象，不需要额外写一个命名或都函数对象。
	// 2）简洁：不需要额外再写一个函数或都函数对象，避免了代码膨胀和功能分散，让开发者更加集中精力在手边的问题，同时也获取了更高的生产率
	// 3）在需要的时间和地点实现功能闭包，使程序更灵活
	
	// 语法：
	// [capture](params) opt->ret{body;};
	// capture 是捕获列表；params 是参数表;opt 是函数选项;ret 是函数返回值类型; body 是函数体

	{
		auto f = [](int a)->int {return a + 1; };
		cout << f(1) << endl;
		// 初始化列表不能用于返回值的自动推导
		//  auto x2 = [](){return{1,2};}; // 错误，无法推导出返回值类型
		// 无参数时
		auto f1 = [](){return 1; };
		auto f2 = []{return 1; }; // 省略空参数表

	}
	{
		// lambda 表达式可以通过捕获列表捕获一定范围内的变量
		// []	  不捕获任何变量
		// [&]	  捕获外部作用域中的所有变量，并作为引用在函数体中使用(按引用捕获)	
		// [=]    捕获外部作用域中的所有变量，并作为副本在函数体中使用(按值捕获)
		// [=,&foo] 按值捕获外部作用域中所有变量，并按引用捕获foo变量 
		// [bar]	按值捕获bar变量，同时不捕获其他变量 
		// [this]	捕获当前类中的this指针，让lambda表达式拥有和当前类成员函数同样的访问权限。目的是可以在lambda中使用当前类的成员函数和成员变量 

		// 如果希望去修改按值捕获的外部变量，需要显式指明lambda表达式为mutable
		int a = 0;
		// auto f1 = [=] {return a++; };	//error,修改按值捕获的外部变量
		auto f2 = [=]() mutable {return ++a; }; // OK,mutable
		cout << a << " "<<f2()<<' '<<a<<endl;
	}
	{
		//lambda表达式代替函数对象的示例
		class CountEven
		{
			int & count_;
		public:
			CountEven(int& count):count_(count)
			{

			}
			void operator()(int val)
			{
				if (!(val & 1))
				{
					++count_;
				}
			}
		};

		vector<int> v{ 1,2,3,4,5,6 };
		int even_count = 0;
		for_each(v.begin(), v.end(), CountEven(even_count));
		cout << "The number of even is  " << even_count << endl;

		even_count = 0;
		// lambda表达式替代仿函数
		for_each(v.begin(), v.end(), [&even_count](int val) {
			if (!(val & 1))
			{
				++even_count;
			}
		});

		cout << "The number of even is  " << even_count << endl;
	}
}
