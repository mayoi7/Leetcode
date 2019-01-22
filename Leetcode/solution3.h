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
class Solution {
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