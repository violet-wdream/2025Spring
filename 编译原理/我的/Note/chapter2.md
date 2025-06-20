

# 词法分析器

字符流 to 词法记号流token

1. 将正确的单词（lexeme）识别为记号；

2. 剥去注释和空白（制表符、回车符、空格等分隔符）

3. 将各阶段产生的错误信息和源程序联系起来

4. 如果源语言支持宏，则宏的预处理可以在词法分析时实现

   注释、空白和宏可以在预处理模块中实现，也可以在词法分析时实现

## 词法记号/属性

词法记号（tokens）、模式（patterns）、单词（lexemes）

### 词法记号

token

<记号名，属性值> 二元组

记号名就是token class，比如运算符属于relation类，数字属于num类

属性值就是value，运算符没有属性值，数字属性值是本身

- 通常关键字和分隔符（标点符号）等可以一词一类；
- 标识符（变量）通常算做一类；
- 常数或常量可按数据类型分类
- 运算符可以一词一类，也可以若干个归为一类，如前例中的relation。

### 模式

描述一个词法记号的单词可能具有的形式

- 当词法记号是一个关键字时，它的模式就是组成这个关键字的字符序列；
- 当词法记号是一个标识符或其他，模式是一个更加复杂的结构，它可以和很多字符串匹配。

例如position和rate都能与id的模式匹配

### 单词

词法单元，它和某个词法记号的模式匹配，它是该记号的实例

![image-20250228094927471](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502280949523.png)

![image-20250228095157454](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502280951485.png)

### 词法错误

词法分析只能发现单词内部“拼写错误”

遇到fi时，词法分析器无法指出fi究竟是关键字if的误写还是一个未声明的函数标识符。

由于fi是标识符id的一个合法的单词，因此词法分析器必须向语法分析器返回这个id的单词fi。而让语法分析器去处理这个错误。

![image-20250228100328420](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502281003453.png)

1. 紧急方式：删除输入指针指向的若干字符（剩余输入的前缀），直到词法分析器能找到一个正确的记号为止
2. 错误修补：尝试以下一个变换能否变成一个合法单词
   - 删除多余字符
   - 插入遗漏字符
   - 用一个正确字符代替不正确字符
   - 交换相邻字符

## 串和语言

![image-20250228103709260](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502281037305.png)

字母表Σ：符号的有限集

- 二进制字母表（binary alphabet）{0，1}
- 英文字母表
- ASCII字符集
- Unicode字符集

串：字母表中符号的一个有穷序列；空串ε

0110是二进制字母表的一个串，abb是英文字母表的一个串

语言：字母表上的一个串集

- {ε, 0, 00, 000, …}，{…}

- 所有语法正确的C程序集合
- 所有语法正确的英语句子的集合

### 串运算

- 连接

  x=dog, y=house, xy=doghouse

  sε = εs = s

- 积

  s=ba，s^1^ =ba， s^2^ =baba， s^3^ =bababa

### 语言运算

- 并∪

  {aa,bb}∪{cc,dd} ={aa,bb,cc,dd}

- 连接（组合）

  {aa,bb} {cc,dd} ={aacc,aadd,bbcc,bbdd}

- 指数/幂

  {0，1}^3^ = {0,1}{0,1}{0,1} = {000,001,010,011,100,101,110,111}

- 闭包

  {0，1}^*^

  ={ε}∪{0,1}∪{00,01,10,11}∪{…}

  ={ε,0,1,00,01,10,11,…}

- 正闭包

  {0，1}^+^

  ={0,1}∪{00,01,10,11}∪{…}

  ={0,1,00,01,10,11,…}

  

  > L:  { A, B, …, Z, a, b, …, z },  D: { 0, 1, …, 9 }

  L∪D, LD, L^6^, L^*^, L(L ∪D )^*^, D^+^

  - L∪D 包含62个长度为1的串，每个串是一个字母/数字
  - LD 包含520个长度为2的串，每个串是一个字母后跟随一个数字
  - L^6^所有由6个字母组成的串的集合
  - L^*^所有字母串的集合，包含空串
  - L(L ∪D )^*^是所有以字母开头的、由字母和数位组成的串的集合
  - D^+^一个或多个数字组成的串的集合，不含空串

D^+^ = DD^*^

## 正规式/正规定义

![image-20250228115602266](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502281156313.png)

- 1-9开头，中间0-9随机组合，结尾0 2 4 6 8；并上个位偶数 0 2 4 6 8
- 非奇数（结尾是0）

![image-20250228115726093](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502281157139.png)



### 正规式

正规式是由最简单的正规式（ε，a），运用连接、|和*运算归纳定义的。

正规式r表示的语言为L(r)

![image-20250228110606127](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502281106217.png)

