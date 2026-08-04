class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        int mn = *min_element(nums.begin(), nums.end());
        int mx = *max_element(nums.begin(), nums.end());

        unordered_set<int> s(nums.begin(), nums.end());

        vector<int> ans;

        for (int x = mn; x <= mx; x++) {
            if (s.find(x) == s.end()) {
                ans.push_back(x);
            }
        }

        return ans;
    }
};