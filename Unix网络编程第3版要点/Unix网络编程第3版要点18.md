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