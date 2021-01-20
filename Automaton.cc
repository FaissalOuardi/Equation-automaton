
#include "Automaton.h"
#include <set>
#include <string.h>
#include <stdlib.h>

 


// ** Constructeur
Automaton::Automaton(set<char> sigma, Regexp* r,map<State*,State*> *Star) {
  int l=0;
  alphabet = sigma;
  Label* eps = new Label(-1);   // epsilon
  Label* epd = new Label(-2);   // (*Right) epsilon
  Label* epg = new Label(-3);   // left epsilon
  Label* epe = new Label(-4);   // epsilon star
  Label* epp = new Label(-5);   // epsilon plus
  Label* epc = new Label(-6);   // epsilon concatenation
  
  int class_nb=0;
  if(r->is_epsilon) {
  	  // Create 2 states
      
      
      State* p1=new State();
     
      State* q1=new State();
      state.push_back(p1);
      state.push_back(q1);
      
      // Transition [state0 --epsilon--> state1]
      succ[state[0]][eps] = state[1];
      back[state[1]][state[0]] = eps ;
      
      initial_state = state[0];
      final_state.push_back(state[1]);
 
      
    }

  if(r->is_letter) {
      //Create 2 states

 
  State* p2=new State();


      State* q2=new State();
      state.push_back(p2);
      state.push_back(q2);
      Label* c = new Label(r->letter);
      //Transition [state0 --letter--> state1]
      succ[state[0]][c] = state[1];
   
      back[state[1]][state[0]] = c;
 
      initial_state = state[0];
      final_state.push_back(state[1]);

   
    }

  if(r->is_star) {
      // Create 2 states
    
         State* p3=new State();
      
      state.push_back(p3); // Initial state
     

      Automaton* a = new Automaton(alphabet,r->reg1,Star);
        succ[state[0]][epe] = a->initial_state;           //initial -> old_initial
        back[a->initial_state][state[0]] = epe;  

        
      
      // Copy the automaton a in the current automaton
      for(int i=0; i<a->state.size(); i++) {		        // Iterating over the states of a
	 	 state.push_back(a->state[i]);		        // Copy state
	 	 succ[a->state[i]] = a->succ[a->state[i]];	// Copy transitions
                 back[a->state[i]] = a->back[a->state[i]];

                
	  }
    
         State* p4=new State();
     
         state.push_back(p4); // Final state
      
      
 int rank=a->state.size()+1;
   
      
      succ[a->final_state[0]][eps] = state[rank];           //old_initial -> final
      back[state[rank]][a->final_state[0]] = eps;
      succ[state[0]][eps] = state[rank];  //old_final -> old_initial
      back[state[rank]][state[0]] = eps;
  
	  
      // Set initial and final states
      initial_state = state[0];
      final_state.push_back(state[rank]);
      (*Star)[a->initial_state] = state[rank]; 
     
    }

  if(r->is_concat) {
   //  state.push_back(new State()); // Initial state
      

      Automaton* a1 = new Automaton(alphabet,r->reg1,Star);
      Automaton* a2 = new Automaton(alphabet,r->reg2,Star);

	// succ[state[0]][new Label()] = a1->initial_state; //initial -> old_initial
	  
// Copy the automaton a1 in the current automaton
      for(int i=0; i<a1->state.size(); i++) {
	  	state.push_back(a1->state[i]);
	  	succ[a1->state[i]] = a1->succ[a1->state[i]];
                back[a1->state[i]] = a1->back[a1->state[i]];
	  }

       
     
      // Copy the automaton a2 in the current automaton
      for(int i=0; i<a2->state.size(); i++)	{
	  	state.push_back(a2->state[i]);
	  	succ[a2->state[i]] = a2->succ[a2->state[i]];
                back[a2->state[i]] = a2->back[a2->state[i]];
                          
         
	  }
  // for(map<Label*,State*>::iterator it =succ[a2->initial_state].begin(); it != succ[a2->initial_state].end(); it++)
                   succ[a1->final_state[0]][epc] = a2->initial_state;
                   back[a2->initial_state][a1->final_state[0]] = epc;
                   
     // state.push_back(new State()); 

     int rank=a1->state.size()+a2->state.size()-1;
    
   //  succ[a2->final_state[0]][new Label(0)] = state[rank];

      initial_state = state[0];
      final_state.push_back(state[rank]); 

     
    }

  if(r->is_union) {
    
      Automaton* a1 = new Automaton(alphabet,r->reg1,Star);
      Automaton* a2 = new Automaton(alphabet,r->reg2,Star);
          
           State* p5=new State();
    
	 state.push_back(p5);
      
	  // Copy the automaton a1 in the current automaton
      for(int i=0; i<a1->state.size(); i++) {
	  	state.push_back(a1->state[i]);
	  	succ[a1->state[i]] = a1->succ[a1->state[i]];
                back[a1->state[i]] = a1->back[a1->state[i]];
	  }
      
      // Copy the automaton a2 in the current automaton
      for(int i=0; i<a2->state.size(); i++)	{
	  	state.push_back(a2->state[i]);
	  	succ[a2->state[i]] = a2->succ[a2->state[i]];
                back[a2->state[i]] = a2->back[a2->state[i]];
                
	  }
       
        State* p6=new State();
    
      state.push_back(p6);

      int rank=a1->state.size()+a2->state.size()+1;
      // Add epsilon transitions
      succ[state[0]][epd] = a1->initial_state;
      succ[state[0]][epg] = a2->initial_state;
      succ[a1->final_state[0]][eps] = state[rank];
      succ[a2->final_state[0]][eps] = state[rank];

      back[a1->initial_state][state[0]] = epd;
      back[a2->initial_state][state[0]] = epg;
      back[state[rank]][a1->final_state[0]] = epp;
      back[state[rank]][a2->final_state[0]] = epp;
       // Set initial and final states 
      initial_state = state[0];
      final_state.push_back(state[rank]);
     

    }
}


