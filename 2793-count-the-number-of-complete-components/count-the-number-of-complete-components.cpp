class Solution {
public:
    vector<vector<int>> graph;
    vector<bool> vis;

    pair<int, int> dfs(int node) {
        vis[node] = true;

        int nodes = 1;
        int degreeSum = graph[node].size();

        for (int nei : graph[node]) {
            if (!vis[nei]) {
                auto [cnt, deg] = dfs(nei);
                nodes += cnt;
                degreeSum += deg;
            }
        }

        return {nodes, degreeSum};
    }

    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        graph.assign(n, {});
        vis.assign(n, false);

        for (auto &e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }

        int ans = 0;

        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                auto [nodes, degreeSum] = dfs(i);

                // degreeSum = 2 * edges in the component
                if (degreeSum == nodes * (nodes - 1))
                    ans++;
            }
        }

        return ans;
    }
};