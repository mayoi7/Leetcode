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
class Solution17 {
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

// 438. Find All Anagrams in a String
class Solution18 {
public:
	bool ifSame(int* a, int* b) {
		for (int i = 'a'; i <= 'z'; i++)
		{
			if (a[i] != b[i]) return false;
		}
		return true;
	}

	vector<int> findAnagrams(string s, string p) {
		int n1 = s.size(), n2 = p.size();
		vector<int> res;
		if (n2 > n1) return res;

		int ch[255];
		memset(ch, 0, sizeof(ch));

		for (int i = 0; i < n2; i++)
		{
			ch[p[i]]++;
		}
		int cp[255];
		memset(cp, 0, sizeof(ch));

		for (int i = 0; i < n2; i++)
		{
			cp[s[i]]++;
		}
		
		for (int i = n2; i < n1; i++)
		{
			if (ifSame(ch, cp)) {
				res.push_back(i - n2);
			}
			--cp[s[i - n2]];
			++cp[s[i]];
		}
		if (ifSame(ch, cp)) {
			res.push_back(n1 - n2);
		}
		return res;
	}
};

// 441. Arranging Coins
class Solution19 {
public:
	int arrangeCoins(int n) {
		return sqrt((long long)2 * n + 0.25) - 0.5;
	}
};

// 287. Find the Duplicate Number
class Solution20 {
public:
	int findDuplicate(vector<int>& nums) {
		int slow = 0, fast = 0, tar = 0;

		do {
			slow = nums[slow];
			fast = nums[nums[fast]];
		} while (slow != fast);

		while (tar != slow) {
			slow = nums[slow];
			tar = nums[tar];
		}
		return tar;
	}
};

// 459. Repeated Substring Pattern
class Solution21 {
public:
	bool testIfCan(string s, int t, int times) {
		int j = 0, p = 0;

		for (int i = 0; times - i > 1; i++)
		{
			p += t;
			for (int j = 0; j < t; j++)
			{
				if (s[j] != s[p + j]) {
					return false;
				}
			}
		}
		return true;
	}

	bool repeatedSubstringPattern(string s) {
		int n = s.size();
		int len = n / 2;

		while (len > 1) {
			if (n % len == 0) {
				if (testIfCan(s, len, n / len)) return true;
			}
			--len;
		}
		for (int i = 1; i < n; i++)
		{
			if (s[i] != s[i - 1]) return false;
		}
		return true;
	}
};

// 557. Reverse Words in a String III
class Solution22 {
public:
	void reversePartition(string& s, int i, int j) {
		int m = (i + j) / 2;
		char ch;

		for (int k = i; k <= m; k++)
		{
			swap(s[k], s[j - k + i]);
		}
	}

	string reverseWords(string s) {
		int n = s.size();
		if (n <= 1) return s;
		string t(s);
		int p = 0;

		for (int i = 0; i < n; i++)
		{
			if (t[i] == ' ') {
				reversePartition(t, p, i - 1);
				p = i + 1;
			}
		}
		if (s[n - 1] != ' ') reversePartition(t, p, n - 1);
		return t;
	}
};

// 476. Number Complement
class Solution23 {
public:
	int findComplement(int num) {
		long r = 1;
		do {
			if (r > num) return r - num - 1;
			r <<= 1;
		} while (true);
	}
};

// 482. License Key Formatting
class Solution24 {
public:
	string licenseKeyFormatting(string S, int K) {
		int size = S.size();
		string s(S);
		int len = 0;
		transform(S.begin(), S.end(), S.begin(), ::toupper);
		for (int i = 0; i < size; i++)
		{
			if (S[i] == '-') continue;
			s[len++] = S[i];
		}
		int fst = len % K;
		if (fst == 0) fst = K;

		string res = "";
		int p = 0;

		for (int i = 0; i < fst && i < len; i++)
		{
			res += s[p++];
		}

		while(p < len)
		{
			res += '-';
			for (int j = 0; j < K; j++)
			{
				res += s[p++];
			}
		}
		return res;
	}
};

// 485. Max Consecutive Ones
class Solution25 {
public:
	int findMaxConsecutiveOnes(vector<int>& nums) {
		int crt = 0, mx = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] == 1) ++crt;
			else {
				if (crt - mx > 0) mx = crt;
				crt = 0;
			}
		}
		if (crt - mx > 0) mx = crt;
		return mx;
	}
};

