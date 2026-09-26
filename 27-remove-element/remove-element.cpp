#include <vector>

class Solution {
public:
    int removeElement(std::vector<int>& nums, int val) {
        int index = 0; // Tracks the position to write the next valid element
        
        for (int i = 0; i < nums.size(); i++) {
            // If the current element is not the value to remove
            if (nums[i] != val) {
                nums[index] = nums[i]; // Move it to the front
                index++; // Advance the write pointer
            }
        }
        return index; 
    }
};
