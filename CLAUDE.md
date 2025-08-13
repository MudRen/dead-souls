# CLAUDE.md

这是Claude Code的中文翻译工作指南，用于指导如何将Dead Souls MUD游戏翻译为中文版本。

## 📋 翻译工作总览

### 🎯 翻译目标
- **保持原汁原味**：保留所有西方奇幻设定，仅做语言转换
- **专业游戏术语**：使用标准中文游戏术语
- **完整覆盖**：涵盖所有用户可见的英文文本

### 🔄 工作流程
1. **识别文本** → 2. **翻译内容** → 3. **测试验证** → 4. **git提交**

## 🏗️ 翻译技术方案

### 直接文件修改策略
由于项目使用git版本控制，我将直接修改原文件进行翻译：

#### 修改范围
- 所有 `.c` 文件中的 `SetShort()`, `SetLong()`, `SetDayLong()`, `SetNightLong()`
- 所有 `write()`, `tell_object()`, `SetHelp()` 中的文本
- 所有 `.txt` 帮助文件内容
- 保持所有函数名、变量名、玩家指令不变

#### 翻译优先级
1. **P1**: 系统消息和错误提示
2. **P2**: 玩家命令帮助文本  
3. **P3**: 房间和物品描述
4. **P4**: NPC对话和任务文本

## 📚 标准术语词典

### 核心术语对照
| 英文 | 中文 | 英文 | 中文 |
|---|---|---|---|
| **人称** | | **游戏机制** | |
| you | 你 | weapon | 武器 |
| your | 你的 | armor | 护甲 |
| **地点** | | health | 生命值 |
| room | 房间 | magic | 魔法值 |
| exit | 出口 | level | 等级 |
| **地名** | | experience | 经验值 |
| Praxis | 普瑞克斯 | Monument Square | 纪念碑广场 |
| Krasna Square | 克拉斯纳广场 | Centre Path | 中心大道 |
| Boc La Road | 博克拉路 | Nightmare | 梦魇 |
| **建筑设施** | | **人名** | |
| bank | 银行 | Clepius | 克勒庇乌斯 |
| post office | 邮局 | Dirk | 德克 |
| church | 教堂 | Lars | 拉尔斯 |
| hotel | 旅店 | 其他 | 音译 |
| Adventurer's Hall | 冒险者大厅 | monastery | 修道院 |
| town hall | 市政厅 | chapel | 小教堂 |
| **系统消息** | | **物品** | |
| What? | 什么？ | torch | 火把 |
| You can't do that. | 你无法这么做。 | flashlight | 手电筒 |
| It is too dark. | 这里太暗了。 | sign | 标牌 |
| You are hungry. | 你感到饥饿。 | manhole | 检修孔 |
| You are thirsty. | 你感到口渴。 | lamp | 路灯 |
| WARNING! | 警告！ | orc | 兽人 |
| HELPFUL HINTS | 有用提示 | container | 容器 |
| player handbook | 玩家手册 | quest | 任务 |
| class | 职业 | fighter | 战士 |
| mage | 法师 | spells | 法术 |
| healing | 治疗 | severed limbs | 断肢 |
| foreign objects | 异物 | historical artifact | 历史文物 |
| museum piece | 博物馆展品 | busy adventuring town | 繁忙冒险小镇 |
| **游戏名称** | | | |
| Dead Souls | 亡者之魂 | | |

### 术语管理

- **人名**: 音译 (如Clepius→克勒庇乌斯)
- **地名**: 音译+意译 (如Praxis→普瑞克斯)
- **机制**: 标准中文术语

## 🔧 翻译操作示例

