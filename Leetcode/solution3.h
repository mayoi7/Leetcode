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