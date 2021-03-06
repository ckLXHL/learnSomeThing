# 13.守护进程和inetd超级服务器程序

## 13.1 概述

系统进程启动过程：

1. 超级用户权限开机启动的守护进程（包括inetd，cron，syslogd）
2. inetd启动的服务器（Telnet，FTP等）
3. cron正常启动守护进程
4. cron初始化程序，在需要的时候唤醒它们。

## 13.2 syslogd守护进程

1. 读取配置。准备写文件
2. 创建unix socket，绑定与 /var/run/log或/dev/log（取决于系统）
3. 创建UDP socket，绑定端口514

syslogd是select的无穷循环

SIGHUP导致syslogd重读配置

## 13.3 syslog函数

配套syslogd志记

第一个参数可以是level

level | Value | 意义
-|-|-
LOG_EMERG | 0 | 系统不可用
LOG_ALERT| 1 | 立即采取行动
LOG_CRIT|2| 关键
LOG_ERR|3| 错误
LOG_WARNING|4| 警告
LOG_NOTICE|5|正常重要内容
LOG_INFO|6|信息
LOG_DEBUG|7|debug级信息

第一个参数也可以是一些代表功能的常量LOG_*。可以用或连接

syslog connect 由syslogd开启的unix socket，可以使用openlog和closelog控制连接


> 13.4 session需要复习

## 13.5 inetd 守护进程

优点：
1. 简化守护进程代码，通用的启动工作交给inetd
2. 让一个守护进程等待所有请求，节省进程数

可以使用openlog将守护进程注册到inetd，由inetd管理fork，exec之类的工作

在inetd中，tcp和udp服务方式不一样，udp只能有一个端口监听，服务开启期间inetd不监听端口，tcp持续监听。

inetd fork exec性能不高，高负载服务器一般不使用