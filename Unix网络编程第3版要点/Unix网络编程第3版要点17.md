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

- SIOCATMARK