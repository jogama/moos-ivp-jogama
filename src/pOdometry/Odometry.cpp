/************************************************************/
/*    NAME: Jonathan Garcia-Mallen                                              */
/*    ORGN: MIT                                             */
/*    FILE: Odometry.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "Odometry.h"
#include <cmath>

using namespace std;

//---------------------------------------------------------
// Constructor

Odometry::Odometry()
{
  m_iterations = 0;
  m_timewarp   = 1;

  m_first_reading  = true;
  m_current_x      = 0;
  m_current_y      = 0;
  m_previous_x     = 0; 
  m_previous_y     = 0; 
  m_total_distance = 0;   
}

//---------------------------------------------------------
// Destructor

Odometry::~Odometry()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool Odometry::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);
  
  MOOSMSG_LIST::iterator p;

  //Edit the Odometry::OnNewMail() method to handle the updated navigation position. Set previous_x to current_x, and current_x to the new NAV_X value. Same for Y. 

  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key = msg.GetKey();
    double dval  = msg.GetDouble();

    if(key == "NAV_X"){
      m_previous_x = m_current_x;
      m_current_x = dval;
    }

    if(key == "NAV_Y"){
      m_previous_y = m_current_y;
      m_current_y = dval;
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

bool Odometry::OnConnectToServer()
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
//    Edit Odometry::Iterate() method to calculate the new distance. Handle the special case of the first navigation measurement. Post the total distance to the MOOS variable ODOMETRY_DIST. 
bool Odometry::Iterate()
{
  AppCastingMOOSApp::Iterate();
  

  m_iterations++;

  double difference_x, difference_y;

  // Hoping that nothing has to be done for the initial reading
  if(!m_first_reading){
    // Calculate new distance
    difference_x = abs(m_current_x - m_previous_x);
    difference_y = abs(m_current_y - m_previous_y);
    m_total_distance += sqrt(pow(difference_x, 2) + pow(difference_y, 2));

    // Post the distance.
    // Would this be more efficient if it isn't always changing?
    m_Comms.Notify("ODOMETRY_DIST", m_total_distance);
  }
  else
    m_first_reading = false;

  AppCastingMOOSApp::PostReport(); 
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool Odometry::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();
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

void Odometry::RegisterVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  // Register("FOOBAR", 0);AppCastingMOOSApp::OnNewMail(NewMail);
  m_Comms.Register("NAV_X", 0);
  m_Comms.Register("NAV_Y", 0);
  m_Comms.Register("APPCAST_REQ", 0);
}

 bool Odometry::buildReport(){
  m_msgs << "Hello, watery world!" << endl;
  m_msgs << "I have swam " << m_total_distance << " meters.\n";
  return(true);
}
   
