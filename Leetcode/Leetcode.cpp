// Leetcode.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "solution.h"

int main()
{
	Solution a;
	vector<int> a1{ 1,8,6,2,5,4,8,3,7 };
	int res = a.maxArea(a1);
	cout << res;
    return 0;
}
