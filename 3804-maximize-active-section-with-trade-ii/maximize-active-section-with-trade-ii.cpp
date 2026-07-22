class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.size();
        vector<int> prefix1(n + 1, 0);
        for (int i = 0; i < n; i++)
            prefix1[i + 1] = prefix1[i] + (s[i] == '1');
        int totalOnes = prefix1[n];

        // Build zero-groups (runs of '0')
        vector<int> gStart, gLen;
        vector<int> zg(n, -1); // zg[i] = index of last zero-group ending at or before i (monotonic)
        int lastIdx = -1;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                if (i > 0 && s[i - 1] == '0') gLen.back()++;
                else { gStart.push_back(i); gLen.push_back(1); }
                lastIdx = (int)gStart.size() - 1;
            }
            zg[i] = lastIdx;
        }
        int m = gStart.size();

        // adjSum[k] = gLen[k] + gLen[k+1]
        vector<int> adjSum;
        for (int k = 0; k + 1 < m; k++) adjSum.push_back(gLen[k] + gLen[k + 1]);
        int am = adjSum.size();

        int LOG = 1;
        while ((1 << LOG) <= max(am, 1)) LOG++;
        vector<vector<int>> st;
        if (am > 0) {
            st.assign(LOG + 1, vector<int>(am));
            st[0] = adjSum;
            for (int j = 1; (1 << j) <= am; j++)
                for (int i = 0; i + (1 << j) <= am; i++)
                    st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
        }
        auto rangeMax = [&](int l, int r) -> long long {
            if (l > r || l < 0 || r >= am) return LLONG_MIN;
            int len = r - l + 1;
            int k = 31 - __builtin_clz(len);
            return max(st[k][l], st[k][r - (1 << k) + 1]);
        };
        auto groupEnd = [&](int idx) { return gStart[idx] + gLen[idx] - 1; };

        vector<int> ans;
        ans.reserve(queries.size());
        for (auto& q : queries) {
            int l = q[0], r = q[1];
            long long best = totalOnes;

            bool lIsZero = (s[l] == '0');
            bool rIsZero = (s[r] == '0');
            int leftIdx  = lIsZero ? zg[l] : -1;
            int rightIdx = rIsZero ? zg[r] : -1;

            if (lIsZero && rIsZero && leftIdx == rightIdx) {
                ans.push_back((int)best); // whole range is one zero-run: no trade possible
                continue;
            }

            long long leftTrunc  = lIsZero ? (groupEnd(leftIdx) - l + 1) : 0;
            long long rightTrunc = rIsZero ? (r - gStart[rightIdx] + 1) : 0;

            int startG = zg[l] + 1;                              // first zero-group not fully left of l
            int endG   = rIsZero ? (zg[r] - 1) : zg[r];           // last zero-group fully within/left of r

            // Case: l's and r's truncated groups are directly adjacent (single 1-block between them)
            if (lIsZero && rIsZero && zg[l] + 1 == zg[r])
                best = max(best, (long long)totalOnes + leftTrunc + rightTrunc);

            // Interior full adjacent-group pairs
            if (startG <= endG - 1)
                best = max(best, (long long)totalOnes + rangeMax(startG, endG - 1));

            // Pair truncated-left group with the first full interior group
            if (lIsZero && startG <= endG)
                best = max(best, (long long)totalOnes + leftTrunc + gLen[startG]);

            // Pair truncated-right group with the last full interior group
            if (rIsZero && zg[l] < endG)
                best = max(best, (long long)totalOnes + rightTrunc + gLen[endG]);

            ans.push_back((int)best);
        }
        return ans;
    }
};