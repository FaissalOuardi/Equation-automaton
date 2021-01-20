#ifndef __AUTOMATON_H
#define __AUTOMATON_H

#include "Regexp.h"

#include <iostream>
#include <stdlib.h>

#include <vector>
#include <map>
#include <set>

using namespace std;


class State {
 public:
   int number;
   string continuation="0";
   State(){}
   State(int l) {number=l;}
 
};

class Label {
 public:
  int is_epsilon, eps_i, is_letter;
  char letter;

  Label(int i) { is_epsilon = true; 
                 is_letter = false; eps_i=i; }
  Label(char l) { is_epsilon = false; is_letter = true; letter = l; eps_i=l; }

};

struct classcomp {
 bool operator() (const map<int,int>& lhs, const map<int,int>& rhs) const {	
  return lhs<rhs;          
            }
};

class Automaton {
 public:
  set<char> alphabet;			// Alphabets du language de l'automate
  vector<State*> state;			// États
  map<State*, map<Label*, State*> > succ;	// Relation de transition d'un DFA
  map<State*, map<Label*, set<State*> > > successor; // Relation de transition d'un NFA
  map<State*,map<State*, Label*> >  back;	// Relation de transition

  State* initial_state;			// État initial
  vector<State*> final_state;	// États finaux
  
  State* default_state; //	État "puits" (seulement après complétion)


  // ** Constructors
  Automaton(set<char> sigma) { alphabet = sigma; 
  Label* eps = new Label(-1);   // epsilon
  Label* epd = new Label(-2);   // (*Right) epsilon
  Label* epg = new Label(-3);   // left epsilon
  Label* epe = new Label(-4);   // epsilon star
  Label* epp = new Label(-5);   // epsilon plus
  Label* epc = new Label(-6);   // epsilon concatenation
 }	
     // Automate vide
  Automaton(set<char> sigma, Regexp* r,map<State*,State*> *Star);			

  set<State*> epsilon_closure(State* s);
  set<State*> epsilon_closure(set<State*> v);

  Automaton* epsilon_closure();

  Automaton* minimize();

  

  pair<pair< vector<vector<int> > , map<char,int> > , vector<int> > transition_table(set<char> markers);
  //==> (  ([transition table],[mapping letter -> rank])  ,  [mapping state -> token]  )

int state_rank(State* s);
int is_final(State* s);

void indexepsilon1();
void indexepsilon2(map<State*,State*> *Star);
void indexepsilon3(map<State*,State*> *Star);
void subexp_id(State* q, map<map<int,int>,int,classcomp> *Reg, map<State*, int> *Map);
void continuation_id(State* q,map<string, State*> *Map,map<State*,State*> *Star);
void continuation_reduce(State* q, vector<State*> *S);



  // ** Pretty-printers
  void print_code(ostream& sout);
  void print_dot(ostream& sout);
  void print_dot_test(ostream& sout);

 private:
  set<State*> epsilon_closure_(State* s, set<State*> reached);
};

ostream& operator <<(ostream& sout, Label& label);

#endif
