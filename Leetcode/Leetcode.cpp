// Leetcode.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "solution.h"

int main()
{
	//Solution a;
	//vector<int> vec = { 10,9,2,5,3,7,101,18 };
	//a.lengthOfLIS(vec);
	//Solution a;
	//string b = "";
	//vector<int> c = { 1,2,3,4,5,6,7,8,9,10 };
	//a.containsNearbyDuplicate(c, 15);
	MyStack a;
	a.push(1);
	a.push(2);	
	a.push(3);
	cout << a.pop() << endl;
	cout << a.pop() << endl;
	cout << a.pop() << endl;
	cout << a.empty() << endl;
    return 0;
}

