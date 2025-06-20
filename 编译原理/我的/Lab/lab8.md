`ast.c`

```c
/* 本文件给出抽象语法树上各数据结构的构造函数，后续实验需要修改该文件的一些函数 */

#include "ast.h"




/* make id node */
a_id A_Id(a_pos pos, string val){
  a_id ret = checked_malloc(sizeof(*ret));
  ret->pos = pos;
  ret->val = val;
  return ret;
}


/* make exp node from integer */
a_exp A_IntExp(a_pos pos, int ival){
  a_exp ret = checked_malloc(sizeof(*ret));
  ret->kind = A_intExp;
  ret->pos = pos;
  ret->exp.ival = ival;
  return ret;
}

/* make exp node from real */
a_exp A_RealExp(a_pos pos, double fval){
  a_exp ret = checked_malloc(sizeof(*ret));
  ret->kind = A_realExp;
  ret->pos = pos;
  ret->exp.fval = fval;
  return ret;
}

/* make exp node from id node */
a_exp A_VarExp(a_pos pos, a_id var){
  a_exp ret = checked_malloc(sizeof(*ret));
  ret->kind = A_varExp;
  ret->pos = pos;
  ret->exp.var = var;
  return ret;
}

/* make binary operands exp node */
a_exp A_OpExp(a_pos pos, a_op op, a_exp left, a_exp right){
  a_exp ret = checked_malloc(sizeof(*ret));
  ret->kind = A_opExp;
  ret->pos = pos;
  ret->exp.biopExp.op = op;
  ret->exp.biopExp.left = left;
  ret->exp.biopExp.right = right;
  return ret;
}

/* make boolean exp node */
a_bexp A_BExp(a_pos pos, a_bop bop, a_exp left, a_exp right){
  a_bexp ret = checked_malloc(sizeof(*ret));
  ret->pos = pos;
  ret->bexp.bop = bop;
  ret->bexp.left = left;
  ret->bexp.right = right;
  return ret;
}

/* make if statement */
a_stm A_If(a_pos pos, a_bexp b, a_stm s1, a_stm s2){
  a_stm ret = checked_malloc(sizeof(*ret));
  ret->kind = A_if;
  ret->pos = pos;
  ret->stm.iff.b = b;
  ret->stm.iff.s1 = s1;
  ret->stm.iff.s2 = s2;
  return ret;
}

/* make while statement */
a_stm A_While(a_pos pos, a_bexp b, a_stm s){
  a_stm ret = checked_malloc(sizeof(*ret));
  ret->kind = A_while;
  ret->pos = pos;
  ret->stm.whilee.b = b;
  ret->stm.whilee.s = s;
  return ret;
}

/* make sequence statement */
a_stm A_Seq(a_pos pos, a_stm_list sl){
  a_stm ret = checked_malloc(sizeof(*ret));
  ret->kind = A_seq;
  ret->pos = pos;
  ret->stm.seq = sl;
  return ret; 
}

/* make statement list */
a_stm_list A_StmList(a_stm s, a_stm_list sl){
  a_stm_list ret = checked_malloc(sizeof(*ret));
  ret->head = s;
  ret->tail = sl;
  return ret;
}

/* make var list */
a_var_list A_VarList(a_id v, a_var_list vl){
  a_var_list ret = checked_malloc(sizeof(*ret));
  ret->head = v;
  ret->tail = vl;
  return ret;
}

/* make variable declaration node */
a_dec A_VarDec(a_pos pos, a_var_list vl, ttype t){
  a_dec ret = checked_malloc(sizeof(*ret));
  ret->type = t;
  ret->pos = pos;
  ret->varlist = vl;
  return ret;
}

/* make variable declaration list */
a_dec_list A_DecList(a_dec vd, a_dec_list vdl){
  a_dec_list ret = checked_malloc(sizeof(*ret));
  ret->head = vd;
  ret->tail = vdl;
  return ret;
}

/* make program node */
a_prog A_Prog (a_pos pos, char * name, a_dec_list dl, a_stm_list sl){
  a_prog ret = checked_malloc(sizeof(*ret));
  ret->name = name;
  ret->pos =pos;
  ret->declist = dl;
  ret->stmlist = sl;
  return ret;
}
/* make assign statement */
a_stm A_Assign (a_pos pos, a_id var, a_exp exp){
  a_stm ret = checked_malloc(sizeof(*ret));
  ret->kind = A_assign;
  ret->pos = pos;
  ret->stm.assign.var = var;
  ret->stm.assign.exp = exp;
  return ret;
}

```



