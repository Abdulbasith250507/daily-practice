class Solution {
public:
    string smallestPalindrome(string s, long long k) {
        vector<int> cnt(26, 0);
        for (char c : s) cnt[c - 'a']++;

        int oddChar = -1;
        vector<int> half(26);
        int halfLen = 0;
        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) oddChar = i;   // s is guaranteed palindromic -> at most one
            half[i] = cnt[i] / 2;
            halfLen += half[i];
        }

        const long long CAP = 2000000;  // safely above max k (1e6)

        // # of distinct arrangements of the multiset in arr, capped at CAP
        auto countPerms = [&](vector<int>& arr) -> long long {
            long long result = 1;
            int total = 0;
            for (int c = 0; c < 26; c++) {
                for (int j = 1; j <= arr[c]; j++) {
                    total++;
                    result = result * total / j;   // incremental multinomial coeff
                    if (result > CAP) return CAP + 1;
                }
            }
            return result;
        };

        if (k > countPerms(half)) return "";

        string firstHalf;
        vector<int> rem = half;
        for (int pos = 0; pos < halfLen; pos++) {
            for (int c = 0; c < 26; c++) {
                if (rem[c] == 0) continue;
                rem[c]--;
                long long cntPerm = countPerms(rem);
                if (cntPerm >= k) {
                    firstHalf.push_back('a' + c);
                    break;                     // lock this char, move to next position
                } else {
                    k -= cntPerm;
                    rem[c]++;                  // undo, try next char
                }
            }
        }

        string res = firstHalf;
        if (oddChar != -1) res.push_back('a' + oddChar);
        reverse(firstHalf.begin(), firstHalf.end());
        res += firstHalf;
        return res;
    }
};