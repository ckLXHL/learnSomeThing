# 7 套接字选项

## 7.5 通用socket选项

1. SO_BROADCAST 广播

网络支持（以太网，令牌环网），数据报socket（即UDP）

广播地址，SO_BROADCAST没有设，触发EACCES

2. SO_DEBUG

只支持TCP，TCP记录发送和接收的信息，可以使用trpt获取

3. SO_DONTROUTE

SO_DONTROUTE 选项将导致数据包不经由网关发送，而是发往直接相连的主机。

4. SO_ERROR

获取socket errno

5. SO_KEEPALIVE

TCP，两个小时无数据，自动传一个probe。ACK没有问题，程序无感知。RST，socket中断报错。无反应，进入重试过程。

设置probe发送时间会影响**全系统**

书上吐糟这不是保活（keep-alive），而是催死（make-dead）

6. SO_LINGER

修改close的行为

    struct linger {
        int l_onoff;
        int l_linger;
    }
    l_onoff == 0，默认
    l_onoff != 0 && l_linger == 0 TCP直接发RST，避免TIME_WATI状态，未发送数据丢弃
    l_onoff != 0 && l_linger != 0 协议栈等待数据全部发送完成或linger time超时，如果socket设置了非阻塞，用户需要检查close返回值。

7. SO_OOBINLINE

带外数据会被排队，MSG_OOB读取不到带外数据

8. SO_RCVBUF和SO_SNDBUF

修改内核缓冲区大小，修改参数必须在connect和listen之前

9. SO_RCVLOWAT和SO_SNDLOWAT

selec时，达到可读可写状态的最低水平

10. SO_RCVTIMEO和SO_SNDTIMEO

对socket读写设置超时

11. SO_REUSEADDR和SO_REUSEPORT

- SO_REUSEADDR 
    1. 服务器重启，原tcp连接存在，允许绑定
    2. 通配符地址服务器和绑定ip地址服务器并存
    3. 同一个进程绑定多个ip和一个port，常用于UDP
    4. 绑定多个socket，一般用于UDP多播
- SO_REUSEPORT 
    - 允许我们将任意数目的socket绑定到完全相同的源地址端口
    - 与SO_REUSEADDR不同的是 ，处理SO_REUSEPORT的代码不仅会检查当前尝试绑定的socket的SO_REUSEPORT，而且也会检查之前已绑定了当前尝试绑定的地址端口对的socket的SO_REUSEPORT选项

12. SO_TYPE

获取SOCK_STREAM或SOCK_DGRAM 即TCP还是UDP

## 7.9 TCP选项

1. TCP_MAXSEG

设置MSS，最大报文段长度

2. TCP_NODELAY

禁用Nagle算法，允许小包发送。用于提高读-写-读-写模式的速度。Nagle基本概念就是攒缓存到一定程度才发包。

