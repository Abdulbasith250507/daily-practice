class Solution {
public:
    // Factor contribution of digits 0..9 for primes 2,3,5,7
    int f[10][4] = {
        {0,0,0,0}, // 0
        {0,0,0,0}, // 1
        {1,0,0,0}, // 2
        {0,1,0,0}, // 3
        {2,0,0,0}, // 4
        {0,0,1,0}, // 5
        {1,1,0,0}, // 6
        {0,0,0,1}, // 7
        {3,0,0,0}, // 8
        {0,2,0,0}  // 9
    };

    vector<int> getFactors(long long t) {
        vector<int> cnt(4, 0);
        int primes[4] = {2, 3, 5, 7};

        for (int i = 0; i < 4; i++) {
            while (t % primes[i] == 0) {
                t /= primes[i];
                cnt[i]++;
            }
        }

        if (t != 1) return {-1};
        return cnt;
    }

    // Minimum number of digits required to provide these factors
    // Returns counts of digits 2..9.
    vector<int> buildDigits(vector<int> cnt) {
        vector<int> res(10, 0);

        // 2^3 -> 8
        res[8] = cnt[0] / 3;
        cnt[0] %= 3;

        // 3^2 -> 9
        res[9] = cnt[1] / 2;
        cnt[1] %= 2;

        // 2^2 -> 4
        res[4] = cnt[0] / 2;
        cnt[0] %= 2;

        // 2 + 3 -> 6
        if (cnt[0] && cnt[1]) {
            res[6]++;
            cnt[0]--;
            cnt[1]--;
        }

        // 4 + 3 can be replaced by 2 + 6
        if (res[4] && cnt[1]) {
            res[4]--;
            res[2]++;
            res[6]++;
            cnt[1]--;
        }

        res[2] += cnt[0];
        res[3] += cnt[1];
        res[5] = cnt[2];
        res[7] = cnt[3];

        return res;
    }

    int countDigits(const vector<int>& v) {
        int ans = 0;
        for (int i = 2; i <= 9; i++)
            ans += v[i];
        return ans;
    }

    string makeString(const vector<int>& cnt) {
        string res;
        for (int d = 2; d <= 9; d++) {
            res += string(cnt[d], char('0' + d));
        }
        return res;
    }

    bool enough(vector<int> need, const vector<int>& have) {
        for (int i = 0; i < 4; i++) {
            if (have[i] < need[i])
                return false;
        }
        return true;
    }

    string smallestNumber(string num, long long t) {
        vector<int> target = getFactors(t);

        // t has a prime factor other than 2,3,5,7
        if (target.size() == 1 && target[0] == -1)
            return "-1";

        vector<int> minDigits = buildDigits(target);

        // Not enough digits in num's length.
        // Therefore the answer must have more digits.
        if (countDigits(minDigits) > (int)num.size()) {
            return makeString(minDigits);
        }

        // Total prime factors in num
        vector<int> total(4, 0);

        for (char c : num) {
            int d = c - '0';
            for (int j = 0; j < 4; j++)
                total[j] += f[d][j];
        }

        int zeroPos = num.find('0');

        // If num itself is zero-free and already works
        if (zeroPos == string::npos && enough(target, total))
            return num;

        /*
            We try changing the number from right to left.

            At position i:
            - prefix [0 ... i-1] stays unchanged
            - choose the smallest digit > num[i]
            - fill the remaining suffix with the smallest possible digits
        */

        vector<int> suffixFactors = total;

        for (int i = (int)num.size() - 1; i >= 0; i--) {
            int d = num[i] - '0';

            // Remove num[i] from the factors of the remaining suffix
            for (int j = 0; j < 4; j++)
                suffixFactors[j] -= f[d][j];

            // If there is a zero after this position,
            // we must change at or before that zero.
            if (zeroPos != string::npos && i > zeroPos)
                continue;

            int space = (int)num.size() - 1 - i;

            for (int bigger = d + 1; bigger <= 9; bigger++) {
                vector<int> need(4);

                for (int j = 0; j < 4; j++) {
                    need[j] = max(
                        0,
                        target[j] - suffixFactors[j] - f[bigger][j]
                    );
                }

                vector<int> digits = buildDigits(need);
                int used = countDigits(digits);

                if (used <= space) {
                    string ans = num.substr(0, i);
                    ans += char('0' + bigger);

                    // Put 1s first because they are the smallest digits
                    ans += string(space - used, '1');

                    ans += makeString(digits);

                    return ans;
                }
            }
        }

        // No answer with the same length.
        // Construct the smallest answer with one extra digit.
        vector<int> digits = buildDigits(target);
        int used = countDigits(digits);

        string ans;
        ans += string(num.size() + 1 - used, '1');
        ans += makeString(digits);

        return ans;
    }
};