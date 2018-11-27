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
class Solution19 {
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

class Solution20 {
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

// 100. Same Tree
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution21 {
public:
	vector<int> pv;
	vector<int> mv;
	int index = 0;

	void pretrl(TreeNode* root) {
		pv.push_back(root->val);
		if (root->left != NULL) pretrl(root->left);
		else pv.push_back('#');
		if (root->right != NULL) pretrl(root->right);
		else pv.push_back('$');
	}

	bool checkpre(TreeNode* root) {
		if (pv[index] != root->val) return false;
		++index;
		bool f1 = true, f2 = true;
		if(root->left != NULL) f1 = checkpre(root->left);
		else {
			f1 = (pv[index++] == '#');
		}
		if (root->right != NULL) f2 = checkpre(root->right);
		else {
			f2 = (pv[index++] == '$');
		}
		return f1 && f2;
	}

	void midtrl(TreeNode* root) {
		if (root->left != NULL) midtrl(root->left);
		else mv.push_back('#');

		mv.push_back(root->val);
		if (root->right != NULL) midtrl(root->right);
		else mv.push_back('$');
	}

	bool checkmid(TreeNode* root) {
		bool f1 = true, f2 = true;
		if (root->left != NULL) f1 = checkmid(root->left);
		else f1 = (mv[index++] == '#');
		if (mv[index] != root->val) return false;
		++index;
		if (root->right != NULL) f2 = checkmid(root->right);
		else f2 = (mv[index++] == '$');
		return f1 && f2;
	}

	bool isSameTree(TreeNode* p, TreeNode* q) {
		if (p == NULL) return q == NULL;
		if (q == NULL) return false;
		index = 0;
		pretrl(p);
		bool flag = checkpre(q);
		if (!flag) return false;
		index = 0;
		midtrl(p);
		flag = checkmid(q);
		return flag;
	}
};

// 107. Binary Tree Level Order Traversal II
class Solution22 {
public:
	vector<vector<int>> levelOrderBottom(TreeNode* root) {
		vector<vector<int>> res;
		if (root == NULL) return res;

		stack<vector<TreeNode*>> stc;
		queue<TreeNode*> tree;

		tree.push(root);
		while (!tree.empty()) {
			vector<TreeNode*> temp;
			while (!tree.empty()) {
				temp.push_back(tree.front());
				tree.pop();
			}
			stc.push(temp);
			int len = temp.size();
			for (int i = 0; i < len; i++)
			{
				if (temp[i]->left != NULL) tree.push(temp[i]->left);
				if (temp[i]->right != NULL) tree.push(temp[i]->right);
			}
		}
		while (!stc.empty()) {
			vector<TreeNode*> temp = stc.top();
			vector<int> vals;
			int len = temp.size();
			for (int i = 0; i < len; i++)
			{
				vals.push_back(temp[i]->val);
			}
			res.push_back(vals);
			stc.pop();
		}
		return res;
	}
};

// 110. Balanced Binary Tree
class Solution23 {
public:
	int depth(TreeNode* root) {
		if (root == NULL) return 0;
		int left = depth(root->left);
		int right = depth(root->right);
		return max(left, right) + 1;
	}

	bool isBalanced(TreeNode* root) {
		if (root == NULL) return true;
		if (abs(depth(root->left) - depth(root->right)) > 1) return false; 
		else return isBalanced(root->left) && isBalanced(root->right);
	}
};

// 111. Minimum Depth of Binary Tree
class Solution24 {
public:

	int depth(TreeNode* root) {
		if (root->left == NULL && root->right == NULL) return 1;
		int left = INT_MAX;
		if (root->left != NULL) left = minDepth(root->left);
		int right = INT_MAX;
		if (root->right != NULL) right = minDepth(root->right);
		return min(left, right) + 1;
	}

