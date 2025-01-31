#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
template <int N, typename T = int> 
struct LazySegmentTree {
    constexpr static T max_T = numeric_limits<T>::max();
    constexpr static T min_T = numeric_limits<T>::min();
    constexpr static int H = int(ceil(log2(N))), _N = 1 << H;

    struct node {
        T _sum, _min, _max;
    } tree[2 * _N];

    node merge(node x, node y) {
        return {x._sum + y._sum, std::min(x._min, y._min), std::max(x._max, y._max)};
    }

    T u[2 * _N];
    bool f[2 * _N];
    int a[2 * _N], b[2 * _N];
    LazySegmentTree() {
        fill(tree, tree + 2 * _N, node({0, 0, 0}));
        fill(f, f + 2 * _N, 0);
        fill(u, u + 2 * _N, 0);
        iota(a + _N, a + 2 * _N, 0);
        iota(b + _N, b + 2 * _N, 0);
        for (int i = _N - 1; i > 0; i--) {
            a[i] = a[2 * i];
            b[i] = b[2 * i + 1];
        }
    }

    void apply(int i, T x, bool _insert) {
        if (_insert) {
            u[i] = x;
            f[i] = 1;
        }
        else {
            u[i] += x;
        }
    }

    void push(int i) {
        if (!f[i] && !u[i]) {
            return;
        }
        if (f[i]) {
            tree[i] = {0, 0, 0};
        }
        tree[i]._sum += u[i] * (b[i] - a[i] + 1);
        tree[i]._min += u[i];
        tree[i]._max += u[i];
        if (i < _N) {
            apply(2 * i, u[i], f[i]), apply(2 * i + 1, u[i], f[i]);
        }
        u[i] = f[i] = 0;
    }

    void update(int l, int r, T x, bool _insert, int i = 1) {
        if (l <= a[i] && r >= b[i]) {
            apply(i, x, _insert);
        }
        push(i);
        if (l > b[i] || r < a[i] || (l <= a[i] && r >= b[i])) {
            return;
        }
        update(l, r, x, _insert, 2 * i);
        update(l, r, x, _insert, 2 * i + 1);
        tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
    }

    node query(int l, int r, int i = 1) {
        push(i);
        if (l <= a[i] && r >= b[i]) {
            return tree[i];
        }
        if (l > b[i] || r < a[i]) {
            return {0, max_T, min_T};
        }
        return merge(query(l, r, 2 * i), query(l, r, 2 * i + 1));
    }

    T get(int i) {
        for (int x = H; x >= 0; x--) {
            push((_N + i) >> x);
        }
        return tree[_N + i]._sum;
    }

    void set(int l, int r, T x) { 
        update(l, r, x, 1); 
    }
    void add(int l, int r, T x) { 
        update(l, r, x, 0); 
    }
    void set(int i, T x) { 
        set(i, i, x); 
    }
    void add(int i, T x) { 
        add(i, i, x);
    }
    T sum(int l, int r) { 
        return query(l, r)._sum; 
    }
    T min(int l, int r) { 
        return query(l, r)._min;
    }
    T max(int l, int r) { 
        return query(l, r)._max;
    }
};

LazySegmentTree<N, int> st;

int main() {
    
}