int Automaton::state_rank(State* s) {
  for(int i=0; i<state.size(); i++)
    if(state[i] == s)
      return i;
  cerr << "Automaton::state_rank: state not found" << endl;
  exit(1);
}



/*************************************************************************************
                           INDEXATION 1
**************************************************************************************/

void Automaton::indexepsilon1(){
     int rank, flag;
for(int i=0; i<state.size(); i++)  
      {
        state[i]->number=i; 

      }
               
 
          
}
																																																																
/*************************************************************************************
                           INDEXATION 2
**************************************************************************************/
void Automaton::indexepsilon2(map<State*,State*> *Star){
  for(int i=0; i<state.size(); i++) {         
    for(map<Label*,State*>::iterator it = succ[state[i]].begin(); it != succ[state[i]].end(); ++it) 
      {    
      	   if(it->first->eps_i==-4){                          
                      for(map<State*,Label*>::iterator iter = back[(*Star)[it->second]].begin(); iter != back[(*Star)[it->second]].end(); ++iter)
                                iter->second->eps_i=it->second->number;
                }
             
      } 
   }
    
}
/*************************************************************************************
                           INDEXATION 3
**************************************************************************************/

void Automaton::indexepsilon3(map<State*,State*> *Star1){


Label* eps = new Label(-1);

 
 for(map<State*,State*>::iterator it = (*Star1).begin(); it != (*Star1).end(); ++it) 
    //if(it->first->number==1)
    //succ[it->second][eps]=state[0] ;
    //else
       succ[it->second][eps]=it->first ;

}

/****************************************************************************************
                          USEFUL FONCTIONS 
****************************************************************************************/

set<State*> operator +(set<State*> s1, set<State*> s2) {
  set<State*> result = s1;
  for(set<State*>::const_iterator it = s2.begin(); it != s2.end(); ++it)
    result.insert(*it);

  return result;
}


set<State*> Automaton::epsilon_closure_(State* s, set<State*> reached) {
  set<State*> result;
  result.insert(s);

  if(reached.find(s) != reached.end())
    return result;

  reached.insert(s);

  for(map<Label*, State*>::const_iterator it = succ[s].begin(); it != succ[s].end(); ++it)
    if(it->first->is_epsilon)
      //For each epsilon-transition starting from s...
      result = result + epsilon_closure_(it->second,reached);

  return result;
}


