#!/usr/bin/env bash

yes | pip install shadowsocks

sslocal -s 35.194.219.96 -p 8989 -k "123456" -m aes-256-gcm >/dev/null 2>&1 &

proxy_on

jupyter notebook >/dev/null 2>&1 &

function proxy_on() {
     export no_proxy="localhost,127.0.0.1,localaddress,.localdomain.com"
     export http_proxy="socks5://127.0.0.1:1080"
     export https_proxy=$http_proxy
     echo -e "已开启代理"
 }