	int minDepth(TreeNode* root) {
		if (root == NULL) return 0;
		else return depth(root);
	}
};

// 112. Path Sum
class Solution25 {
public:
	bool hasPathSum(TreeNode* root, int sum) {
		if (root == NULL) return false;
		if (root->left == NULL && root->right == NULL) return sum == root->val;
		return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
	}
};

// 168. Excel Sheet Column Title
class Solution26 {
public:
	string convertToTitle(int n) {
		string a = "";
		int site = 0;

		while (n) {
			site = (n - 1) % 26;
			a += (site + 'A');
			n = (n - 1) / 26;
		}

		string b = "";
		int len = a.size();
		for (int i = 0; i < len; i++)
		{
			b += (a[len - i - 1]);
		}
		return b;
	}
};

// 169. Majority Element
class Solution27 {
public:
	int majorityElement(vector<int>& nums) {
		int len = nums.size();
		int cnt = 1;
		int num = nums[0];

		for (int i = 1; i < len; i++)
		{
			if (nums[i] == num) ++cnt;
			else if (cnt <= 1) {
				cnt = 1;
				num = nums[i];
			}
			else {
				--cnt;
			}
		}
		return num;
	}
};

// 171. Excel Sheet Column Number
class Solution28 {
public:
	int titleToNumber(string s) {
		int len = s.size();
		if (len == 1) return s[0] - 'A' + 1;
		int sum = s[len - 1] - 'A' + 1;
		int cnt = 1;
		for (int i = len - 2; i >= 0; i--,cnt*=26)
		{
			sum += ((s[i] - 'A' + 1) * cnt * 26);
		}
		return sum;
	}
};

// 203. Remove Linked List Elements
class Solution29 {
public:
	ListNode * removeElements(ListNode* head, int val) {
		while (head && head->val == val) {
			head = head->next;
		}
		if (head == NULL) return NULL;

		ListNode* pre = head;
		ListNode* node = head->next;
		while (node) {
			if (node->val == val) {
				pre->next = pre->next->next;
				ListNode* t = node;
				node = node->next;
				free(t);
			} else { 
				node = node->next; 
				pre = pre->next;
			}
		}
		return head;
	}
};

// 219. Contains Duplicate II
class Solution30 {
public:
	bool containsNearbyDuplicate(vector<int>& nums, int k) {
		unordered_map<int, int> mp;
		int len = nums.size();
		if (len <= 1 || k == 0) return false;

		for (int j = 1; j < k + 1 && j < len; j++) {
			if (nums[j] == nums[0]) return true;
			else {
				mp[nums[j]] = j;
			}
		}

		for (int i = 1; i < len - 1; i++)
		{
			auto site = mp.find(nums[i]);
			if (site != mp.end() && (*site).second != i) {
				return true;
			}
			if (i + k >= len) continue;
			else {
				int maxL = i + k;
				if (nums[maxL] == nums[i]) return true;
				else {
					mp[nums[maxL]] = maxL;
				}
			}
		}
		return false;
	}
};

// 225. Implement Stack using Queues
class MyStack {
public:
	queue<int> q1, q2;
	int ptr = 0;

	/** Initialize your data structure here. */
	MyStack() {
		ptr = 0;
	}

	/** Push element x onto stack. */
	void push(int x) {
		if (ptr == 0) {
			while(!q1.empty()) {
				int t = q1.front();
				q2.push(t);
				q1.pop();
			}
			q1.push(x);
		}
		else {
			while (!q2.empty()) {
				int t = q2.front();
				q1.push(t);
				q2.pop();
			}
			q2.push(x);
		}
	}

	/** Removes the element on top of the stack and returns that element. */
	int pop() {
		if (ptr == 0) {
			if (!q1.empty()) {
				int t = q1.front();
				q1.pop();
				return t;
			}
			else {
				while (q2.size() > 1) {
					int t = q2.front();
					q1.push(t);
					q2.pop();
				}
				int t = q2.front();
				q2.pop();
				ptr = 1;
				return t;
			}
		}
		else {
			if (!q2.empty()) {
				int t = q2.front();
				q2.pop();
				return t;
			}
			else {
				while (q1.size() > 1) {
					int t = q1.front();
					q2.push(t);
					q1.pop();
				}
				int t = q1.front();
				q1.pop();
				ptr = 0;
				return t;
			}
		}
	}

