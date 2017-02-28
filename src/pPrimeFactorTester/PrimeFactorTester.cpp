/************************************************************/
/*    NAME: Jonathan Garcia-Mallen                          */
/*    ORGN: MIT                                             */
/*    FILE: PrimeFactorTester.cpp                           */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include <string>
#include "MBUtils.h"
#include "PrimeFactorTester.h"

using namespace std;

//---------------------------------------------------------
// Constructor

PrimeFactorTester::PrimeFactorTester()
{
  m_iterations = 0;
  m_timewarp   = 1;
}

//---------------------------------------------------------
// Destructor

PrimeFactorTester::~PrimeFactorTester()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool PrimeFactorTester::OnNewMail(MOOSMSG_LIST &NewMail)
{
  MOOSMSG_LIST::iterator p;
  
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;

    string key = msg.GetKey();

    if(key == "PRIME_RESULT"){
      string sval = msg.GetString();
      string factorization_validity = GenValidityString(sval);
      m_Comms.Notify("PRIME_RESULT_VALID", factorization_validity);

    }
  }
	
  return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool PrimeFactorTester::OnConnectToServer()
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

bool PrimeFactorTester::Iterate()
{
  m_iterations++;
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool PrimeFactorTester::OnStartUp()
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

void PrimeFactorTester::RegisterVariables()
{
  // Register("FOOBAR", 0);
  m_Comms.Register("PRIME_RESULT", 0);
}

string PrimeFactorTester::GenValidityString(string& message)
{ 
  // message takes this form:
  //   message = "orig=30030,received=34,calculated=33,solve_time=2.03, primes=2:3:5:7:11:13,username=jane"

  // split the string
  vector<string> split_string = parseString(message,",");
  string soriginal = parseString(split_string[0], '=')[1];
  int original = stoi(soriginal);

  vector<string> sfactors = parseString(parseString(split_string[4],'=')[1],':');
  vector<int> factors (sfactors.size());
  for(int i=0; i<sfactors.size(); i++){
    factors[i] = stoi(sfactors[i]);
  }
  
  int multiplied = 1;
  for(int factor : factors){
    multiplied *= factor;
  }

  // test validity
  string valid;
  if(multiplied == original){
    valid = "true";
  }else{
    valid = "false";
  }

  // append the validity to the old string
  stringstream stream;
  stream << message << ",valid=" << valid;
  return stream.str();
}

