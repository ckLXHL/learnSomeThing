# 非阻塞I/O

## 介绍

- TCP阻塞写会在没有内核缓存的情况下阻塞，TCP非阻塞写直接返回EWOULDBLOCK
- UDP没有实际的内核缓存，直接从用户内存到协议栈。一些系统可能会阻塞于缓存和拥塞控制。
- accept非阻塞返回EWOULDBLOCK
- connect对于TCP是个连接过程，对于UDP只是存储对方的IP和port
- TCP的connect阻塞等到ACK或者RTT
- 非阻塞TCP，第一次握手直接返回EINPROGRESS