//
//  main.cpp
//  train_guide
//
//  Created by didi on 2018/2/23.
//  Copyright © 2018年 didi. All rights reserved.
//

#include "myh.h"
using namespace std;

int main() {
    // insert code here...
    freopen("./tt.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    int ca = 0;
    while(cin>>n &&  n > 0) {
        ca++;
        vector<pair<int, int>> head(n);
        for(int i = 0; i < n; i++)
            cin>> head[i].first >> head[i].second;
        cout << "Case " << ca << ": " << commando(head) << endl;
    }
    return 0;
}
