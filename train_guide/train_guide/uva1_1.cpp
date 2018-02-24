//
//  uva1_1_11292.cpp
//  train_guide
//
//  Created by didi on 2018/2/23.
//  Copyright © 2018年 didi. All rights reserved.
//

#include "myh.h"

void print_vars(ostream&){}
//uva 11292
int loowater(vector<int>& head,vector<int>& knight) {
    sort(begin(head), end(head));
    sort(begin(knight), end(knight));
    auto kb = knight.begin();
    int ret = 0;
    for (int p: head) {
        kb = lower_bound(kb, end(knight), p);
        if (kb != end(knight)) {
            ret += *kb;
            kb ++;
        } else return -1;
    }
    return ret;
}

//uva11729

int commando(vector<pii>& bux) {
    sort(bux.begin(), bux.end(), [](pii a, pii b) {
        return a.second > b.second;
    });
    
    int maxi = 0;
    int now = 0;
    for (auto p: bux) {
        maxi = max(now + p.first + p.second, maxi);
        now += p.first;
    }
    return maxi;
}
//uva 11300
ll stw(vector<ll>& nows) {
    ll m = accumulate(begin(nows), end(nows), static_cast<ll>(0)) / nows.size();
    nows[0] = 0;
    
    for (int i = 1; i < nows.size(); i++) {
        nows[i] += nows[i-1] - m;
    }
    sort(begin(nows), end(nows));
    ll xm = nows[nows.size() / 2];
    return accumulate(begin(nows), end(nows), static_cast<ll>(0), [xm](ll pre, ll now) {
        return pre + abs(now - xm);
    });
}
// LA 3708
double grav(int n, int m) {
    double unit = static_cast<double>(n) / (n+m);
    vector<double> res(n + 1, 1.0);
    for (int i = 1; i * unit < n; i++) {
        auto now = i * unit;
        int bottom = static_cast<int>(now);
        int top = static_cast<int>(ceil(now));
        res[bottom] = min(res[bottom], abs(bottom - now));
        res[top] = min(res[top], abs(top - now));
    }
    //dump(res);
    return accumulate(++begin(res), --end(res), 0.0) *10000/ n;
}
//uva 10881
void ants(int l, int t, vector<pii>& pos, vector<threeI>& three) {
    sort(begin(pos), end(pos));
    sort(begin(three), end(three), [](threeI& a, threeI& b) {
        return a.pos == b.pos? a.pos < b.pos: a.di < b.di;
    });
    for (int i = 0; i < pos.size(); i++) {
        pos[i].first += three[i].di * t;
    }
    sort(begin(pos), end(pos));
}
