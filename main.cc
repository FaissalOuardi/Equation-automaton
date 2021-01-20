#include "Regexp.cc"
#include "Automaton.cc"

#include <iostream>
//#include <istream>
#include <chrono>
#include <numeric>
#include <sys/time.h>
#include <unistd.h>

#include <fstream>
#include <bitset>
	
int main(int argc, char** argv) {
using namespace std;
using namespace std::chrono;
 
ofstream file_out1("equation.dot", ios::out);
ofstream file_out2("position.dot", ios::out);
 //  yyparse();
 
   /*preprocessing*/
   
    set<char> sigma;
   
     char c;
     for(c='a'; c <= 'z'; c++)
        sigma.insert(c);
  

        Regexp *eps = new Regexp();  // Epsilon Reg. Exp.

   /* Variables Declaration */

          map<State*,State*> Star;
          map<map<int,int>,int,classcomp>  Reg;
          map<State*, int> Map;
          map<map<int,string>,State* >  Continu;
          map<string,State*> M;
          

     /* Examples of regular expressions */

             // E = ((((a^*)b)^*)c)^*
   //  Regexp re =  star(star(star(w('a'))*w('a'))*w('a'));
             
             // E = a.(a^*)
   //   Regexp re =  (w('a')*star(w('a')));

            // E = (a^*).b
   //  Regexp re =  (star(w('a'))*w('b'));

             // E = (a.b^*+b)^*.a
      //  Regexp re =  (star((w('a')*star(w('b')))+w('b'))*w('a'));

            // E = (a+b)+eps
      //  Regexp re =  ((((w('a')+w('b'))+ *eps)*((w('a')+w('b'))+ *eps))*((w('a')+w('b'))+ *eps))*star(w('a')+w('b'));

             // E = ((a* b)+(a* b a)+a*)*
   // Regexp re =  (star((star(w('a'))*w('b'))+(((star(w('a'))*w('b'))*w('a'))+star(w('a'))))*w('b'));

             // E = ((a+b.c).d)^*.e
    // Regexp re =  (star((w('a')+(w('b')*w('c')))*w('d'))*w('e'));
             

      // Regexp re = (((w('a')*((w('b')*w('c'))*w('d')))+((w('a')*w('b'))*(w('c')*w('d')))));

           //   E = (a+b) (a*+(b a*)+b*)*
  Regexp re = (w('a')+w('b'))*(star(star(w('a'))+ w('b')*star(w('a'))+star(w('b'))));

             //     
      // Regexp re = ((star((w('a')*w('b'))+w('b'))*w('b'))*w('a'));
             //+(w('b')*(w('a')+w('b'))));
              
             // E = (a+eps).(b+eps).(c+eps).(d+eps)
     //   Regexp re = ((((w('a')+*eps)*(w('b')+*eps))*(w('c')+*eps))*(w('d')+*eps));
         
            // E = (a^*+a^*+.....+a^*+a^*)^*
   //  Regexp re = star((star(w('a'))+star(w('a')))+star(w('a'))+star(w('a')));
        
      //      E = ((a^*.b)^*+(a.(a^*.b)^*)))^*
        //      Regexp re = star(star(star(w('a'))*w('b'))+(w('a')*star(star(w('a'))*w('b'))));



      
      

  
   ///////////////////////////////////
   //    Thompson construction      //
   ///////////////////////////////////
          //  cout << *exp << " valid expression"<< endl;
       
            Automaton* aut_re = new Automaton(sigma,&re,&Star);

   
   
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
   /*

 ///////////////////////////////////
   //    Run-Time computation   //
   ///////////////////////////////////

 auto apres = system_clock::now();
 int x=  std::chrono::duration_cast<microseconds>(apres-avant).count();
   //  cout << "Temps requis : " << x << " micros." << endl;


 // file_out << x;
   cout << x << endl;
           
   /*///////////////////////////////////
   //    pretty printer               //
   ///////////////////////////////////*/               
  

 //   cout << aut_re1->state.size() << endl;           // print regular expression
 
  aut_re1->print_dot_test(file_out1);  // print Antimirov automaton
  
 

   aut_re->print_dot(file_out2);      // print thompson automaton

   

return 0;
}

