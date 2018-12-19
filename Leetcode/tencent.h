#pragma once
#include "stdafx.h"

// 4. Median of Two Sorted Arrays
class Solution01 {
public:
	double getMid(int pre, int now, int sum) {
		if ((sum & 1) == 0) return ((double)pre + now) / 2;
		return now;
	}

	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int len1 = nums1.size(), len2 = nums2.size();
		int sum = len1 + len2;
		int mid = sum / 2;
		int pre = 0, now = 0;
		int p = 0, q = 0;
		int i = 0;

		if (len1 != 0 && len2 != 0) {
			if (nums1[p] < nums2[q]) {
				pre = nums1[p++];
			}
			else {
				pre = nums2[q++];
			}
		}
		else {
			len1 == 0 ? pre = nums2[q++] : pre = nums1[p++];
		}
		now = pre;

		while (p < len1 && q < len2) {
			pre = now;
			nums1[p] < nums2[q] ? now = nums1[p++] : now = nums2[q++];
			if ((++i) == mid) return getMid(pre, now, sum);
		}

		while (p < len1) {
			pre = now;
			now = nums1[p++];
			if ((++i) == mid) return getMid(pre, now, sum);
		}

		while (q < len2) {
			pre = now;
			now = nums2[q++];
			if ((++i) == mid) return getMid(pre, now, sum);
		}

		return getMid(pre, now, sum);
	}
};

// 11
class Solution {
public:
	int getP(int h1, int h2, int i, int j) {
		return abs(min(h1, h2) * (j - i));
	}

	int maxArea(vector<int>& height) {
		set<int> ss;
		int len = height.size();
		int max = 0;

		for (int i = 0; i < len - 1; i++)
		{
			int tmax = -1;
			if (ss.find(i) != ss.end() || height[i] * (len - i - 1) < max) continue;
			int p = i + 1;
			for (int j = p + 1; j < len; j++)
			{
				if (height[j] > height[p]) {
					p = j;
				}
				else {
					if (getP(height[j], height[i], j, i) >=  getP(height[p], height[i], p, i)) {
						p = j;
					}
				}
			}
			tmax = getP(height[p], height[i], p, i);
			if (tmax > max) max = tmax;
			int temp = i;
			while (i < len - 1 && height[i + 1] < height[temp]) {
				ss.insert(++i);
			}
		}
		return max;
	}
};