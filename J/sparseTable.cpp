#include <bits/stdc++.h>
using namespace std;

template <class T>
struct sparseTable { // 0 - indexed

    T op(T a, T b) {
        return min(a, b); // max(a, b), a & b, and etc.....
    }

    int n;
    vector<vector<T>> st;
    sparseTable() {}

    sparseTable(vector<T> v) {
        n = (T)v.size();
        st = vector<vector<T>> (__lg(n) + 1, vector<T> (n, 0));
        st[0] = v;
        for (int i = 1; i < (T)st.size(); i++) {
            for (int j = 0; j + (1 << i) <= n; j++) {
                st[i][j] = op(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    T query(int l, int r) { // inclusive range
        int sz = __lg(r - l + 1);
        return op(st[sz][l], st[sz][r - (1 << sz) + 1]);
    }
};
