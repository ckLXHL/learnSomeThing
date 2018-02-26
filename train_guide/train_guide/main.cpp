//
//  main.cpp
//  train_guide
//
//  Created by didi on 2018/2/23.
//  Copyright © 2018年 didi. All rights reserved.
//

//#include "myh.h"
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <iostream>
#include <string>
using namespace std;
int main() {
    
    int sockfd;
    socklen_t len;
    string path = "/tmp/moose";
    struct sockaddr_un addr1, addr2;
    
    sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    unlink(path.c_str());
    bzero((&addr1), sizeof(addr1));
    addr1.sun_family = AF_LOCAL;
    strncpy(addr1.sun_path, path.c_str(), path.length());
    bind(sockfd, (struct sockaddr*) &addr1, SUN_LEN(&addr1));
    len = sizeof(addr2);
    bzero(&addr2, len);
    getsockname(sockfd, (struct sockaddr*)&addr2, &len);
    cout << "bound name = " <<  addr2.sun_path << " returned " <<  len << endl;
    // insert code here...
    /*freopen("./tt.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int l, t, n, sszz;
    cin >> sszz ;
    vector<string> mm = { "L", "Turning", "R"};
    for(int i = 1; i <= sszz; i++) {
        cin>>l>>t>>n;
        vector<threeI> ant;
        rep(j, n){
            int now;
            string nows;
            cin >> now >> nows;
            ant.pb(threeI{now, nows == "R"? 1: -1, j});
        }
        ants(t, ant);
        cout << "Case #" << i << ":" << endl;
        for_each(ant.begin(), ant.end(), [l, &mm](const threeI& a) {
            if (a.pos < 0 || a.pos > l) {
                cout << "Fell off" << endl;
            } else {
                cout << a.pos << " " << mm[a.di] << endl;
            }
        });
        cout << endl;
    }*/
    return 0;
}
