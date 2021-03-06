
#include "pch.h"
#include <iostream>
#include <future>

using namespace std;
int main()
{
	/*
		async 的基本用法
	*/
	{
		future<int> f1 = async(launch::async, []() {return 8; });
		cout << f1.get() << endl;

		future<void> f2 = async(launch::async, []() {cout << 7<< endl; });
		f2.wait();

		future<int> future = async(launch::async, []() {this_thread::sleep_for(chrono::seconds(3)); return 7; });
		cout << "waiting...\n";
		
		
		future_status status;
		do 
		{
			status = future.wait_for(chrono::seconds(1));
			if (status == future_status::deferred)
			{
				cout << "deferred\n";
			}
			else if (status == future_status::timeout) {
				cout << "time out" << endl;
			}
			else if (status == future_status::ready) {
				cout << "ready!\n";
			}
		} while (status != future_status::ready);

		cout << "result is " << future.get() << endl;
	}
}

