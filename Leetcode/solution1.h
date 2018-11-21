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

// 搜索二维矩阵 II
// https://leetcode-cn.com/explore/interview/card/top-interview-questions-medium/50/sorting-and-searching/103/
class Solution11 {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		int raw = matrix.size();
		if (raw == 0) return false;
		int col = matrix[0].size();
		int x = 0, y = col - 1;
		if (raw == 0 || col == 0) return false;
		while (x < raw && y >= 0) {
			if (matrix[x][y] == target) return true;
			else if (matrix[x][y] < target) ++x;
			else if (matrix[x][y] > target) --y;
		}
		return false;
	}
};

// 跳跃游戏
// https://leetcode-cn.com/explore/interview/card/top-interview-questions-medium/51/dynamic-programming/104/
class Solution12 {
public:
	unordered_map<int, int> uMap;
	int len = 0;

	bool canJ(vector<int> nums, int start) {
		if (start >= len - 1) return true;
		if (nums[start] == 1) {
			if (canJ(nums, start + 1)) return true;
			else {
				uMap[start] = 1;
				return false;
			}
		}

		int maxJump = start + nums[start];
		if (maxJump >= nums.size() - 1) {
			return true;
		}
		if (nums[start] == 0) {
			uMap[start] = 1;
			return false;
		}
		for (int i = nums[start]; i >= 1; i--)
		{
			int target = start + i;
			if (uMap.find(target) != uMap.end() ) {
				uMap[start] = 1;
				return false;
			}
			if (canJ(nums, target) == true) {
				return true;
			}
			else {
				uMap[start] = 1;
			}
		}
		return false;
	}

	bool canJump(vector<int>& nums) {
		if (nums.size() == 0) return true;
		len = nums.size();
		return canJ(nums, 0);
	}
};

// 不同路径
// https://leetcode-cn.com/explore/interview/card/top-interview-questions-medium/51/dynamic-programming/105/
class Solution13 {
public:
	int uniquePaths(int m, int n) {
		if (m == 0 || n == 0) return 0;
		if (m == 1 && n == 1) return 1;
		int a[105][105] = { 0 };
		for (int i = m - 2; i >= 0; i--) {
			a[i][n - 1] = 1;
		}
		for (int j = n - 2; j >= 0; j--) {
			a[m - 1][j] = 1;
		}
		for (int i = m - 2; i >= 0; i--) {
			for (int j = n - 2; j >= 0; j--) {
				a[i][j] = a[i + 1][j] + a[i][j + 1];
			}
		}
		return a[0][0];
	}
};

// 零钱兑换
// https://leetcode-cn.com/explore/interview/card/top-interview-questions-medium/51/dynamic-programming/106/
// source add: https://blog.csdn.net/qq_22080999/article/details/80860182
class Solution14 {
public:
	int coinChange(vector<int>& coins, int amount) {
		vector<int> dp;
		//初始化，-1表示这个金额的最优解没有
		for (int i = 0; i <= amount; ++i)
			dp.push_back(-1);

		dp[0] = 0;

		for (int i = 1; i <= amount; ++i)//递推金额，从1元到amount元
		{
			for (int j = 0; j < coins.size(); ++j)//循环面值数组
			{//如果现在这个金额大于等于现在的面值的话，并且，差值是一个最优解可达的金额，那么接下来就要更新当前金额钞票张数了
				if (i - coins[j] >= 0 && dp[i - coins[j]] != -1)
				{//如果这个金额是第一次循环到，等于-1,或者已经有了钞票张数，但是这个张数更大，那么就用更小的张数代替
					if (dp[i] == -1 || dp[i] > dp[i - coins[j]] + 1)
						dp[i] = dp[i - coins[j]] + 1;
				}
			}
		}

		return dp[amount];
	}
};

