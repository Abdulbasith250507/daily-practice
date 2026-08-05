class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> adj(n);

        for (auto &e : invocations) {
            adj[e[0]].push_back(e[1]);
        }

        // Find all methods suspicious because they are reachable from k.
        vector<bool> suspicious(n, false);
        queue<int> q;

        suspicious[k] = true;
        q.push(k);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (!suspicious[v]) {
                    suspicious[v] = true;
                    q.push(v);
                }
            }
        }

        // If any non-suspicious method calls a suspicious method,
        // we cannot remove the suspicious group.
        for (int u = 0; u < n; u++) {
            if (!suspicious[u]) {
                for (int v : adj[u]) {
                    if (suspicious[v]) {
                        vector<int> ans;
                        for (int i = 0; i < n; i++) {
                            ans.push_back(i);
                        }
                        return ans;
                    }
                }
            }
        }

        // Safe to remove all suspicious methods.
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (!suspicious[i]) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};