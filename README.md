﻿# 神原，启动！！！

## 说明：由于本项目工程文件过大，故仅在GitHub上传一些关键部分，完整版请访问[网盘](https://pan.baidu.com/s/1wwSsaZyBPPIn0j_97vSL4g?pwd=vu7r)。


1.  \*\*大学\*\*工程专业程序设计范式期末大项目，选题《开放世界》
2.  小组成员与分工：
   * **2351269 黄一和**：
   * **2353608 顾亦周**：完成整体地图环境建设和任务场景搭建，帮助完善演示视频。
   * **2352048 夏浩博**：完成地图系统及敌人C++基类的设计，并完善了一部分功能（等级，金币，宝箱，踏板）
   * **2252964 张峻搏**：完成一部分C++类的设计（主角类，GameMode类，主角状态视图类，游戏状态类，火球类，障碍物类，可交互部件基类，重生点类，元素类）
3. 项目介绍：你说得对，但是《神原》是一款开放世界冒险作品，游戏发生在一片被称为“荒原”的幻想世界，在这里，玩家与他的敌人拥有名为SpiritPower的力量，导引元素之力。玩家将在自由的冒险中收获经验与金钱，提升等级，并去击败强敌，解放被邪恶势力侵占的城镇，逐步发掘“神原”的真相。


## 本项目对于本选题的功能完成情况：

### 1. 基础功能完成情况：

* 多样化地形：拥有平原，森林，湖泊，峡谷，城镇，盆地等地形。允许玩家自由探索。
* 高级地图：⽀持⼤地图的探索和动态放⼤、缩⼩视图功能；地图锚点⽀持快速传送，玩家可以在已解锁的锚点之间快速移动；玩家死亡后会自动在已解锁的最近处的重生点复活。
* ⻆⾊系统：⽀持玩家自由更换装备：剑或者魔法。⻆⾊可以通过经验升级，并达到6级后解锁新技能。
* 任务系统：包括一个主线任务：击败大恶魔，解放被侵占的城镇；以及多个支线任务：火球术练习；调查古代机关（踩踏板）；护送宝珠。以及玩家自由探索部分。这其中必然离不开战斗。
* 战斗系统：玩家与敌人拥有“火地风水”四大元素属性，并且实现了属性相克，且玩家通过组合按键可以释放组合技，提供丰富的战⽃体验。怪物具备⾼级AI，能根据玩家策略调整战⽃⾏为。
* 交互系统：玩家可以与环境中的多个元素进⾏互动，如点亮重生点，劈开障碍物，使用铁砧之箱（将金钱转化为经验）等。

### 2. 可选功能完成情况：

* 声⾳与⾳乐：拥有优美的背景音乐。并且在特定事件有相应的⾳效。
* 玩家死亡时记录玩家的一些比如等级最大生命值等状态，在已解锁的最近处的重生点处重生后不需要“从头再来”。
* 拥有暂停键，可以随时暂停并选择是否继续游戏。
* 实现了精美的开始界面。

### 3. 其他要求

* 使用了虚幻5.4.4
* 游戏界⾯⽀持⾼清分辨率。
* 实现了流畅的动画效果和⻆⾊互动。
* 保证能在Windows平台上流畅运行，
* 满足的C++特性有：类和多态，模板，函数和操作符的重载，异常检验，C++11或以上功能。

## 我们认为本项目所具有的其他加分项：

* 合理使用git和云盘
* 团队分工合理
* 团队实际人数少于推荐人数
* 源文件项目目录结构清晰
* 不会崩溃
* 结合Unreal特性，可视化蓝图代码编辑与C++代码相结合
* 完善而复杂的游戏机制设计
* UI设计合理，兼具美观和功能性，和游戏系统有良好交互
* 运行流畅
