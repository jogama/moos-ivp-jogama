/************************************************************/
/*    NAME: Jonathan Garcia-Mallen                          */
/*    ORGN: MIT                                             */
/*    FILE: FactoredInput.cpp                               */
/*    DATE:                                                 */
/************************************************************/



#include "FactoredInput.h"
#include <sstream>

using namespace std;

FactoredInput::FactoredInput(unsigned long int input, int order,
			      int time){
  original        = input;
  order_received  = order;
  start_time      = time;
  working_divisor = 2;
  working_number  = original;  
}

FactoredInput::FactoredInput(){
  //for debugging
}

//---------------------------------------------------------
// Procedure: do_work()
//            Finds prime factors in
//                O(sqrt(original) time, O(1) space.
//            Called in PrimeFactor::Iterate()


void FactoredInput::do_work(){
  if(working_number != 1){
    if(working_number % working_divisor == 0){
      factors.push_back(working_divisor);
      working_number /= working_divisor;
    }
    else{
      working_divisor++;
    }
  }
}

//---------------------------------------------------------
// Procedure: get_result
//            returns a string in the form
// PRIME_RESULT = "orig=30030,received=34,calculated=33,
//                 solve_time=2.03,primes=2:3:5:7:11:13,
//                 username=jogama"
//            to be posted in MOOS.
string FactoredInput::get_result(double end_time, int order_processed){
  stringstream stream;

  stream << "PRIME_RESULT = \"orig=" << original << ","
	 << "received=" << order_received << ","
	 << "calculated=" << order_processed << ","
	 << "solve_time=" << end_time - start_time << ","
	 << "primes=";

  int lastfactor =factors.back();
  factors.pop_back();
  for(int prime : factors){
    stream << prime << ":";
  }

  stream << lastfactor << "," << username << "\"";  
  
  return stream.str();  
}
