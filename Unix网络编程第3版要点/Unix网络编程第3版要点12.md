# 12.IPv4和IPv6的互操作性

## 12.2 IPv4 客户端和IPv6服务器

服务器使用双协议栈，通过检查数据报头，IPv4地址会在服务器TCP栈中映射为IPv6地址。

服务器双协议栈条件：

1. 通配符服务器没有设置IPV6_V6ONLY标志。
2. server绑定Pv4映射得到的IPv6地址。

## 12.3 IPv4服务器和IPv6客户端

1. IPv4地址socket
2. IPv6 调用getaddrinfo，在hints参数内设置AF_INET6和AI_V4MAPPED标志，得到一个IPv4映射得到的IPv6地址
3. 客户端内核监测到地址是映射的，网路上使用IPv4通信

IPv6和IPv4服务器客户端通信：

客户端\服务器 | 仅IPv4服务器 | 仅IPv6服务器 | 双栈IPv4服务器 | 双栈IPv6服务器
-| -|-|-|-
仅IPv4客户端 | IPv4|(no)| IPv4 | IPv4
仅IPv6客户端 | (no)|IPv6| (no) | IPv6
IPv4双栈客户端 | IPv4|(no)| IPv4 | IPv4
IPv6双栈客户端 | IPv4|IPv6| (no*) | IPv6

IPv6双栈客户端和双栈IPv4服务器的通信取决于使用记录的类型，A可以，AAAA不行

## 12.4 IPv6测试宏

IN6_IS_ADDR_* 基础测试宏

IN6_IS_ADDR_MC* 用来测试多播地址

FTP需要分别 IPv6和IPv4 地址，命令的参数不一样