### **1. 标准房间描述翻译**
```diff
// lib/domains/Praxis/bank.c
SetShort("the bank of praxis");
SetLong(
    "Welcome to the Bank of Praxis!\n"
    "The Bank of Praxis is a lovely looking building. Red carpeting "
    "covers the worn floor, and to the north there is a polished wooden "
    "counter. In the back of the bank there is a vault where all "
    "the town's deposits are kept. A sign by the teller details "
    "all commands. The exit to the bank is back south.");
↓
SetShort("普瑞克斯银行");
SetLong(
    "欢迎来到普瑞克斯银行！\n"
    "普瑞克斯银行是一栋漂亮的建筑。红色地毯覆盖着磨损的地板，"
    "北边有一个抛光的木制柜台。银行后面有一个金库，"
    "存放着城里所有的存款。出纳员旁边的标牌详细说明了"
    "所有命令。银行的出口在南边。");
```

### **2. NPC描述翻译**
```diff
// lib/domains/Praxis/bank.c
mon->SetShort("Bank guard");
mon->SetLong("A big, ugly ogre hired to guard the "
             "bank vault. He looks like he would love to bash "
             "your head in.");
↓
mon->SetShort("银行守卫");
mon->SetLong("一个被雇来保护银行金库的丑陋大食人魔。"
             "他看起来很想把你的头敲碎。");
```

### **3. 系统消息翻译**
```diff
// lib/secure/daemon/master.c
write_file(DIR_LOGS "/crashes",
        mud_name() + " crashed " + ctime(time()) + " with error " +
        err+".\n"+guilty_stack+"\n"+guilty_obs+"\n---\n");
message("system", "Reality implosion!!!  Everyone duck!!!", users());
↓
write_file(DIR_LOGS "/crashes",
        mud_name() + " 崩溃了 " + ctime(time()) + " 错误 " +
        err+".\n"+guilty_stack+"\n"+guilty_obs+"\n---\n");
message("system", "现实崩塌！！！大家快躲！！！", users());
```

### **4. 命令帮助翻译**
```diff
// lib/cmds/players/score.c
SetHelp("Syntax: score\n\n"
        "Displays information about your character.\n"
        "See also: stat, status, env");
↓
SetHelp("语法：score\n\n"
        "显示关于你角色的信息。\n"
        "另见：stat, status, env");
```

### **5. 特殊翻译场景处理**

#### **场景1：多选项选择**
**原始代码：**
```c
receive("Please choose an interesting gender (male, female, neutral, or none): \n");
```
**正确处理方式：**
```c
receive("请选择一个性别：男性(male)/女性(female)/中性(neutral)/无(none)\n");
```

#### **场景2：二元确认**
```diff
receive("Do you really wish to be known as " + cap + "? (y/n) \n");
↓
receive("你真的希望被称为" + cap + "吗？是(y)/否(n)\n");
```

#### **场景3：SetItems中的物品描述**
**原始代码：**
```c
SetItems( ([
    "sign":"A large sign on the road. To read it, 'read sign'.",
]) );
```
**正确处理方式：**
```c
SetItems( ([
    "sign":"路边的一个大标牌。要阅读它，请使用'read sign'命令。",
]) );
```
**重要规则：**
- **键名**（如"sign"）**不能翻译**，这是游戏指令
- **指令部分**（如'read sign'）**保持英文**，放在中文描述后的括号中
- **描述部分**可以完整翻译

#### **场景4：物品对象中的翻译边界**
**原始代码：**
```c
protected void create(){
    item::create();
    SetKeyName("clock tower");
    SetId( ({"great clock tower rising majestically into the sky", "great clock of the town", "clock", "tower", "structure", "architecture", "clocktower"}) );
    SetAdjectives( ({"large", "great", "majestic", "impressive", "proud"}) );
    SetShort("a great clock tower rising majestically into the sky");
    SetLong("This is a large clock tower, rising magestically into "+
            "the sky. Some forty feet up you can see the great clock of "+
            "the town, which can be read to know the local time.");
}
```
**正确处理方式：**
```c
protected void create(){
    item::create();
    SetKeyName("钟楼"); // ✅ 可以翻译
    SetId( ({"great clock tower rising majestically into the sky", "great clock of the town", "clock", "tower", "structure", "architecture", "clocktower"}) ); // ❌ 保持英文，这些是玩家look指令的识别词
    SetAdjectives( ({"large", "great", "majestic", "impressive", "proud"}) ); // ❌ 保持英文，这些是look指令的修饰词
    SetShort("一座雄伟高耸入云的大钟楼"); // ✅ 可以翻译
    SetLong("这是一座大钟楼，雄伟地高耸入云..."); // ✅ 可以翻译
}
```

