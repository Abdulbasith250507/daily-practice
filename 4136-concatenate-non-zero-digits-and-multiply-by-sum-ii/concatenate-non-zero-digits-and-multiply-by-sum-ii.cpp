class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        const int MOD = 1000000007;
        int n = s.size();

        vector<long long> prefSum(n + 1, 0);
        vector<long long> prefCnt(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefSum[i + 1] = prefSum[i] + (s[i] - '0');
            prefCnt[i + 1] = prefCnt[i] + (s[i] != '0');
        }

        vector<long long> pow10(n + 1, 1);
        for (int i = 1; i <= n; i++)
            pow10[i] = (pow10[i - 1] * 10) % MOD;

        vector<long long> prefVal(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefVal[i + 1] = prefVal[i];
            if (s[i] != '0')
                prefVal[i + 1] = (prefVal[i + 1] * 10 + (s[i] - '0')) % MOD;
        }

        vector<int> ans;

        for (auto &q : queries) {
            int l = q[0], r = q[1];

            long long sum = prefSum[r + 1] - prefSum[l];
            long long cnt = prefCnt[r + 1] - prefCnt[l];

            long long before = prefCnt[l];

            long long x = (prefVal[r + 1] -
                          prefVal[l] * pow10[cnt] % MOD + MOD) % MOD;

            ans.push_back((x * (sum % MOD)) % MOD);
        }

        return ans;
    }
};