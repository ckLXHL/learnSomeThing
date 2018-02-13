
# 4 基本TCP套接字

## 4.2（AF address family，PF protocol family）

func Socket(domain, typ, proto int) (fd int, err error) 

有效的domain和type组合：

|type\domain  | AF_INET | AF_INET6 | AF_LOCAL | AF_ROUTE | AF_KEY
|SOCK_STREAM  | tcp/sctp| tcp/sctp |	yes	  |    no
|SOCK_DGRAM	  |   udp	|   udp	   |    yes	  |    no
|SOCK_SEQPACKET|	 sctp	|  sctop   |    yes	  |   no
|SOCK_RAW	  |  ipv4   |   ipv6   |     no   |    yes	 |yes

## 4.3 connect tcp客户端三次握手

错误处理：

ETIMEDOUT超时，
ECONNREFUSED response带RST （1、没有服务器，2、tcp中断链接，3、tcp连接不存在）

EHOSTUNREACH，ENETUNREATH，连接不到，可能是连接不到，或者本地连接完全没有等待
c
onnect失败，申请的socket也不能用，只能关闭，需要重试只能重新申请socket

## 4.4 bind

TCP服务器一般要指定端口（反例1、是RPC调用，注册内核选定的端口到RPC port mapper。反例2、通配符地址服务器）

使用系统选择的端口，没法使用bind获取，必须使用getsockname获取
错误EADDRINUSE，端口被占了

## 4.5 listen

close状态转listen状态

backlog，第二个参数代表内核需要排最多多少连接。内核维护两条队列，一条维护三次握手途中的连接，另一条维护已经连接的队列，backlog代表两个队列连接的数量和（berkeley实现增加了一个系数*1.5，backlog=0在不同系统代表不同意义

不完整连接的队列中连接只维护一个RTT中间值

队列中连接达到上限，则忽视新到达的SYN请求，而且不回应RST，客户端会产生error，需要用户态处理，而TCP自动重试机制不会被触发
处于连接完毕，accept之间的数据，会被TCP协议栈排队

## 4.6 accept
系统创建新socket返回

## 4.7 fork exec
fcntl FD_CLOEXEC，对fd指定这个标志，exec时该fd自动被关闭

## 4.8 并发服务器

原文采用多进程**forkexec**的方式并发，golang直接采用**goroutine**的方式更方便，也更高效。

注1：golang中的ForkExec完成从头开始一个新进程，和c中的forkexec行为不太一样

注2: 父进程中关闭socket fd不会造成socket关闭，由于文件描述符有引用计数

## 4.9 close

close **标记** socket关闭并立即返回,TCP会尝试发送已经排队的数据，接着进入关闭流程（四次挥手）（默认行为）,如果父进程不调用close，文件描述符和tcp连接会过多。

注1、关闭流程即四次挥手

注2、以上为默认行为

注3、使用shutdown可以强制发送Fin

## 4.10 getpeername getsockname

场景：1、connent之后获取本机，2、未指定端口bind，3、通配符服务器，4、forkexec替换内存后（accept的地址数据被覆盖），只能通过这种方式