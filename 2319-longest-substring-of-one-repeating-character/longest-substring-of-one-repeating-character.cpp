class Solution {
public:
    struct Node {
        int len;
        int pref, suff, best;
        char lc, rc;

        Node() {
            len = pref = suff = best = 0;
            lc = rc = '#';
        }
    };

    vector<Node> tree;
    string s;

    Node merge(Node a, Node b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;
        res.len = a.len + b.len;
        res.lc = a.lc;
        res.rc = b.rc;

        res.pref = a.pref;
        res.suff = b.suff;
        res.best = max(a.best, b.best);

        if (a.rc == b.lc) {
            res.best = max(res.best, a.suff + b.pref);

            if (a.pref == a.len)
                res.pref = a.len + b.pref;

            if (b.suff == b.len)
                res.suff = b.len + a.suff;
        }

        return res;
    }

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node].len = 1;
            tree[node].pref = 1;
            tree[node].suff = 1;
            tree[node].best = 1;
            tree[node].lc = tree[node].rc = s[l];
            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, char c) {
        if (l == r) {
            tree[node].lc = tree[node].rc = c;
            tree[node].pref = 1;
            tree[node].suff = 1;
            tree[node].best = 1;
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(node * 2, l, mid, idx, c);
        else
            update(node * 2 + 1, mid + 1, r, idx, c);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    vector<int> longestRepeating(string s, string queryCharacters,
                                 vector<int>& queryIndices) {
        this->s = s;

        int n = s.size();
        tree.resize(4 * n + 5);

        build(1, 0, n - 1);

        vector<int> ans;

        for (int i = 0; i < queryCharacters.size(); i++) {
            int idx = queryIndices[i];
            char c = queryCharacters[i];

            update(1, 0, n - 1, idx, c);

            ans.push_back(tree[1].best);
        }

        return ans;
    }
};