set<State*> Automaton::epsilon_closure(State* s) {
  set<State*> reached;
  return epsilon_closure_(s,reached);
}


set<State*> Automaton::epsilon_closure(set<State*> state_set) {
  set<State*> result;
  for(set<State*>::const_iterator it = state_set.begin();it != state_set.end(); ++it)
    //For each state of the set...
    result = result + epsilon_closure(*it);
  return result;
}

int Automaton::is_final(State* state) {
 
  for(vector<State*>::const_iterator it = final_state.begin();it != final_state.end(); ++it)
       if (*it==state)
             return 1;
              
  return 0;
}

ostream& operator<< (ostream& sout, set<State*> s) {
  sout << "{";
  for(set<State*>::const_iterator it = s.begin(); 
      it != s.end(); ++it)
    cout << *it << " ";
  sout << "}"; 
}

State* get_state(set<State*> actual_det_state, map<State*, set<State*> > actual_det_states) {
  for(map<State*, set<State*> >::const_iterator it = actual_det_states.begin(); 
      it != actual_det_states.end(); ++it)
    //For each det_state -> vector<non_det_states> ..
    if(it->second == actual_det_state)
      return it->first;

  return 0; //not found => return NULL pointer (0)
}


/********************************************************************************************
                                  epsilon removal
********************************************************************************************/


Automaton* Automaton::epsilon_closure() {
  Automaton* result = new Automaton(alphabet);
  map<State*,set<State*> > non_epsilon_states;

  result->state.push_back(new State());
  result->initial_state = result->state[0];
  non_epsilon_states[result->state[0]] = epsilon_closure(initial_state); //initial state = closure(initial)
  //   cout << epsilon_closure(initial_state).size(),"\n";
  vector<State*> state_stack;
  state_stack.push_back(result->state[0]); 

  //
  // Build the automaton by depth-first traversal
  //

 while(state_stack.size() != 0) 
   {	//For each (set of) state...
     
      State* current_state = state_stack.back();
      state_stack.pop_back();           //pop a state

      //
      // Collect outgoing letters and corresponding target states 
      //
      set<char> outgoing_letters;

      map<char,set<State*> > chartarget; //letter -> set of target states
    

      set<State*> actual_states = non_epsilon_states[current_state];


      for(set<State*>::const_iterator it = actual_states.begin(); it != actual_states.end(); ++it) 
      { //For each (non-det) state in the current state...
	    State* non_eps_state = *it;
              

	    //For each transition starting from non-det state... 
	    for(map<Label*,State*>::const_iterator it2 = succ[non_eps_state].begin();it2 != succ[non_eps_state].end(); ++it2)
	       {
                                       
                                        if(it2->first->is_letter){
                                        outgoing_letters.insert(it2->first->letter);
                                        chartarget[it2->first->letter].insert(it2->second);
                                      
                                            }                                                         
	       }
        }
       
        // Then, update the target automaton
      
        for(set<char>::const_iterator it = outgoing_letters.begin(); it != outgoing_letters.end(); ++it) 
        { //For each outgoing letter...
             
           for(set<State*>::iterator it1=chartarget[*it].begin(); it1!=chartarget[*it].end(); it1++)
           { 
                   set<State*> closure = epsilon_closure(*it1);

                  State* target_state = get_state(closure,non_epsilon_states);
	    
	         if(target_state != 0 ){	//Target state already exists?
	          result->successor[current_state][new Label(*it)].insert(target_state);
           
                  }
                //just add a transition
	         else 
                  {			        //Target state does not exists?
	        //Create a new (det) state, and map it to its (non-det) states
	           State* target_state = new State();
	           non_epsilon_states[target_state] = closure;
	           result->state.push_back(target_state);
   
	        //Add a transition labelled by the letter
	          result->successor[current_state][new Label(*it)].insert(target_state);
	 
	        //Mark target state to be processed
	          state_stack.push_back(target_state);
                  } 
	   } 
         }  
	  	
 }	  	
 
 
    for(vector<State*>::const_iterator iter =final_state.begin();iter!= final_state.end(); ++iter)  {       
          State* non_epsilon_final_state = *iter; //Assumption: only one final state in non-det automaton

         for(map<State*,set<State*> >::const_iterator it = non_epsilon_states.begin(); it != non_epsilon_states.end(); ++it)
              if (it->second.find(*iter) != it->second.end())	// non-det final state in the non-det set?
               result->final_state.push_back(it->first);	
     }
return result;
}


