/************************************************************/
/*    NAME: Jonathan Garcia-Mallen                          */
/*    ORGN: MIT                                             */
/*    FILE: PrimeFactorTester.h                             */
/*    DATE:                                                 */
/************************************************************/

#ifndef PrimeFactorTester_HEADER
#define PrimeFactorTester_HEADER

#include <string>
#include <vector> 
#include "MOOS/libMOOS/MOOSLib.h"

class PrimeFactorTester : public CMOOSApp
{
 public:
   PrimeFactorTester();
   ~PrimeFactorTester();

 protected:
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();
   void RegisterVariables();

 private: // Configuration variables

 private: // State variables
   unsigned int m_iterations;
   double       m_timewarp;
   struct MessageData{
     unsigned long int original;
     int recieved;
     int calculated;
     double solve_time;
     std::vector<int> factors;
     std::string username;
     bool valid;
   };
  
 private: // helper methods
   std::string GenValidityString(std::string&);
};

#endif 
