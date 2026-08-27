// BRUTE FORCE APPROACH
/*
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.size() > haystack.size())
            return -1;
        for(int i=0; i<=haystack.size()-needle.size(); i++){
            bool match = true;
            for(int j=0; j<needle.size(); j++){
                if(haystack[i+j]!=needle[j]){
                    match = false;
                    break;
                }
            }
            if(match)
            return i;
        }
        return -1;
    }
};
*/

// OPTIMIZED CODE USING KMP(KRUTH MORRIS PRATT) ALGORITHM
class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size();
        int m = needle.size();
        if (m > n)
            return -1;
        // Build LPS array
        vector<int> lps(m, 0);
        int len = 0;
        int i = 1;
        while (i < m) {
            if (needle[i] == needle[len]) {
                len++;
                lps[i] = len;
                i++;
            }
            else {
                if (len != 0) {
                    len = lps[len - 1];
                }
                else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        // KMP search
        i = 0;
        int j = 0;
        while (i < n) {
            if (haystack[i] == needle[j]) {
                i++;
                j++;
            }
            if (j == m)
                return i - j;
            if (i < n && haystack[i] != needle[j]) {
                if (j != 0) {
                    j = lps[j - 1];
                }
                else {
                    i++;
                }
            }
        }
        return -1;
    }
};