class Solution {
public:
    int smallestIndex(vector<int>& nums) {
        int sum;
        for(int i=0; i<nums.size(); i++){
            int n = nums[i];
            sum = 0;
            while(n!=0){
                int id = n % 10;
                sum = sum + id;
                n = n / 10;
            }
            if(sum == i){
                return i;
            }
        }
        return -1;
    }
};