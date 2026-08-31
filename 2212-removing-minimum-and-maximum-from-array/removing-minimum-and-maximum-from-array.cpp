class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();
        int minIdx = 0;
        int maxIdx = 0;
        for (int i = 1; i < n; i++) {
            if (nums[i] < nums[minIdx]) {
                minIdx = i;
            }
            if (nums[i] > nums[maxIdx]) {
                maxIdx = i;
            }
        }
        int left = min(minIdx, maxIdx);
        int right = max(minIdx, maxIdx);

        // Remove both from the front
        int option1 = right + 1;

        // Remove both from the back
        int option2 = n - left;

        // Remove one from each side
        int option3 = (left + 1) + (n - right);

        return min({option1, option2, option3});
    }
};