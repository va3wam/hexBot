/*******************************************************************************
 * @file configDetails.cpp  
 * @brief setup & display config parameters and boot status
 *******************************************************************************/
#ifndef showCfgDetails_cpp // Start of precompiler check to avoid dupicate inclusion of this code block.

#define showCfgDetails_cpp // Precompiler macro used for precompiler check.

#include <main.h> // Header file for all libraries needed by this program.


/**
 * @brief Do configuration set up that is unique to each robot, including:
 * - define servo calibration offset values
 * called from setup() in main.cpp
 * tried to put this routine in hexBot/lib/aaWeb-1.0.0/lib/aaNetwork-main/src/aaNetwork.cpp
 *    but couldn't get it to work, due to object structure issues I suspect
 =============================================================================*/
 void setupPerBotConfig()     // do the robot-specific setup
 {
    String macAdd = WiFi.macAddress(); // Get MAC address as String
    sp2("<setupPerBotConfig> MAC Address: ", macAdd);  // see if we can read this variable
    if(macAdd == "3C:61:05:4A:DD:98")  // Doug's robot 1 MAC address
    {
       sp1l("  Doing bot-specific setup for Doug's robot 1 MAC address");
       // set up the servo calibration offsets
       // PWM value used = (PWM calculated from angle) + (calibration offset for this servo) - 299
       // note that servoOffset[0] is not used
       servoOffset[ 1] = 299;
       servoOffset[ 2] = 299;
       servoOffset[ 3] = 299;
       servoOffset[ 4] = 299;
       servoOffset[ 5] = 299;
       servoOffset[ 6] = 299;
       servoOffset[ 7] = 299;
       servoOffset[ 8] = 299;
       servoOffset[ 9] = 299;
       servoOffset[10] = 299;
       servoOffset[11] = 299;
       servoOffset[12] = 299;
       servoOffset[13] = 299;
       servoOffset[14] = 299;
       servoOffset[15] = 299;
       servoOffset[16] = 299;
       servoOffset[17] = 299;
       servoOffset[18] = 299;

    }
    else if(macAdd == "94:B9:7E:5F:4A:40")  // Andrew's robot 1 MAC address
    {
       sp1l("  Doing bot-specific setup for Andrew's robot 1 MAC address");
       // set up the servo calibration offsets
       // PWM value used = (PWM calculated from angle) + (calibration offset for this servo)
       // note that servoOffset[0] is not used
       servoOffset[ 1] = 299;
       servoOffset[ 2] = 299;
       servoOffset[ 3] = 299;
       servoOffset[ 4] = 299;
       servoOffset[ 5] = 299;
       servoOffset[ 6] = 299;
       servoOffset[ 7] = 299;
       servoOffset[ 8] = 299;
       servoOffset[ 9] = 299;
       servoOffset[10] = 299;
       servoOffset[11] = 299;
       servoOffset[12] = 299;
       servoOffset[13] = 299;
       servoOffset[14] = 299;
       servoOffset[15] = 299;
       servoOffset[16] = 299;
       servoOffset[17] = 299;
       servoOffset[18] = 299;
    }
    else if(macAdd == "94:B9:7E:5F:48:B8")  // Doug's robot 2 MAC address
    {
       sp1l("  Doing bot-specific setup for Doug's robot 2 MAC address");
       // set up the servo calibration offsets
       // PWM value used = (PWM calculated from angle) + (calibration offset for this servo) - 299
       // note that servoOffset[0] is not used
       servoOffset[ 1] = 299;
       servoOffset[ 2] = 299;
       servoOffset[ 3] = 299;
       servoOffset[ 4] = 299;
       servoOffset[ 5] = 299;
       servoOffset[ 6] = 299;
       servoOffset[ 7] = 299;
       servoOffset[ 8] = 299;
       servoOffset[ 9] = 299;
       servoOffset[10] = 299;
       servoOffset[11] = 299;
       servoOffset[12] = 299;
       servoOffset[13] = 299;
       servoOffset[14] = 299;
       servoOffset[15] = 299;
       servoOffset[16] = 299;
       servoOffset[17] = 299;
       servoOffset[18] = 299;

    }
    else if(macAdd == "94:B9:7E:5F:52:DC")  // Andrew's robot 2 MAC address
    {
       sp1l("  Doing bot-specific setup for Andrew's robot 2 MAC address");
       // set up the servo calibration offsets
       // PWM value used = (PWM calculated from angle) + (calibration offset for this servo)
       // note that servoOffset[0] is not used
       servoOffset[ 1] = 299;
       servoOffset[ 2] = 299;
       servoOffset[ 3] = 299;
       servoOffset[ 4] = 299;
       servoOffset[ 5] = 299;
       servoOffset[ 6] = 299;
       servoOffset[ 7] = 299;
       servoOffset[ 8] = 299;
       servoOffset[ 9] = 299;
       servoOffset[10] = 299;
       servoOffset[11] = 299;
       servoOffset[12] = 299;
       servoOffset[13] = 299;
       servoOffset[14] = 299;
       servoOffset[15] = 299;
       servoOffset[16] = 299;
       servoOffset[17] = 299;
       servoOffset[18] = 299;
    }
    else    // neither MAC address matched
    {
       nl;
       sp2l("<setupPerBotConfig> Unrecognized MAC address. Per Bot configuration was bypassed", macAdd);
    }
 } // void setupPerBotConfig()