`parser.l`

```c
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "errormsg.h"
#include "parser.tab.h"

/* 用于跟踪当前位置 */
int charPos = 1;

/* 更新位置信息 */
#define ADJ (EM_tokPos = charPos, charPos += yyleng)

/* 字符串表，用于存储标识符和字符串常量 */
typedef struct string_list {
    char *str;
    struct string_list *next;
} *string_list;

static string_list strings = NULL;

/* 将字符串添加到字符串表中 */
string String(char *s) {
    string_list p = strings;
    /* 查找是否已存在 */
    for (; p; p = p->next) {
        if (strcmp(p->str, s) == 0) {
            return p->str;
        }
    }
    /* 不存在则添加新的 */
    p = malloc(sizeof(*p));
    p->str = malloc(strlen(s) + 1);
    strcpy(p->str, s);
    p->next = strings;
    strings = p;
    return p->str;
}

%}

/* 定义正则表达式模式 */
letter      [a-zA-Z]
digit       [0-9]
id          {letter}({letter}|{digit})*
integer     {digit}+
real        {digit}+\.{digit}+
whitespace  [ \t]+
comment1    \{[^\}]*\}
comment2    \(\*([^*]|[\r\n]|(\*+([^*\)])))*\*+\)

%%

{comment1}      { ADJ; /* 忽略花括号注释 */ }
{comment2}      { ADJ; /* 忽略圆括号-星号注释 */ }
{whitespace}    { ADJ; /* 忽略空白字符 */ }
\n              { ADJ; EM_newline(); }

"program"       { ADJ; return PROGRAM; }
"begin"         { ADJ; return BEGINN; }
"end"           { ADJ; return END; }
"var"           { ADJ; return VAR; }
"if"            { ADJ; return IF; }
"then"          { ADJ; return THEN; }
"else"          { ADJ; return ELSE; }
"while"         { ADJ; return WHILE; }
"do"            { ADJ; return DO; }
"integer"       { ADJ; return INTEGER; }
"real"          { ADJ; return REAL; }

{id}            { ADJ; yylval.sval = String(yytext); return ID; }
{integer}       { ADJ; yylval.ival = atoi(yytext); return INT; }
{real}          { ADJ; yylval.fval = atof(yytext); return FLOAT; }

","             { ADJ; return COMMA; }
":"             { ADJ; return COLON; }
";"             { ADJ; return SEMICOLON; }
"("             { ADJ; return LPAREN; }
")"             { ADJ; return RPAREN; }
"."             { ADJ; return PERIOD; }

":="            { ADJ; return ASSIGN; }
"="             { ADJ; return EQ; }
"<>"            { ADJ; return NEQ; }
"<"             { ADJ; return LT; }
"<="            { ADJ; return LE; }
">"             { ADJ; return GT; }
">="            { ADJ; return GE; }

"+"             { ADJ; return PLUS; }
"-"             { ADJ; return MINUS; }
"*"             { ADJ; return TIMES; }
"/"             { ADJ; return DIVIDE; }

.               { ADJ; EM_error(EM_tokPos, "非法字符: %s", yytext); }

%%

int yywrap(void) {
    charPos = 1;
    return 1;
}
```





`parser.y`

