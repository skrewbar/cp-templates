#include <bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(), (v).end()

struct DisjointSet {
    vector<int> parent;

    DisjointSet(int n) : parent(n) { iota(all(parent), 0); }

    int findParent(int x) {
        if (x != parent[x])
            parent[x] = findParent(parent[x]);
        return parent[x];
    }

    void unionParent(int u, int v) {
        u = findParent(u), v = findParent(v);

        if (u != v)
            parent[v] = u;
    }

    bool isConnected(int u, int v) { return findParent(u) == findParent(v); }
};