## lab6.1

```c
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TODO()                                  \
  do{                                                           \
    printf ("\nAdd your code here: file \"%s\", line %d\n",     \
            __FILE__, __LINE__);                                \
  }while(0)

///////////////////////////////////////////////
// Data structures for the Sum language.
enum Exp_Kind_t {EXP_INT, EXP_SUM};
struct Exp_t
{
  enum Exp_Kind_t kind;
};

struct Exp_Int
{
  enum Exp_Kind_t kind;
  int i;
};

struct Exp_Sum
{
  enum Exp_Kind_t kind;
  struct Exp_t *left;
  struct Exp_t *right;
};

// "constructors"
struct Exp_t *Exp_Int_new (int i)
{
  struct Exp_Int *p = malloc (sizeof(*p));
  p->kind = EXP_INT;
  p->i = i;
  return (struct Exp_t *)p;
}

struct Exp_t *Exp_Sum_new (struct Exp_t *left, struct Exp_t *right)
{
  struct Exp_Sum *p = malloc (sizeof(*p));
  p->kind = EXP_SUM;
  p->left = left;
  p->right = right;
  return (struct Exp_t *)p;
}

// "printer"
void Exp_print(struct Exp_t* exp)
{
    switch (exp->kind) {
    case EXP_INT: {
        struct Exp_Int* p = (struct Exp_Int*)exp;
        printf("%d", p->i);
        break;
    }
    case EXP_SUM: {
        struct Exp_Sum* p = (struct Exp_Sum*)exp;
        printf("(");
        Exp_print(p->left);
        printf("+");
        Exp_print(p->right);
        printf(")");
        break;
    }
    default:
        break;
    }
}

//////////////////////////////////////////////
// Data structures for the Stack language.
enum Stack_Kind_t {STACK_ADD, STACK_PUSH};
struct Stack_t
{
  enum Stack_Kind_t kind;
};

struct Stack_Add
{
  enum Stack_Kind_t kind;
};

struct Stack_Push
{
  enum Stack_Kind_t kind;
  int i;
};

// "constructors"
struct Stack_t *Stack_Add_new ()
{
  struct Stack_Add *p = malloc (sizeof(*p));
  p->kind = STACK_ADD;
  return (struct Stack_t *)p;
}

struct Stack_t *Stack_Push_new (int i)
{
  struct Stack_Push *p = malloc (sizeof(*p));
  p->kind = STACK_PUSH;
  p->i = i;
  return (struct Stack_t *)p;
}

/// instruction list
struct List_t
{
  struct Stack_t *instr;
  struct List_t *next;
};

struct List_t *List_new (struct Stack_t *instr, struct List_t *next)
{
  struct List_t *p = malloc (sizeof (*p));
  p->instr = instr;
  p->next = next;
  return p;
}

// "printer"
void List_reverse_print (struct List_t *list)
{
  if (!list) return;
	List_reverse_print(list->next);
	switch (list->instr->kind) {
			case STACK_ADD:
					printf("ADD\n");
					break;
			case STACK_PUSH:
					printf("PUSH %d\n", ((struct Stack_Push*)list->instr)->i);
					break;
			default:
					break;
	}
}

//////////////////////////////////////////////////
// a compiler from Sum to Stack
struct List_t *all = 0;

void emit (struct Stack_t *instr)
{
  all = List_new (instr, all);
}

void compile (struct Exp_t *exp)
{
  switch (exp->kind){
  case EXP_INT:{
    struct Exp_Int *p = (struct Exp_Int *)exp;
    emit (Stack_Push_new (p->i));
    break;
  }
  case EXP_SUM:{
    struct Exp_Sum *p = (struct Exp_Sum *)exp;
    compile(p->left);
    compile(p->right);
    emit(Stack_Add_new());
    break;
  }
  default:
    break;
  }
}

/* 用c模拟的简单词法分析器，利用yylex()函数来体现，该函数的返回值为词法记号的类别（用enum表示），参数value是额外用来返回整数的属性值的。
 * 关于yylex()函数的定义，可查阅实验附带的Lex说明手册。
 * 忽略空格和制表符。
 * 能够识别加号、整数、括号和逗号。
 */
enum type { PLUS, ENTER, NUM, LPAREN, RPAREN, COMMA };

int yylex(int* value) {
    int c;
    do {
        c = getchar();
    } while (c == ' ' || c == '\t');
    switch (c) {
    case '+': return PLUS;
    case '\n': case EOF: return ENTER;
    // 本实验中不需要识别这三个符号，故注释掉
    // case '(': return LPAREN;
    // case ')': return RPAREN;
    // case ',': return COMMA;
    default:
        // 本实验中不需要识别'.''，故注释掉
        if (/*(c == '.') || */(isdigit(c))) {
            ungetc(c, stdin);
            scanf("%d", value);
            return NUM;
        }
        else {
            printf("\nLEX:ERROR! c=%c\n", c);
            return -1;
        }
    }
}

/* 简易的抽象语法树的读取器。
 * 能够诸如：++2 3 4 这样的抽象语法树输入。
 */
struct Exp_t* Read_ast()
{
    int value;
    int token = yylex(&value);
    if (token == NUM) {
        return Exp_Int_new(value);
    } else if (token == PLUS) {
        struct Exp_t* left = Read_ast();
        struct Exp_t* right = Read_ast();
        return Exp_Sum_new(left, right);
    } else {
        return NULL;
    }
}


//////////////////////////////////////////////////
// program entry
int main()
{
  printf("Compile starting\n");
  // build an expression tree:
  //            +
  //           / \
  //          +   4
  //         / \
  //        2   3
  struct Exp_t *exp = Exp_Sum_new (Exp_Sum_new(Exp_Int_new (2)
                                               , Exp_Int_new (3))
                                   , Exp_Int_new (4));

  /* 你可以用的Read_ast()函数从外部获取抽象语法树，用于代替上面固定的抽象语法树。 
   * Read_ast()调用了yylex()函数，yylex()模拟了词法分析器过程，每次会返回一个单词。
   * 为了便于输入，本例中的抽象语法树使用前缀表示法来输入，数字间以空格隔开，如上述语法树可输入为：++2 3 4。
   */
  // struct Exp_t* exp = Read_ast ();

  if (exp)
  {
    // print out this tree:
    printf ("\nThe expression is:\n");
    Exp_print (exp);

    // compile this tree to Stack machine instructions
    compile (exp);

    // print out the generated Stack instructons:
    printf("\nThe stack instruction list is:\n");
    List_reverse_print (all);
  }
  
  printf("\nCompile finished\n");
  return 0;
}
```





