# tcpdump抓包

>fastdev2.0的开发依赖于tcpdump的抓包，而不是1.0时的代理转发
>切换到tcpdump抓包的原因在于需要在录制流量的时候就解析请求数据，生成相应的特征用于分析
>tcpdump抓包需要匹配表达式

## 1. 命令行选项
- 默认选项
    - 取编号最小的网络接口 i
    - 监听获取所有数据包 c
    - 默认抓包大小 s
    - 解析主机名和端口
    - 默认出入包都抓
    - 只打印包头，不打印数据
- -i 用于指定网络接口，
- -s len 指定抓到包的大小
- -n不解析主机名
- -nn 不解析主机名和端口
- -P 指定入包还是出包
- -vvv 随v增多打印更多信息
- -X 打印包头部数据
- -q 快速打印，较少信息
- -A 打印ASCII的包数据

## 2. tcpdump表达式

- type类型指定 host/net/port/portrange
- dir入出包指定 src/dst/src or dst/src and dst
- proto协议指定 tcp/udp/arp/ip/ether/icmp
- 表达式基本格式为 proto dir type ID
- 表达式可以用 and  &&  or  ||  not  ! 连接
> 例如 host foo and not port ftp and not port ftp-data

> 表示 

> 主机为foo且端口不是ftp(端口21)和ftp-data(端口20)的包

## 3. tcpdump抓包mysql请求