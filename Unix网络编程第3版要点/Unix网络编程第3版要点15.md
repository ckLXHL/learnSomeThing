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
8. 