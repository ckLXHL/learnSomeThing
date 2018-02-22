# 名字地址转换

## 11.2 域名系统

recourse record RRs资源记录
- A host->IPv4
- AAAA host->IPv6
- PTR 
    - IPv4 数字表示加 .in-addr.arpa
    - IPv6 16进制表示加 .ip6.arpa
- MX 区分mail地址
- CNAME 常用服务名

本地的域名服务配置 /etc/resolv.conf

本地直接获取的域名 /etc/hosts

## 11.3 gethostbyname

只能用于IPv4，建议使用getaddrinfo替换，或者使用gethostbyname2函数（gethostbyname2被标记为deprecated

不设置errno，而是设置h_errno全局变量

## 11.5 getservbyname 和 getservbyport

port和服务之间的映射

可以通过/etc/services查看

## 11.6 getaddrinfo

能够同时解析 host->addr 和 service->port，返回的sockaddr可以直接用，包装了socket addr的细节。

参数hostname，service可以是名称也可以是数字表示的地址，hints指定一些选项（类似于指定hostname的形式，指定UDP或TCP等），返回地址的链表。

端口53是域名服务

gai_strerror 从getaddrinfo错误码获取错误信息

freeaddrinfo 释放getaddrinfo获得的链表

## 11.9 getaddrinfo IPv6

- getaddrinfo同时处理两种输入： socket address struct 和 RR的类型
- hints可以指定搜索的协议
- AF_UNSPEC会造成，一个拥有AAAA类型RR和A类型RR的host，sockaddr_in和sockaddr_in6会一起返回，但这没有什么意义
- 指定AI_PASSIVE同时未指定hostname，返回一个通配符地址
- hint参数中的结构体成员ai_family指定了返回地址的类型
- hostname参数可以是IPv6的16进制表示，也可以是Ipv4的点分表示，有效性由调用者保证

## 11.17 getnameinfo

从sock_addr->getnameinfo

参数host，serv字符串由调用者分配内存，后面跟着的参数len==0时表示不返回host或serv

- NI_DGRAM 指定UDP
- NI_NAMEREQD 域名不可解析，返回非0错误码
- NI_NOFQDN 返回域名的第一个.之前的域

标志用或连接

## 11.18 可重入函数

不可重入：在并发或触发信号量时，由于共用一个变量，造成结果被篡改

gethostbyname，gethostbyaddr，getservbyname，getservbyport 不可重入，因为共用一个static结构体变量

inet_pton和inet_ntop总是可重入

inet_ntoa一般不可重入，一些系统提供线程专用可重入版本

getaddrinfo要看实现，底层是否使用了可重入版本的gethostbyname等。

getnameinfo要看实现，底层是否使用了可重入版本的gethostbyaddr等。

errno每个进程一份，系统调用返回非0错误，errno会存储错误码

## 11.19 gethostbyname_r 和 gethostbyaddr_r 

可重入的版本

缺点在于自己需要管理内存，参数的增多（buf，buflen，h_errnop），返回值需要手动释放。

优点，可重入，错误码变量唯一。

## 11.20 废弃的IPv6 地址解析函数

- RES_USE_INET6，全局变量，使gethostbyname先查找AAAA类型的记录，没有AAAA记录才查找A记录，导致IPv6和IPv4只能返回一个。
- gethostbyname2 使用FAMILY控制IPv4或6
- getipnodebynamne 被getaddrinfo和getnameinfo取代


## 11.21

- 使用 getXXXent系列函数通过读取信息文件，获取每一行定义的信息
- 使用 setXXXent系列函数允许对域名服务器的查询进行控制（参数true使用TCP连接，保持socket连接，参数false，使用UDP连接）
- 使用 endXXXend系列函数关闭与域名服务的连接

信息 | 文件 | 数据结构 | 键值查找函数
- | - | - | :-:
host | /etc/hosts | hostent | gethostbyaddr, gethostbyname
network | /etc/networks | netent | getnetbyaddr, getnetbyname
protocol | /etc/protocols | protoent | getprotobyname, getprotobynumber
service | /etc/services | servent | getservbyname, getservbyport