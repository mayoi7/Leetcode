#pragma once
#include "stdafx.h"

// 349. Intersection of Two Arraysz
class Solution01 {
public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		vector<int> res;
		unordered_map<int, int> mp;	// <num, count>
		for (auto i = nums1.begin(); i < nums1.end(); i++)
		{
			if (mp.find(*i) == mp.end()) {
				mp[*i] = 1;
			}
		}

		for (auto i = nums2.begin(); i < nums2.end(); i++)
		{
			if (mp.find(*i) == mp.end()) continue;
			res.push_back(*i);
			mp.erase(*i);
		}
		return res;
	}
};

// 80. Remove Duplicates from Sorted Array II
class Solution02 {
public:
	int removeDuplicates(vector<int>& nums) {
		int len = nums.size();
		if (len <= 2) return len;
		bool f = 0;
		int p = 1;
		for (int i = 1; i < len; i++)
		{
			if (nums[i] == nums[i - 1]) {
				if (f) {
					while (i < len && nums[i] == nums[i - 1]) ++i;
					if (i == len) break;
					f = 0;
				}
				else {
					f = 1;
				}
			}
			else f = 0;
			nums[p++] = nums[i];
		}
		return p;
	}
};

// 950. Reveal Cards In Increasing Order
class Solution03 {
public:
	vector<int> deckRevealedIncreasing(vector<int>& deck) {
		int n = deck.size();
		vector<int> vec(n, -7623);
		sort(deck.begin(), deck.end());
		int p = 0;
		int i = 0;
		bool f = 1;
		while (p < n) {
			if (vec[i] == -7623) {
				if (f) {
					vec[i] = deck[p++];
				}
				f = !f;
			}

			i = (i + 1) % n;
		}
		return vec;
	}
};

// 374. Guess Number Higher or Lower
class Solution04 {
public:
	int tar = 12;
	int guess(int num) {
		if (tar == num) return 0;
		else if (tar < num) return -1;
		return 1;
	}

	int guessNumber(int n) {
		int lo = 1, hi = n + 1;
		int mid = 0;
		int f = 0;
		while (true) {
			mid = lo + (hi - lo) / 2;
			f = guess(mid);
			if (f == 0) return mid;
			else if (f == -1) hi = mid;
			else lo = mid + 1;
		}
	}
};

// 375. Guess Number Higher or Lower II
class Solution05 {
public:
	int check(vector<vector<int>>& arr, int p, int q) {
		if (p >= q) return 0;
		if (arr[p][q]) return arr[p][q];

		arr[p][q] = INT_MAX;
		for (int i = p; i <= q; i++)
		{
			int left = check(arr, p, i - 1);
			int right = check(arr, i + 1, q);
			int now = i + max(left, right);
			arr[p][q] = min(arr[p][q], now);
		}
		return arr[p][q];
	}

	int getMoneyAmount(int n) {
		vector<vector<int>> arr(n + 1, vector<int>(n + 1, 0));
		return check(arr, 1, n);
	}
};

// 383. Ransom Note
class Solution06 {
public:
	bool canConstruct(string ransomNote, string magazine) {
		int a[26] = { 0 };
		int n2 = magazine.size(), n1 = ransomNote.size();

		for (int i = 0; i < n2; i++)
		{
			a[magazine[i] - 'a']++;
		}

		for (int i = 0; i < n1; i++)
		{
			if (a[ransomNote[i] - 'a']-- == 0) return false;
		}
		return true;
	}
};

// 401. Binary Watch
class Solution07 {
public:
	int st[10] = { 1,2,4,8,1,2,4,8,16,32 };

	// 通过on数组的亮灯位置来得出一个时间
	string countOn(vector<int> on) {
		int h = 0, m = 0;
		for (int i = 0; i < 4; i++)
		{
			if (on[i]) {	// 如果目标位置灯是亮的
				h += st[i];
			}
		}
		for (int i = 4; i < 10; i++)
		{
			if (on[i]) {
				m += st[i];
			}
		}
		string s = "";
		s += (to_string(h) + ":");
		if (m < 10) s += "0";
		s += to_string(m);
		return s;
	}