#### **场景5：帮助文件翻译**
```diff
// lib/domains/town/txt/praxis_sign.txt
WARNING!

This area is Praxis. It is the ancient remains of the 
predecessor to Dead Souls, Nightmare 3.
↓
警告！

这片区域是普瑞克斯。它是亡者之魂的前身——
梦魇3号的古老遗迹。
```

### **6. 翻译边界速查表**

| 字段类型 | 是否翻译 | 示例 | 原因 |
|---|---|---|---|
| `SetShort/SetLong` | ✅ 翻译 | 房间描述 | 玩家可见文本 |
| `SetKeyName` | ✅ 翻译 | 物品名称 | 物品基础名称 |
| `SetId` | ❌ 保持英文 | `{"clock", "tower"}` | 玩家`look`指令的识别词 |
| `SetAdjectives` | ❌ 保持英文 | `{"large", "great"}` | 玩家`look`指令的修饰词 |
| 函数名/变量名 | ❌ 保持英文 | `create()`, `item` | 代码结构需要 |
| 文件路径 | ❌ 保持英文 | `SetExits`中的路径字符串 | 代码引用需要 |
| 游戏指令 | ❌ 保持英文 | `
**翻译边界说明：**
| 字段类型 | 是否翻译 | 原因 |
|---|---|---|
| `SetKeyName` | ✅ 翻译 | 物品基础名称 |
| `SetShort` | ✅ 翻译 | 物品简短描述 |
| `SetLong` | ✅ 翻译 | 物品详细描述 |
| `SetId` | ❌ 保持英文 | 玩家`look`指令的识别词 |
| `SetAdjectives` | ❌ 保持英文 | 玩家`look`指令的修饰词 |
| 函数名/变量名 | ❌ 保持英文 | 代码结构需要 |

#### **场景：房间连接路径**
**SetExits中的路径** - 这些是代码路径，**不要翻译**路径字符串，只翻译对应房间的描述文本。

## 🎯 翻译处理原则

| 场景类型 | 处理方法 | 示例 |
|---|---|---|
| **纯文本描述** | 完全翻译 | `"Welcome to the Bank"` → `"欢迎来到银行"` |
| **命令提示** | 中文描述 + 英文指令 | `"choose gender (male/female)"` → `"选择性别：男性(male)/女性(female)"` |
| **确认提示** | 中文问题 + 英文简答 | `"Are you 13? (y/n)"` → `"你是否年满13岁？是(y)/否(n)"` |
| **技术术语** | 保留英文 | `"MudOS"`, `"LPC"` 等技术术语保持原样 |
| **游戏名称** | 统一翻译 | `"Dead Souls"` → `"亡者之魂"` |
| **代码变量** | 不翻译 | `Player`, `Name`, `crypt()` 保持原样 |
| **游戏指令** | 不翻译 | `"read sign"`, `"look"` 等保持英文 |
| **物品识别词** | 不翻译 | `SetId`中的英文识别词保持英文 |
| **物品修饰词** | 不翻译 | `SetAdjectives`中的英文修饰词保持英文 |
| **文件路径** | 不翻译 | `SetExits`中的路径字符串保持英文 |
| **格式规则** | 玩家输入内容放()中，中文描述放括号外 | 避免双重括号嵌套 |

## 🧪 测试验证

### 快速测试流程
1. 启动游戏: `./run.sh`
2. 连接测试: `telnet localhost 6666`
3. 验证显示: 检查中文显示是否正常
4. 功能测试: 确保游戏功能不受影响

### 常见验证点
- [ ] 中文显示无乱码
- [ ] 文本长度不影响界面布局
- [ ] 特殊字符正确处理
- [ ] 游戏命令正常执行


## 📞 注意事项

1. **保持代码结构**：只修改文本字符串，不动函数逻辑
2. **术语一致**：使用本词典的术语标准
3. **长度控制**：避免翻译后文本过长影响界面
4. **实时测试**：每修改几个文件就测试一次
5. **版本记录**：详细git提交信息

---

## 📋 术语管理规则

### 🔍 术语发现与记录
**重要规则**：每遇到新的英文术语，必须立即更新以下术语表

### 📊 已发现术语记录

| 英文原名 | 中文翻译 | 首次发现位置 | 翻译日期 |
|----------|----------|--------------|----------|
| Monument Square | 纪念碑广场 | lib/domains/Praxis/square.c | 2025-08-13 |
| Krasna Square | 克拉斯纳广场 | lib/domains/Praxis/square.c | 2025-08-13 |
| Praxis | 普瑞克斯 | lib/domains/Praxis/square.c | 2025-08-13 |
| Centre Path | 中心大道 | lib/domains/Praxis/square.c | 2025-08-13 |
| Boc La Road | 博克拉路 | lib/domains/Praxis/square.c | 2025-08-13 |
| Nightmare | 梦魇 | lib/domains/Praxis/square.c | 2025-08-13 |
| adventurer's hall | 冒险者大厅 | lib/domains/Praxis/square.c | 2025-08-13 |
| Praxis Monastary | 普瑞克斯修道院 | lib/domains/Praxis/square.c | 2025-08-13 |
| bank | 银行 | lib/domains/Praxis/square.c | 2025-08-13 |
| post office | 邮局 | lib/domains/Praxis/square.c | 2025-08-13 |
| sign | 标牌 | lib/domains/Praxis/square.c | 2025-08-13 |
| busy adventuring town | 繁忙冒险小镇 | lib/domains/Praxis/square.c | 2025-08-13 |
| small yard | 小庭院 | lib/domains/Praxis/yard.c | 2025-08-13 |
| alley | 小巷 | lib/domains/Praxis/yard.c | 2025-08-13 |
| manhole | 检修孔 | lib/domains/Praxis/yard.c | 2025-08-13 |
| lamp | 路灯 | lib/domains/Praxis/yard.c | 2025-08-13 |
| church | 教堂 | lib/domains/Praxis/n_centre1.c | 2025-08-13 |
| hotel | 旅店 | lib/domains/Praxis/n_centre1.c | 2025-08-13 |
| stain glass window | 彩色玻璃窗 | lib/domains/Praxis/n_centre1.c | 2025-08-13 |
| Lars' Pub | 拉尔斯酒馆 | lib/domains/Praxis/s_centre1.c | 2025-08-13 |
| business district | 商业区 | lib/domains/Praxis/s_centre1.c | 2025-08-13 |
| Port of Praxis | 普瑞克斯港口 | lib/domains/Praxis/s_centre1.c | 2025-08-13 |
| monastery | 修道院 | lib/domains/Praxis/e_boc_la1.c | 2025-08-13 |
| town hall | 市政厅 | lib/domains/Praxis/e_boc_la1.c | 2025-08-13 |
| chapel | 小教堂 | lib/domains/Praxis/w_boc_la1.c | 2025-08-13 |
| WARNING! | 警告！ | lib/domains/town/txt/praxis_sign.txt | 2025-08-13 |
| historical artifact | 历史文物 | lib/domains/town/txt/praxis_sign.txt | 2025-08-13 |
| museum piece | 博物馆展品 | lib/domains/town/txt/praxis_sign.txt | 2025-08-13 |
| HELPFUL HINTS | 有用提示 | lib/domains/town/txt/hints_sign.txt | 2025-08-13 |
| player handbook | 玩家手册 | lib/domains/town/txt/hints_sign.txt | 2025-08-13 |
| container | 容器 | lib/domains/town/txt/hints_sign.txt | 2025-08-13 |
| two-handed combat | 双手武器战斗 | lib/domains/town/txt/hints_sign.txt | 2025-08-13 |
| two-weapon combat | 双武器战斗 | lib/domains/town/txt/hints_sign.txt | 2025-08-13 |
| wimpy command | wimpy命令 | lib/domains/town/txt/hints_sign.txt | 2025-08-13 |
| armor | 护甲 | lib/domains/town/txt/hints_sign.txt | 2025-08-13 |
| bank | 银行 | lib/domains/town/txt/hints_sign.txt | 2025-08-13 |
| Clepius | 克勒庇乌斯 | lib/domains/town/txt/hints_sign.txt | 治疗师 |
| Dirk | 德克 | lib/domains/town/txt/hints_sign.txt | 职业导师 |
| fighter | 战士 | lib/domains/town/txt/hints_sign.txt | 2025-08-13 |
| mage | 法师 | lib/domains/town/txt/hints_sign.txt | 2025-08-13 |
| spells | 法术 | lib/domains/town/txt/hints_sign.txt | 2025-08-13 |
| healing | 治疗 | lib/domains/town/txt/hints_sign.txt | 2025-08-13 |
| severed limbs | 断肢 | lib/domains/town/txt/hints_sign.txt | 2025-08-13 |
| foreign objects | 异物 | lib/domains/town/txt/hints_sign.txt | 2025-08-13 |
| Adventurer's Hall | 冒险者大厅 | lib/domains/town/txt/hints_sign.txt | 2025-08-13 |
| class | 职业 | lib/domains/town/txt/hints_sign.txt | 2025-08-13 |
| torch | 火把 | lib/domains/town/txt/hints_sign.txt | 2025-08-13 |
| flashlight | 手电筒 | lib/domains/town/txt/hints_sign.txt | 2025-08-13 |
| orc | 兽人 | lib/domains/town/txt/hints_sign.txt | 2025-08-13 |
| newbie mansion | 新手公馆 | lib/domains/town/txt/hints_sign.txt | 2025-08-13 |
| quest | 任务 | lib/domains/town/txt/hints_sign.txt | 2025-08-13 |
| Dead Souls | 亡者之魂 | lib/news/deadsouls | 2025-08-13 |

### 🔄 术语更新工作流
1. **发现新术语** → 在代码中发现新的英文术语
2. **确定翻译** → 根据上下文确定最准确的中文翻译
3. **检查一致性** → 确认是否已有相同术语的翻译
4. **更新术语表** → 将新术语添加到本表格
5. **应用到所有文件** → 确保所有相同术语统一翻译

### 📈 翻译进度追踪
翻译进度和短期任务目标请单独记录在独立的工作[日志文件](translation_progress.md)中。

### 🔍 术语一致性检查清单
- [ ] 每月扫描所有文件确保术语统一
- [ ] 新发现的术语立即添加到词典
- [x] 人名采用音译或标准意译（如Clepius→克勒庇乌斯，Dirk→德克）
- [x] 地名采用音译或标准意译（如Praxis→普瑞克斯，Monument Square→纪念碑广场）
- [x] 游戏机制术语使用标准中文

---

## 🏗️ 项目架构详解

### ⚙️ 运行时配置文件 `config.deadsouls`
FluffOS驱动的核心配置文件，定义：
- **游戏名称**: 亡者之魂
- **连接端口**: 6666(telnet) + 8888(websocket)
- **Mudlib目录**: `./lib/` - 游戏核心逻辑根目录

### 📁 关键目录结构

#### `lib/` - Mudlib主目录结构
```
lib/
├── secure/           # 系统安全核心【翻译禁区】
│   ├── daemon/       # 守护进程
│   │   └── master.c  # 主控制器(MudOS核心)
│   ├── sefun/        # 模拟外部函数
│   │   └── sefun.c   # 核心功能库
│   └── include/      # 全局头文件
│       └── global.h  # 全局定义文件
├── domains/          # 游戏世界区域【翻译重点】
│   ├── Praxis/       # 主城普瑞克斯
│   ├── town/         # 城镇区域
│   └── ...           # 其他区域
├── cmds/             # 命令系统
│   ├── players/      # 玩家命令【翻译重点】
│   ├── creators/     # 创建者命令
│   └── admins/       # 管理员命令
├── daemon/           # 游戏守护进程
├── include/          # 全局包含文件
│   ├── armor_types.h # 护甲类型定义
│   ├── damage_types.h # 伤害类型
│   ├── magic.h       # 魔法系统
│   └── ...           # 其他系统定义
├── std/              # 标准对象库
├── doc/              # 开发文档
├── news/             # 游戏公告【翻译重点】
└── www/              # Web界面
```

### 🎯 翻译工作核心区域

#### 1. **游戏世界文本** (`lib/domains/`)
- **Praxis主城**: `lib/domains/Praxis/` - 主要翻译目标
- **城镇区域**: `lib/domains/town/` - 包含标志牌和帮助文本
- **其他区域**: 各区域房间描述、NPC对话

#### 2. **系统消息** (`lib/secure/daemon/`)
- `master.c`: 主系统消息、连接提示、错误信息
- 各守护进程的系统反馈消息

#### 3. **命令帮助** (`lib/cmds/players/`)
- 所有玩家可用命令的帮助文本
- 使用方法说明和示例

#### 4. **公告文档** (`lib/news/`)
- 游戏欢迎信息、更新公告
- 玩家手册和帮助文档

#### 5. **Web界面** (`lib/www/`)
- 网页版游戏界面文本
- 帮助文档和FAQ

### 🔍 关键配置文件说明

| 配置项 | 文件路径 | 作用 |
|--------|----------|------|
| **Master对象** | `/secure/daemon/master.c` | 游戏主控制器 |
| **模拟函数** | `/secure/sefun/sefun.c` | 核心功能库 |
| **全局定义** | `/secure/include/global.h` | 全局常量和定义 |
| **命令路径** | `/cmds/players/` | 玩家可用命令 |
| **世界区域** | `/domains/Praxis/` | 主城区域 |
| **帮助文档** | `/domains/town/txt/` | 标志牌和帮助文本 |
| **系统公告** | `/news/` | 游戏公告和新闻 |

### ⚡ 快速翻译指南

#### 翻译顺序规则
**按玩家体验路径顺序翻译：**
1. **主文件本身**（如start.c）- 房间描述和基本设置
2. **SetInventory中的对象** - 房间内的物品
3. **AddItem中的对象** - 额外添加的物品
4. **SetExits中的连接房间** - 延伸路径

#### 翻译路径参考
使用以下命令快速定位翻译目标：

#### 常用翻译路径
```bash
# 系统消息翻译
grep -r "write(" lib/secure/daemon/ | grep -v ".git"

# 房间描述翻译
find lib/domains/ -name "*.c" -exec grep -l "SetLong\|SetShort" {} \;

# 帮助文本翻译
find lib/domains/town/txt/ -name "*.txt" 

# 命令帮助翻译
find lib/cmds/players/ -name "*.c" -exec grep -l "SetHelp\|write" {} \;
```

### 🧪 测试验证清单

#### 启动测试
1. **启动游戏**: `./run.sh`
2. **连接测试**: `telnet localhost 6666`
3. **中文显示**: 检查所有翻译文本显示正常
4. **功能验证**: 确保游戏功能不受影响

#### 验证项目
- [ ] 中文显示无乱码
- [ ] 文本长度不影响界面布局
- [ ] 特殊字符正确处理（引号、换行等）
- [ ] 游戏命令正常执行
- [ ] 系统消息正确显示
- [ ] 帮助文档可正常访问