### 运算

闭包运算（*）优先级最高，且左结合；

连接运算优先级次之，且左结合；

或运算（|）优先级最低，且左结合

![image-20250228111228190](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502281112227.png)

### 正规式描述正规语言

![image-20250228111438366](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502281114409.png)

- 以aa或者ab结尾的a ，b组成的所有串
- 只有两个b的a，b组成的所有串

### 正规定义

![image-20250228114009623](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502281140674.png)



![image-20250228114432576](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502281144621.png)



![image-20250228114744168](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202502281147217.png)

## 定义速查

---

### **1. 字母表（Alphabet）**

• **定义**：符号的有限集合，通常用符号 **Σ** 表示。
•**示例**：
  • 二进制字母表：Σ = {0, 1}
  • 英文字母表：Σ = {a, b, c, ..., z}

---

### **2. 串（String）**
• **定义**：由字母表中的符号组成的有限序列。
• **关键术语**：
  • **空串**：长度为零的串，用符号 **ε** 表示。
  • **长度**：串中符号的个数，如 `abc` 的长度为 3。
• **示例**：
  • 二进制串：`0101`
  • 单词串：`hello`

---

### **3. 语言（Language）**
• **定义**：字母表 **Σ** 上所有可能的串的某个子集。
• **示例**：
  • 所有偶数长度的二进制串：{00, 01, 10, 11, 0000, ...}
  • 所有英文单词组成的集合。

<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503101051717.png" alt="image-20250310105140662" style="zoom: 50%;" />

<details>
    <summary>答案</summary>
    <img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503101052497.png" alt="image-20250310105247468" style="zoom: 67%;" />
</details>





---

### **4. 正规式（正则表达式，Regular Expression）**
• **定义**：一种描述正规集（正则语言）的符号表示方法，通过基本操作（选择、连接、闭包）组合而成。
• **基本操作**：
  • **选择（|）**：`a|b` 表示匹配 `a` 或 `b`。
  • **连接（·）**：`ab` 表示先匹配 `a`，再匹配 `b`。
  • **闭包（*）**：`a*` 表示匹配零个或多个 `a`。
• **示例**：
  • 匹配所有以 `a` 开头、以 `b` 结尾的串：`a(a|b)*b`
  • 匹配二进制偶数（以 `0` 结尾）：`(0|1)*0`

<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503101054233.png" alt="image-20250310105427191" style="zoom:50%;" />

<details>
    <summary>答案</summary>
<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503101057751.png" alt="image-20250310105717724" />
</details>







---

### **5. 正规集（正则语言，Regular Set）**
• **定义**：能用正规式描述的语言集合，属于形式语言中的 **类型-3 文法**（最受限的形式语言）。
• **性质**：
  • 能被有限自动机（DFA/NFA）识别。
  • 在并、连接、闭包运算下封闭。
• **示例**：
  • 所有由偶数个 `a` 组成的串：`(aa)*`
  • 所有包含连续两个 `1` 的二进制串：`(0|1)*11(0|1)*`

---

### **概念关系总结**
| 概念   | 定义         | 与其他概念的关系   |
| ------ | ------------ | ------------------ |
| 字母表 | 符号集合     | 生成串的基础       |
| 串     | 符号序列     | 语言的基本元素     |
| 语言   | 串的集合     | 由正规式或文法定义 |
| 正规式 | 符号表达式   | 描述正规集的工具   |
| 正规集 | 正则语言集合 | 由正规式生成       |



##  FA

<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503101106127.png" alt="image-20250310110633095" style="zoom:50%;" />

|       特性       |                        NFA                         |                DFA                 |
| :--------------: | :------------------------------------------------: | :--------------------------------: |
|   **状态转移**   | 同一输入符号可能对应**多个转移路径**（包括空转移） | 每个输入符号对应**唯一确定**的转移 |
|    **ε-转移**    |            允许（不消耗输入符号的转移）            |               不允许               |
|   **初始状态**   |              可以有一个或多个初始状态              |         仅一个确定初始状态         |
| **状态转移函数** |      定义：`Q × (Σ ∪ {ε}) → P(Q)`（幂集映射）      |   定义：`Q × Σ → Q`（确定映射）    |
|   **计算过程**   |       可能存在多条并行路径，需跟踪所有可能性       |      每一步路径唯一，无需回溯      |
|  **设计复杂度**  |                状态数较少，设计灵活                |        状态数较多，设计复杂        |

1. DFA任何状态都没有转换，NFA可以有。（最本质区别）
2. 对于任何状态s和任何输入符号a，DFA最多有一条标记为a的边离开s，而NFA可以有多条。

![image-20250310111344927](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503101113956.png)

