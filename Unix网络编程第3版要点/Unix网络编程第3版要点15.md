# 15.Unix 域协议

## 15.1 介绍

1. 同host下域socket总是比TCP快
2. 域socket一般用于进程间传递文件描述符
3. 新版本域socket可以提供uid和gid，用于附加安全检查

提供stream socket类似于TCP，datagram socket 类似于UDP

域socket与正常文件地址绑定，IP不是正常文件地址

## 15.2 Unix域套接字地址结构

family变为了AF_LOCAL

bind会根据socket结构中的地址创建路径，已存在路径则bind失败

## 15.3 socketpair

全双工socket对

## 15.4 针对域socket的socket函数

1. bind创建的域socket的路径默认0777
2. 域socket路径应该是绝对路径
3. connect必须连接到已存在，且协议相同的socket，错误如下：
    - 路径不存在
    - 没有已经打开的socket连接到域socket路径
    - 协议不相同
4. 连接的权限类似于open write-only
5. stream类似于tcp，提供byte流，没有记录边界
6. socket listen队列满，立即返回ECONNREFUSED。与TCP不同，TCP无视SYN，连接方会再发送几次SYN。
7. datagram类似于UDP
8. datagram socket，在没有绑定的socket上，发送数据不会绑定path。UDP发送数据时会绑定临时端口。connect对于datagram也不会绑定path，和TCPUDP不同。意味着datagram socket需要主动bind。

## 15.7 描述符传递

使用fork后，子进程分享父进程文件描述符。

exec后，一般所有文件描述符依然存在。

使用域socket和sendmsg，传送一个描述符在两个不相干的进程。

传递文件描述符步骤：

1. 创建一个域socket
    - 父子关系，可以使用socketpair
2. 开启一个描述符
3. 使用msghdr结构中的msg_control对象传递描述符
    - 传递一个文件描述符等于描述符引用加1，知道对面接受为止
4. 接收方接收到一个描述符
    - 该描述符不一定和原始数字一样，代表对一个文件表的引用
    - 接受描述符不可以使用MSG_PEEK，该结果是不可peek的



