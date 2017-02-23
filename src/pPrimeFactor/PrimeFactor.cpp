/************************************************************/
/*    NAME: Jonathan Garcia-Mallen                          */
/*    ORGN: MIT                                             */
/*    FILE: PrimeFactor.cpp                                 */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "PrimeFactor.h"
#include "FactoredInput.h"

using namespace std;

//---------------------------------------------------------
// Constructor

PrimeFactor::PrimeFactor()
{
  m_iterations = 0;
  m_timewarp   = 1;

  m_nums_received  = 0;
  m_nums_processed = 0;   
}

//---------------------------------------------------------
// Destructor

PrimeFactor::~PrimeFactor()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool PrimeFactor::OnNewMail(MOOSMSG_LIST &NewMail)
{
  MOOSMSG_LIST::iterator p;
   
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;

    if(msg.GetKey() == "NUM_VALUE"){
      m_nums_received++;

      // convert to unsigned long int
      string sval = msg.GetString();
      unsigned long int input_num = stoul(sval);

      // Append to std::list of jobs
      FactoredInput fi;
      fi = FactoredInput(input_num, m_nums_received, MOOSTime());
      m_unfinished_results.push_back(fi);
    }
    
#if 0 // Keep these around just for template
    string key   = msg.GetKey();
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString(); 
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool PrimeFactor::OnConnectToServer()
{
   // register for variables here
   // possibly look at the mission file?
   // m_MissionReader.GetConfigurationParam("Name", <string>);
   // m_Comms.Register("VARNAME", 0);
	
   RegisterVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool PrimeFactor::Iterate()
{
  m_iterations++;

  // This could be done without a for loop, since Iterate() will iterate.
  // ¿Would it be better/more effient to take everything out of the for
  // and call fi.do_work() only once per Iterate()?
  
  list<FactoredInput>::iterator position;
  for(position=m_unfinished_results.begin(); position!=m_unfinished_results.end(); ) {

    // Select the FactoredInput object from the list to work with it
    FactoredInput& fi = *position;

    if(fi.is_finished()){
      m_nums_processed++;      
      string result = fi.get_result(MOOSTime(), m_nums_processed);
      
      // remove the object from the list (and from memory?).
      // and set position iterator to the next element.
      position = m_unfinished_results.erase(position);

      // post the result
      m_Comms.Notify("PRIME_RESULT", result);
    }
    else{
      fi.do_work();
      ++position;
    }
  }
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool PrimeFactor::OnStartUp()
{
  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(m_MissionReader.GetConfiguration(GetAppName(), sParams)) {
    list<string>::iterator p;
    for(p=sParams.begin(); p!=sParams.end(); p++) {
      string original_line = *p;
      string param = stripBlankEnds(toupper(biteString(*p, '=')));
      string value = stripBlankEnds(*p);
      
      if(param == "FOO") {
        //handled
      }
      else if(param == "BAR") {
        //handled
      }
    }
  }
  
  m_timewarp = GetMOOSTimeWarp();

  RegisterVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void PrimeFactor::RegisterVariables()
{
  // Register("FOOBAR", 0);
  m_Comms.Register("NUM_VALUE", 0);
}