```c
%{
#include <stdio.h>
#include "ast.h" //该文件定义了抽象语法树（分析树）的数据结构
#include "errormsg.h"
#define YYDEBUG 1 
/* 允许跟踪错误，与%debug功能相同 */

int yylex(void); /* function prototype */

/* 该函数显示错误信息s，显示时包含了错误发生的位置。*/
void yyerror(char *s)
{
 EM_error(EM_tokPos, "%s", s);
}

/* 存放抽象语法树中 "程序" 数据结构的变量 */
a_prog program = NULL;

%}


 /* 定义属性值栈的类型 */
%union {
    int ival;
    double fval;
    string sval;
    a_exp exp;
    a_stm stm;
    a_stm_list stms;
    a_prog prog;
    a_dec dec;
    a_dec_list decl;
    a_var_list vars;
    a_id id;
    a_bexp bexp;
}

 /* 定义各个终结符，以及他们的属性值的类型 */
%token <sval> ID /* id */
%token <ival> INT  /*整型数*/
%token <fval> FLOAT /*浮点数*/
%token INTEGER REAL  /*两种类型名：整型、实型*/
%token 
  COMMA COLON SEMICOLON LPAREN RPAREN PERIOD /* 符号 , : ; ( ) . */
  PROGRAM BEGINN END VAR IF WHILE DO   /* 关键字：PROGRAM BEGIN END VAR IF WHILE Do */
  /* 想想为什么不声明为BEGIN？ */
  THEN ELSE /* 关键字：THEN ELSE */
  ASSIGN EQ NEQ LT LE GT GE /* 符号 :=	 =  <>  <  <=  >  >= */
  PLUS MINUS TIMES DIVIDE /* 符号 + = * / */
%start program

  /* 定义各个非终结符的属性值类型 */
%type <prog> program
%type <decl> declist
%type <dec> vardec vardecitem
%type <vars> varlist
%type <stms> stmts
%type <stm> stmt
%type <exp> exp
%type <id> variable
%type <bexp> boolexp

/* 定义运算符优先级和结合性 */
%left EQ NEQ LT LE GT GE
%left PLUS MINUS
%left TIMES DIVIDE
%right UMINUS

%%
 /* 扩展的文法，支持更复杂的语言结构 */
program	:	PROGRAM ID SEMICOLON declist BEGINN stmts END PERIOD	
                    {program = A_Prog(EM_tokPos, $2, $4, $6);}
                ;

declist : vardec declist  {$$ = A_DecList($1, $2);}
        | vardec          {$$ = A_DecList($1, NULL);}
        | /* empty */     {$$ = NULL;}
                ;

vardec  : VAR vardecitem  {$$ = $2;}
        | vardecitem      {$$ = $1;}
                ;

vardecitem : varlist COLON INTEGER SEMICOLON	
        {$$ = A_VarDec(EM_tokPos, $1, T_int);}
        | varlist COLON REAL SEMICOLON	
        {$$ = A_VarDec(EM_tokPos, $1, T_real);}  
                ;

varlist : ID COMMA varlist    {$$ = A_VarList(A_Id(EM_tokPos, $1), $3);}
        | ID                  {$$ = A_VarList(A_Id(EM_tokPos, $1), NULL);}
        ;

variable : ID                 {$$ = A_Id(EM_tokPos, $1);}
        ;

stmts   : stmt stmts      {$$ = A_StmList($1, $2);}
        | stmt            {$$ = A_StmList($1, NULL);}
        ;

stmt    : variable ASSIGN exp SEMICOLON
        {$$ = A_Assign(EM_tokPos, $1, $3);}
        | variable ASSIGN exp       
        {$$ = A_Assign(EM_tokPos, $1, $3);}
        | IF boolexp THEN stmt ELSE stmt
        {$$ = A_If(EM_tokPos, $2, $4, $6);}
        | IF boolexp THEN stmt
        {$$ = A_If(EM_tokPos, $2, $4, NULL);}
        | WHILE boolexp DO stmt
        {$$ = A_While(EM_tokPos, $2, $4);}
        | BEGINN stmts END
        {$$ = A_Seq(EM_tokPos, $2);}
        ;

boolexp : exp EQ exp   {$$ = A_BExp(EM_tokPos, A_eqOp, $1, $3);}
        | exp NEQ exp  {$$ = A_BExp(EM_tokPos, A_neqOp, $1, $3);}
        | exp LT exp   {$$ = A_BExp(EM_tokPos, A_ltOp, $1, $3);}
        | exp LE exp   {$$ = A_BExp(EM_tokPos, A_leOp, $1, $3);}
        | exp GT exp   {$$ = A_BExp(EM_tokPos, A_gtOp, $1, $3);}
        | exp GE exp   {$$ = A_BExp(EM_tokPos, A_geOp, $1, $3);}
        ;

exp     : INT	      {$$ = A_IntExp(EM_tokPos, $1);}
        | FLOAT       {$$ = A_RealExp(EM_tokPos, $1);}
        | variable    {$$ = A_VarExp(EM_tokPos, $1);}
        | exp PLUS exp   {$$ = A_OpExp(EM_tokPos, A_plusOp, $1, $3);}
        | exp MINUS exp  {$$ = A_OpExp(EM_tokPos, A_minusOp, $1, $3);}
        | exp TIMES exp  {$$ = A_OpExp(EM_tokPos, A_timesOp, $1, $3);}
        | exp DIVIDE exp {$$ = A_OpExp(EM_tokPos, A_divideOp, $1, $3);}
        | MINUS exp %prec UMINUS {$$ = A_OpExp(EM_tokPos, A_minusOp, A_IntExp(EM_tokPos, 0), $2);}
        | LPAREN exp RPAREN   {$$ = $2;}
        ;

%%
```