	/** Get the top element. */
	int top() {
		if (ptr == 0) {
			if (q1.empty()) {
				while (q2.size() > 1) {
					int t = q2.front();
					q2.pop();
					q1.push(t);
				}
				int t = q2.front();
				q1.push(t);
				q2.pop();
				ptr = 1;
				return t;
			}
			return q1.front();
		}
		else {
			if (q2.empty()) {
				while (q1.size() > 1) {
					int t = q1.front();
					q1.pop();
					q2.push(t);
				}
				int t = q1.front();
				q2.push(t);
				q1.pop();
				ptr = 0;
				return t;
			}
			return q2.front();
		}
	}

	/** Returns whether the stack is empty. */
	bool empty() {
		return q1.empty() && q2.empty();
	}
};

// 226. Invert Binary Tree
class Solution31 {
public:
	TreeNode * invertTree(TreeNode* root) {
		if (root == NULL) return root;
		TreeNode* left = invertTree(root->left);
		TreeNode* right = invertTree(root->right);

		root->left = right;
		root->right = left;
		
		return root;
	}
};

// 231. Power of Two
class Solution32 {
public:
	bool isPowerOfTwo(int n) {
		if (n == 0) return false;
		else if (n == 1) return true;
		else if (n == 2) return true;

		if (n & 1 == 1) return false;
		long long k = 2;
		for (int i = 0; i < 40; i++)
		{
			k = (k << 1);
			if (k == n) return true;
			if (k > n) return false;
		}
		return false;
	}
};

// 232. Implement Queue using Stacks
class MyQueue {
public:
	stack<int> a, b;

	/** Initialize your data structure here. */
	MyQueue() {

	}

	/** Push element x to the back of queue. */
	void push(int x) {
		if (b.empty()) {
			a.push(x);
		}
		else {
			while (!b.empty()) {
				int t = b.top();
				b.pop();
				a.push(t);
			}
			a.push(x);
		}
	}

	/** Removes the element from in front of queue and returns that element. */
	int pop() {
		if (!a.empty()) {
			while (!a.empty()) {
				int t = a.top();
				a.pop();
				b.push(t);
			}
		}
		int t = b.top();
		b.pop();
		return t;
	}

	/** Get the front element. */
	int peek() {
		if (!a.empty()) {
			while (!a.empty()) {
				int t = a.top();
				a.pop();
				b.push(t);
			}
		}
		return b.top();
	}

	/** Returns whether the queue is empty. */
	bool empty() {
		return a.empty() && b.empty();
	}
};

// 235. Lowest Common Ancestor of a Binary Search Tree
class Solution33 {
public:
	TreeNode * lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root->val == p->val) return p;
		else if (root->val == q->val) return q;
		else if (max(p->val, q->val) > root->val && min(p->val, q->val) < root->val) {
			return root;
		}
		if (p->val > root->val) return lowestCommonAncestor(root->right, p, q);
		else return lowestCommonAncestor(root->left, p, q);
	}
};

// 257. Binary Tree Paths
class Solution34 {
public:
	vector<string> vec;

	void getCurrentPath(TreeNode* root, string s) {
		s += ("->" + to_string(root->val));
		if (root->left == NULL) {
			if (root->right != NULL) {
				getCurrentPath(root->right, s);
			}
			else {
				vec.push_back(s);
			}
		}
		else {
			getCurrentPath(root->left, s);
			if (root->right != NULL) {
				getCurrentPath(root->right, s);
			}
		}
		return;
	}

	vector<string> binaryTreePaths(TreeNode* root) {
		if (root == NULL) return vec;
		string s = ("" + to_string(root->val));
		if (root->left == NULL) {
			if (root->right != NULL) {
				getCurrentPath(root->right, s);
			}
			else {
				vec.push_back(s);
			}
		}
		else {
			getCurrentPath(root->left, s);
			if (root->right != NULL) {
				getCurrentPath(root->right, s);
			}
		}
		return vec;
	}
};

// 263. Ugly Number
class Solution35 {
public:
	bool isUgly(int num) {
		long n = num;

		if (n == 1) return true;
		else if (n == 0) return false;
		else if (n < 0) return false;

		while (n > 1) {
			if (n % 5 == 0) n /= 5;
			else if (n % 3 == 0) n /= 3;
			else if ((n & 1) == 0) n /= 2;
			else return false;
		}
		return true;
	}
};

// 290. Word Pattern
class Solution36 {
public:
	vector<string> vec;

