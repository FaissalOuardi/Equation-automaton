%{
#include <iostream>
#include "Regexp.cc"
#include "test.tab.h" 

Regexp *reg;
Regexp *ep = new Regexp(); // to get the token types that we return
%}
%option noyywrap
%%

"@epsilon" {reg = ep;
	return lettre;}
[a-zA-Z] {
	// we have to copy because we can't rely on yytext not changing underneath us:
	char *res = new char[strlen(yytext) + 1];
	strcpy(res, yytext);
	//#include "Regexp.cc"yylval.REG = new Regexp(yytext[0]);
        reg = new Regexp(yytext[0]); 
	return lettre;}

"\n" {return '\n';}
.    {return yytext[0];}
%%