/******************************************************************************************************************
                                     Indexation of identical subexpressions in DFA (Bubenzer Algorithm 2013)
*******************************************************************************************************************/
 void Automaton::subexp_id(State* q, map<map<int,int>,int,classcomp>  *Reg, map<State*, int> *Map){

   for(map<Label*,State*>::const_iterator it = succ[q].begin(); it != succ[q].end(); it++){ //For each out going transition...
	   if (!(*Map)[it->second])
                subexp_id(it->second,Reg,Map);
            state[it->second->number] = state[(*Map)[it->second]];
     }

map<int,int>  sign;
      for(map<Label*,State*>::const_iterator it = succ[q].begin(); it != succ[q].end(); it++)
               { 
              if(it->first->eps_i != -1) 
               sign[it->first->eps_i]=it->second->number;
               }  

  if(!(*Reg)[sign]){
  
              (*Reg)[sign]=q->number;
              (*Map)[q]= q->number;
        }               
    else 
        {          
              (*Map)[q]= (*Reg)[sign];
                q->number=(*Map)[q];
        }
}

/******************************************************************************************************************
                     Indexation of identical C-continuations (Bubenzer Algorithm 2013)
*******************************************************************************************************************/
 void Automaton::continuation_id(State* q,map<string, State*> *Map,map<State*,State*> *Star){

   for(map<Label*,State*>::iterator it = succ[q].begin(); it != succ[q].end(); it++){ //For each out going transition...
	  if (it->second->continuation =="0")
            {  
               continuation_id(it->second,Map,Star);
            
            }
    }
    int rank= state_rank(q);
    string s;
  
  
  if(succ[q].empty()){  
       q->continuation=string("final");
      }
  else{
        
        for(map<Label*,State*>::iterator it = succ[q].begin(); it != succ[q].end(); it++){
          if(it->first->is_letter){
               
                 q->continuation=it->first->letter+string(it->second->continuation);
                 
                 it->second->continuation="*"+string(it->second->continuation);
              
                 if(!(*Map)[it->second->continuation]){
                 
                  (*Map)[it->second->continuation]= it->second;
                       
                 }               
                 else  
                     {     
                             (*Star).erase((*Map)[it->second->continuation]);
                              for(map<State*, Label*>::iterator iter = back[(*Map)[it->second->continuation]].begin(); iter != back[(*Map)[it->second->continuation]].end(); ++iter) 
                                 {   back[it->second][iter->first]=iter->second;
                                    succ[iter->first][iter->second]=it->second;
                                                                                  
                                 } 
                          
  

                      (*Map)[it->second->continuation]=it->second;
                      
                      
                      }
                   
                             
            }
          else
           if(it->first->eps_i<0)
            {
             if((it->first->eps_i==-1)){
             
               q->continuation=it->second->continuation;
             }
             else  
               if(it->first->eps_i==-6){
                q->continuation=it->second->continuation;
               }
               else
                 if((it->first->eps_i==-2)||(it->first->eps_i==-3)) 
                    if(q->continuation=="0")
                    q->continuation = string(to_string(it->second->number));
                    else
                        q->continuation = string(q->continuation)+"+"+string(to_string(it->second->number));      
             }
           else 
                  if(it->second->continuation!="final")
                   q->continuation=to_string(it->first->eps_i)+"."+it->second->continuation;
                  else
                   q->continuation=to_string(it->first->eps_i);
        }
   }
     if(q==initial_state)
        {
         q->continuation = "*"+q->continuation;
         if((*Map)[q->continuation]){
            (*Star).erase((*Map)[q->continuation]);
                              for(map<State*, Label*>::iterator iter = back[(*Map)[q->continuation]].begin(); iter != back[(*Map)[q->continuation]].end(); ++iter) 
                                 {   back[q][iter->first]=iter->second;
                                     succ[iter->first][iter->second]=q;
                                                                                  
                                 } 
           }
        }       
       
   
 }

