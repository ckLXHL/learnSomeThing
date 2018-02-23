//
//  main.cpp
//  train_guide
//
//  Created by didi on 2018/2/23.
//  Copyright © 2018年 didi. All rights reserved.
//
#include <cstdio>
#include <regex>
#include <list>
#include <iomanip>
#include <iterator>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <climits>
#include <string>
#include <set>
#include <numeric>
#include <bitset>
#include <cmath>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <numeric>
#include <vector>
#include <cassert>
#include <ctime>

using namespace std;
int loowater(vector<int>& head,vector<int>& knight);
int commando(vector<pair<int, int>>& bux);
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