## 正规式到NFA的变换（手写/Thompson算法）

### 手写

a^+^ = aa*

![image-20250319143537086](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503191435158.png)

就是一个“部分”认为是一个状态，比如(a|b)*ab，可以分为三个状态(a|b)\*,a,b

<details>
    <summary>识别aa*|bb*的NFA，手写形式</summary>
    <img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503101125927.png" alt="image-20250310112515894" style="zoom:50%;" />
</details>
<details>
    <summary>(a|b)*ab的NFA，手写形式</summary>
    <img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503101115250.png" alt="image-20250310111555221" style="zoom:50%;" />
</details>







### 转换表

横向排列状态，图中深度最大的为接收状态，可以为多个 ??

2是接受状态

表项：(0,a)从状态0开始出发，通过a，可以到达？{0,1}

![image-20250310111739418](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503101117444.png)



### Thompson算法

<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503101130176.png" alt="image-20250310113057145" style="zoom:50%;" />

`s|t`

<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503101132193.png" alt="image-20250310113227165" style="zoom:50%;" />

`st`

<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503101132925.png" alt="image-20250310113256900" style="zoom:50%;" />

`s*`

<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503101133832.png" alt="image-20250310113307803" style="zoom:50%;" />

<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503101156470.png" alt="image-20250310115628421" style="zoom: 67%;" />



<details>
    <summary>(a|b)*ab的分解</summary>
    <img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503101158252.png" referrerpolicy="no-referrer">
</details>
<details>
    <summary> (a | b) b*的NFA</summary>
    <img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503101200278.png" alt="image-20250310120001245" />
</details>




### 最长字串匹配原则

1. 当输入串的多个前缀与一个或多个模式匹配时，  总是选择最长的前缀进行匹配
2. 在到达某个终态之后，   只要输入带上还有符号，   FA就继续前进，   以便寻找尽可能长的匹配。

## NFA到DFA的变换（子集Subset构造算法）

### 子集构造法(Subset Construction)

DFA的转换表中不允许存在空集

1. 正规式手写形式/Thompson算法(更麻烦，但是更稳定)做出NFA状态转换图
2. 画出NFA对应转换表或者ε-closure方法求出状态划分
3. 然后画出DFA状态转换图

例： `(a|b)* ab `

<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503121053153.png" alt="image-20250312105301123" style="zoom:67%;" />

PPT图片NFA给错了，没有ε

<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503101203882.png" alt="image-20250310120354853" style="zoom:67%;" />

 **ε-closure 定义**：所有从 `S` 中状态出发，通过`零次或多次 ε`-转移能到达的所有状态的集合。

如下：ε-closure(s0) = {0,1,2}为DFA的起始状态

1. 求出DFA起始状态A = ε-closure(s0) 

2. 更新表项B = ε-closure(move(A,a))… C = ε-closure(move(A,b))，注意结果可能会重复

   move(A,a)表示从A中的状态出发，通过a可以到达？

   ε-closure(move(A,a)) = ε-closure({?})= { ? ? }





- ε-closure(s0) = {0,1,2} = A
- ε-closure(move(A,a)) = ε-closure({1,3}) = {1,2,3} = B
- ε-closure(move(A,b)) = ε-closure({1}) = {1,2} = C
- ε-closure(move(B,a)) = ε-closure({1,3}) = B
- ε-closure(move(B,b)) = ε-closure({1,4}) = {1,2,4} = D
- ε-closure(move(C,a)) = ε-closure({1,3}) = B
- ε-closure(move(C,b)) = ε-closure({1}) = C
- ε-closure(move(D,a)) = ε-closure({1,3}) = B
- ε-closure(move(D,b)) = ε-closure({1}) = C

|      | 输入符号 |      |
| ---- | :------- | ---- |
| 状态 | a        | b    |
| A    | B        | C    |
| B    | B        | D    |
| C    | B        | C    |
| D    | B        | C    |

如果用Thompson算法，最后得出来的表应该也是一样的。

<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503121108628.png" alt="image-20250312110835584" style="zoom:67%;" />

仔细观察，A C可以合并

<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503121108176.png" alt="image-20250312110851144" style="zoom:67%;" />

<details>
    <summary><img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503121111437.png" alt="image-20250312111104412" />		</summary>
    <img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503121111266.png" alt="image-20250312111132228" />
</details>


## 最简DFA



<details>
    <summary><img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503191455815.png" alt="image-20250319145505769" style="zoom:50%;" /></summary>
   <img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503191455332.png" alt="image-20250319145533299" style="zoom:50%;" /> </details>

将 S0 S1 S2 S3当成一类A1，S4 S5 S6当成另一类B1

S0和S1通过a的去向都是B1，通过b的去向都是A1，所以可以归为一类A2

