# 语法分析

1. 语法规则: 就是用来描述记号流中的哪些记号如何能构成一个合法的语法结构的

2. 语法分析器（syntax analyzer）: 根据语法规则将记号流构成语法结构

   语法分析器简称分析器（parser）



## 上下文无关文法

每个正规语言都是一个上下文无关语言，反之则不成立。

### 上下文无关

句型中出现的产生式的左部非终结符可以在任何时候被替换，这种替换不依赖于句型中的其他符号（上下文）

### 写法

上下文无关文法（context-free grammar，CFG）G是四元组（V~T~ , V~N~ , S, P）

V~T~ :  终结符集合（非空，有限，在谈论编程语言时，终结符即词法记号名）

V~N~ :  非终结符集合（非空，有限）        V~T~  ∩ V~N~ = ∅

S :    开始符号，是一个非终结符。其定义的终结符串集就是文法定义的语言。

P :   产生式（production）有限集合，产生式形式 : 

​	     A → α

其中A∈V~N~,  α∈(V~T~ ∪ V~N~)* 

有时用::=代替→

S至少要出现在某产生式左部。



不引起歧义的前提下，G可以只写产生式。

<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503261936930.png" alt="image-20250326193651880" style="zoom:67%;" />

终结符：

1. 字母表中前面的小写字母：如a,b,c；
2. 粗体字符串：如 id 或 while，每个这样的字符串表示一个终结符；
3. 数字0,1,…,9;标点符号和运算符号：,  )  +  - 等。

非终结符

1. 在字母表中排在前面的大写字母：如A,B,C；
2. 字母S，通常表示开始符号；
3. 小写字母组成的名字，如expr 和stmt；
4. 有些教材中，当讨论程序设计语言的构造时，大写字母可以用于表示代表程序构造的非终结符，如表达式、项和因子的非终结符通常用E、T、F表示。

### 简化文法

<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503261955215.png" alt="image-20250326195535185" style="zoom:67%;" />



<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503262000458.png" alt="image-20250326200058431" style="zoom:67%;" />

### 推导

![image-20250326201144140](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503262011170.png)

=>是推导，->是文法产生式

E=>E+E读作“E推导出E+E”

A->α是文法的产生式

![image-20250326214510581](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503262145614.png)

1. L(G) ： 文法G产生的全部句子组成的集合称为G产生的语言
2. 句型α ： 如果S=>* α ， α可能含有非终结符
3. 两个文法产生同样的语言，则称这两个文法等价

### 最左推导/最右推导

![image-20250326224454243](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503262244272.png)

**最左推导**（逐步替换最左侧非终结符）

**最右推导**（逐步替换最右侧非终结符）



<details>
    <summary><img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503262315462.png" alt="image-20250326231506438" /></summary>
    <img src="C:/Users/86182/AppData/Roaming/Typora/typora-user-images/image-20250326231534881.png" alt="image-20250326231534881" /> </details>


### 分析树

<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503271050769.png" alt="image-20250327105006715" />



### 二义性

- 二义的文法：该文法存在某个句子，有不止一个最左（最右）推导。（两棵不同的分析树）
- 产生一个语言的所有文法都是二义时，这个语言才称为二义的

<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503271105020.png" alt="image-20250327110542981" style="zoom:67%;" />

### 正规式和上下文无关文法的比较



<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503271558524.png" alt="image-20250327155839438" style="zoom:67%;" />



## 语言和文法

### 消除二义性

解决优先级和结合性

1. 改变语言的语法
2. 制定规则，抛弃其中一棵分析树，即隐式规定符号的优先级和结合性
3. 将二义文法改成等价的非二义文法，即显式规定符号的优先级和结合性

id * id + id 改为(id * id) + id 

![image-20250327163027290](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503271630333.png)



<details>
    <summary><img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503271631776.png" alt="image-20250327163128748" /></summary>
    <img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503271631926.png" alt="image-20250327163146895" /> </details>



优先级： or < and < not  

E -> E or T | T

T -> T and F | F

F -> not F | true | false | (S)



<details>
    <summary><img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503271639409.png" alt="image-20250327163910375" /></summary>
    <img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503271639218.png" alt="image-20250327163922188" /> </details>

优先级：+ = - < * = / < ()

E -> E+T | E-T | T

T -> T*F | T/F | F

F-> (E) | id 

### “悬空else”文法

<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503271651739.png" alt="image-20250327165140702" />

1. 悬空else问题出现的原因是then数量多于else，让else有多个可以结合的then。在二义文法中，由于选哪两个then、else配对都可以，故会引起出现二义的情况。
2. 规定else和左边最接近的还没有配对的then相配对。
3. 把stmt分成配对的（MS）和不配对的（UMS）两种条件语句
4. 在MS里，then和else个数相等且匹配（包括0个）在UMS里，then个数比else多

stmt -> MS | UMS 

MS -> if expr then MS else MS | other

UMS -> if expr then stmt | if expr then MS else UMS

> 用无二义文法重写句型：   if expr then if expr then stmt else stmt
>
> 用新的文法从stmt推导到上述句型：
>
> stmt 
>
> =>两个then 一个else  UMS
>
> => 如果选if expr then MS else UMS，这里就是将 if expr then stmt认为是MS，显然不正确，因为then和else的数量不匹配
>
> 所以 if expr then stmt
>
> =>if expr then   MS
>
> =>if expr then  if expr then MS else MS
>
> 



### 消除左递归

<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503271913318.png" alt="image-20250327191357266"  />

自上而下的分析不能用于左递归文法，所以需要消除左递归
$$
A -> Aα | β \space \space 消除左递归
\\
A -> βA’ 
\\
A’ -> αA' | ε
$$



> 为什么A -> Aα | β是左递归的？
>
> A => Aα => Aαα => Aααα => …
>
> 式子的左部可以不断推导

$$
E -> E + T | T 
\\ 
T -> T * F | F
$$


$$
消除左递归
\\
E -> TE'
\\E' -> +TE'|ε
\\T -> FT'
\\T'-> *FT'|ε
$$

<details>
    <summary><img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503271914528.png" alt="image-20250327191432495" /></summary>
    <img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503271917354.png" alt="image-20250327191745308" /> </details>





<details>
    <summary><img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503271920958.png" alt="image-20250327192013922" /></summary>
    <img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503271920877.png" alt="image-20250327192047840" /> </details>



![image-20250327193826318](https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503271938358.png)

###  消除无用符号/产生式

<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503271941086.png" alt="image-20250327194145036" />



### 提左因子

$$
A -> αβ_1 | αβ_2
\\提左因子
\\
A -> αA'
\\
A' -> β_1 | β_2
$$



<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503271953768.png" alt="image-20250327195333727" style="zoom: 80%;" />



<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503272001433.png" alt="image-20250327200103386" style="zoom:80%;" />

继续消除左递归

<img src="https://cdn.jsdelivr.net/gh/violet-wdream/Drawio/PNG/202503272004629.png" alt="image-20250327200450593"  />

## 语法分析方法



### 自上而下分析

### 自下而上分析



## 语法分析器的自动生成



LL(k)

LR(k)、SLR、LALR