// Longest Increasing Subsequence
// https://leetcode-cn.com/explore/interview/card/top-interview-questions-medium/51/dynamic-programming/107/
class Solution15 {
public:
	int lengthOfLIS(vector<int>& nums) {
		if (nums.size() <= 1) return nums.size();
		vector<int> a(nums.size(), 1);

		int maxN = 1;
		for (int i = 1; i < nums.size(); i++)
		{
			a[i] = 1;
			for (int j = 0; j < i; j++)
			{
				if (nums[i] > nums[j]) {
					a[i] = a[i] < a[j] + 1 ? a[j] + 1 : a[i];
				}
			}
			if (a[i] > maxN) maxN = a[i];
		}
		return maxN;
	}
};

//class RandomizedSet {
//public:
//	vector<int> nums;
//	int hashset[10086] = { 0 };
//	/** Initialize your data structure here. */
//	RandomizedSet() {
//		
//	}
//
//	/** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
//	bool insert(int val) {
//		if (hashset[val % 10086] != 0) return false;
//		hashset[val % 10086] = val / 10086 + 1;
//		nums.push_back(val);
//		return true;
//	}
//
//	/** Removes a value from the set. Returns true if the set contained the specified element. */
//	bool remove(int val) {
//		if (hashset[val % 10086] == 0) return false;
//		else 
//	}
//
//	int makeRondom() {
//		
//	}
//
//	/** Get a random element from the set. */
//	int getRandom() {
//		
//	}
//};

// 快乐数
// https://leetcode-cn.com/explore/interview/card/top-interview-questions-medium/53/math/112/
class Solution16 {
public:
	set<int> nset = { 0 };

	bool isHappy(int n) {
		if (n == 1) return true;
		if (nset.find(n) != nset.end()) {	// loop exist
			return false;
		}
		nset.insert(n);
		return isHappy(getAllSiteSum(n));
	}

	int getAllSiteSum(int n) {
		int sum = 0;
		while (n) {
			int k = n % 10;
			sum += k * k;
			n /= 10;
		}
		return sum;
	}
};

// 阶乘后的零
// https://leetcode-cn.com/explore/interview/card/top-interview-questions-medium/53/math/113/
class Solution17 {
public:
	long a[15] = { 1,5,25,125,625,3125,15625,78125,390625,1953125,9765625,48828125,244140625 };

	int trailingZeroes(int n) {
		return getFiveCount(n);
	}

	int getFiveCount(int n) {
		if (n < 5) return 0;
		else return n / 5 + getFiveCount(n / 5);
	}
};

// 67. Add Binary
class Solution18 {
public:
	string addBinary(string a, string b) {
		int len1 = a.size();
		int len2 = b.size();
		int c = 0;
		string a1;
		string b1;
		if (len1 > len2) {
			a1 = a;
			b1 = b;
		}
		else {
			b1 = a;
			a1 = b;
			swap(len1, len2);
		}

		for (int i = 1; i <= len1; i++)
		{
			int sum = (a1[len1 - i] - '0') + c;
			if (i <= len2) {
				sum += (b1[len2 - i] - '0');
			}
			if (sum > 1) {
				c = 1;
				sum %= 2;
			}
			else c = 0;

			a1[len1 - i] = (sum + '0');
		}
		if (c > 0) {
			a1.insert(a1.begin(), '1');
		}
		return a1;
	}
};

// 69. Sqrt(x)
class Solution {
public:
	int mySqrt(int x) {
		if (x < 2) return x;
		int res = 0;
		for (int i = 1; i <= x/2 + 1; i++)
		{
			long long t = (long long)i * i;
			if (t > x) return res;
			else if (t == x)return i;
			else res = i;
		}
		return -1;
	}
};

// 83. Remove Duplicates from Sorted List

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	ListNode * deleteDuplicates(ListNode* head) {
		if (head == NULL || head->next == NULL) return head;
		ListNode* p = head;
		ListNode* node = head->next;
		while (node) {
			if (node->val != p->val) {
				p->next = node;
				p = p->next;
			}
			node = node->next;
		}
		p->next = node;
		return head;
	}
};