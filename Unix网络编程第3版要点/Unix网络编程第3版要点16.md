# 非阻塞I/O

## 1.介绍

- TCP阻塞写会在没有内核缓存的情况下阻塞，TCP非阻塞写直接返回EWOULDBLOCK
- UDP没有实际的内核缓存，直接从用户内存到协议栈。一些系统可能会阻塞于缓存和拥塞控制。
- accept非阻塞返回EWOULDBLOCK
- connect对于TCP是个连接过程，对于UDP只是存储对方的IP和port
- TCP的connect阻塞等到ACK或者RTT
- 非阻塞TCP，第一次握手直接返回EINPROGRESS

## 16.3 非阻塞connect

非阻塞connect的意义：

1. 三次握手连接中间做其他事情
2. 可以并发多个连接，类似于浏览器
3. 使用select实现可控制的超时

需要处理的问题：

1. 同host连接是立即完成的
2. berkeley实现有两条规则
    - 连接完成，描述符可写
    - 出现错误，描述符同时可读可写

## 16.6 非阻塞accept

需要防止accpet前RST，导致select可读但accpet失败，错误宏EWOULDBLOCK（Berkeley-derived），ECONNABORTED（POSIX），EPROTO（SVR4），EINTR（信号打断）