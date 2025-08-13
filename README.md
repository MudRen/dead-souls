# 亡者之魂 3.8.6 - FluffOS v2019

## 当前状态

- [X] 启动正常
- [X] 支持Websocket
- [ ] 不需要FluffOS 2019特殊配置
- [ ] 无警告或错误

## 如何测试和贡献

```
git clone --recurse-submodules https://github.com/fluffos/dead-souls.git
cd dead-souls
./build.sh
./run.sh
```

连接到 http://localhost:8888 开始游戏！

## 管理员设置

1. 编辑 `lib/secure/cfg/groups.cfg` 将 `mudren` 替换为你将要创建的管理员角色名（小写）
2. 通过浏览器连接到 http://localhost:8888 或使用mud客户端连接到本地端口6666
3. 选择创建者而非玩家
4. 设置角色名与上面使用的名称匹配
5. 开始游戏！

## 截图

![游戏界面](https://user-images.githubusercontent.com/1256464/71966839-2f444180-31b7-11ea-8cd4-f2fdf5f0cec7.png)

## 贡献

发送PR来修复问题！