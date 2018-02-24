//
//  main.cpp
//  train_guide
//
//  Created by didi on 2018/2/23.
//  Copyright © 2018年 didi. All rights reserved.
//

#include "myh.h"

int main() {
    // insert code here...
    freopen("./tt.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int l, t, n, sszz;
    cin >> sszz ;
    for(int i = 1; i <= sszz; i++) {
        cin>>l>>t>>n;
            vector<threeI> ant;
        rep(j, n){
            int now;
            string nows;
            cin >> now >> nows;
            ant.pb(threeI{now, nows == "R"? 1: -1, j});
        }
        ants(l, t, ant);
        cout << "Case #" << i << ":" << endl;
    }
    return 0;
}
