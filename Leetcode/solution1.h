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
class Solution02 {
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

// 单词搜索
// https://leetcode-cn.com/explore/interview/card/top-interview-questions-medium/49/backtracking/95/
class Solution03 {
public:
	bool findIt(string s_sub, vector<vector<char>> board, int i, int j, int begin, bool* visited) {
		if (i < 0 || i >= board.size() || j < 0 || j >= board[i].size()) {
			return false;
		}
		int col = board[i].size();
		if (visited[i*col + j] == true) return false;

		if (begin >= s_sub.size()) return false;
		else if (begin == s_sub.size() - 1) {
			return board[i][j] == s_sub[begin];
		}
		if (board[i][j] != s_sub[begin]) {
			return false;
		}

		bool flag = false;
		
		visited[i*col + j] = true;
		flag = flag || findIt(s_sub, board, i - 1, j, begin + 1, visited);
		flag = flag || findIt(s_sub, board, i, j - 1, begin + 1, visited);
		flag = flag || findIt(s_sub, board, i + 1, j, begin + 1, visited);
		flag = flag || findIt(s_sub, board, i, j + 1, begin + 1, visited);
		if (flag) {
			return true;
		}
		else {
			visited[i*col + j] = false;
			return false;
		}
	}

	bool exist(vector<vector<char>>& board, string word) {
		if (word == "") return false;
		if (board.empty() || board.size() == 0) return false;

		int raw = board.size(), col = board[0].size();
		bool* visited = new bool[raw*col];

		for (int i = 0; i < board.size(); i++)
		{
			for (int j = 0; j < board[i].size(); j++)
			{
				if (board[i][j] == word[0]) {
					if (findIt(word, board, i, j, 0, visited) == true) return true;
				}
			}
		}
		return false;
	}
};

// 颜色分类
// https://leetcode-cn.com/explore/interview/card/top-interview-questions-medium/50/sorting-and-searching/96/
class Solution04 {
public:
	void sortColors(vector<int>& nums) {
		int k = 0;
		int cnt = 0;
		if (nums.size() <= 1) return;
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] == 0) {
				nums[k] = 0;
				++k;
			}
			else if (nums[i] == 1) {
				++cnt;
			}
		}
		for (int i = 0; i < cnt; i++)
		{
			nums[k + i] = 1;
		}
		for (int i = k + cnt; i < nums.size(); i++)
		{
			nums[i] = 2;
		}
	}
};

// 前K个高频元素
// https://leetcode-cn.com/explore/interview/card/top-interview-questions-medium/50/sorting-and-searching/97/
class Solution05 {
public:
	vector<int> topKFrequent(vector<int>& nums, int k) {
		unordered_map<int, int> m;
		priority_queue<pair<int, int>> q;
		vector<int> res;
		for (auto a : nums) ++m[a];
		for (auto it : m) q.push({ it.second, it.first });
		for (int i = 0; i < k; ++i) {
			res.push_back(q.top().second); q.pop();
		}
		return res;
	}
};

// 数组中的第K个最大元素
// https://leetcode-cn.com/explore/interview/card/top-interview-questions-medium/50/sorting-and-searching/98/
class Solution06 {
public:
	int findKthLargest(vector<int>& nums, int k) {
		priority_queue<int> q;
		for (int i = 0; i < nums.size(); i++)
		{
			q.push(nums[i]);
		}
		for (int i = 0; i < k - 1; i++)
		{
			q.pop();
		}
		return q.top();
	}
};