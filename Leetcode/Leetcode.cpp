// Leetcode.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "solution.h"

int main()
{
	Solution a;
	vector<vector<int>> vec{ {1,2,3},{4,5,6},{7,8,9} };
	vector<int> res = a.spiralOrder(vec);
    return 0;
}