## lab6.2

```c
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TODO()                                  \
  do{                                                           \
    printf ("\nAdd your code here: file \"%s\", line %d\n",     \
            __FILE__, __LINE__);                                \
  }while(0)

///////////////////////////////////////////////
// Data structures for the Sum language.
enum Exp_Kind_t {EXP_INT, EXP_SUM};
struct Exp_t
{
  enum Exp_Kind_t kind;
};

struct Exp_Int
{
  enum Exp_Kind_t kind;
  int i;
};

struct Exp_Sum
{
  enum Exp_Kind_t kind;
  struct Exp_t *left;
  struct Exp_t *right;
};

// "constructors"
struct Exp_t *Exp_Int_new (int i)
{
  struct Exp_Int *p = malloc (sizeof(*p));
  p->kind = EXP_INT;
  p->i = i;
  return (struct Exp_t *)p;
}

struct Exp_t *Exp_Sum_new (struct Exp_t *left, struct Exp_t *right)
{
  struct Exp_Sum *p = malloc (sizeof(*p));
  p->kind = EXP_SUM;
  p->left = left;
  p->right = right;
  return (struct Exp_t *)p;
}

// "printer"
void Exp_print(struct Exp_t* exp)
{
    switch (exp->kind) {
    case EXP_INT: {
        struct Exp_Int* p = (struct Exp_Int*)exp;
        printf("%d", p->i);
        break;
    }
    case EXP_SUM: {
        struct Exp_Sum* p = (struct Exp_Sum*)exp;
        printf("(");
        Exp_print(p->left);
        printf("+");
        Exp_print(p->right);
        printf(")");
        break;
    }
    default:
        break;
    }
}

//////////////////////////////////////////////
// Data structures for the Stack language.
enum Stack_Kind_t {STACK_ADD, STACK_PUSH};
struct Stack_t
{
  enum Stack_Kind_t kind;
};

struct Stack_Add
{
  enum Stack_Kind_t kind;
};

struct Stack_Push
{
  enum Stack_Kind_t kind;
  int i;
};

// "constructors"
struct Stack_t *Stack_Add_new ()
{
  struct Stack_Add *p = malloc (sizeof(*p));
  p->kind = STACK_ADD;
  return (struct Stack_t *)p;
}

struct Stack_t *Stack_Push_new (int i)
{
  struct Stack_Push *p = malloc (sizeof(*p));
  p->kind = STACK_PUSH;
  p->i = i;
  return (struct Stack_t *)p;
}

/// instruction list
struct List_t
{
  struct Stack_t *instr;
  struct List_t *next;
};

struct List_t *List_new (struct Stack_t *instr, struct List_t *next)
{
  struct List_t *p = malloc (sizeof (*p));
  p->instr = instr;
  p->next = next;
  return p;
}

// "printer"
void List_reverse_print (struct List_t *list)
{
  if (!list) return;
	List_reverse_print(list->next);
	switch (list->instr->kind) {
			case STACK_ADD:
					printf("ADD\n");
					break;
			case STACK_PUSH:
					printf("PUSH %d\n", ((struct Stack_Push*)list->instr)->i);
					break;
			default:
					break;
	}
}

//////////////////////////////////////////////////
// a compiler from Sum to Stack
struct List_t *all = 0;

void emit (struct Stack_t *instr)
{
  all = List_new (instr, all);
}

void compile (struct Exp_t *exp)
{
  switch (exp->kind){
  case EXP_INT:{
    struct Exp_Int *p = (struct Exp_Int *)exp;
    emit (Stack_Push_new (p->i));
    break;
  }
  case EXP_SUM:{
    struct Exp_Sum *p = (struct Exp_Sum *)exp;
    compile(p->left);
    compile(p->right);
    emit(Stack_Add_new());
    break;
  }
  default:
    break;
  }
}

/* 用c模拟的简单词法分析器，利用yylex()函数来体现，该函数的返回值为词法记号的类别（用enum表示），参数value是额外用来返回整数的属性值的。
 * 关于yylex()函数的定义，可查阅实验附带的Lex说明手册。
 * 忽略空格和制表符。
 * 能够识别加号、整数、括号和逗号。
 */
enum type { PLUS, ENTER, NUM, LPAREN, RPAREN, COMMA };

int yylex(int* value) {
    int c;
    do {
        c = getchar();
    } while (c == ' ' || c == '\t');
    switch (c) {
    case '+': return PLUS;
    case '\n': case EOF: return ENTER;
    // 本实验中不需要识别这三个符号，故注释掉
    // case '(': return LPAREN;
    // case ')': return RPAREN;
    // case ',': return COMMA;
    default:
        // 本实验中不需要识别'.''，故注释掉
        if (/*(c == '.') || */(isdigit(c))) {
            ungetc(c, stdin);
            scanf("%d", value);
            return NUM;
        }
        else {
            printf("\nLEX:ERROR! c=%c\n", c);
            return -1;
        }
    }
}

/* 简易的抽象语法树的读取器。
 * 能够诸如：++2 3 4 这样的抽象语法树输入。
 */
struct Exp_t* Read_ast()
{
    int value;
    int token = yylex(&value);
    if (token == NUM) {
        return Exp_Int_new(value);
    } else if (token == PLUS) {
        struct Exp_t* left = Read_ast();
        struct Exp_t* right = Read_ast();
        return Exp_Sum_new(left, right);
    } else {
        return NULL;
    }
}

//////////////////////////////////////////////////
// program entry
int main()
{
  printf("Compile starting\n");
  struct Exp_t* exp = Read_ast ();

  if (exp)
  {
    // print out this tree:
    printf ("\nThe expression is:\n");
    Exp_print (exp);

    // compile this tree to Stack machine instructions
    compile (exp);

    // print out the generated Stack instructons:
    printf("\nThe stack instruction list is:\n");
    List_reverse_print (all);
  }
  
  printf("\nCompile finished\n");
  return 0;
}
```



