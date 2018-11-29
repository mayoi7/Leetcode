#pragma once
#include "stdafx.h"


// 413. Arithmetic Slices
class Solution {
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
