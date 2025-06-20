![image-20250226145646115](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502261456260.png)

![img](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502271050693.png)



# 导论



1. 编译： 高级语言 翻译成 机器语言/汇编语言

2. 编译器的一项重要工作是记录并收集标识符及其各种属性，以提供标识符存储分配、类型、作用域等信息
3. 编译器划分前端后端有利于移植及简化编译器的设计



## GCC/LLVM/CLANG





![image-20250226150055938](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502261500984.png)

预处理 > 编译 > 汇编 > 链接  



## 编译器过程



![image-20250226151141823](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502261511869.png)

### 词法分析 （字符流 to 记号流token）

1. 从左到右扫描源程序字符，识别出各个单词，确定单词类型
2. 将识别的单词转化为统一的**机内表示** ——词法记号  token: <记号名, 属性值>

![image-20250226151831242](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502261518276.png)



![image-20250226185152236](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502261851322.png)



### 语法分析 （记号流token to 语法树）

语法分析器(parser)从词法分析器输出的token序列中识别出各类短语，并构造语法树(syntax tree)

可以由token语句解析为分析树，再将分析树转化为语法树

#### 分析树

![image-20250226185831745](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502261858779.png)

#### 语法树

![image-20250226190101880](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502261901909.png)







### 语义分析 （语法树 to 语法树）

1. 收集标识符的属性信息
2. 类型检查
3. 语义一致性检查
4. 隐式类型转换

![image-20250226190833253](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502261908288.png)

### 中间代码生成

![image-20250226213418241](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502262134287.png)

### 代码优化（独立于目标机器）

### 代码生成

### 代码优化（依赖于目标机器）

### 符号表管理

符号表为每个标识符保存一个**记录的数据结构**，记录的域是标识符的各个属性。

该数据结构应允许编译器迅速找到一个名字的记录并读取和存储数据。

![image-20250227102719913](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502271027940.png)

## 阶段分组

![image-20250226151141823](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502271057118.png)

## 翻译器/编译器/解释器

![image-20250227103232278](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502271032328.png)



![image-20250227103343300](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502271033329.png)

> 为什么解释器的效率比编译器要低？

1. 编译器生成目标程序，运行时直接执行机器指令。
2. 解释器不会生成目标程序，而是将源代码直接在目标机器上运行。
3. 执行时，解释器读取一句源代码之后，先进行词法分析和语法分析，再将源代码转换为解释器能够执行的中间代码（字节码BYTECODE），最后，由解释器将中间代码解释为可执行的机器指令。
4. 由于解释器运行时步骤更加繁琐，所以解释型语言的执行效率会低一些。
