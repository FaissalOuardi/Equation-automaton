#ifndef __REGEXP_H
#define __REGEXP_H

#include <iostream>

using namespace std;

enum op_t {
    UNION,
    CONCAT,
    STAR
  };

class Regexp {
 public:
  bool is_epsilon;
  
  bool is_letter;
  
  
  bool is_union;
  bool is_concat;
  bool is_star;

  char letter;
  
  Regexp* reg1;
  Regexp* reg2;
  
  // -- Constructors
  Regexp();									// epsilon
  Regexp(char letter);						// letter
  Regexp(op_t op, Regexp* r);				//star
  Regexp(op_t op, Regexp* r1, Regexp* r2);	//union, concat
  Regexp(Regexp* r);	

 // Regexp(const Regexp& r);
Regexp& operator =( Regexp& r); 
};
/* 
 A parser to be constructed each time
 a regular expression needs to be parsed.
 */





// -- Pretty-printer
ostream& operator <<(ostream& sout, Regexp& reg);

// -- Pretty constructor
Regexp& w(char c);
Regexp& w(string s);

Regexp& operator +(Regexp& r1, Regexp& r2);
Regexp& operator *(Regexp& r1, Regexp& r2);
Regexp& star(Regexp& r);



#endif
