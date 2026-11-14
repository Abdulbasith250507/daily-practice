class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int inc = 1, dec = 1;
        int maxinc = 1, maxdec = 1;
        int n = nums.size();
        for(int i=0; i<n-1; i++){
            if(nums[i]<nums[i+1]){
                inc++;
            }
            else{
                inc = 1;
            }
            if(maxinc < inc)
                maxinc = inc;
            if(nums[i]>nums[i+1]){
                dec++;
            }
            else{
                dec = 1;
            }
            if(maxdec < dec)
                maxdec = dec;
        }
        return max(maxinc, maxdec);
    }
};