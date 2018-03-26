# mysql二进制协议解析
> mysql使用TCP协议
>
> 在tcpdump获取的的IP包数据中，首先是IP协议头，其次是TCP协议头，之后就是TCP包体
>
> 以上协议头都可以通过协议头中的头长度字段准确分离
>
> mysql协议头紧跟着TCP协议头，是TCP包体中最初的数据
>
> 本文中数据是通过抓包方式得到，所以一些具体的内容可能会绑定具体的状态，请求方式，认证方式等。

## 1. mysql协议的数据包基本形式

- 包头
    - 3byte 表示mysql包体长度
    > mysql协议中称mysql包体为payload
    - 1byte 表示sequence_id序列id，从0开始
    > 例如：一次请求中，请求序列0，响应序列1
- 包体
    - 附加的mysql协议，根据数据包类型不同有各种字段
    - 实际的数据
> mysql 一个TCP包最多16M数据，多余的数据会分包

## 2. mysql协议阶段

- 连接阶段
    - Initial Handshake 初始化握手
    - Auth Phase 认证阶段
- 命令阶段
    - request
        - 命令类型
        - 命令
    - response
        - OK_Packet 命令成功
        - ERR_Packet 命令错误
        - Text Resultset 带数据response
        > 截止18-3-22 mysql版本8.0.0

## 3. mysql请求流程

### 3.1 握手阶段字段

> 这个阶段是建立TCP连接后第一个报文
>
> 由server 发送给 client
>
> 这个阶段可以看到TCP ACK包
>
> 以下字段通过实际抓包得到字段解析，官方文档上的条件字段解析不判断

类型+长度| [默认值]描述
-|-
1 byte           |  [0a] 协议版本
string[NULL]   | 服务器版本
4 byte            | connection id
string[8]     | 认证数据 part 1
1             | [00] 常零filler
2             | capability flags
1             | 字符集
2             | 状态位
2             | 扩展capability flags字段
1 | 认证数据长度，取决于标志位CLIENT_PLUGIN_AUTH
string[10]    | 保留字段，全0
string[len] |指定CLIENT_SECURE_CONNECTION标志，则代表认证数据 part 2。len = 认证数据长度 - 8
string[NULL] | 指定CLIENT_PLUGIN_AUTH标志，代表 auth name, 例如“mysql_native_password”

### 3.2 握手响应-认证阶段
> 这个阶段是握手后客户端response的报文
>
> 由client 端发送给 server端
>
> 这个阶段同样可以看到TCP ACK包

- 认证完成后 Client会收到 Server端的 response OK 包。

- 从认证完成后第一个 response OK包开始，之后的TCP ACK包都会变成mysql的 response OK包，即序列号和响应状态都由mysql协议管理，网络上看不到单纯的TCP ACK包了

> 该段字段解析根据抓包得到的实际请求解析，mysql官方文档中的条件解析不涉及
 
类型+长度| [默认值]描述
-|-
4 byte            | capability flags
4 byte     | max-packet size
1             | character set
string[23]    | 全0保留字段
string[NULL]  | username
1             | length of auth-response，取决于标志CLIENT_SECURE_CONNECTION
string[len]   | auth-response，长度为length of auth-response字段
string[NULL] | database，取决于标志位CLIENT_CONNECT_WITH_DB
string[NULL]    | string[NUL]    auth plugin name，类似于 “mysql_native_password”，取决于标志位CLIENT_PLUGIN_AUTH

### 3.3 request "set names utf8"

这是一个用于解决乱码问题的请求，具体问题的原因如
[解决乱码](http://www.cnblogs.com/hongfei/archive/2011/12/29/set-names-utf8.html)。

### 3.4 request "command"

类型+长度| [默认值]描述
-|-
4byte | 通用mysql协议头
1byte          |    [03] COM_QUERY请求类型标志位，3表示通用请求
string[EOF]   | the query the server shall execute

### 3.5 response

### 3.6 request Quit

## 4 response详解

### 4.1 ERR_Packet

### 4.2 OK_Packet

### 4.3 ProtocolText::Resultset