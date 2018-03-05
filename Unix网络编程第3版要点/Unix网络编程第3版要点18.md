# 18.路由套接字

## 18.1 概述

没有命令可以获取完整的路由

netstat从内核内存中获取路由表

AF_ROUTE只支持raw socket

路由socket支持以下三种操作：

1. 向路由socket写可以发送信息到内核，路由的添加删除都是这种操作
2. 读路由socket。用于内核通知进程，ICMP重定向的接收和处理，来自外部路由过程的路由解析请求
3. sysctl可以保存路由表或列举所有配置的网络接口

## 18.2 数据链路socket地址结构

    struct sockaddr_dl {
        uint8_t      sdl_len;
        sa_family_t  sdl_family; /* AF_LINK */ 
        uint16_t sdl_index; /* system assigned index, if > 0 */ 
        uint8_t      sdl_type; /* IFT_ETHER, etc. from  */ 
        uint8_t      sdl_nlen; /* name length, starting in sdl_data[0] */ 
        uint8_t      sdl_alen; /* link-layer address length */ 
        uint8_t      sdl_slen; /* link-layer selector length */ 
        char sdl_data[12]; /* minimum work area, can be larger;
    }

## 18.3 读写

message type | to k | from k | 描述 | 数据结构
-|-|-|-|-
RTM_ADD|*|*|添加路由|rt_msghdr
RTM_CHANGE|*|*|更改网管、metrics、flag|rt_msghdr
RTM_DELADDR||*|从网络接口中删除地址|ifa_msghdr
RTM_DELETE|*|*|删除路由|rt_msghdr
RTM_DELMADDR||*|删除多播地址|ifma_msghdr
RTM_GET|*|*|获取metrics和其他路由信息|rt_msghdr
RTM_IFANNOUNCE||*|系统中添加删除网络接口|if_announcemsghdr
RTM_IFINFO||*|网路接口的开启关闭|if_msghdr
RTM_LOCK|*|*|锁metrics|rt_msghdr
RTM_LOSING||*|系统假定路由失败|rt_msghdr
RTM_MISS||*|该地址查找失败|rt_msghdr
RTM_NEWADDR||*|网络接口添加地址|ifa_msghdr
RTM_NEWMADDR||*|网络接口添加多播地址|ifma_msghdr
RTM_REDIRECT||*|内核告知使用不同的路由|rt_msghdr
RTM_RESOLVE||*|请求将目的地址解析为链路层地址|rt_msghdr

## 18.4 sysctl

route socket需要root权限，sysctl任意进程可用

sysctl 第一个参数是一个数组，包含了查询的层次结构

## 18.6 接口名字和索引函数

if_nametoindex, if_indextoname 函数提供了网络接口名称到索引的映射

if_nameindex提供所有网络接口的名称索引结构, if_freenameindex，释放获取的名称索引结构