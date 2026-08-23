class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();
        int half = n / 2;
        int lefthalf=0, righthalf=0;
        int leftQ=0, rightQ=0;
        for(int i=0; i<n; i++){
            if(num[i]=='?'){
                if(i<half) leftQ++;
                else rightQ++;
            }
            else{
                int number = num[i] - '0';
                if(i<half) lefthalf += number;
                else righthalf += number;
            }
        }
        int sumdiff = lefthalf - righthalf;
        int qdiff = leftQ - rightQ;
        if (qdiff % 2 != 0)
            return true;
        return sumdiff != -9 * qdiff / 2;
    }
};