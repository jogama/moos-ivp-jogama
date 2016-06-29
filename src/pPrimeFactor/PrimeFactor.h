/************************************************************/
/*    NAME: Jonathan Garcia-Mallen                          */
/*    ORGN: MIT                                             */
/*    FILE: PrimeFactor.h                                   */
/*    DATE:                                                 */
/************************************************************/

#ifndef PrimeFactor_HEADER
#define PrimeFactor_HEADER
 
#include "MOOS/libMOOS/MOOSLib.h"
#include "FactoredInput.h"

class PrimeFactor : public CMOOSApp
{
 public:
   PrimeFactor();
   ~PrimeFactor();

 protected:
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();
   void RegisterVariables();

   // private: // Configuration variables

 private: // State variables
   std::list<FactoredInput> m_unfinished_results;    
   unsigned int m_iterations;
   double       m_timewarp;
   int m_nums_received;
   int m_nums_processed;
};

 #endif
