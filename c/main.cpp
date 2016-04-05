#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

void dfs(vector<vector<unsigned>> &g, vector<bool> &used,
    unsigned v, vector<unsigned> &path) {
    path.push_back(v);
    used[v] = true;
    for (auto &u : g[v]) {
        if (!used[u]) {
            dfs(g, used, u, path);
        }    
    }
}

void print_result(vector<unsigned> &ind, vector<unsigned> &path) {
    for (unsigned i = 0; i < path.size(); ++i) {
        cout << ind[path[i]] << " ";
    }
    cout << endl;
}

void brute(vector<vector<unsigned>> &db, vector<unsigned> &ind,
    vector<vector<int>> &g, unsigned c, unsigned v, unsigned n,
    vector<unsigned> &perm) {
    if (v == n) {
        vector<vector<unsigned>> tmp_g(n);
        for (unsigned v = 0; v < n; ++v) {
            for (unsigned i = 0; i < 6; ++i) {
                unsigned cv = db[ind[v] - 1][(i + perm[v]) % 6];
                if (cv != c) {
                    continue;
                }
                if (g[v][i] == -1) {
                    return;
                }
                tmp_g[v].push_back(g[v][i]);
            }
        }
        vector<bool> used(n, false);
        vector<unsigned> path;
        dfs(tmp_g, used, 0, path);
        if (path.size() == n) {
            print_result(ind, path);
            exit(0);
        }
        return;
    }
    for (unsigned p = 0; p < 6; ++p) {
        perm[v] = p;
        bool ok = true;
        for (unsigned i = 0; i < 6; ++i) {
            if ((g[v][i] != -1) && (g[v][i] < v)) {
                unsigned u = g[v][i];
                unsigned c1 = db[ind[v] - 1][(i + p) % 6];
                if (c1 != c) {
                    continue;
                }
                unsigned s = 0;
                while (g[u][s] != v) {
                    ++s;
                }
                unsigned c2 = db[ind[u] - 1][(s + perm[u]) % 6];
                if (c1 != c2) {
                    ok = false;
                }
            }
        } 
        if (ok) {
            brute(db, ind, g, c, v + 1, n, perm);
        }
    }
}

int main() {
    vector<vector<unsigned>> db(10);
    for (unsigned i = 0; i < 10; ++i) {
        for (unsigned j = 0; j < 6; ++j) {
            unsigned x;
            cin >> x;
            db[i].push_back(x);
        }
    }
    unsigned n;
    cin >> n;
    vector<unsigned> item_indices(n);
    for (unsigned i = 0; i < n; ++i) {
        cin >> item_indices[i];
    }
    vector<vector<int>> item_graph(n);
    for (unsigned i = 0; i < n; ++i) { 
        item_graph[i].resize(6);
        for (unsigned j = 0; j < 6; ++j) {
            cin >> item_graph[i][j];
        }
    }         
    vector<unsigned> perm(n);
    for (unsigned c = 1; c <= 3; ++c) {
        brute(db, item_indices, item_graph, c, 0, n, perm);
    }
    return 0;
}
