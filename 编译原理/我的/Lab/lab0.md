## FLEX编译Lex

```bash
cd /data/workspace/myshixun/exam1/
flex exam1.l 
gcc -o exam1 lex.yy.c -lfl
./exam1 exam1input.txt
```

- flex编译lex源程序（flex生成的c源程序名固定为lex.yy.c）

- gcc编译器编译flex生成的c源程序，并指定输出可执行文件的名字为exam1

  通用的编译命令为：` gcc [-o outfile] lex.yy.c -lfl`。-lfl是链接flex的库函数的，库函数中可能包含类似yywrap一类的标准函数。

  -o outfile是可选编译选项，该选项可将编译生成的可执行程序命名为outfile，如果不写该编译选项，默认情况下生成的可执行程序名为a.exe（linux下实际为a.out）

## BISON编译Yacc

```c
cd /data/workspace/myshixun/exam2/
bison exam2.y
gcc -o exam2 exam2.tab.c -ly
./exam2
```

- bison编译yacc源程序

- gcc编译器编译bison翻译器生成的c源程序

  -ly是链接bison的库函数的

## 联合编译Lex和Yacc

```c
cd /data/workspace/myshixun/exam3
flex exam3.l
bison -d exam3.y
gcc -c lex.yy.c
gcc -c exam3.tab.c
gcc -o exam3 exam3.tab.o lex.yy.o -ly
./exam3
```

- 编译lex源程序，得到lex.yy.c文件

- 编译bison源程序，得到exam3.tab.c文件

  参数-d表示除生成filename.tab.c以外，还将生成名为filename.tab.h的头文件

- 用gcc分别编译lex.yy.c和exam3.tab.c文件，得到链接文件lex.yy.o与exam3.tab.o

  之前的关卡并没有生成后缀名为.o的目标文件，而是直接从c文件生成了可执行文件。本关需要链接多个源文件，因此需要先生成若干目标文件，便于链接，编译选项-c表示仅把源代码编译为机器语言的目标代码，即.o文件

- gcc编译器链接所有目标文件，并指定输出可执行文件的名字为exam3

- 运行可执行文件exam3

## MAKEFILE

```makefile
target... : prerequisites ...
	command
	
target... : prerequisites ...
	command
	
 ...
```

command前面必须是一个tab键，而不能用空格代替

target是目标文件，它可以是object file（.o文件），也可以是可执行文件（例如.exe文件），还可以仅仅是一个标签；

prerequisites是要生成target所需要的文件的列表；

command是make真正执行的命令。

这实际上是一个文件的依赖关系，target这一个或多个的目标文件依赖于prerequisites中的文件，其生成规则定义在command中。也就是说，如果prerequisites中有一个以上的文件比target文件要新的话，command所定义的命令就会被执行。

makefile中的注释以#开头，#开头直到行末的部分为注释内容

```makefile
exam4.exe: exam4.tab.o lex.yy.o
    gcc -o exam4 exam4.tab.o lex.yy.o -ly
# 如果exam4还不存在，则要生成exam4文件，首先看exam4.tab.o和lex.yy.o是否存在，
# 如果不存在，则根据其他的makefile规则先生成这两文件，如果已存在，则检验他们是否是最新的文件，
# 如果不是的话要更新他们。然后运行命令gcc –o exam4 exam4.tab.o lex.yy.o –ly（这个命令将exam4.tab.o
# 和lex.yy.o链接起来）生成exam4。
# 如果exam4已经存在，则需要将exam4更新为最新文件。先将exam4.tab.o和lex.yy.o更新到最新以后，
# 看他们是否比exam4新，如果有一个以上比exam4新，则运行gcc –o exam4 cal.tab.o lex.yy.o –ly
# 命令重新生成exam4。
lex.yy.o: lex.yy.c exam4.tab.h
    gcc -c lex.yy.c
# lex.yy.o依赖于lex.yy.c和exam4.tab.h，如果目标文件比其依赖文件旧，则要
#重新运行命令生成lex.yy.o。 -c选项表示只生成object文件（.o文件）
exam4.tab.o: exam4.tab.c
    gcc -c exam4.tab.c
lex.yy.c: exam4.l
    flex exam4.l
exam4.tab.c: exam4.y
    bison -dv exam4.y
exam4.tab.h: exam4.y
    echo "exam4.tab.h was created at the same time as exam4.tab.c."
# echo命令表示把后面的文字在屏幕上回显一遍 
clean:
    rm -f exam4.exe lex.yy.o exam4.tab.o lex.yy.c exam4.tab.c exam4.tab.h exam4.stackdump exam4.output
# 这里clean只是个标签，其后也没有依赖文件，运行下面的rm命令不会生成clean
# 文件。注意rm命令（该命令是linux底下删除文件的命令）的参数没有换行。 
```



```c
make clean
```



```c
exam5.exe: exam5.tab.o lex.yy.o main.c errormsg.h errormsg.c
	gcc -o exam5 exam5.tab.o lex.yy.o main.c errormsg.h errormsg.c -ly

lex.yy.o: lex.yy.c exam5.tab.h
	gcc -c lex.yy.c

exam5.tab.o: exam5.tab.c
	gcc -c exam5.tab.c
	
lex.yy.c: exam5.l
	flex exam5.l

exam5.tab.c: exam5.y
	bison -dv exam5.y
```

