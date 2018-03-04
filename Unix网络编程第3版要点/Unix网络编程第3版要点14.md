# 14.高级I/O函数

## 14.2套接字超时

处理超时方法：

1. alarm，发出SIGALRM
2. 使用select内置超时
3. 使用SO_RCVTIMEO和SO_SNDTIMEO socket option

## 14.3 recv和send

flag | 功能 | recv | send
-|-|-|-
MSG_DONTROUTE| bypass绕过路由表搜索| | * 
MSG_DONTWAIT| 对单个IO操作非阻塞 | * | *
MSG_OOB| 收发带外数据|*|*
MSG_PEEK| peek数据|*|
MSG_WAITALL| 等待所有数据|*|

> peek数据是指，读取数据到buffer，但协议栈中并不删除数据，下次还可以读到

这里列出的不是全部选项

## 14.4 readv和writev

可以同时读写多个buffer

## 14.5 recvmsg和sendmsg

可以用于替换所有IO函数的通用IO函数，提供更细粒度的控制，设置控制信息

## 14.7 协议栈存了多少数据？

1. 如果只是为了非阻塞，可以设置非阻塞标志
2. 如果想peek一下可以设置peek标志
3. 一些实现里有FIONREAD标志，可以获取当前UDP socket数据量

## 14.8 socket和标准IO

标准IO提供了buffer能力，但是会引起一些其他问题

使用fdopen把fd转换为标准IO流

使用fileno把标准IO流转换为fd

IO多路服务只支持fd

对socket开启读写IO流，读和写之间需要一些介入的流函数。

所以最好打开两个流分开读写

标准IO流有三种缓存标准：全缓存，行缓存，无缓存

标准错误无缓存。其他流和标准输出输入一般全缓存，终端下是行缓存。

使用setvbuf强制行缓存，使用fflush强制刷新缓存

最佳实践是不使用标准IO，而是直接在buffer上操作行缓存

## 14.9 高级轮训技术

使用poll，kqueue等技术代替select

