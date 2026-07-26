# Dead Souls MUD 中文汉化指南

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

## 文件结构

```
lib/
├── domains/          # 游戏世界区域（主要汉化目标）
│   ├── town/        # 城镇区域
│   ├── Ylsrim/      # 伊斯林姆区域
│   ├── amigara/     # 阿米加拉区域
│   ├── cave/        # 洞穴区域
│   └── ...
├── realms/          # 创作者区域
├── secure/          # 核心系统（选择性汉化）
├── std/             # 标准对象模板
└── www/             # Web界面
```

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

## 汉化进度追踪

- [ ] domains/town/ - 城镇区域
- [ ] domains/Ylsrim/ - 伊斯林姆区域
- [ ] domains/amigara/ - 阿米加拉区域
- [ ] domains/cave/ - 洞穴区域
- [ ] domains/campus/ - 校园区
- [ ] domains/learning/ - 学习区
- [ ] domains/default/ - 默认区域
- [ ] domains/examples/ - 示例区域
- [ ] domains/Praxis/ - 普拉克西斯区域
- [ ] secure/ - 核心系统
- [ ] std/ - 标准对象
- [ ] realms/ - 创作者区域
- [ ] doc/help/ - 帮助文档

## 注意事项

1. **保持代码功能** - 只修改字符串内容，不改变代码逻辑
2. **保留英文标识符** - SetKeyName(), SetId() 中的英文名用于程序匹配
3. **测试汉化结果** - 每个区域汉化后测试功能正常
4. **备份原文件** - 使用git跟踪所有修改
5. **分批处理** - 按目录分批汉化，避免遗漏

## 批量汉化命令示例

```bash
# 查找所有包含SetShort的文件
grep -r "SetShort" lib/domains/town/

# 查找所有包含SetLong的文件
grep -r "SetLong" lib/domains/town/
```
