// Leetcode.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "solution.h"

int main()
{
	Solution a;
	vector<vector<char>> s_vec = {
		{ 'A','B','C','E' },
		{ 'S','F','C','S' },
		{ 'A','D','E','E' }
	};
	cout << a.exist(s_vec, "ABCD");
    return 0;
}