S2 -a- A2  -b- B1 

S3 -a- A1 -b- B1

S2 S3单独划分为A3 A4

所以A1被划分为 ：{S0,S1}  {S2}  {S3}

B1同理划分为 {S4} {S5,S6}

|                  | a    | b    |
| ---------------- | ---- | ---- |
| A{S0,S1}         | E    | B    |
| B{S2}            | A    | D    |
| C{S3}            | C    | E    |
| D{S4}接受状态    | E    | B    |
| E{S5,S6}接受状态 | C    | A    |





DFA（Deterministic Finite Automaton，确定性有限自动机）的化简是指将一个DFA转换为一个状态数最少且功能等价的DFA。化简DFA的常用方法是**状态等价性划分**，也称为**Hopcroft算法**或**Moore算法**。以下是DFA化简的步骤：

---

### **DFA化简步骤**

1. **移除不可达状态**  
   • 从初始状态出发，遍历所有可达状态，移除那些无法从初始状态到达的状态。

2. **划分等价状态**  
   • 将状态划分为等价类。两个状态是等价的，如果对于所有输入符号，它们都转移到等价的状态，并且它们要么都是接受状态，要么都是非接受状态。
   • 初始划分：将所有接受状态划分为一个集合，所有非接受状态划分为另一个集合。
   • 逐步细化划分：检查每个集合中的状态是否对每个输入符号转移到相同的集合。如果不是，则进一步划分。

3. **合并等价状态**  
   • 将每个等价类中的所有状态合并为一个新的状态。

4. **构建最小化DFA**  
   • 使用合并后的状态重新构建DFA，并更新转移函数和接受状态。

---

### **示例**

 假设有一个DFA如下：

- 状态：\( \{A, B, C, D, E\} \)
- 输入符号：\( \{0, 1\} \)
- 初始状态：\( A \)
- 接受状态：\( \{C, D\} \)
- 转移函数：

$$
( A \xrightarrow{0} B ), ( A \xrightarrow{1} C )
  ( B \xrightarrow{0} B ), ( B \xrightarrow{1} D )
  ( C \xrightarrow{0} B ), ( C \xrightarrow{1} C )
  ( D \xrightarrow{0} B ), ( D \xrightarrow{1} D )
  ( E \xrightarrow{0} B ), ( E \xrightarrow{1} D )
$$

<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503121145753.png" alt="image-20250312114555717" style="zoom:67%;" />





**化简过程**：

1. **移除不可达状态**  
   • 状态 \( E \) 不可达，移除。

2. **初始划分**  
   • 接受状态：\( \{C, D\} \)
   • 非接受状态：\( \{A, B\} \)

3. **细化划分**  
   • 检查 \( \{C, D\} \)：
     ◦$$ ( C \xrightarrow{0} B ) 和 ( D \xrightarrow{0} B )$$ 都转移到非接受状态。
     ◦ $$( C \xrightarrow{1} C ) 和 ( D \xrightarrow{1} D ) $$都转移到接受状态。
     ◦ 因此，\( C \) 和 \( D \) 等价。
   • 检查 \( \{A, B\} \)：
     ◦$$ ( A \xrightarrow{0} B ) 和 ( B \xrightarrow{0} B ) $$都转移到非接受状态。
     ◦ $$( A \xrightarrow{1} C ) 和 ( B \xrightarrow{1} D ) $$都转移到接受状态。
     ◦ 因此，\( A \) 和 \( B \) 等价。

4. **合并等价状态**  
   • \( \{A, B\} \) 合并为 \( S_1 \)
   • \( \{C, D\} \) 合并为 \( S_2 \)

5. **构建最小化DFA**  
   • 状态：\( \{S_1, S_2\} \)
   • 输入符号：\( \{0, 1\} \)
   • 初始状态：\( S_1 \)
   • 接受状态：\( S_2 \)
   • 转移函数：
     ◦$$ ( S_1 \xrightarrow{0} S_1 ), ( S_1 \xrightarrow{1} S_2 )$$
     ◦$$ ( S_2 \xrightarrow{0} S_1 ), ( S_2 \xrightarrow{1} S_2 )$$

---

### **最终最小化DFA**

• 状态：\( \{S_1, S_2\} \)
• 输入符号：\( \{0, 1\} \)
• 初始状态：\( S_1 \)
• 接受状态：\( S_2 \)
• 转移函数：
$$
• ( S_1 \xrightarrow{0} S_1 )
  • ( S_1 \xrightarrow{1} S_2 )
  • ( S_2 \xrightarrow{0} S_1 )
  • ( S_2 \xrightarrow{1} S_2 )
$$
这个最小化DFA与原DFA功能等价，但状态数更少。