// 492. Construct the Rectangle
class Solution26 {
public:
	vector<int> constructRectangle(int area) {
		int p = 1, q = area;
		vector<int> res = { p, q };
		while (p <= q) {
			if (p * q == area) {
				res[0] = q;
				res[1] = p;
			}
			p++;
			q = (area / p);
		}
		return res;
	}
};

// 279. Perfect Squares
class Solution27 {
public:
	int a[2050] = { 0 };
	int b[20000] = { 0,1,2,3,1 };

	int getSquares(int n) {
		if (b[n] != 0) return b[n];

		int sq = sqrt(n);
		if (a[sq] == n) return 1;
		int num = 0;
		int crt = 0, mn = n;
		for (int i = sq; i > 0; i--)
		{
			crt = getSquares(n - a[i]);
			if (crt < mn) mn = crt;
		}
		b[n] = crt + 1;
		return mn + 1;
	}

	int numSquares(int n) {
		int sq = sqrt(n);
		if (sq * sq == n) return 1;

		for (int i = 1; i <= sq; i++)
		{
			a[i] = i * i;
		}
		memset(b, 0, sizeof(b));
		return getSquares(n);
	}
};

// 496. Next Greater Element I
class Solution28 {
public:
	vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
		int len1 = findNums.size(), len2 = nums.size();
		if (len2 == 1) return { -1 };
		else if (len2 == 0) return {};
		if (len1 == 0) return {};

		vector<int> res;
		vector<int> a(nums);

		unordered_map<int, int> mp;

		for (int i = 0; i < len2; i++)
		{
			a[i] = i;
			auto key = find(findNums.begin(), findNums.end(), nums[i]);
			if (key != findNums.end()) {
				// 找到元素
				mp[*key] = i;
			}
		}

		int p = -1;
		for (int i = len2 - 2; i >= 0; i--)
		{
			if (nums[i] < nums[i + 1]) {
				a[i] = i + 1;
			} else {
				p = i + 1;
				while (p != a[p]) {
					if (nums[i] < nums[a[p]]) {
						a[i] = a[p];
						break;
					}
					p = a[p];

					if (p < len2 - 1);
					else if (p >= len2) break;
					else {
						if (nums[i] < nums[len2 - 1]) {
							a[i] = len2 - 1;
						} else {
							break;
						}
					}
				}
			}
		}
		int site = 0;
		for (int i = 0; i < len1; i++)
		{
			site = mp[findNums[i]];
			if (a[site] == site) res.push_back(-1);
			else res.push_back(nums[a[site]]);
		}

		return res;
	}
};

// 504. Base 7
class Solution29 {
public:
	string convertToBase7(int num) {
		string res = "";

		bool flag = false;
		if (num < 0) {
			flag = true;
			num = -num;
		}
		if (num < 7) {
			res += to_string(num);
			if (flag) res = "-" + res;
			return res;
		}

		int rem = 0;
		while (num) {
			res.insert(res.begin(), (num % 7) + '0');
			num /= 7;
		}
		if (flag) res = "-" + res;
		return res;
	}
};

// 506. Relative Ranks
class Solution30 {
public:
	vector<string> findRelativeRanks(vector<int>& nums) {
		priority_queue<int> pri;
		unordered_map<int, int> mp;
		vector<string> res(nums.size());
		for (int i = 0; i < nums.size(); i++)
		{
			mp[nums[i]] = i;
			pri.push(nums[i]);
		}
		int rank = 1;
		while (!pri.empty()) {
			if (rank == 1) res[mp[pri.top()]] = "Gold Medal";
			else if(rank == 2) res[mp[pri.top()]] = "Silver Medal";
			else if (rank == 3) res[mp[pri.top()]] = "Bronze Medal";
			else res[mp[pri.top()]] = to_string(rank);
			++rank;
			pri.pop();
		}
		return res;
	}
};

