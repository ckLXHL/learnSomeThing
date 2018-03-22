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

1              [0a] protocol version
string[NUL]    server version
4              connection id
string[8]      auth-plugin-data-part-1
1              [00] filler
2              capability flags (lower 2 bytes)
  if more data in the packet:
1              character set
2              status flags
2              capability flags (upper 2 bytes)
  if capabilities & CLIENT_PLUGIN_AUTH {
1              length of auth-plugin-data
  } else {
1              [00]
  }
string[10]     reserved (all [00])
  if capabilities & CLIENT_SECURE_CONNECTION {
string[$len]   auth-plugin-data-part-2 ($len=MAX(13, length of auth-plugin-data - 8))
  if capabilities & CLIENT_PLUGIN_AUTH {
string[NUL]    auth-plugin name
  }