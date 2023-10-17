Entity 表示游戏中的对象，Scene 包含多个 Entity，Layer 是对 Entity 的逻辑分组，LayerStack 管理多个 Layer，Window 表示应用程序的窗口，Application 是整个游戏的入口点，持有一个 Window 和 LayerStack。这些类之间形成了一种组织结构，通过调用各自的 Update 函数来执行相应的逻辑。
