#pragma once
#include "stdafx.h"

// 414. Third Maximum Number
class Solution {
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