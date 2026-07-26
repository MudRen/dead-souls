# Dead Souls MUD 中文汉化指南

## 汉化状态：✅ 已完成

**分支**: chinese
**统计**: 1,392 个文件已修改，9,299 行插入，11,211 行删除

## 汉化原则

### 需要汉化的内容
1. **房间描述** - SetShort(), SetLong() 中的文本
2. **物品描述** - SetShort(), SetLong() 中的文本
3. **NPC描述** - SetShort(), SetLong() 中的文本
4. **消息文本** - write(), eventPrint() 等函数中的字符串
5. **帮助文档** - doc/help/ 目录下的文件
6. **系统提示** - 错误消息、系统通知等

### 不需要汉化的内容
1. **指令名称** - north, south, look, get, drop 等动词
2. **标识符** - SetKeyName(), SetId() 中的英文键名（保留用于程序逻辑）
3. **文件路径** - 所有文件路径保持不变
4. **变量名/函数名** - 程序代码中的标识符
5. **颜色代码** - %^RED%^, %^GREEN%^ 等格式代码

## 汉化示例

### 原文
```c
SetShort("The Village Church");
SetLong("Decades ago this tiny, one-room church was the center "
        "of activity in the village...");
```

### 汉化后
```c
SetShort("村庄教堂");
SetLong("几十年前，这座小小的单间教堂曾是村庄活动的中心。"
        "随着村庄的繁荣和世俗化，村民们的参与越来越少，"
        "直到它变得破旧废弃，正如你所见。这个地方"
        "布满了蛛网和灰尘，但没有遭到破坏。只是被尘封遗忘。"
        "西村路在南边，西墙上看起来像是一个电梯。"
        "\n%^GREEN%^电梯旁边有一个按钮。%^RESET%^");
```

## 已完成的汉化区域

| 区域 | 提交 | 状态 |
|------|------|------|
| domains/town | `dc0fea9` | ✅ 完成 |
| domains/amigara | `461525e` | ✅ 完成 |
| domains/cave | `1126c90` | ✅ 完成 |
| domains/campus | `fce3980` | ✅ 完成 |
| domains/default | `9f60e43` | ✅ 完成 |
| domains/Ylsrim | `c9033ea` | ✅ 完成 |
| domains/Praxis | `fb8b23c` | ✅ 完成 |
| domains/learning | `0ad2bfc` | ✅ 完成 |
| domains/examples | `2cf0dd9` | ✅ 完成 |
| std | `06dda5b` | ✅ 完成 |
| realms | `57cb45e` | ✅ 完成 |
| estates | `b227504` | ✅ 完成 |
| doc/help | `9a257e7` | ✅ 完成 |
| verbs | `0d12395` | ✅ 完成 |
| powers/shadows | `66899a9` | ✅ 完成 |
| 核心系统消息 | `8f5917f` | ✅ 完成 |
| 剩余lib目录 | `0d50274` | ✅ 完成 |

## 使用方法

```bash
# 切换到中文分支
git checkout chinese

# 编译
./build.sh

# 启动
./run.sh

# 访问
# Web: http://localhost:5555
# Telnet: localhost:6666
```

## 注意事项

1. **保持代码功能** - 只修改字符串内容，不改变代码逻辑
2. **保留英文标识符** - SetKeyName(), SetId() 中的英文名用于程序匹配
3. **测试汉化结果** - 每个区域汉化后测试功能正常
4. **备份原文件** - 使用git跟踪所有修改
5. **分批处理** - 按目录分批汉化，避免遗漏
