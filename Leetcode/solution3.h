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
class Solution {
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