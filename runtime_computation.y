%{
#include "Regexp.h"
#include "Automaton.cc"

#include <iostream>
#include <chrono>
#include <numeric>
#include <sys/time.h>
#include <unistd.h>

#include <fstream>

using namespace std;
#include <stdlib.h>
#include <string.h>
extern int yylex();
extern int yyparse();
int yyerror(string);
extern FILE *yyin;



#include <bitset>

set<char> sigma;
   
     char c;
     int n=0;
 using namespace std;
using namespace std::chrono;   
  
ofstream file_out("f_result_linear_200_210.txt", ios::out);
        Regexp *eps = new Regexp();  // Epsilon Reg. Exp.

   /* Variables Declaration */

          map<State*,State*> Star;
          map<map<int,int>,int,classcomp>  Reg;
          map<State*, int> Map;
          map<map<int,string>,State* >  Continu;
          map<string,State*> M;


extern Regexp *reg;
Regexp  *exp;
%}


%union {
 
   Regexp* REG;
      
}


%type <REG>   expression
%token <REG>  lettre

%left '+'

%%
file : 
     | file line  ;
line : '\n'
     | expression '\n' {  exp = $1; /*preprocessing*/
   
   



  
   ///////////////////////////////////
   //    Thompson construction      //
   ///////////////////////////////////
          //  cout << *exp << " valid expression"<< endl;
       
            Automaton* aut_re = new Automaton(sigma,exp,&Star);

   
   
               aut_re->indexepsilon1();
    
   auto avant = system_clock::now();
          
   ///////////////////////////////////
   //    SubExpressions Identif     //
   ///////////////////////////////////

   
    State* q_0=aut_re->initial_state;
   
    aut_re->subexp_id(q_0,&Reg,&Map);

   ///////////////////////////////////
   //    C-continuation Identif     //
   ///////////////////////////////////

    
 
   q_0->continuation="0";
   aut_re->indexepsilon2(&Star);
 
   aut_re->continuation_id(q_0,&M,&Star);
   aut_re->indexepsilon3(&Star);
   Automaton* aut_re1 = aut_re->epsilon_closure();  
   

 ///////////////////////////////////
   //    Run-Time computation   //
   ///////////////////////////////////

 auto apres = system_clock::now();
 int x=  std::chrono::duration_cast<milliseconds>(apres-avant).count();
   //  cout << "Temps requis : " << x << " micros." << endl;


  file_out << x << endl;
  
  
  

              delete reg; delete exp; delete aut_re1; Star.clear();   Reg.clear(); Map.clear(); Continu.clear(); M.clear();}
;
expression : expression '+' expression {$$ = new Regexp(UNION,$3,$1);  }
         |  expression  ' ' expression {$$ = new Regexp(CONCAT,$1,$3); }
         |  expression '*' {$$ = new Regexp(STAR,$1); }
         | '(' expression ')' { $$ = $2 ;  }
	| lettre { $1=reg;  $$ = $1 ; }
	;
%%
int yyerror(string s)
{
  printf("Syntax error\n");
}
int main(int argc, char* argv[]){
  
   for(c='a'; c <= 'z'; c++)
        sigma.insert(c);
          
      int n=0;
     yyin = fopen("f_linear_200_210.txt","r");
yyparse();
  file_out.close(); 

return 0;
}
