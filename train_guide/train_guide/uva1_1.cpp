//
//  uva1_1_11292.cpp
//  train_guide
//
//  Created by didi on 2018/2/23.
//  Copyright © 2018年 didi. All rights reserved.
//

#include "myh.h"


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
