// Leetcode.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "solution.h"

int main()
{
	Solution a;
	Interval* b = new Interval(1, 3);
	Interval* c = new Interval(2, 6);
	Interval* d = new Interval(8, 10);
	Interval* e = new Interval(15, 18);
	vector<Interval> vec;
	vec.push_back(*b);
	vec.push_back(*c);
	vec.push_back(*d);
	vec.push_back(*e);
	a.merge(vec);
    return 0;
}

