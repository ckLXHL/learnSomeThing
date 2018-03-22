# mysql二进制协议解析
> mysql使用TCP协议
> 在tcpdump获取的的IP包数据中，首先是IP协议头，其次是TCP协议头，之后就是TCP包体
> 以上协议头都可以通过协议头中的头长度字段准确分离
> mysql协议头紧跟着TCP协议头，是TCP包体中最初的数据

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
     - 请求
        - 命令类型
        - 命令
    - 响应
        - OK_Packet 命令成功
        - ERR_Packet 命令错误
        > 截止18-3-22 mysql版本8.0.0

## 3. mysql包体数据解析

### 3.1 握手阶段字段

类型+长度| [默认值]描述
-|-
1 byte           |  [0a] 协议版本
string[NUL]   | 服务器版本
4 byte            | connection id
string[8]     | 认证数据 part 1
1             | [00] 常零filler
2             | capability flags
|附加的字段
1             | 字符集
2             | 状态位
2             | 扩展capability flags字段
1 | 认证数据长度或0，取决于标志位CLIENT_PLUGIN_AUTH
string[10]    | 保留字段，全0
string |指定CLIENT_SECURE_CONNECTION标志，则代表认证数据 part 2。指定CLIENT_PLUGIN_AUTH标志，则代表 auth name