	void getProperArray(vector<vector<int>>& vec, int num, int start, vector<int>& cpy) {
		if (start >= 10) {
			vec.push_back(cpy);
			return;
		}
		if (num <= 0) {
			vec.push_back(cpy);
			return;
		}
		if (start + num == 10) {	// 正好够亮，不能不亮的情况
			for (int i = start; i < 10; i++) cpy[i] = 1;

			vec.push_back(cpy);
			return;
		}

		vector<int> arr(cpy);

		// 有亮和不亮两个选择
		cpy[start] = 1;
		getProperArray(vec, num - 1, start + 1, cpy);


		// 选择不亮
		getProperArray(vec, num, start + 1, arr);
	}

	vector<string> readBinaryWatch(int num) {
		vector<string> res;
		if (num < 0 || num > 10) return res;
		vector<vector<int>> vec;
		vector<int> arr(10, 0);

		getProperArray(vec, num, 0, arr);
		for (auto i = vec.begin(); i < vec.end(); i++)
		{
			string s = countOn(*i);
			res.push_back(s);
		}
		return res;
	}
};

// 404. Sum of Left Leaves
class Solution08 {
public:
	int sumOfLeftLeaves(TreeNode* root) {
		if (root == NULL) return 0;
		if (root->left != NULL)
		{
			if (root->left->left == NULL && root->left->right == NULL) return root->left->val + sumOfLeftLeaves(root->right);
			return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
		}
		else return sumOfLeftLeaves(root->right);
	}
};

// 559. Maximum Depth of N-ary Tree
class Node {
public:
	int val;
	vector<Node*> children;

	Node() {}

	Node(int _val, vector<Node*> _children) {
		val = _val;
		children = _children;
	}
};
class Solution09 {
public:
	int maxDepth(Node* root) {
		if (root == NULL) return 0;
		int max = 0;
		int pre = 0;
		for (auto i = root->children.begin(); i < root->children.end(); i++)
		{
			pre = maxDepth(*i);
			if (max < pre) max = pre;
		}
		return max + 1;
	}
};

// 389. Find the Difference
class Solution10 {
public:
	char findTheDifference(string s, string t) {
		int a[26];
		memset(a, 0, sizeof(a));
		int len1 = s.size(), len2 = t.size();
		for (int i = 0; i < len1; i++)
		{
			a[s[i] - 'a']++;
		}
		for (int i = 0; i < len2; i++)
		{
			if (a[t[i] - 'a']-- == 0) return t[i];
		}
		return -1;
	}
};

// 405. Convert a Number to Hexadecimal
class Solution11 {
public:
	char hex[16] = { '0','1','2','3', '4','5', '6','7', '8','9','a','b','c','d','e','f' };
	string toHex(int num) {
		if (num == 0) return "0";
		int n = num;
		if (num < 0) n = -n;
		string s = "";

		if (num > 0) {
			while (n) {
				s.insert(s.begin(), hex[n % 16]);
				n /= 16;
			}
		}
		else {
			n++;
			while (n) {
				s.insert(s.begin(), hex[15 - n % 16]);
				n /= 16;
			}
			int i = s.size();
			for (; i < 8; i++)
			{
				s.insert(s.begin(), 'f');
			}
		}
		return s;
	}
};

// 409. Longest Palindrome
class Solution12 {
public:
	int longestPalindrome(string s) {
		unordered_map<char, int> mp;	// <char, times_appeared>
		for (auto i = s.begin(); i < s.end(); i++)
		{
			if (mp.find(*i) == mp.end()) {
				mp[*i] = 1;
			}
			else mp[*i]++;
		}

		int ml = 0;
		int f = 0;
		for (auto i = mp.begin(); i != mp.end(); i++)
		{
			if ((i->second & 1) == 0) ml += i->second;
			else {
				ml += (i->second - 1);
				f = 1;
			}
		}
		return ml + f;
	}
};

