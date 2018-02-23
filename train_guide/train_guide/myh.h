//
//  myh.h
//  train_guide
//
//  Created by didi on 2018/2/23.
//  Copyright © 2018年 didi. All rights reserved.
//

#ifndef myh_h
#define myh_h

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

#define dump(...) do{print_vars(cout<<"# "<<#__VA_ARGS__<<'=',__VA_ARGS__);cout<<endl;}while(0)
#define repi(i,a,b) for(int i=int(a);i<int(b);i++)
#define peri(i,a,b) for(int i=int(b);i-->int(a);)
#define FORi(i,a,b) for(int i=int(a);i<=int(b);i++)
#define FOR(i,n) FORi(i,1,n)
#define rep(i,n) repi(i,0,n)
#define per(i,n) peri(i,0,n)
#define all(c) begin(c),end(c)
#define mt make_tuple
#define pb push_back
#define sz size()
#define SET(__set, val) memset(__set, val, sizeof(__set))

using uint=unsigned;
using ll=long long;
using ull=unsigned long long;
using vi=vector<int>;
using vvi=vector<vi>;
using vl=vector<ll>;
using vvl=vector<vl>;
using vd=vector<double>;
using vvd=vector<vd>;
using vs=vector<string>;
using pii=pair<int, int>;
using pdd=pair<double, double>;
template<typename T1,typename T2>
ostream& operator<<(ostream& os,const pair<T1,T2>& p){
    return os<<'('<<p.first<<','<<p.second<<')';
}

template<typename Ch,typename Tr,typename C>
basic_ostream<Ch,Tr>& operator<<(basic_ostream<Ch,Tr>& os,const C& c){
    os<<'[';
    for(auto& p: c) os << p << " ";
    return os<<']';
}

template<typename Car,typename... Cdr>
void print_vars(ostream& os,const Car& car,const Cdr&... cdr){
    print_vars(os<<car<<(sizeof...(cdr)?",":""),cdr...);
}


template<int I,typename Tuple>
void print_tuple(ostream&,const Tuple&){}
template<int I,typename Car,typename... Cdr,typename Tuple>
void print_tuple(ostream& os,const Tuple& t){
    os<<get<I>(t)<<(sizeof...(Cdr)?",":"");
    print_tuple<I+1,Cdr...>(os,t);
}
template<typename... Args>
ostream& operator<<(ostream& os,const tuple<Args...>& t){
    print_tuple<0,Args...>(os<<'(',t);
    return os<<')';
}

constexpr int INF=1e9;
constexpr int MOD=1000000007;
constexpr double EPS=1e-9;
constexpr int maxw=31;
constexpr int maxn=305;

int loowater(vector<int>& head,vector<int>& knight);
int commando(vector<pair<int, int>>& bux);

#endif /* myh_h */
