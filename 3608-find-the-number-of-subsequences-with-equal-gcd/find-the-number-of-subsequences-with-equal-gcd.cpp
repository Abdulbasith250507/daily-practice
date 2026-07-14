class Solution {
public:
    static const int MOD = 1000000007;

    int subsequencePairCount(vector<int>& nums) {
        int mx = *max_element(nums.begin(), nums.end());

        vector<vector<int>> dp(mx + 1, vector<int>(mx + 1, 0));
        dp[0][0] = 1;

        for (int x : nums) {
            vector<vector<int>> ndp = dp;

            for (int g1 = 0; g1 <= mx; g1++) {
                for (int g2 = 0; g2 <= mx; g2++) {
                    if (!dp[g1][g2]) continue;

                    int ng1 = (g1 == 0) ? x : gcd(g1, x);
                    ndp[ng1][g2] += dp[g1][g2];
                    if (ndp[ng1][g2] >= MOD)
                        ndp[ng1][g2] -= MOD;

                    int ng2 = (g2 == 0) ? x : gcd(g2, x);
                    ndp[g1][ng2] += dp[g1][g2];
                    if (ndp[g1][ng2] >= MOD)
                        ndp[g1][ng2] -= MOD;
                }
            }

            dp.swap(ndp);
        }

        long long ans = 0;
        for (int g = 1; g <= mx; g++) {
            ans += dp[g][g];
            ans %= MOD;
        }

        return (int)ans;
    }
};