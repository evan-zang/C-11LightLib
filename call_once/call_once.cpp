
#include "pch.h"
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
once_flag flag;

void do_once()
{
	call_once(flag, []() {cout << "Called once" << endl; });
}
int main()
{

	thread t1(do_once);
	thread t2(do_once);
	thread t3(do_once);	
	t1.join();
	t2.join();
	t3.join();

}
