# 5 TCP示例

## 5.6 正常启动
客户端read_chan阻塞于标准IO，服务器tcp_data_wai阻塞于socketIO，服务器wait_for_connet阻塞于accept或connect

几个tcp进程stat是S，即sleep

## 5.7正常终止

客户端：客户端：FIN_WAIT_1 -> FIN_WAIT_2->TIME_WAIT

服务器：CLOSE_WAIT->LAST_ACK->SIGCHLD子进程进入僵尸状态

## 5.8 POSIX信号处理

SIGKILL和SIGSTOP无法被捕获

SIG_IGN设置忽视信号，SIG_DFL设置默认行为

signal函数比较简单，但由于历史比POSIX标准早，各个系统的一些实现不一致。

sigaction是推荐的方式

sa_mask=0保证没有额外的信号会被捕获

SIGALRM一般表示IO超时中断，一般是一种功能中断

SA_RESTART表示内核自动重启被信号中断的系统调用

系统默认不对信号量queue，一段时间只会下发一次

使用sa_mask选择性过滤系统信号量

## 5.9

僵尸进程状态：父进程可以在稍晚一点的时间后获取子进程信息，包括进程id，结束状态，资源信息

僵尸进程ppid变为1，等待1删除它们

信号导致系统调用中断需要考虑（accept，read，write，select，open等），返回EINTER。connect不能重启

SA_RESTART自动重启中断的系统调用，在一些系统中没有效果


## 5.10 wait和waitpid

获取结束子进程的状态

信号捕获中处理结束子进程，需要循环处理，保证一次捕获信号量可以处理所有并发的信号。

同时设置信号处理中获取子进程状态的函数非阻塞用于退出。

使用waitpid可以设置非阻塞，wait不行。

## 5.11 accept前连接RST

使用POSIX标准ECONNABORTED处理，可以忽视错误，重新调用accept

## 5.12 服务器子进程中断

需要使用select，poll，epoll之类的同时监听多个fd

## 5.13 SIGPIPE

收到RST，继续写，触发SIGPIPE信号量 

## 5.14 服务器崩溃

一段时间后TCP超时，或发现不可到达错误

## 5.16 主机关机
shutdown主机，init进程向全部进程发SIGTERM，一段时间后发SIGKILL