// 507. Perfect Number
class Solution31 {
public:
	bool checkPerfectNumber(int num) {
		int i = 2;
		long sum = 1;
		int lim = num / 2 + 1;
		int mx = num / 2;
		int k = 0;
		for (int i = 2; i < lim; i++)
		{
			if (i == mx) break;
			if (num % i == 0) {
				k = num / i;
				if (k - i > 0) mx = k;
				sum += (i + k); 
				if (sum > num) return false;
			}
			
		}

		return sum == num;
	}
};

// 728. Self Dividing Numbers
class Solution32 {
public:
	bool checkIf(int num) {
		int n = num;
		int k = 0;
		while (n) {
			k = n % 10;
			if (k == 0) return false;
			if (num % k != 0) return false;
			n /= 10;
		}
		return true;
	}

	vector<int> selfDividingNumbers(int left, int right) {
		vector<int> res;
		for (int i = left; i < right; i++)
		{
			if (checkIf(i)) {
				res.push_back(i);
			}
		}
		return res;
	}
};

// 397. Integer Replacement
class Solution33 {
public:
	unordered_map<int, int> mp;

	int getNum(int n) {
		if (n == 1) return 0;
		if (mp.find(n) != mp.end()) {
			return mp[n];
		}
		else {
			int res = 0;
			if ((n & 1) == 1) {
				// odd
				res = min(getNum(n - 1), getNum(n + 1)) + 1;
				mp[n] = res;
			} else {
				res = getNum(n / 2) + 1;
				mp[n] = res;
			}
			return res;
		}
	}

	int integerReplacement(int n) {
		if (n == 2147483647) {
			return 32;
		}
		return getNum(n);
	}
};

// 520. Detect Capital
class Solution34 {
public:
	bool detectCapitalUse(string word) {
		int len = word.size();
		if (len < 2) return true;
		if (word[0] >= 'a') {
			for (int i = 1; i < len; i++)
			{
				if (word[i] <= 'Z') return false;
			}
			return true;
		} else if (word[1] <= 'Z') {
			for (int i = 2; i < len; i++)
			{
				if (word[i] >= 'a') return false;
			}
			return true;
		} else if (word[0] <= 'Z') {
			for (int i = 2; i < len; i++)
			{
				if (word[i] <= 'Z') return false;
			}
			return true;
		}
		return false;
	}
};

// 541. Reverse String II
class Solution35 {
public:
	void reverseStr(string& s, int i, int j) {
		while (i < j) {
			swap(s[i], s[j]);
			i++;
			j--;
		}
	}

	string reverseStr(string s, int k) {
		int m = 2 * k;
		int len = s.size();
		int t1 = len / m;
		int t2 = len % m;
		for (int i = 0; i < t1; i++)
		{
			reverseStr(s, i*m, i*m + k - 1);
		}
		if (t2 >= k) {
			reverseStr(s, len - t2, len - t2 + k - 1);
		}
		else {
			reverseStr(s, len - t2, len - 1);
		}
		return s;
	}
};

// 893. Groups of Special-Equivalent Strings
class Solution36 {
public:
	int numSpecialEquivGroups(vector<string>& A) {
		unordered_map<string, int> mp;
		for (auto s : A) {
			string even = "", odd = "";
			for (int i = 0; i < s.size(); i += 2)
			{
				even.push_back(s[i]);
			}
			for (int i = 1; i < s.size(); i += 2)
			{
				odd.push_back(s[i]);
			}
			sort(even.begin(), even.end());
			sort(odd.begin(), odd.end());
			mp[even + odd]++;
		}
		return mp.size();
	}
};

