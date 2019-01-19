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
class Solution02 {
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

// 23
class Solution03 {
public:
	ListNode * mergeTwoLists(ListNode* l1, ListNode* l2) {
		ListNode* a = new ListNode(0);
		ListNode* head = a;
		while (l1 && l2)
		{
			if (l1->val < l2->val) {
				a->next = l1;
				l1 = l1->next;
			}
			else
			{
				a->next = l2;
				l2 = l2->next;
			}
			a = a->next;
		}
		if (l1) {
			a->next = l1;
		}
		else
		{
			a->next = l2;
		}
		return head->next;
	}

	ListNode* mergeKLists(vector<ListNode*>& lists) {
		int len = lists.size();
		if (len == 0) return nullptr;
		else if (len == 1) return lists[0];
		else if (len == 2) return mergeTwoLists(lists[0], lists[1]);

		vector<ListNode*> vec;
		int i = 0;
		if ((len & 1) != 0) {
			vec.push_back(lists[i++]);
		}

		for (; i < len; i += 2) {
			vec.push_back(mergeTwoLists(lists[i], lists[i + 1]));
		}

		return mergeKLists(vec);
	}
};

// 54. Spiral Matrix
class Solution {
public:
	void addEdgeElemInCircle(vector<int>& a, vector<vector<int>>& b, int si, int sj, int ei ,int ej) {
		if (si == ei) {
			for (int i = sj; i <= ej; i++)
			{
				a.push_back(b[si][i]);
			}
			return;
		}
		if (sj == ej) {
			for (int i = si; i <= ei; i++)
			{
				a.push_back(b[i][sj]);
			}
			return;
		}

		for (int i = sj; i < ej; i++)
		{
			a.push_back(b[si][i]);
		}
		for (int i = si; i < ei; i++)
		{
			a.push_back(b[i][ej]);
		}
		for (int i = ej; i > sj; i--)
		{
			a.push_back(b[ei][i]);
		}
		for (int i = ei; i > si; i--)
		{
			a.push_back(b[i][sj]);
		}
	}

	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		vector<int> res;
		int row = matrix.size();
		if (row == 0) return res;
		int col = matrix[0].size();
		int si = row / 2, sj = col / 2;
		int mm = min(si, sj);
		row--;
		col--;
		if (min(row, col) <= 1) {
			addEdgeElemInCircle(res, matrix, 0, 0, row, col);
			return res;
		}

		for (int i = 0; i <= mm; i++)
		{
			addEdgeElemInCircle(res, matrix, i, i, row - i, col - i);
		}
		return res;
	}
};