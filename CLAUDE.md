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
- 保持所有函数名、变量名不变

#### 翻译优先级
1. **P1**: 系统消息和错误提示
2. **P2**: 玩家命令帮助文本  
3. **P3**: 房间和物品描述
4. **P4**: NPC对话和任务文本

## 📚 标准化术语词典

### 核心术语对照
| 英文 | 中文 | 使用场景 |
|------|------|----------|
| you | 你 | 第二人称 |
| your | 你的 | 所有格 |
| room | 房间 | 地点描述 |
| exit | 出口 | 方向指示 |
| weapon | 武器 | 装备描述 |
| armor | 护甲 | 装备描述 |
| health | 生命值 | 属性显示 |
| magic | 魔法值 | 属性显示 |
| level | 等级 | 角色属性 |
| experience | 经验值 | 角色属性 |

### 地名翻译
| 英文原名 | 中文翻译 | 说明 |
|----------|----------|------|
| Praxis | 普瑞克斯 | 主城，音译 |
| Monument Square | 纪念碑广场 | 意译 |
| Centre Path | 中心大道 | 意译 |
| Boc La Road | 博克拉路 | 音译+意译 |
| Nightmare | 梦魇 | 世界名称 |

### 系统消息翻译
| 英文原文 | 中文翻译 |
|----------|----------|
| What? | 什么？ |
| You can't do that. | 你无法这么做。 |
| It is too dark. | 这里太暗了。 |
| You are hungry. | 你感到饥饿。 |
| You are thirsty. | 你感到口渴。 |

## 🔧 实际翻译操作

### 文件修改示例
```diff
// 修改前
SetShort("Monument Square");
SetLong("You are in Monument Square, once known as Krasna Square...");

// 修改后  
SetShort("纪念碑广场");
SetLong("你位于纪念碑广场，这里曾被称为克拉斯纳广场...");
```

### 批量修改命令
```bash
# 查找并替换房间描述
find . -name "*.c" -exec sed -i 's/SetShort("Monument Square");/SetShort("纪念碑广场");/g' {} \;

# 查找系统消息
grep -r "write(" lib/ | grep -v ".git"
```

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

## 📊 翻译进度追踪

### 当前进度
- [x] 制定翻译方案
- [ ] 系统消息翻译 (0/500)
- [ ] 房间描述翻译 (0/1000)  
- [ ] 物品描述翻译 (0/800)
- [ ] 帮助文本翻译 (0/300)
- [ ] 集成测试验证

### 每日任务
- 翻译50-100条文本
- 运行测试验证
- 提交git变更
- 更新进度记录

## 🚀 立即开始

### 第一步：翻译核心系统消息
从以下文件开始：
- `lib/secure/daemon/master.c` - 主系统消息
- `lib/cmds/players/` - 玩家命令帮助
- `lib/domains/Praxis/` - 主城房间描述

### 使用工具
- **翻译工具**: 直接文本编辑器修改
- **测试工具**: `./run.sh` 启动后立即验证
- **版本控制**: git commit -m "翻译XXX内容"

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
#### 已完成翻译的术语
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
| Dead Souls Object Library | 亡者之魂对象库 | lib/news/welcome | 2025-08-13 |
| The Dead Souls Development and Demo MUD | 亡者之魂开发与演示MUD | lib/news/deadsouls | 2025-08-13 |

#### 新增术语发现记录表
| 英文术语 | 中文翻译 | 使用场景 | 备注 |
|----------|----------|----------|------|
|  |  |  |  |

### 🔄 术语更新工作流
1. **发现新术语** → 在代码中发现新的英文术语
2. **确定翻译** → 根据上下文确定最准确的中文翻译
3. **检查一致性** → 确认是否已有相同术语的翻译
4. **更新术语表** → 将新术语添加到本表格
5. **应用到所有文件** → 确保所有相同术语统一翻译

### ⚡ 术语发现工具
```bash
# 查找未翻译的英文术语
grep -r "[A-Za-z][A-Za-z ]*" lib/ --include="*.c" --include="*.txt" | \
grep -v "#include\|inherit\|object\|string\|int\|void\|function\|return\|if\|else\|while\|for" | \
grep -v ".git"

# 检查术语一致性
grep -r "英文术语" lib/ --include="*.c" --include="*.txt"
```

### 📈 翻译进度追踪
#### 已完成翻译统计
- **房间描述**: 6/1000 (纪念碑广场、庭院、中心大道北/南段、博克拉路东/西段)
- **帮助文本**: 2/300 (praxis_sign.txt, hints_sign.txt)
- **系统消息**: 1/500 (look命令)
- **物品描述**: 0/800

#### 当前工作文件
- ✅ lib/domains/Praxis/square.c
- ✅ lib/domains/town/txt/praxis_sign.txt
- ✅ lib/domains/town/txt/hints_sign.txt
- 🔄 下一个目标: lib/domains/Praxis/yard.c

### 🔍 术语一致性检查清单
- [ ] 每月扫描所有文件确保术语统一
- [ ] 新发现的术语立即添加到词典
- [x] 人名采用音译或标准意译（如Clepius→克勒庇乌斯，Dirk→德克）
- [x] 地名采用音译或标准意译（如Praxis→普瑞克斯，Monument Square→纪念碑广场）
- [x] 游戏机制术语使用标准中文

**继续工作！** 保持术语一致性，每发现新术语请立即更新上表。