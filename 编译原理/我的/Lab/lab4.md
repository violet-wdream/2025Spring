

```bash
cd /data/workspace/myshixun/
flex test4.l;gcc -o test4 lex.yy.c -lfl
```



```c
%{

#include <stdio.h> 
#include <string.h> 

#define LT					1
#define	LE					2
#define GT					3
#define	GE					4
#define	EQ					5
#define NE					6

#define PROGRAM             7
#define SEMICOLON           8
#define VAR                 9
#define COLON              10
#define INTEGER            11
#define COMMA              12
#define REAL               13
#define BEGIN_TOKEN        14  // 重命名为BEGIN_TOKEN
#define ASSIGN             15
#define MINUS              16
#define TIMES              17
#define END_TOKEN          18  // 重命名为END_TOKEN
#define PERIOD             19

#define WHILE              20
#define DO                 21
#define ID                 22
#define NUMBER             23

#define PLUS               30
#define DIVIDE             31
#define ELSE               32
#define THEN               33
#define IF                 34  


#define NEWLINE            25
#define ERRORCHAR          26


    /* 提示：你需要将yylval的类型修改为union类型！ 
    * 对于记号ID来说，属性值是ID的名字（字符串）；
    * 对于整数和浮点数来说，属性值是整数或者浮点数的值。
    */
typedef union {
    char *str;    // 存储标识符
    int ival;     // 存储整数
    double dval;  // 存储浮点数
} YYLVAL;

YYLVAL yylval;
    /* yylval 是yacc中定义的变量，用来保存记号的属性值，默认是int类型。 
    * 在用lex实现的词法分析器中可以使用这个变量将记号的属性传递给用
    * yacc实现的语法分析器。
    */

%}
%x COMMENT

 
delim        [ \t\n]
ws           {delim}+
letter       [A-Za-z]
digit        [0-9]
id           {letter}({letter}|{digit})*
number       {digit}+(\.{digit}+)?(E[+-]?{digit}+)?
float_start  \.{digit}+

/* 状态（或条件）定义可以定义在这里 
 * INITIAL是一个默认的状态，不需要定义
 */

%%

"/*"                       { BEGIN(COMMENT); }
<COMMENT>"*/"              { BEGIN(INITIAL); }
<COMMENT>.|\n              { /* 忽略注释内容 */ }

{ws}                       { /* 忽略空白字符 */ }
"PROGRAM"                  { return (PROGRAM); }
"VAR"                      { return (VAR); }
"INTEGER"                  { return (INTEGER); }
"REAL"                     { return (REAL); }
"BEGIN"                    { return (BEGIN_TOKEN); }
"END"                      { return (END_TOKEN); }
"WHILE"                    { return (WHILE); }
"DO"                       { return (DO); }
"ELSE"                     { return (ELSE); }
"THEN"                     { return (THEN); }
"IF"                       { return (IF); }  

";"                        { return (SEMICOLON); }
":"                        { return (COLON); }
","                        { return (COMMA); }
":="                       { return (ASSIGN); }
"+"                        { return (PLUS); }  
"-"                        { return (MINUS); }
"*"                        { return (TIMES); }
"/"                        { return (DIVIDE); }
"."                        { return (PERIOD); }

{id}                       { yylval.str = strdup(yytext); return (ID); }
{float_start}              {
    yylval.dval = atof(yytext);
    return (NUMBER);
}
{number}                   {
    if(strchr(yytext, '.') || strchr(yytext, 'E')) {
        yylval.dval = atof(yytext);  // 浮点数
    } else {
        yylval.ival = atoi(yytext);  // 整数
    }
    return (NUMBER);
}

"<"                        { return (LT); }
"<="                       { return (LE); }
"="                        { return (EQ); }
"<>"                       { return (NE); }
">"                        { return (GT); }
">="                       { return (GE); }

.                          { return ERRORCHAR; }
 

 
%%

int yywrap (){
  return 1;
}

    /* 请你修改该函数，利用yylval来输出字符串、整数、浮点数的值
    * 枚举类型可以保持不变，继续用yytext输出
    */
void writeout(int c){
  switch(c){
  	case ERRORCHAR: fprintf(yyout, "(ERRORCHAR, \"%s\") ", yytext); break;
	case LT: fprintf(yyout, "(LT, \"%s\") ", yytext); break;
    case LE: fprintf(yyout, "(LE, \"%s\") ", yytext); break;
    case EQ: fprintf(yyout, "(EQ, \"%s\") ", yytext); break;
    case NE: fprintf(yyout, "(NE, \"%s\") ", yytext); break;
    case GT: fprintf(yyout, "(GT, \"%s\") ", yytext); break;
    case GE: fprintf(yyout, "(GE, \"%s\") ", yytext); break;      

	case PLUS: fprintf(yyout, "(PLUS, \"%s\") ", yytext); break;
    case DIVIDE: fprintf(yyout, "(DIVIDE, \"%s\") ", yytext); break;
    case ELSE: fprintf(yyout, "(ELSE, \"%s\") ", yytext); break;
    case THEN: fprintf(yyout, "(THEN, \"%s\") ", yytext); break;
    case IF: fprintf(yyout, "(IF, \"%s\") ", yytext); break;  

	case WHILE: fprintf(yyout, "(WHILE, \"%s\") ", yytext); break;
      case DO: fprintf(yyout, "(DO, \"%s\") ", yytext); break;
      case PROGRAM: fprintf(yyout, "(PROGRAM, \"%s\") ", yytext); break;
      case VAR: fprintf(yyout, "(VAR, \"%s\") ", yytext); break;
      case INTEGER: fprintf(yyout, "(INTEGER, \"%s\") ", yytext); break;
      case REAL: fprintf(yyout, "(REAL, \"%s\") ", yytext); break;
      case BEGIN_TOKEN: fprintf(yyout, "(BEGIN, \"%s\") ", yytext); break;  
      case END_TOKEN: fprintf(yyout, "(END, \"%s\") ", yytext); break;      
      case SEMICOLON: fprintf(yyout, "(SEMICOLON, \"%s\") ", yytext); break;
      case COLON: fprintf(yyout, "(COLON, \"%s\") ", yytext); break;
      case COMMA: fprintf(yyout, "(COMMA, \"%s\") ", yytext); break;
      case ASSIGN: fprintf(yyout, "(ASSIGN, \"%s\") ", yytext); break;
      case MINUS: fprintf(yyout, "(MINUS, \"%s\") ", yytext); break;
      case TIMES: fprintf(yyout, "(TIMES, \"%s\") ", yytext); break;
      case PERIOD: fprintf(yyout, "(PERIOD, \"%s\") ", yytext); break;
      case NUMBER:
          if(strchr(yytext, '.') || strchr(yytext, 'E')) {
              fprintf(yyout, "(FLOAT, \"%.6f\") ", yylval.dval); // 浮点数保留6位小数
          } else {
              fprintf(yyout, "(INT, \"%d\") ", yylval.ival); // 整数
          }
          break;
      case ID: fprintf(yyout, "(ID, \"%s\") ", yylval.str); break;
      case NEWLINE: fprintf(yyout, "\n"); break;
  }
  return;
}


int main (int argc, char ** argv){
	int c, j=0;
    if (argc>=2) {
      if ((yyin = fopen(argv[1], "r")) == NULL) {
        printf("Can't open file %s\n", argv[1]);
        return 1;
      }
      if (argc>=3) {
        yyout=fopen(argv[2], "w");
      }
    }

    while (c = yylex()) {
        writeout(c);
        j++;
        if (j%5 == 0) writeout(NEWLINE);
        if (c == ID) {
            free(yylval.str); // 释放为ID分配的内存
        }
    }
    
    if(argc>=2) {
      fclose(yyin);
      if (argc>=3) fclose(yyout);
    }
	return 0;
}
```

