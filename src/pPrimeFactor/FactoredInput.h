/************************************************************/
/*    NAME: Jonathan Garcia-Mallen                          */
/*    ORGN: MIT                                             */
/*    FILE: FactoredInput.h                                 */
/*    DATE:                                                 */
/************************************************************/

#ifndef FACTOREDINPUT_H 
#define FACTOREDINPUT_H 

#include <list>
#include <iostream>
#include <string>  

class FactoredInput
{
 private:
   // Quantities used in result string
   unsigned long int original;
   int order_received; 
   double solve_time;
   std::list<int> factors;
   std::string username = "jogama"; // should be const IMO, but don't know how to.

   // State variables
   unsigned long int working_number;
   unsigned int working_divisor;
   double start_time;

 public:
   FactoredInput(unsigned long int, int, int);
   FactoredInput();
   bool is_finished() {if(working_number == 1)
       return true;
       else return false;}
   void do_work();
   std::string get_result(double, int); 
};

#endif // FACTOREDINPUT.H 
