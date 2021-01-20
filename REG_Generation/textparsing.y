%{
#include<stdio.h>
#include <stdlib.h>
#include<string.h>

#define YYSTYPE char *

char exp[20];

%}

%token  symbol 
%%

expression: expression '\n' {printf("%s\n",exp);} 
        | expression '+' expression  { strcpy(exp,$1); strcat(exp,"+");strcat(exp,$3); printf("%s + %s",$1,$3); }
      
        | symbol {strcpy(exp,$1);}
        ;


%%

#include <stdio.h>
#include <ctype.h>
char *progname;

main( argc, argv )
char *argv[];
{
  progname = argv[0];
  yyparse();
}

yyerror( s )
char *s;
{
  fprintf( stderr ,"%s: %s\n" , progname , s );
}