## lab6.3

```c
/* 该程序可以读入一行加法表达式并进行语法分析，显示语法分析是否成功。
 * 加法表达式可由+，(,),数字组成，以换行结尾。
 * 空格和table将被忽略。
 * 该程序的输入可以为标准输入（键盘），也可以为任意文本文件，输出可以为标准输出（屏幕），也可以为任意文本文件。
 * 如遇文件结尾，则分析结束。
 */
#include <ctype.h>
#include <stdio.h>

#define TODO()                                  \
  do{                                                           \
    printf ("\nAdd your code here: file \"%s\", line %d",     \
            __FILE__, __LINE__);                                \
  }while(0)

#define PLUS   		1
#define LPAREN		2
#define RPAREN		3
#define NUM				4
#define ENTER			5

#define LEXERROR  -10
//#define EOF -1

FILE *yyin; 
FILE *yyout;

int yylval;
int lookahead;

int yylex();
int match(int token);
int expr();
void print(int token);
void printError(int token);

/* 词法分析器，每调用一次返回一个token，可能的token有：+， （， ），\n，number，另外还有表示文件结尾的EOF
 * 分析出错时返回LEXERROR。
 */
int yylex(){
  int c;
  do{
    c=getc(yyin);
  } while(c==' ' || c=='\t');
  switch(c){
  case '+': return PLUS;
  case '(': return LPAREN;
  case ')': return RPAREN;
  case '\n': return ENTER;
  case EOF: return EOF;
  default: 
    // 本实验中不需要识别'.''，故注释掉
    if (/*(c == '.') || */(isdigit(c))){
    	ungetc(c,yyin);
      fscanf(yyin,"%d", &yylval);
      return NUM;
    } else {
      fprintf(yyout, "LEX:ERROR! c=%c ", c);
  	  return LEXERROR;}
  }
}

/* 打印当前 token 到输出文件中，如果当前token不是合法的，则打印 ERROR TOKEN
 */
void print(int token){
	switch(token){
		case LPAREN:
			fprintf(yyout, "LPAREN ");
			break;
		case RPAREN:
			fprintf(yyout, "RPAREN ");
			break; 
		case PLUS:
			fprintf(yyout, "PLUS ");
			break;
		case NUM:
			fprintf(yyout, "NUM(%d) ", yylval);
			break;
		case ENTER:
			fprintf(yyout, "ENTER");
			break;
		case EOF:
			fprintf(yyout, "EOF");
			break;
		default:
			fprintf(yyout, "ERROR TOKEN ");
	}
}

/* 语法分析出错时，打印出错的token到输出文件中。
 */
void printError(int token){
	fprintf(yyout, "PARSE_ERROR:( ");
	print(token);
	fprintf(yyout, ")");
}

int match(int token){
	if (lookahead == token){
		print(token);
		lookahead = yylex();
		return 1;
	} else{ 
		printError(lookahead);
		return 0;
	}
}

/* 函数expr()：对表达式进行递归下降的预测分析。表达式可以包含数字（0和正整数），左右小括号和加号。
 * 如果分析成功，则该函数返回真（1），否则返回假（0）  
 * 该函数需要改写。
 */
int term() {
    if (lookahead == LPAREN) {
        if (!match(LPAREN)) return 0;
        if (!expr()) return 0;
        if (!match(RPAREN)) return 0;
        return 1;
    } else if (lookahead == NUM) {
        if (!match(NUM)) return 0;
        return 1;
    } else {
        printError(lookahead);
        return 0;
    }
}

int exprp() {
    if (lookahead == PLUS) {
        if (!match(PLUS)) return 0;
        if (!term()) return 0;
        if (!exprp()) return 0;
        return 1;
    }
    return 1;
}

int expr() {
    if (!term()) return 0;
    if (!exprp()) return 0;
    return 1;
}

/* 一行表达式由一个表达式跟上一个回车组成 */
int exprln(){
	return(expr() && match(ENTER));
}

int main(int argc, char ** argv){
  //可以指定输入输出文件，默认为键盘输入屏幕输出。
	if (argc>=2){
	  if ((yyin = fopen(argv[1], "r")) == NULL){
	    printf("Can't open file %s\n", argv[1]);
	    return 1;
	  }
	  if (argc>=3){
	    yyout=fopen(argv[2], "w");
	  } else {
	  	yyout = stdout;
	  }
	} else {
		yyin = stdin;
		yyout =stdout;
	}
	//lookahead指向当前输入缓冲器的一个token
	lookahead = yylex();
	if (lookahead != EOF){
		if (exprln()){
			fprintf(yyout, "\nParsing Success!\n");
		} 	else {
			fprintf(yyout, "\nParsing Fail!\n");
		}
	}
	
	if(argc>=2){
	  fclose(yyin);
	  if (argc>=3) fclose(yyout);
	}
	return 0;
}
```

