# 实验1 学习Lex并使用Flex调试1



```c
/* 这是注释的形式，与C中的/*...* /注释相同。 */
/* 第一部分是定义、声明部分。这部分内容可以为空。*/

%{

/* 写在 %{...%}这对特殊括号内的内容会被直接拷贝到C文件中。 */
#include <stdio.h> 
#define RELOP       1
#define OTHER       2
#define BRACKETS    3
%}

 /* 这里进行正规定义和状态定义。如果没有，可以不写。 */ 
relop       \<|\<=|=|\<\>|\>|\>=
other       ([^<=>()])+

%%

  /* 规则部分的注释要有前导空格，这点很重要 */
"("         { return BRACKETS; }
")"         { return BRACKETS; }
{relop}     { return RELOP; }
{other}     { return OTHER; }
.           {}
 
%%

int yywrap (){
  return 1;
}

void writeout(int c){
  switch(c){
    case OTHER: fprintf(yyout, "(OTHER,%d)", yyleng);break;
    case RELOP: fprintf(yyout, "(RELOP,\"%s\")", yytext);break;
    case BRACKETS: fprintf(yyout, "(BRACKETS,\"%s\")", yytext);break;
    default:break;
  }
  return;
}

int main (int argc, char ** argv){
  int c,j=0;
  if (argc>=2){
    if ((yyin = fopen(argv[1], "r")) == NULL){
      printf("Can't open file %s\n", argv[1]);
      return 1;
    }
    if (argc>=3){
      yyout=fopen(argv[2], "w");
    }
  }
  while (c = yylex()){
    writeout(c);
  }
  if(argc>=2){
    fclose(yyin);
    if (argc>=3) fclose(yyout);
  }
  return 0;
}
```





```c
/* %%作为lex文件三个部分的分割符，必须位于行首 */
%{
#include <stdio.h> 
/* 定义所有需要的记号类型 */
#define RELOP                 1
#define PLUS                  2
#define MINUS                 3
#define TIMES                 4
#define DIV                   5
#define LPAREN                6
#define RPAREN                7
#define LBRACE                8
#define RBRACE                9
#define SEMICOLON             10
#define ASSIGN                11
#define IF                    12
#define ELSE                  13
#define WHILE                 14
#define DO                    15
#define ID                    16
#define NUM                   17
#define ERRORCHAR             18
#define NEWLINE               19

int yylval;
%}

/* 正规定义 */
delim       [ \t\n]
ws          {delim}+
letter      [A-Za-z]
digit       [0-9]
id          [A-Za-z_][A-Za-z0-9_]*
number      {digit}+(\.{digit}+)?(E[+-]?{digit}+)?

/* 注释状态 */
%x COMMENT
%x LINE_COMMENT

%%
  /* 处理注释 - %x 表示排他状态，将完全忽略其他规则 */
"//"                { BEGIN LINE_COMMENT; }
<LINE_COMMENT>\n    { BEGIN INITIAL; }
<LINE_COMMENT>.     { /* 忽略单行注释中的所有内容 */ }

"/*"                { BEGIN COMMENT; }
<COMMENT>"*/"       { BEGIN INITIAL; }
<COMMENT>.|\n       { /* 忽略多行注释中的所有内容 */ }

  /* 忽略空白字符 */
{ws}                { /* 忽略空白字符 */ }

  /* 关键字 - 只在非注释状态下识别 */
"if"                { return IF; }
"else"              { return ELSE; }
"while"             { return WHILE; }
"do"                { return DO; }

  /* 关系运算符 (C语言形式) */
"=="                { return RELOP; }
"!="                { return RELOP; }
"<="                { return RELOP; }
">="                { return RELOP; }
"<"                 { return RELOP; }
">"                 { return RELOP; }

  /* 赋值符号 */
"="                 { return ASSIGN; }

  /* 算术运算符 */
"+"                 { return PLUS; }
"-"                 { return MINUS; }
"*"                 { return TIMES; }
"/"                 { return DIV; }

  /* 括号和分号 */
"("                 { return LPAREN; }
")"                 { return RPAREN; }
"{"                 { return LBRACE; }
"}"                 { return RBRACE; }
";"                 { return SEMICOLON; }

  /* 标识符和数字 */
{id}                { return ID; }
{number}            { return NUM; }

  /* 其他字符视为错误 */
.                   { return ERRORCHAR; }

%%

int yywrap() {
    return 1;
}

void writeout(int c) {
    switch(c) {
        case ERRORCHAR: fprintf(yyout, "(ERRORCHAR, \"%s\") ", yytext); break;
        case RELOP:     fprintf(yyout, "(RELOP, \"%s\") ", yytext); break;
        case PLUS:      fprintf(yyout, "(PLUS, \"%s\") ", yytext); break;
        case MINUS:     fprintf(yyout, "(MINUS, \"%s\") ", yytext); break;
        case TIMES:     fprintf(yyout, "(TIMES, \"%s\") ", yytext); break;
        case DIV:       fprintf(yyout, "(DIV, \"%s\") ", yytext); break;
        case LPAREN:    fprintf(yyout, "(LPAREN, \"%s\") ", yytext); break;
        case RPAREN:    fprintf(yyout, "(RPAREN, \"%s\") ", yytext); break;
        case LBRACE:    fprintf(yyout, "(LBRACE, \"%s\") ", yytext); break;
        case RBRACE:    fprintf(yyout, "(RBRACE, \"%s\") ", yytext); break;
        case SEMICOLON: fprintf(yyout, "(SEMICOLON, \"%s\") ", yytext); break;
        case ASSIGN:    fprintf(yyout, "(ASSIGN, \"%s\") ", yytext); break;
        case IF:        fprintf(yyout, "(IF, \"%s\") ", yytext); break;
        case ELSE:      fprintf(yyout, "(ELSE, \"%s\") ", yytext); break;
        case WHILE:     fprintf(yyout, "(WHILE, \"%s\") ", yytext); break;
        case DO:        fprintf(yyout, "(DO, \"%s\") ", yytext); break;
        case NUM:       fprintf(yyout, "(NUM, \"%s\") ", yytext); break;
        case ID:        fprintf(yyout, "(ID, \"%s\") ", yytext); break;
        case NEWLINE:   fprintf(yyout, "\n"); break;
        default: break;
    }
}

int main(int argc, char** argv) {
    int c, j = 0;
    if (argc >= 2) {
        if ((yyin = fopen(argv[1], "r")) == NULL) {
            printf("Can't open file %s\n", argv[1]);
            return 1;
        }
        if (argc >= 3) {
            yyout = fopen(argv[2], "w");
        }
    }
    
    while (c = yylex()) {
        writeout(c);
        j++;
        if (j % 5 == 0) writeout(NEWLINE);
    }
    
    if (argc >= 2) {
        fclose(yyin);
        if (argc >= 3) fclose(yyout);
    }
    return 0;
}
```

