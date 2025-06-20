## lab5-1

.l

```c
%{
#include "test5-1.tab.h"
int yywrap(void){ return 1; }
%}

ws      [ \t]
true    "true"
false   "false"
or      "or"
and     "and"
not     "not"

%%

{true}      { return TRUE; }
{false}     { return FALSE; }
{or}        { return OR; }
{and}       { return AND; }
{not}       { return NOT; }
"("         { return LPAREN; }
")"         { return RPAREN; }
{ws}        { /* skip */ }
"\n"        { return ENTER; }
.           { printf("LEX ERROR: %s\n", yytext); }

%%
```



.y

```c
%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%union {
    int bval;
}

%token TRUE FALSE OR AND NOT LPAREN RPAREN ENTER
%type <bval> S

%left OR
%left AND
%right NOT

%%

input:
    S ENTER { printf("%s\n", $1 ? "true" : "false"); }
    ;

S:
      S OR S   { $$ = $1 || $3; }
    | S AND S  { $$ = $1 && $3; }
    | NOT S    { $$ = !$2; }
    | LPAREN S RPAREN { $$ = $2; }
    | TRUE     { $$ = 1; }
    | FALSE    { $$ = 0; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}

int main() {
    yyparse();
    return 0;
}
```





## lab5-2

.l

```c
%{
#include "test5-2.tab.h"
int yywrap(void){ return 1; }
%}

ws      [ \t]
true    "true"
false   "false"
or      "or"
and     "and"
not     "not"

%%

{true}      { return TRUE; }
{false}     { return FALSE; }
{or}        { return OR; }
{and}       { return AND; }
{not}       { return NOT; }
"("         { return LPAREN; }
")"         { return RPAREN; }
{ws}        { /* skip */ }
"\n"        { return ENTER; }
.           { printf("LEX ERROR: %s\n", yytext); }

%%
```



.y

```c
%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%union {
    int bval;
}

%token TRUE FALSE OR AND NOT LPAREN RPAREN ENTER
%type <bval> S

%left OR
%left AND
%right NOT

%%

input:
    S ENTER { printf("%s\n", $1 ? "true" : "false"); }
    ;

S:
      S OR S   { $$ = $1 || $3; }
    | S AND S  { $$ = $1 && $3; }
    | NOT S    { $$ = !$2; }
    | LPAREN S RPAREN { $$ = $2; }
    | TRUE     { $$ = 1; }
    | FALSE    { $$ = 0; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}

int main() {
    yyparse();
    return 0;
}
```

