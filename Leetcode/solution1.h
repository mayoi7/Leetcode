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

// 寻找峰值
// https://leetcode-cn.com/explore/interview/card/top-interview-questions-medium/50/sorting-and-searching/99/
class Solution07 {
public:
	int findPeakElement(const vector<int> &num) {
		if (num.size() == 0) return 0;

		int start = 0;
		int end = num.size() - 1;

		while (start <= end)
		{
			if (start == end) return start;

			int mid = start + (end - start) / 2;

			if (num[mid] < num[mid + 1])
			{
				start = mid + 1;
			}
			else
			{
				end = mid;
			}
		}
	}
};

// 在排序数组中查找元素的第一个和最后一个位置
// https://leetcode-cn.com/explore/interview/card/top-interview-questions-medium/50/sorting-and-searching/100/
class Solution08 {
public:
	void findStart(vector<int> nums, int lo, int hi, int target, int& start, int& end) {
		while (lo <= hi) {
			int mid = (lo + hi) / 2; 
			if (lo == hi) {
				if (nums[lo] == target) {
					start = lo;
					end = lo;
				}
				else {
					start = -1;
					end = -1;
				}
				return;
			}
			if (nums[mid] > target) {
				hi = mid;
			}
			else if (nums[mid] < target) {
				lo = mid + 1;
			}
			else {
				for (int i = mid - 1; i >= 0; i--)
				{
					if (nums[i] != target) {
						start = i + 1;
						break;
					}
				}
	
				for (int i = mid + 1; i < nums.size(); i++)
				{
					if (nums[i] != target) {
						end = i - 1;
						break;
					}	
				}
				return;
			}
		}
	}

	vector<int> searchRange(vector<int>& nums, int target) {
		vector<int> res = { -1,-1 };
		if (nums.size() <= 0) return res;
		else if (nums.size() == 1) {
			if (nums[0] == target) {
				res[0] = 0;
				res[1] = 0;
			}
			return res;
		}
		int s = 0, e = nums.size();
		
		findStart(nums, 0, nums.size(), target, s, e);
		if (nums[0] == target) s = 0;
		if (*(nums.end() - 1) == target) e = nums.size() - 1;
		res[0] = s;
		res[1] = e;
		return res;
	}
};

// 合并区间
// https://leetcode-cn.com/explore/interview/card/top-interview-questions-medium/50/sorting-and-searching/101/
struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

struct cmp
{
	bool operator() (Interval a, Interval b) {
		return a.start > b.start;
	}
};

class Solution09 {
public:
	Interval* cmpr(Interval& a, Interval& b) {	// a.start < b.start
		if (b.end < a.end) {
			return &a;
		}
		else
		{
			if (b.start > a.end) {
				return NULL;
			}
			Interval* temp = new Interval(a.start, b.end);
			return temp;
		}
	}

	vector<Interval> merge(vector<Interval>& intervals) {
		priority_queue<Interval, vector<Interval>, cmp> q;
		vector<Interval> res;
		for (int i = 0; i < intervals.size(); i++)
		{
			q.push(intervals[i]);
		}
		while (!q.empty())
		{
			Interval a = q.top();
			q.pop();
			if (q.empty()) {
				res.push_back(a);
				break;
			}
			Interval b = q.top();

			Interval* t = cmpr(a, b);
			if (t == NULL) {
				res.push_back(a);
			}
			else {
				q.pop();
				q.push(*t);
			}
		}
		return res;
	}
};

//搜索旋转排序数组
// https://leetcode-cn.com/explore/interview/card/top-interview-questions-medium/50/sorting-and-searching/102/
class Solution10 {
public:
	int halfSearch(vector<int> nums,int target, int lo, int hi) {
		while (lo <= hi) {
			if (lo == hi) return nums[lo] == target ? lo : -1;
			int mid = (lo + hi) / 2;
			if (nums[mid] == target) return mid;
			else if (nums[mid] < target) lo = mid + 1;
			else hi = mid;
		}
		return -1;
	}

	int search(vector<int>& nums, int target) {
		int hi = nums.size();
		if (hi == 0) return -1;
		else if (hi == 1) return nums[0] == target ? 0 : -1;
		if (nums[0] == target) return 0;
		if (nums[hi - 1] == target) return hi - 1;

		int lo = 0;
		if (nums[hi - 1] > target) {
			if (nums[lo] < target) {
				return halfSearch(nums, target, lo, hi);
			}
			else {
				int tHi = hi;
				int tLo = lo;
				while (tLo <= tHi) {
					if (tLo == tHi) {
						if (nums[tLo] > target) return -1;
						lo = tLo;
						break;
					}
					int tMid = (tLo + tHi) / 2;
					if (nums[tMid] == target) return tMid;
					else if (nums[tMid] > target) {
						if (nums[tMid] <= nums[hi - 1]) {
							hi = tMid;
							tHi = tMid;
						}
						else {
							tLo = tMid + 1;
						}
					}
					else {
						lo = tMid;
						break;
					}
				}
				return halfSearch(nums, target, lo, hi);
			}
		}
		else {
			if (nums[lo] > target) return -1;
			else {
				int tLo = lo;
				int tHi = hi;
				while (tLo <= tHi) {
					if (tLo == tHi) {
						if (nums[tLo] > target) return -1;
						hi = tLo;
						break;
					}
					int tMid = (tLo + tHi) / 2;
					if (nums[tMid] == target) return tMid;
					else if (nums[tMid] > target) {
						hi = tHi;
						break;
					}
					else {
						if (nums[tMid] <= nums[hi - 1]) {
							tHi = tMid;
						}
						else {
							lo = tMid + 1;
							tLo = tMid + 1;
						}
					}
				}
				return halfSearch(nums, target, lo, hi);
			}
		}
	}
};