

# 实验3 使用Lex设计词法分析器1

flt像几把若致，鸟用没有还哈气，态度差的，也中一条，碰到这私人室友，这辈子有了😋



建议开secure shell做

头歌狗答辩平台卡的要死

修改完.l之后，使用下面的指令进行编译

然后回到头歌评测

```c
flex test3.l;gcc -o test3 lex.yy.c -lfl
```

test3.l

```c
%{
#include <stdio.h>
#include <string.h>
FILE *yyin, *yyout;
char *strdup(const char *s); // for MSVC
static int token_count = 0;
#define PRINT_TOKEN(fmt, ...) \
    do { \
        fprintf(yyout, fmt, __VA_ARGS__); \
        token_count++; \
        if(token_count % 5 == 0) fprintf(yyout, "\n"); \
    } while(0)
%}

delim      [ \t\r\n]
ws         {delim}+
letter     [A-Za-z]
digit      [0-9]
id         {letter}({letter}|{digit})*
int        {digit}+
float      {digit}+"."{digit}+|{digit}+"."|\.{digit}+

%s COMMENT

%%

"/*"                { BEGIN COMMENT; }
<COMMENT>"*/"       { BEGIN INITIAL; }
<COMMENT>[^*]+      { /* skip all non-* chars */ }
<COMMENT>.|\n       { /* skip comment */ }

{ws}                { /* skip whitespace */ }

"PROGRAM"           { PRINT_TOKEN("(PROGRAM, \"%s\") ", yytext); }
"VAR"               { PRINT_TOKEN("(VAR, \"%s\") ", yytext); }
"BEGIN"             { PRINT_TOKEN("(BEGIN, \"%s\") ", yytext); }
"END"               { PRINT_TOKEN("(END, \"%s\") ", yytext); }
"IF"                { PRINT_TOKEN("(IF, \"%s\") ", yytext); }
"THEN"              { PRINT_TOKEN("(THEN, \"%s\") ", yytext); }
"ELSE"              { PRINT_TOKEN("(ELSE, \"%s\") ", yytext); }
"WHILE"             { PRINT_TOKEN("(WHILE, \"%s\") ", yytext); }
"DO"                { PRINT_TOKEN("(DO, \"%s\") ", yytext); }
"INTEGER"           { PRINT_TOKEN("(INTEGER, \"%s\") ", yytext); }
"REAL"              { PRINT_TOKEN("(REAL, \"%s\") ", yytext); }

":="                { PRINT_TOKEN("(ASSIGN, \"%s\") ", yytext); }
"="                 { PRINT_TOKEN("(EQ, \"%s\") ", yytext); }
"<>"                { PRINT_TOKEN("(NEQ, \"%s\") ", yytext); }
"<="                { PRINT_TOKEN("(LE, \"%s\") ", yytext); }
"<"                 { PRINT_TOKEN("(LT, \"%s\") ", yytext); }
">="                { PRINT_TOKEN("(GE, \"%s\") ", yytext); }
">"                 { PRINT_TOKEN("(GT, \"%s\") ", yytext); }

"+"                 { PRINT_TOKEN("(PLUS, \"%s\") ", yytext); }
"-"                 { PRINT_TOKEN("(MINUS, \"%s\") ", yytext); }
"*"                 { PRINT_TOKEN("(TIMES, \"%s\") ", yytext); }
"/"                 { PRINT_TOKEN("(DIVIDE, \"%s\") ", yytext); }

","                 { PRINT_TOKEN("(COMMA, \"%s\") ", yytext); }
":"                 { PRINT_TOKEN("(COLON, \"%s\") ", yytext); }
";"                 { PRINT_TOKEN("(SEMICOLON, \"%s\") ", yytext); }
"("                 { PRINT_TOKEN("(LPAREN, \"%s\") ", yytext); }
")"                 { PRINT_TOKEN("(RPAREN, \"%s\") ", yytext); }
"."                 { PRINT_TOKEN("(PERIOD, \"%s\") ", yytext); }

{float}             { PRINT_TOKEN("(FLOAT, \"%s\") ", yytext); }
{int}               { PRINT_TOKEN("(INT, \"%s\") ", yytext); }
{id}                { PRINT_TOKEN("(ID, \"%s\") ", yytext); }

.                   { PRINT_TOKEN("(ERRORCHAR, \"%s\") ", yytext); }

%%

int yywrap() { return 1; }

int main(int argc, char **argv) {
    if(argc >= 2) {
        yyin = fopen(argv[1], "r");
        if(!yyin) { printf("Can't open file %s\n", argv[1]); return 1; }
        if(argc >= 3) yyout = fopen(argv[2], "w");
        else yyout = stdout;
    } else {
        yyin = stdin;
        yyout = stdout;
    }
    yylex();
    if(argc >= 2) fclose(yyin);
    if(argc >= 3) fclose(yyout);
    return 0;
}
```



老残测试样例每5个token换一次行，找半天以为是碰到分号换行