/******************************************************************************************************************
                                Reduction of  of identical c-continuation
*******************************************************************************************************************/
void Automaton::continuation_reduce(State* q, vector<State*> *S){
 
         
      for(map<Label*,State*>::iterator it = succ[q].begin(); it != succ[q].end(); it++) //For each out going transition...	 
             {  
               continuation_reduce(it->second,S);
             }
   
    if(q->number != -1) {

             (*S).push_back(q);
              q->number = -1;
        
   }
}
/******************************************************************************************************************
                                Pretty -printer
*******************************************************************************************************************/
// *** Pretty-printers
void Automaton::print_dot_test(ostream& sout) {
  sout << "digraph g {" << endl
         << "rankdir=LR;" << endl;
      
  //Nodes
  for(int i=0; i<state.size(); i++) { //For each state...
   // sout << "  state" << i << "[shape=circle, label= \""<< "(" << i << "," << state[i]->number << "," << state[i]->continuation <<  ")";
     sout << "  state" << i << "[shape=circle, label= \""<<  i ;
    if(initial_state == state[i])
	  sout << "\n initial";
    for(int j=0; j<final_state.size(); j++)
	  if(final_state[j] == state[i])
	    sout << "\n final";
    sout << "\"];" << endl;
  }

  //Transitions
  for(int i=0; i<state.size(); i++) {
    for(map<Label*,set<State*> >::const_iterator it = successor[state[i]].begin(); it != successor[state[i]].end(); ++it){
	  Label* lab= it->first;
          for(set<State*>::const_iterator iter = it->second.begin(); iter != it->second.end(); ++iter)
	  sout << "  state" << i << " -> state" << state_rank(*iter)
	       << "[label=\"" << (*lab) << "\"];" << endl;
  }
  }
  sout << "}" << endl;
}


/**************************************************************************************
                          PRETTY PRINTERS
**************************************************************************************/

// *** Pretty-printers
void Automaton::print_dot(ostream& sout) {
  sout << "digraph g {" << endl
         << "rankdir=LR;" << endl;
      
  //Nodes
  for(int i=0; i<state.size(); i++) { //For each state...
    sout << "  state" << i << "[shape=circle, label= \""<< "(" << i << "," << state[i]->number << "," << state[i]->continuation <<  ")";
     // sout << "  state" << i << "[shape=circle, label= \"";
    if(initial_state == state[i])
	  sout << "\n initial";
    for(int j=0; j<final_state.size(); j++)
	  if(final_state[j] == state[i])
	    sout << "\n final";
    sout << "\"];" << endl;
  }

  //Transitions
  for(int i=0; i<state.size(); i++) {
    for(map<Label*,State*>::const_iterator it = succ[state[i]].begin(); it != succ[state[i]].end(); ++it)
	  //For each transition starting from 'state'...
	  sout << "  state" << i << " -> state" << state_rank(it->second)
	       << "[label=\"" << *(it->first) << "\"];" << endl;
  }
  sout << "}" << endl;
}



ostream& operator <<(ostream& sout, Label& label) {


  if(label.is_epsilon){
         if(label.eps_i==-1)
              sout << "\u03F5";
            else
               if(label.eps_i==-6)
                   sout << "\u03F5.";
               else  
                if(label.eps_i==-5)
                   sout << "\u03F5+";
          	else 
                 if(label.eps_i==-4)
                   sout << "\u03F5*";
          	 else if(label.eps_i==-3)
                   sout<< "d⁺";
        	      else
                        if(label.eps_i==-2)
                           sout<< "g⁺";
                        else 
                              sout << "\u03F5" << label.eps_i;
   }
 else
          if(label.is_letter) 
                   sout << label.letter;     
      
 return sout;        }          
	
