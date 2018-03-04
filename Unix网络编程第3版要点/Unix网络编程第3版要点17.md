# 17.ioctl操作

## 17.1概述

传统使用ioctl，作为系统接口访问信息，接口信息，路由表，arp缓存之类，ioctl是实现独立的。

POSIX提供一些替代函数：
- tcgetattr获取终端属性
- tcflush flush输入输出
- sockatmark 替换 SIOCARMARK ioctl

ioctl的网络编程通常应用在于获取网络接口地址，网络接口是否支持多播广播等。

## 17.2 ioctl

参数2 request类型：

- socket操作
- 文件操作
- 网络接口操作
- ARP缓存操作
- 路由表操作
- 流操作

ioctl与fcntl有一部分操作重叠，有些功能可以用ioctl以不同方式实现。

## 17.3 socket操作

1. socket

Request|说明|数据类型
-|-|-
SIOCATMARK |是否位于带外标记 |int 
SIOCSPGRP |设置套接口的进程ID 或进程组ID 接受SIGIO或SIGURG|int 
SIOCGPGRP |获取套接口的进程ID 或进程组ID 接受SIGIO或SIGURG|int

2. 文件

Request|说明|数据类型
-|-|-
FIONBIN |设置/ 清除非阻塞I/O 标志（O_NONBLOCK） |int 
FIOASYNC |设置/ 清除信号驱动异步I/O 标志(SIGIO) |int 
FIONREAD |获取接收缓存区中的字节数 |int
FIOSETOWN |等于SIOCSPGRP |int
FIOGETOWN |等于SIOCGPGRP|int

3. 接 口

Request|说明|数据类型
-|-|-
SIOCGIFCONF |获取所有接口的清单 |struct ifconf
SIOCSIFADDR |设置接口地址 |struct ifreq
SIOCGIFADDR |获取接口地址 |struct ifreq
SIOCSIFFLAGS |设置接口标志 |struct ifreq
SIOCGIFFLAGS |获取接口标志 |struct ifreq
SIOCSIFDSTADDR |设置点到点地址 |struct ifreq
SIOCGIFDSTADDR |获取点到点地址 |struct ifreq
SIOCGIFBRDADDR |获取广播地址 |struct ifreq
SIOCSIFBRDADDR |设置广播地址 |struct ifreq
SIOCGIFNETMASK |获取子网掩码 |struct ifreq
SIOCSIFNETMASK |设置子网掩码 |struct ifreq
SIOCGIFMETRIC |获取接口的测度 |struct ifreq
SIOCSIFMETRIC |设置接口的测度 |struct ifreq
SIOCGIFMTU |获取接口MTU |struct ifreq
SIOCxxx| (取决于系统实现)

4. ARP

Request|说明|数据类型
-|-|-
SIOCSARP |创建/ 修改ARP 表项 |struct arpreq
SIOCGARP |获取ARP 表项 |struct arpreq
SIOCDARP|删除ARP 表项|struct arpreq

5. 路由

Request|说明|数据类型
-|-|-
SIOCADDRT |增加路径 |struct rtentry
SIOCDELRT|删除路径|struct rtentry

6. 流

Request: I_xxx
 
## 17.6

ioctl 在一些系统中的实现可能不一致，在内存分配不够的情况下，有些返回错误，有些不返回错误，需要手动检查长度。

用ioctl取出的数据中，ifr的数据长度需要根据family处理，类似于IPv6 

## 17，7 网络接口操作

SIOCGxxx函数集代表netstat命令

SIOCSxxx函数集代表ifconfig命令

## 17.8 arp高速缓存

struct arpreq和 ATF_XXX，头文件是net/if_arp.h

类似于命令arp，可以读取网卡地址