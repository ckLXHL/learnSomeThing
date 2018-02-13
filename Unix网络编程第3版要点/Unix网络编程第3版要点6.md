# IO多路复用

## 6.1

- 常用场景：
- 客户端监听多fd
- 客户端同时监听多socket
- 服务端同时监听listenfd和socketfd
- 服务端同时处理tcp和udp
- 多协议多服务服务端

## 6.2 

- IO模型
    - 阻塞
    - 非阻塞
    - IO多路复用
    - 信号量驱动 SIGIO
    - 异步IO

## 6.3 select

fd read ready条件：

* 接受buffer数据超过最低水平，默认1，使用SO_RCVLOWAT操作
* EOF
* listen fd连接完成
* socket error

fd write ready条件

* 写数据量超过传输层buffer最低水平，默认2048，使用SO_SNDLOWAT操作
* SIGPIPE连接半关闭
* connect连接成功或失败
* socket error
* udp随时写，因为没有连接

## 6.5 批量输出和缓冲

stdio和select配合必须非常小心，select只知道可读状态，不知道读取会剩余数据

## 6.6 shutdown

close减少描述符引用数，造成四次挥手

使用shutdown，发送Fin，进行半关闭，不管socket引用数是否为0

SHUT_RD，socket读被关闭，缓冲区数据抛弃

SHUT_WR，缓冲区写数据被发送

## 6.9 pselect

pselect可以用来屏蔽一些信号量，防止select阻塞早成信号量丢失