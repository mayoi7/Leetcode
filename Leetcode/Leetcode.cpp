// Leetcode.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "solution.h"

int main()
{
	//Solution a;
	//vector<int> vec = { 10,9,2,5,3,7,101,18 };
	//a.lengthOfLIS(vec);
	Solution a;
	int b = 0;
	TreeNode* r = new TreeNode(1);
	r->left = new TreeNode(2);
	r->right = new TreeNode(3);
	cout << a.isSameTree(r, r);
	/*while (cin >> b)
	{
		cout << a.mySqrt(b) << endl;
	}*/
    return 0;
}

