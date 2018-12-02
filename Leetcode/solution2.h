#pragma once
#include "stdafx.h"


// 413. Arithmetic Slices
class Solution01 {
public:
	int getNum(int n) {
		return (n - 2)*(n - 1) / 2;
	}

	// û�������һ��ʼд�����ˣ������߼��ܹ�Ҳû������
	int numberOfArithmeticSlices(vector<int>& A) {
		int cnt = 0;
		int len = A.size();
		unordered_map<int, unordered_set<int>> mp;

		int sl = 2, rm = 0, last = 0;
		for (int i = 0; i < len - 2; i++)
		{
			int j = i + 1;
			rm = A[j] - A[i];
			if (mp.find(rm) != mp.end()) {
				unordered_set<int> st = mp[rm];
				if (st.find(i) != st.end() || st.find(j) != st.end()) continue;
			}

			unordered_set<int> st;
			st.insert(i);
			st.insert(j);

			sl = 2;
			last = A[j];
			for (int k = j + 1; k < len; k++)
			{
				if ((A[k] - last) == rm) {
					st.insert(k);
					++sl;
					last = A[k];
				}
				else break;
			}
			if (sl >= 3) {
				cnt += getNum(sl);
				if (mp.find(rm) == mp.end()) {
					mp[rm] = st;
				}
				else {
					mp[rm].insert(st.begin(), st.end());
				}
			}
		}
		return cnt;
	}
};

// 414. Third Maximum Number
class Solution02 {
public:
	int thirdMax(vector<int>& nums) {
		int a[4] = { INT_MIN, INT_MIN, INT_MIN, INT_MIN };
		int len = nums.size();
		int f = 0;
		if (len == 0) return -INFINITY;
		else if (len == 1) nums[0];
		for (int i = 0; i < len; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (nums[i] == a[j]) break;
				else if (nums[i] > a[j]) {
					++f;
					for (int k = 3; k >= j + 1; k--) {
						a[k] = a[k - 1];
					}
					a[j] = nums[i];
					break;
				}
			}
		}
		if (f < 3) return a[0];
		return a[2];
	}
};

// 415. Add Strings
class Solution03 {
public:
	string addStrings(string num1, string num2) {
		if (num1 == "") return num2;
		else if (num2 == "") return num1;

		int len1 = num1.size(), len2 = num2.size();
		int i = len1 - 1, j = len2 - 1;
		int c = 0;
		stack<char> stk;
		string res = "";
		int sum = 0;
		while (i >= 0 && j >= 0) {
			sum = (num1[i--] - '0' + num2[j--] - '0' + c);
			c = sum / 10;
			sum %= 10;
			stk.push(sum + '0');
		}
		while (i >= 0) {
			sum = (num1[i--] - '0' + c);
			c = sum / 10;
			sum %= 10;
			stk.push(sum + '0');
		}
		while (j >= 0) {
			sum = (num2[j--] - '0' + c);
			c = sum / 10;
			sum %= 10;
			stk.push(sum + '0');
		}
		if (c > 0) {
			stk.push(c + '0');
		}
		while (!stk.empty()) {
			res += stk.top();
			stk.pop();
		}
		return res;
	}
};

// 429. N-ary Tree Level Order Traversal
//class Solution04 {
//public:
//	vector<vector<int>> levelOrder(Node* root) {
//		vector<vector<int>> res;
//		if (root == NULL) return res;
//		queue<Node*> que;
//		que.push(root);
//		while (!que.empty()) {
//			Node* last = que.back();
//			vector<int> temp;
//			Node* tNode = que.front();
//
//			while (tNode != last) {	// traverse one level
//				vector<Node*> nodes = tNode->children;
//				for (auto i = nodes.begin(); i != nodes.end(); i++)
//				{
//					que.push(*i);
//				}
//				temp.push_back(tNode->val);
//				que.pop();
//				tNode = que.front();
//			}
//			vector<Node*> nodes = tNode->children;
//			for (auto i = nodes.begin(); i != nodes.end(); i++)
//			{
//				que.push(*i);
//			}
//			temp.push_back(tNode->val);
//			que.pop();
//
//			res.push_back(temp);
//		}
//		return res;
//	}
//};

// 437. Path Sum III
class Solution05 {
public:
	int pathSum(TreeNode* root, int sum) {
		if (!root) return 0;
		return sumUp(root, 0, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
	}

	int sumUp(TreeNode* root, int pre, int& sum) {
		if (!root) return 0;
		int current = pre + root->val;
		return (current == sum) + sumUp(root->left, current, sum) + sumUp(root->right, current, sum);
	}
};

// 438. Find All Anagrams in a String
class Solution06 {
public:
	vector<int> findAnagrams(string s, string p) {
		if (s.empty()) return {};
		vector<int> res, m(256, 0);
		int left = 0, right = 0, cnt = p.size(), n = s.size();
		for (char c : p) ++m[c];
		while (right < n) {
			if (m[s[right++]]-- >= 1) --cnt;
			if (cnt == 0) res.push_back(left);
			if (right - left == p.size() && m[s[left++]]++ >= 0) ++cnt;
		}
		return res;
	}
};

// 441. Arranging Coins
class Solution07 {
public:
	int arrangeCoins(int n) {
		long long t = n;
		long a = (long long)sqrt(8 * t + 1);
		return (a - 1) / 2;
	}
};

// 442. Find All Duplicates in an Array
class Solution08 {
public:
	vector<int> findDuplicates(vector<int>& nums) {
		vector<int> ans;
		for (auto p : nums)
		{
			if (nums[abs(p) - 1] < 0)
				ans.push_back(abs(p));
			nums[abs(p) - 1] = 0 - nums[abs(p) - 1];
		}
		return ans;
	}
};

// 443. String Compression
class Solution {
public:

	int compress(vector<char>& chars) {
		int tc = 1, index = 0;
		int len = chars.size();
		chars.push_back('-');
		for (int i = 1; i <= len; i++)
		{
			if (chars[i] == chars[i - 1]) ++tc;
			else {
				chars[index++] = chars[i - 1];
				if (tc >= 10) {
					string st = to_string(tc);
					for (int j = 0; j < st.size(); j++)
						chars[index++] = st[j];
				}
				else if (tc > 1) chars[index++] = tc + '0';
				tc = 1;
			}
		}
		chars.pop_back();
		return index;
	}
};