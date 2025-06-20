c

```
/* 请自行编写词法分析器代码，并按照提示使用makefile进行编译。*/
/* 常见错误提示：编写词法分析器时，需要 #include "parser.tab.h" （这个文件是yacc文件编译时自动生成的。想一想为什么词法分析器里要包含这个文件？）*/
/* 常见错误提示：需要增加一个resetLexState()函数，否则编译不能通过。该函数可以重置lex状态为初始状态，如下：
/* void resetLexState(){
/*   BEGIN INITIAL;
/* }
/* 请自行编写词法分析器代码，并按照提示使用makefile进行编译。*/
/* 常见错误提示：编写词法分析器时，需要 #include "parser.tab.h" （这个文件是yacc文件编译时自动生成的。想一想为什么词法分析器里要包含这个文件？）*/
/* 常见错误提示：需要增加一个resetLexState()函数，否则编译不能通过。该函数可以重置lex状态为初始状态，如下：

%{
#include <stdio.h>
#include <string.h>
#include "parser.tab.h"    
#include "errormsg.h"
#include "util.h"
%}
%x COMMENT

delim      [ \t\n]
letter     [A-Za-z]
digit      [0-9]
id         {letter}({letter}|{digit})*
number     {digit}+(\.{digit}+)?(E[+-]?{digit}+)?
float_start  \.{digit}+

%%

"/*"                { BEGIN(COMMENT); }
"(*"                { BEGIN(COMMENT); }

<COMMENT>"*/"       { BEGIN(INITIAL); }
<COMMENT>"*)"       { BEGIN(INITIAL); }

<COMMENT>.|\n       { /* skip */ }

{delim}+            { /* skip whitespace */ }


"("                 { return LPAREN; }
")"                 { return RPAREN; }
"PROGRAM"           { return PROGRAM; }
"VAR"               { return VAR; }
"INTEGER"           { return INTEGER; }
"REAL"              { return REAL; }
"BEGIN"             { return BEGIN; }
"END"               { return END; }
"IF"                { return IF; }
"THEN"              { return THEN; }
"ELSE"              { return ELSE; }
"WHILE"             { return WHILE; }
"DO"                { return DO; }

";"                 { return SEMICOLON; }
":"                 { return COLON; }
","                 { return COMMA; }
"."                { return PERIOD; }
":="                { return ASSIGN; }
"+"                 { return PLUS; }
"-"                 { return MINUS; }
"*"                 { return TIMES; }
"/"                 { return DIVIDE; }

{id}                { yylval.sval = strdup(yytext); return ID; }
{float_start}       { yylval.fval = atof(yytext); return FLOAT; }
{number}            {
                      if (strchr(yytext,'.')||strchr(yytext,'E')||strchr(yytext,'e')) {
                        yylval.fval = atof(yytext);
                        return FLOAT;
                      } else {
                        yylval.ival = atoi(yytext);
                        return INT;
                      }
                      
                    }

"<>"                { return NEQ; }
"<="                { return LE; }
"<"                 { return LT; }
">="                { return GE; }
">"                 { return GT; }
"="                 { return EQ; }

.                   { EM_error(EM_tokPos, "illegal character \"%s\"", yytext); }

%%

int yywrap(void){ return 1; }
void resetLexState(){BEGIN INITIAL;}

```



`parser.y`

```c
%{
#include <stdio.h>
#include "util.h"
#include "errormsg.h"

extern FILE *yyin;
int yylex(void);
void yyerror(char *s) { EM_error(EM_tokPos, "%s", s); }
%}

%union {
  int    ival;
  double fval;
  char  *sval;
}

/* 关键字和符号 */
%token LPAREN RPAREN

%token <sval> ID
%token <ival> INT
%token <fval> FLOAT
%token        INTEGER REAL
%token        PROGRAM VAR BEGINN END
%token        IF THEN ELSE WHILE DO
%token        COMMA COLON SEMICOLON PERIOD
%token        ASSIGN EQ NEQ LT LE GT GE
%token        PLUS MINUS TIMES DIVIDE

%type  <fval> number

%start program

%%

program:
    PROGRAM ID SEMICOLON var_section BEGINN stmt_list END PERIOD
  ;

var_section:
    /* empty */
  | VAR var_decl_list
  ;

var_decl_list:
    var_decl SEMICOLON
  | var_decl SEMICOLON var_decl_list
  ;

var_decl:
    id_list COLON type
  ;

id_list:
    ID
  | id_list COMMA ID
  ;

type:
    INTEGER
  | REAL
  ;

stmt_list:
    stmt
  | stmt_list SEMICOLON stmt
  ;

stmt_list_opt:
    /* empty */
  | stmt_list
  ;

stmt:
    ID ASSIGN expr
  | IF rel_expr THEN stmt ELSE stmt
  | WHILE rel_expr DO stmt
  | BEGINN stmt_list_opt END
  ;
rel_expr:
    expr LT expr
  | expr LE expr
  | expr GT expr
  | expr GE expr
  | expr EQ expr
  | expr NEQ expr
  | expr
  ;

expr:
    expr PLUS term
  | expr MINUS term
  | term
  ;

term:
    term TIMES factor
  | term DIVIDE factor
  | factor
  ;

factor:
    ID
  | number
  | LPAREN expr RPAREN
  ;

number:
    INT    { $$ = $1; }
  | FLOAT  { $$ = $1; }
  ;

%%

```



还有问题参考Lab7 - myshixun文件夹，不行全部替换即可

