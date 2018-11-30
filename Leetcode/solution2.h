#pragma once
#include "stdafx.h"


// 413. Arithmetic Slices
class Solution01 {
public:
	int getNum(int n) {
		return (n - 2)*(n - 1) / 2;
	}

	// 没理解题意一开始写复杂了，整体逻辑架构也没来及改
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
class Solution {
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
