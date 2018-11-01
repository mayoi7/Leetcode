#pragma once
#include "stdafx.h"

// 全排列
// https://leetcode-cn.com/explore/interview/card/top-interview-questions-medium/49/backtracking/93/
class Solution01 {
public:
	int len = 0;

	void getAndPushNum(vector<vector<int>> &res, vector<int> nums, vector<int> pre) {
		if (pre.size() == len - 1) {	// 该向res中添加最终的结果了
			for (int i = 0; i < nums.size(); i++)
			{
				vector<int> temp(pre);
				temp.push_back(nums[i]);
				res.push_back(temp);
			}
		}
		else {
			for (int i = 0; i < nums.size(); i++)
			{
				vector<int> tNum(nums);
				vector<int> tPre(pre);
				tPre.push_back(*(nums.begin() + i));
				tNum.erase(tNum.begin() + i);	// 删掉以保证不出现重复元素
				getAndPushNum(res, tNum, tPre);
			}
			
		}
		return;
	}

	vector<vector<int>> permute(vector<int>& nums) {
		vector<vector<int>> res;
		if (nums.size() == 0)
			return res;

		vector<int> temp;
		len = nums.size();
		getAndPushNum(res, nums, temp);
		return res;
	}
};

// 子集
// https://leetcode-cn.com/explore/interview/card/top-interview-questions-medium/49/backtracking/94/
class Solution {
public:
	void getSubSets(vector<vector<int>> &res, vector<int> nums, int begin, vector<int> pre) {
		res.push_back(pre);
		for (int i = begin; i < nums.size(); i++)
		{
			vector<int> tPre(pre);
			tPre.push_back(nums[i]);
			getSubSets(res, nums, i + 1, tPre);
		}
		return;
	}

	vector<vector<int>> subsets(vector<int>& nums) {
		vector<vector<int>> res;
		vector<int> nullVec = {};
		if (nums.size() == 0) return res;
		getSubSets(res, nums, 0, nullVec);
		return res;
	}
};