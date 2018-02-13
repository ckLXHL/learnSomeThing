# Unix网路编程第3版要点

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