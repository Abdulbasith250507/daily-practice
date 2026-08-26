class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        vector<int> pos;

        // Store positions of all 1s
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '1')
                pos.push_back(i);
        }

        // Not enough 1s
        if (pos.size() < k)
            return "";

        string ans = "";

        for (int i = 0; i + k - 1 < pos.size(); i++) {
            int start = pos[i];
            int end = pos[i + k - 1];

            string cur = s.substr(start, end - start + 1);

            // First valid substring
            if (ans == "") {
                ans = cur;
            }
            // Shorter is better
            else if (cur.size() < ans.size()) {
                ans = cur;
            }
            // Same length -> lexicographically smaller
            else if (cur.size() == ans.size() && cur < ans) {
                ans = cur;
            }
        }

        return ans;
    }
};