/** 
 * @brief Show the environment details of this application on console.
 * ============================================================================*/
void showCfgDetails()
{
   Log.verboseln("<showCfgDetails> Robot Configuration Report");
   Log.verboseln("<showCfgDetails> ==========================");
   appCpu.cfgToConsole(); // Display core0 information on the console.
   if(networkConnected == true)
   {
      Log.verboseln("<showCfgDetails> Network connection status = TRUE");
      network.cfgToConsole(); // Display network information on the console.
      if(mqttBrokerConnected == true)
      {
         Log.verboseln("<showCfgDetails> MQTT broker connection status = TRUE");
         Log.verbose("<showCfgDetails> MQTT broker IP address = ");
         Log.verboseln(getMqttBrokerIP());
      } // if
      else
      {
         Log.verboseln("<showCfgDetails> MQTT broker connection status = FALSE");
      } // else
   } // if
   else
   {
      Log.verboseln("<showCfgDetails> Network connection status = FALSE");
   } // else
   if(oledConnected == true)
   {
      Log.verboseln("<showCfgDetails> OLED connection status = TRUE.");
   } // if
   else
   {
      Log.verboseln("<showCfgDetails> OLED connection status = FALSE.");
   } // else
   if(motorController1Connected == true)
   {
      Log.verboseln("<showCfgDetails> Left servo driver connection status = TRUE.");
   } // if
   else
   {
      Log.verboseln("<showCfgDetails> Left servo driver connection status = FALSE.");
   } // else
   if(motorController2Connected == true)
   {
      Log.verboseln("<showCfgDetails> Right servo driver connection status = TRUE.");
   } // if
   else
   {
      Log.verboseln("<showCfgDetails> Right servo driver connection status = FALSE.");
   } // else
} //showCfgDetails()

/** 
 * @brief Show the environment details of this application on OLED.
 * @details Uses menu system to show different information as needed.
 * ============================================================================*/
void displayCfgDetails(int8_t menuToShow)
{
   switch (menuToShow) 
   {
      case 2:
         Log.verboseln("<displayCfgDetails> Display second menu.");
         break;
      case 3:
         Log.verboseln("<displayCfgDetails> Display third menu.");
         break;
      default:
         Log.verboseln("<displayCfgDetails> Display first menu.");
         break;
   } // switch
} // displayCfgDetails()

/** 
 * @brief Check to see how the boot up process went.
 * ============================================================================*/
void checkBoot()
{
   Log.traceln("<checkBoot> Checking boot status flags."); 
   if(networkConnected == true && mqttBrokerConnected == true && oledConnected == true && mobilityStatus == true)
   {
      Log.verboseln("<checkBoot> Bootup was normal. Set RGB LED to normal colour."); 
      setStdRgbColour(GREEN); // Indicates that bootup was normal.
   } // if
   else
   {
      Log.verboseln("<checkBoot> Bootup had an issue. Set RGB LED to warning colour."); 
      setStdRgbColour(YELLOW); // Indicates that there was a bootup issue.
   } // else
} // checkBoot

#endif // End of precompiler protected code block