// 414. Third Maximum Number
class Solution13 {
public:
	int thirdMax(vector<int>& nums) {
		priority_queue<int> nq;
		unordered_set<int> st;

		for (auto i = nums.begin(); i < nums.end(); i++)
		{
			st.insert(*i);
		}

		for (auto i = st.begin(); i != st.end(); i++)
		{
			nq.push(*i);
		}

		int mx = nq.top();
		if (nq.size() < 3) return mx;

		nq.pop();
		nq.pop();
		return nq.top();
	}
};

// 415. Add Strings
class Solution14 {
public:
	string addStrings(string num1, string num2) {
		int n1 = num1.size(), n2 = num2.size();
		int c = 0, p = n1 - 1, q = n2 - 1, n = max(n1, n2) - 1;
		string s(n1 > n2 ? num1 : num2);
		int t = 0;

		while (p >= 0 && q >= 0) {
			t = num1[p--] - '0' + num2[q--] - '0' + c ;
			if (t > 9) {
				c = 1;
				t -= 10;
			}
			else c = 0;

			s[n--] = (t + '0');
		}

		while (p >= 0) {
			t = num1[p--] - '0' + c;
			if (t > 9) {
				c = 1;
				t -= 10;
			}
			else c = 0;
			s[n--] = (t + '0');
		}

		while (q >= 0) {
			t = num2[q--] - '0' + c;
			if (t > 9) {
				c = 1;
				t -= 10;
			}
			else c = 0;
			s[n--] = (t + '0');
		}
		
		if (c > 0) s.insert(s.begin(), '1');
		return s;
	}
};

// 429. N-ary Tree Level Order Traversal
class Solution15 {
public:
	vector<vector<int>> levelOrder(Node* root) {
		vector<vector<int>> res;
		queue<Node*> q1, q2;

		if (root == NULL) return res;
		q1.push(root);

		while (!q1.empty()) {
			vector<int> vec, vec2;
			while (!q1.empty()) {
				Node* temp = q1.front();
				vec.push_back(temp->val);
				for (auto i = temp->children.begin(); i < temp->children.end(); i++)
				{
					q2.push(*i);
				}
				q1.pop();
			}
			if (vec.size() == 0) break;
			res.push_back(vec);

			while (!q2.empty()) {
				Node* temp = q2.front();
				vec2.push_back(temp->val);
				for (auto i = temp->children.begin(); i < temp->children.end(); i++)
				{
					q1.push(*i);
				}
				q2.pop();
			}
			if (vec2.size() == 0) break;
			res.push_back(vec2);
		}
		return res;
	}
};

// 437. Path Sum III
class Solution16 {
public:
	int rs = 0;	// real_sum
	unordered_set<TreeNode*> st;
	int pathSum2(TreeNode* root, int sum) {
		if (root == NULL) return 0;
		if (root->val == sum)
			return 1 + pathSum2(root->left, 0) + pathSum2(root->right, 0);
		return pathSum2(root->left, sum - root->val) + pathSum2(root->right, sum - root->val);
	}

	int pathSum3(TreeNode* root) {
		if (root == NULL) return 0;
		return pathSum2(root, rs) + pathSum3(root->left) + pathSum3(root->right);
	}

	int pathSum(TreeNode* root, int sum) {
		rs = sum;
		return pathSum3(root);
	}
};

// 113. Path Sum II
class Solution {
public:
	void addPath(vector<vector<int>>& res, vector<int>& vec, TreeNode* node, int sum) {
		if (node->left == NULL && node->right == NULL) {
			if (sum == node->val) {
				vec.push_back(node->val);
				res.push_back(vec);
			}
			else return;
		}
		vec.push_back(node->val);
		vector<int> oth(vec);
		if (node->left != NULL) {
			addPath(res, vec, node->left, sum - node->val);
		}
		if (node->right != NULL) {
			addPath(res, oth, node->right, sum - node->val);
		}
	}

	vector<vector<int>> pathSum(TreeNode* root, int sum) {
		vector<vector<int>> res;
		vector<int> vec;
		if (root == NULL) return res;
		
		addPath(res, vec, root, sum);
		return res;
	}
};