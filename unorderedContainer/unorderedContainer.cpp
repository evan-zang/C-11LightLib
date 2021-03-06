
#include "pch.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>
#include <bitset>
using namespace std;
int main()
{
   /*
		无序容器中的元素是不排序的，map和set内部是红黑树,在插入元素的时会自动排序，
		而无序容器内部是散列表(Hash Table),通过哈希(Hash)，而不是排序来快速操作元素
		，使得效率更高。   
   */
	{
		struct Key {
			string first;
			string second;
		};

		struct KeyHash
		{
			size_t operator() (const Key& k) const {
				return hash<string>()(k.first) ^ (hash<string>()(k.second)<<1);
			}
		};

		struct KeyEqual {
			bool operator()(const Key& lhs, const Key& rhs)const {
				return lhs.first == rhs.first && lhs.second ==rhs.second;
			}
		};

		// default constructor:empty map
		unordered_map<string, string> ml;

		//list constructor
		unordered_map<int, string> m2 = {
			{1,"foo"},
			{3,"bar"},
			{2,"baz"},
		};

		// copy constructor 
		unordered_map<int, string> m3 = m2;

		// move constructor
		unordered_map<int, string> m4 = move(m2);

		// range constructor 
		vector<pair<bitset<8>, int>> v = { {0x12,1},{0x01,-1} };
		unordered_map<bitset<8>,double> m5(v.begin(),v.end());

		// constructor for a custom type
		unordered_map<Key, string, KeyHash, KeyEqual> m6 = {
			{{"John","Doe"},"example"},
			{{"Mary","Sue"},"another"}
		};
	}
	
}