// 522. Longest Uncommon Subsequence II
class Solution37 {
public:
	struct cmp {
		bool operator()(const string x,const string y) {
			return x.size() < y.size();
		}
	};

	bool validIf(string a, string b) {
		int l1 = a.size(), l2 = b.size();
		int p = 0, q = 0;
		while (p < l1 && q < l2) {
			if (b[q] == a[p++]) {
				++q;
			}
		}
		return q < l2;
	}

	int findLUSlength(vector<string>& strs) {
		int len = strs.size();
		if (len == 1) return strs[0].size();
		priority_queue<string, vector<string>, cmp> pq;
		unordered_map<string, int> mp;
		for (int i = 0; i < len; i++)
		{
			pq.push(strs[i]);
			if(mp.find(strs[i]) == mp.end()) mp[strs[i]] = 1;
			else mp[strs[i]]++;
		}
		string s = pq.top();
		pq.pop();
		if (mp[s] == 1) return s.size();
		while (!pq.empty()) {
			string t(pq.top());
			pq.pop();
			if (t.size() == s.size()) {
				if (mp[t] == 1) return s.size();
			}
			else if (t.size() < s.size()) {
				if (validIf(s, t) && (pq.empty() || mp[t] == 1)) {
					return t.size();
				}
				s = t;
			}
		}
		return -1;
	}
};

// 1137
class Solution38 {
public:
	vector<vector<string>> res;

	bool valid(string s, int i, int j) {
		while (i < j) {
			if (s[i--] != s[j--]) {
				return false;
			}
		}
		return true;
	}

	void once(string s, int idx, vector<string>& a) {
		int len = s.size();

		if (idx == len) {
			res.emplace_back(vector<string>(a));
			return;
		}
		string t;
		for (int i = idx; i < len; i++)
		{
			if (valid(s, idx, i)) {
				a.emplace_back(s.substr(idx, i - idx + 1));
				once(s, i + 1, a);
				a.pop_back();
			}
		}
	}

	vector<vector<string>> partition(string s) {
		vector<string> t;
		once(s, 0, t);
		return res;
	}
};

// 530. Minimum Absolute Difference in BST
class Solution39 {
public:
	vector<int> res;

	void putVal(TreeNode* node) {
		if (node->left != nullptr) putVal(node->left);
		res.emplace_back(node->val);
		if (node->right != nullptr) putVal(node->right);
	}

	int getMinimumDifference(TreeNode* root) {
		int min = INT_MAX;
		putVal(root);
		int len = res.size();
		for (int i = 1; i < len; i++)
		{
			if (min > res[i] - res[i - 1]) {
				min = res[i] - res[i - 1];
			}
			if (min == 1) return min;
		}
		return min;
	}
};

// 532. K-diff Pairs in an Array
class Solution40 {
public:
	int findPairs(vector<int>& nums, int k) {
		if (k < 0) return 0;
		map<int, int> mp;	// <num, times>

		for (auto i = nums.begin(); i != nums.end(); i++)
		{
			if (mp.find(*i) != mp.end()) {
				mp[*i]++;
			}
			else mp[*i] = 1;
		}
		int ans = 0;

		if (k == 0) {
			for (auto i = mp.begin(); i != mp.end(); i++)
			{
				if (i->second >= 2) ++ans;
			}
			return ans;
		}

		for (auto i = mp.begin(); i != mp.end(); i++)
		{
			if (mp.find(i->first + k) != mp.end()) {
				// exist
				++ans;
			}
		}
		return ans;
	}
};

// 561. Array Partition I
class Solution {
public:
	int arrayPairSum(vector<int>& nums) {
		priority_queue<int> qe;
		
		for (int i : nums) {
			qe.push(i);
		}

		int max = 0;

		while (!qe.empty()) {
			qe.pop();
			max += qe.top();
			qe.pop();
		}
		return max;
	}
};