class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048;

        vector<bool> present(MAXX, false);
        for (int x : nums)
            present[x] = true;

        vector<bool> pairXor(MAXX, false);
        for (int a = 0; a < MAXX; a++) {
            if (!present[a]) continue;
            for (int b = 0; b < MAXX; b++) {
                if (!present[b]) continue;
                pairXor[a ^ b] = true;
            }
        }

        vector<bool> ans(MAXX, false);
        for (int x = 0; x < MAXX; x++) {
            if (!pairXor[x]) continue;
            for (int y = 0; y < MAXX; y++) {
                if (!present[y]) continue;
                ans[x ^ y] = true;
            }
        }

        int res = 0;
        for (bool v : ans)
            if (v) res++;

        return res;
    }
};