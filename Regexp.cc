#include "Regexp.h"


// ------------------
// -- Constructors --
// ------------------
Regexp::Regexp() {
  is_epsilon = true; //epsilon
  is_letter= false;
  is_union= false;
  is_concat= false;
  is_star= false;
}

Regexp::Regexp(char letter) {
  is_epsilon = false;
  is_letter= true; //letter
  is_union= false;
  is_concat= false;
  is_star= false;
  this->letter = letter;
}

Regexp::Regexp(op_t op, Regexp* reg) {
  is_epsilon = false;
  is_letter= false; 
  is_union= false;
  is_concat= false;
  is_star= true; //star
  this->reg1 = reg;
  this->reg2 = NULL;
}

Regexp::Regexp(op_t op, Regexp* r1, Regexp* r2) {
  is_epsilon = false;
  is_letter= false; 
  is_star= false;
  is_union= false;
  is_concat= false;
  this->reg1 = r1;
  this->reg2 = r2;

  if(op == CONCAT){
    is_concat = true;
   
   }
      
  if(op == UNION){
    is_union = true;
    }
 
}

Regexp::Regexp(Regexp* reg) {
  is_epsilon = reg->is_epsilon;
  is_letter= reg->is_letter; 
  is_union= reg->is_union;
  is_concat= reg->is_concat;
  is_star= reg->is_star; 
  this->reg1 = reg;
  this->reg2 = NULL;
}

// --------------------
// -- Pretty-printer --
// --------------------
ostream& operator <<(ostream& sout, Regexp& r) {
  if(r.is_epsilon)
    sout << "\u03F5";
  if(r.is_letter)
    sout << r.letter;
  if(r.is_concat)
    sout << "(" << *(r.reg1) << ").(" << *(r.reg2) << ")";
  if(r.is_union)
    sout << "(" << *(r.reg1) << ")+(" << *(r.reg2) << ")";
  if(r.is_star)
    sout << "(" << *(r.reg1) << ")*";
  return sout;
}




// ------------------------
// -- Pretty constructor --
// ------------------------
Regexp& w(char c) {
  return *new Regexp(c);
}

Regexp& w(string s) {
  Regexp* result = new Regexp();
  for(int i=0; i<s.length(); i++)
    result = new Regexp(CONCAT,result,new Regexp(s[i]));
  return *result;
}


Regexp& operator +(Regexp& r1, Regexp& r2) {
  return *new Regexp(UNION,&r1,&r2);
}

Regexp& operator *(Regexp& r1, Regexp& r2) {
  return *new Regexp(CONCAT,&r1,&r2);
}

Regexp& star(Regexp& r) {
  return *new Regexp(STAR,&r);
}



Regexp& Regexp::operator =( Regexp& r) {
     
  return *this;
}
