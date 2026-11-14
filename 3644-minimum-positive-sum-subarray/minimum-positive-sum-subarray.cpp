class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int n = nums.size();
        int min_sum = INT_MAX;
        for(int i=0; i<=n-1; i++){
            int curr_sum = 0;
            for(int j=i; j<n; j++){
                curr_sum += nums[j];
                int length = j-i+1;
                if(l<=length && length<=r){
                    if(curr_sum>0){
                        min_sum = min(min_sum, curr_sum);
                    }
                }
                if(length>r){
                    break;
                }
            }
        }
        if(min_sum==INT_MAX)
            return -1;
        return min_sum;
    }
};