	void getStringFromStr(string s) {
		int len = s.size();
		int k = 0;
		for (int i = 0; i < len; i++)
		{
			if (s[i] != ' ') {
				k = i;
				break;
			}
		}
		string t = "";
		for (int i = k; i < len; i++)
		{
			if (s[i] != ' ') {
				t += s[i];
			}
			else if(t != "") {
				vec.push_back(t);
				t = "";
			}
		}
		if (t != "") {
			vec.push_back(t);
			t = "";
		}
	}

	bool wordPattern(string pattern, string str) {
		if (pattern == "" || str == "") return false;
		unordered_map<string, char> mp;
		unordered_set<char> st;

		getStringFromStr(str);
		if (vec.size() != pattern.size()) return false;

		int len = vec.size();
		int k = 0;
		for (int i = 0; i < len; i++)
		{
			if (mp.find(vec[i]) != mp.end()) {
				if (mp[vec[i]] != pattern[k]) return false;
			}
			else {
				if (st.find(pattern[k]) != st.end()) {
					return false;
				}
				st.insert(pattern[k]);
				mp[vec[i]] = pattern[k];
			}
			++k;
		}
		return true;
	}
};

// 292. Nim Game
class Solution37 {
public:
	bool canWinNim(int n) {
		return n % 4;
	}
};

// 303. Range Sum Query - Immutable
class NumArray {
public:
	vector<int> nums;
	int nl[10050] = { 0 };

	NumArray(vector<int> nums) {
		this->nums = nums;
		int len = nums.size();
		int sum = 0;
		for (int i = 0; i < len; i++)
		{
			sum += nums[i];
			nl[i] = sum;
		}
	}

	int sumRange(int i, int j) {
		return nl[j] - nl[i] + nums[i];
	}
};

// 345. Reverse Vowels of a String
class Solution38 {
public:
	string reverseVowels(string s) {
		if (s.size() == 0) return s;
		unordered_set<char> vowels = { 'a','e','i','o','u','A','E','I','O','U' };
		int p = 0, q = s.size() - 1;
		int len = s.size();

		do {
			for (int i = p; i < q; i++)
			{
				if (vowels.find(s[i]) != vowels.end()) {
					p = i;
					break;
				}
			}
			for (int i = q; i > p; i--)
			{
				if (vowels.find(s[i]) != vowels.end()) {
					q = i;
					break;
				}
			}
			if (vowels.find(s[p]) == vowels.end() || vowels.find(s[q]) == vowels.end()) break;
			swap(s[p], s[q]);
			++p;
			--q;
		} while (p < q);
		return s;
	}
};

// 349. Intersection of Two Arrays
class Solution39 {
public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		unordered_set<int> st;
		int len1 = nums1.size(), len2 = nums2.size();
		vector<int> res;
		for (int i = 0; i < len1; i++)
		{
			if (st.find(nums1[i]) == st.end()) {
				st.insert(nums1[i]);
			}
		}

		for (int i = 0; i < len2; i++)
		{
			if (st.find(nums2[i]) != st.end()) {
				res.push_back(nums2[i]);
				st.erase(nums2[i]);
			}
		}
		return res;
	}
};

// 350. Intersection of Two Arrays II
class Solution40 {
public:
	vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
		unordered_map<int, int> mp;	// key: num, value: times appear
		int len1 = nums1.size(), len2 = nums2.size();
		vector<int> res;
		if (len1 == 0 || len2 == 0) return res;
		for (int i = 0; i < len1; i++)
		{
			if (mp.find(nums1[i]) == mp.end()) {
				mp[nums1[i]] = 1;
			}
			else {
				mp[nums1[i]]++;
			}
		}

		for (int i = 0; i < len2; i++)
		{
			if (mp.find(nums2[i]) == mp.end()) continue;
			mp[nums2[i]]--;
			res.push_back(nums2[i]);
			if (mp[nums2[i]] == 0) {
				mp.erase(nums2[i]);
			}
		}
		return res;
	}
};

// 371. Sum of Two Integers
class Solution41 {
public:
	int getSum(int a, int b) {
		while (b)
		{
			int c = a ^ b;
			b = (a & b) << 1;
			a = c;
		}
		return a;
	}
};