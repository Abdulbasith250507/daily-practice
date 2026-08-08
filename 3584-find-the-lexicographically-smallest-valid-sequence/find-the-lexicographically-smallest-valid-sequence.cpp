class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        vector<int> ans(m);

        // last[j] = leftmost index in word1 that can be used
        // to match word2[j] while matching the remaining suffix.
        vector<int> last(m, -1);

        int i = n - 1;
        int j = m - 1;

        // Build a valid matching sequence from the right.
        while (i >= 0 && j >= 0) {
            if (word1[i] == word2[j]) {
                last[j] = i;
                j--;
            }
            i--;
        }

        // Greedily build lexicographically smallest index sequence.
        bool canSkip = true;
        j = 0;

        for (i = 0; i < n && j < m; i++) {

            // Exact match
            if (word1[i] == word2[j]) {
                ans[j++] = i;
            }

            // Use our one allowed mismatch
            else if (canSkip &&
                     (j == m - 1 || i < last[j + 1])) {
                ans[j++] = i;
                canSkip = false;
            }
        }

        // Couldn't construct a complete sequence
        if (j < m)
            return {};

        return ans;
    }
};