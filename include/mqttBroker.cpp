/*******************************************************************************
 * @file mqttBroker.cpp  
 * @brief File containing all MQTT functions.
 *******************************************************************************/
#ifndef connectToMqttBroker_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define connectToMqttBroker_h // Precompiler macro used for precompiler check.

#include <main.h> // Header file for all libraries needed by this program.

// quick and dirty easily typed debug commands
   #define sp1(_y) Serial.print(_y);
//   #define sp1l(_a) Serial.println(_a);
   #define sp1l(_z) Serial.println(_z);
   #define sp1s(_b) Serial.print(_b); Serial.print(" ");
   #define sp2(x,y) Serial.print(x); Serial.print(y);
   #define sp2s(x,y) Serial.print(x); Serial.print(" ");Serial.print(y);
   #define sp2l(x,y) Serial.print(x); Serial.println(y);
   #define sp2sl(x,y) Serial.print(x); Serial.print(" ");Serial.println(y);
   #define sp Serial.print(" ");
   #define nl Serial.println();


// TODO #7 : A pingable but non MQTT IP address crash loops code.
/** 
 * @brief Establish connect to the the MQTT broker.
 * @details Retrieve the MQTT broker IP address from Flash memory and ping that 
 *          address to see if there is a responsive device on the network. If there 
 *          is then publish a health message noting that end-to-end network services 
 *          are working. Note that upon connecting to the broker the MQTT library 
 *          automatically subscribes to the <unique name>/commands topic.  
 * =================================================================================*/
bool connectToMqttBroker(aaNetwork &network)
{
   network.getUniqueName(uniqueNamePtr); // Puts unique name value into uniqueName[]
   Log.noticeln("<connectToMqttBroker> Hexbot unique network name = %s.", uniqueName);
   Log.noticeln("<connectToMqttBroker> Health topic = %s.", HEALTH_MQTT_TOPIC);
   strcpy(healthTopicTree, uniqueName);
   strcat(healthTopicTree, HEALTH_MQTT_TOPIC);
   Log.noticeln("<connectToMqttBroker> Full health topic tree = %s (length = %d).", healthTopicTree, strlen(healthTopicTree));
   Log.noticeln("<connectToMqttBroker> Help topic = %s.", HELP_MQTT_TOPIC);
   strcpy(helpTopicTree, uniqueName);
   strcat(helpTopicTree, HELP_MQTT_TOPIC);
   Log.noticeln("<connectToMqttBroker> Full help topic tree = %s (length = %d).", helpTopicTree, strlen(helpTopicTree));
   brokerIP = flash.readBrokerIP(); // Retrieve MQTT broker IP address from NV-RAM.
   Log.noticeln("<connectToMqttBroker> MQTT broker IP believed to be %p.", brokerIP);
   bool tmpPingResult = network.pingIP(brokerIP, 5);
   String tmpResult[2];
   tmpResult[0] = "Not found - invalid address";
   tmpResult[1] = "Found - valid address";
   Log.noticeln("<connectToMqttBroker> Ping of broker at %p resulted in %T.", brokerIP, tmpPingResult);
   if(tmpPingResult == true)
   {
      mqtt.connect(brokerIP, uniqueName);
      bool x = false;
      while(x == false)
      {
         x = mqtt.publishMQTT(healthTopicTree, "End-to-end network services estabished");
         delay(1);
      } //while  
   } //if
   else
   {
      Log.errorln("<connectToMqttBroker> Cannot reach MQTT broker.");
      return false; 
   } //else
   return true;
} //connectToMqttBroker()

/**
 * @brief Check is a string variable is a valid number.
 * @return true if it is a valid number and false if it is not.
 * =================================================================================*/
boolean isValidNumber(String str)
{
   for(byte i=0;i<str.length();i++)
   {
      if(!isDigit(str.charAt(i))) 
      {
         return false;
      } //if
   } // for
   return true;
} // isValidNumber()

/**
 * @brief Converts a string variable to a unit32_t variable.
 * @param var is the string to be converted.
 * @return The convereted value. 
 * =================================================================================*/
uint32_t convertStrToUint32_t(String var)
{
   unsigned long numToConvert = strtoul(var.c_str(), NULL, 10); 
   return (uint32_t) numToConvert;  
} // convertStrToUint32_t()

/**
 * @brief Converts a string variable to a uint8_t variable.
 * @param var is the string to be converted.
 * @return The convereted value. 
 * =================================================================================*/
uint8_t convertStrToUint8_t(String var)
{
   unsigned long numToConvert = strtoul(var.c_str(), NULL, 10); 
   return (uint8_t) numToConvert;  
} // convertStrToUint8_t()

/**
 * @brief Converts a string variable to a int8_t variable.
 * @param var is the string to be converted.
 * @return The convereted value. 
 * =================================================================================*/
int8_t convertStrToInt8_t(String var)
{
   unsigned long numToConvert = strtoul(var.c_str(), NULL, 10); 
   return (int8_t) numToConvert;  
} // convertStrToInt8_t()

/**
 * @brief Check if command arguments are valid numbers.
 * @param numArgumentsRequired how many numbers are expected.
 * @param argN number of arguments passed by command.
 * @param *arg pointer to array containing the arguments to be checked.
 * @return true if there are the right number of arguments and they are all numbers,
 * false if the number of arguments is wrong or if one of the arguments is not a 
 * number. 
 * =================================================================================*/
bool checkNumArg(int8_t numArgumentsRequired, int argN, String *arg)
{
   if(argN == numArgumentsRequired) // Right number of arguments?
   {
      Log.verboseln("<checkNumArg> Correct number of arguments recieved."); 
      for(int8_t i = 1; i <= numArgumentsRequired; i ++) // Are the three arguments valid numbers. 
      {
         if(isValidNumber(arg[i])) // If current argument is a valid number.
         {
            Log.verboseln("<checkNumArg> arg[%d] = %s and is a valid number.", i, arg[i]); 
         } // if
         else //  If current argument is not a valid number.
         {
            Log.warningln("<checkNumArg> Ignoring command. arg[%d] = %s and is not a valid number.", i, arg[i]);
            return false; 
         } // if
      } // for 
   } // if
   else // Wrong number of arguments
   {
      Log.warningln("<checkNumArg> Ignoring command. SET_CUST_RGB_CLR requires %d arguments but recieved %i.", numArgumentsRequired, argN); 
      return false;
   } // else
   return true;   
} // checkNumArg()

/**
 * @brief Process the incoming command.
 * @param payload Command recieved from MQTT broker.
 * @return True is the command is known. False if the cmmand is unknown.
 * =================================================================================*/
bool processCmd(String payload)
{
Serial.println("<processCmd>");
   aaFormat format;
   String ucPayload = format.stringToUpper(payload);
   const int8_t maxArg = 30; // Allow 1 cmd and up to 29 args in an MQTT message.
   String arg[maxArg]; // arg[0] = cmd, arg[1] = 1st argument, arg[2] = second ...
   int argN = 0; // argument number that we're working on
   int argStart = 0; // character number where current argument starts
   int argEnd = ucPayload.indexOf(",",argStart);  // position of comma at end of cmd
   // Parse comma delimited message into array elements 
   while(argEnd >= 0) // .indexOf returns -1 if no string found
   {  
      arg[argN] = ucPayload.substring(argStart,argEnd);  // extract the current argument
      argN ++ ; // advance the argument counter
      argStart = argEnd + 1; // next arg starts after previous arg's delimiting comma
      argEnd = ucPayload.indexOf(",",argStart); // find next arg's delimiting comma
   } // while            
   arg[argN] = ucPayload.substring(argStart,argEnd); // last argument has no comma 
                                                     // delimiter. argN ends up as a 
                                                     // count of the number of 
                                                     // arguments, excluding the command
   String cmd = arg[0]; // first comma separated value in payload is the command
   // TEST command.
   if(cmd == "TEST")
   {
      Log.noticeln("<processCmd> Recieved test command."); 
      return true;
   }  // if 
   // HELP command.
   if(cmd == "HELP")
   {
      Log.noticeln("<processCmd> Recieved help command."); 
      bool x = false;
      while(x == false)
      {
         x = mqtt.publishMQTT(helpTopicTree, "TEST - Issues test message to terminal.");
         delay(1);
      } //while        
      x = false;
      while(x == false)
      {
         x = mqtt.publishMQTT(helpTopicTree, "HELP - Lists valid commands to help topic tree.");
         delay(1);
      } //while        
      x = false;
      while(x == false)
      {
         x = mqtt.publishMQTT(helpTopicTree, "SET_CUST_RGB_CLR,red,green,blue - Custom colour for RGB LED. (arg values 0-256).");
         delay(1);
      } //while        
      x = false;
      while(x == false)
      {
         x = mqtt.publishMQTT(helpTopicTree, "SET_STD_RGB_CLR,colour - Standard colour for RGB LED. (arg values 0-8).");
         delay(1);
      } //while        
      x = false;
      while(x == false)
      {
         x = mqtt.publishMQTT(helpTopicTree, "ROTATE_OLED,orientation - Orient text on OLED. (arg values 0-3).");
         delay(1);
      } //while        
      Log.noticeln("<processCmd> List of valid MQTT commands sent to MQTT broker."); 
      return true;
   }  // if 
   // SET_CUST_RGB_CLR command.
   if(cmd == "SET_CUST_RGB_CLR")
   {
      const int8_t numArgumentsRequired = 3; // How many arguments expected?
      if(checkNumArg(numArgumentsRequired, argN, &arg[0]))
      {
         uint32_t red = convertStrToUint32_t(arg[1]);
         uint32_t green = convertStrToUint32_t(arg[2]); 
         uint32_t blue = convertStrToUint32_t(arg[3]);
         Log.noticeln("<processCmd> Set RGB LED values R = %u, G = %u, B = %u.", red, green, blue); 
         setCustRgbColour(red, green, blue);
         return true;
      } // if
      else
      {
         return false;
      } // else            
   }  // if 
   // SET_STD_RGB_CLR command.
   if(cmd == "SET_STD_RGB_CLR")
   {   
      const int8_t numArgumentsRequired = 1; // How many arguments expected?
      if(checkNumArg(numArgumentsRequired, argN, &arg[0]))
      {
         uint8_t colour = convertStrToUint8_t(arg[1]);
         setStdRgbColour(colour);
         return true;
      } // if
      else
      {
         return false;
      } // else       
   } // if
   // ROTATE_OLED command.
   if(cmd == "ROTATE_OLED")
   {   
      const int8_t numArgumentsRequired = 1; // How many arguments expected?
      if(checkNumArg(numArgumentsRequired, argN, &arg[0]))
      {
         int8_t tmp = convertStrToInt8_t(arg[1]);
         rotateDisplay(tmp);
         displaySplashScreen("");
         return true;
      } // if
      else
      {
         return false;
      } // else       
   } // if

//  =========================== quick and dirty transplant from old stuff - needs rewrite
/*
if(cmd == "GOTO_ANGLES" || cmd == "GA")
// ==== add a leg argument
   // format: goto_angles,<leg>,<operation>,<hip angle>,<knee angle>,<ankle angle>
   //       with all angles in degrees, center (north) = 0
   // example: ga,4,0,0,0    would move left front leg to neutral stance, all angles = 0
   {
      Serial.println("start goto_angles command");
 
      // move the servos in parallel at top speed to desired angles
      float f_th = arg[1].toFloat();  // compiler won't allow direct substitution below
      float f_tk = arg[2].toFloat();
      float f_ta = arg[3].toFloat();
      
      pwm.setPWM(servoMotor[1].driverPort, SERVO_START_TICK, mapDegToPWM(f_th, 0)); // Hip
      pwm.setPWM(servoMotor[2].driverPort, SERVO_START_TICK, mapDegToPWM(f_tk, 0)); // Knee
      pwm.setPWM(servoMotor[3].driverPort, SERVO_START_TICK, mapDegToPWM(f_ta, 0)); // Ankle 

      anglesToCoords(f_th, f_tk, f_ta);
      spr("` coords: "); spr(f_cx); sp; spr(f_cy); sp; spl(f_cz);

      // worst case is moving 90 degrees at .17 sec per 60 degrees, so ...
      delay(510);  // wait for moves to complete
      return true;
   } // if cmd = goto_angles


   if(cmd == "GOTO_COORDS" || cmd == "GC")
   // ==== add a leg argument, and a coordinate type: absolute, rel to home position, rel to current position
   // ==== use same coord type symbols as flow rows
   // format: goto_coords,<x value>,<y value>,<z value>
     // example: gc, 13.22, -10.52,0    would put robot in normal neutral stance
   {
      Serial.println("start goto_coords command");
 
      // convert coordinates given into angles in degrees
      f_tx = arg[1].toFloat();   // compiler won't allow direct substitution below
      f_ty = arg[2].toFloat();
      f_tz = arg[3].toFloat();

      coordsToAngles(f_tx, f_ty, f_tz);  
spr(" args: "); spr(f_tx); sp; spr(f_ty); sp; spl(f_tz);      
      // angle values in degrees, are returned in globals f_angH, f_angK and f_angA

      // move the servos in parallel at top speed to these angles
      
      pwm.setPWM(servoMotor[1].driverPort, SERVO_START_TICK, mapDegToPWM(f_angH, 0)); // Hip
      pwm.setPWM(servoMotor[2].driverPort, SERVO_START_TICK, mapDegToPWM(f_angK, 0)); // Knee
      pwm.setPWM(servoMotor[3].driverPort, SERVO_START_TICK, mapDegToPWM(f_angA, 0)); // Ankle 
      spr("` angles: "); spr(f_angH); sp; spr(f_angK); sp; spl(f_angA);

      // worst case is moving 90 degrees at .17 sec per 60 degrees, so ...
      delay(510);  // wait for moves to complete
      return true;
   } // if cmd = goto_coords
*/


// FLOW command for storing next position in a smooth motion flow between multiple positions
// the flow command builds arrays describing the desired movement
// the flow_go command starts the movement and controls repetitions, resets, etc

   if(cmd == "FLOW" || cmd == "FL")
// ==== follow new flow row structure
// ==== add a bunch of new arrays
// ==== ad a bunch of symbolic definitions
// ==== need a lockout so flow can't be redefined while executing

// see flows.h for definition of flow arrays and parameters
//
// flow command format
// FL,msec,operation,lShape1,lS2,lS3,lS4, L1X,L1Y,L1Z, L2X,L2Y,L2Z, L3X,L3Y,L3Z, L4X,L4Y,L4Z, L5X,L5Y,L5Z, L6X,L6Y,L6Z
//
// example: // move all toes to to 1 cm above home position, i.e. slightly squatting from neutral
// FL,1000,2,10,0,0,0, 0,0,1, 0,0,1, 0,0,1, 0,0,1, 0,0,1, 0,0,1
//
// action: - save given data into next position in the flow arrays, to be part of the motion initiated by flow_go command

   {
      Serial.println("start processing flow command");
 
      // copy position description from MQTT flow command to next flow row
      // f_count starts at 0, which we use to store first position in row 0
      f_msecs[f_count] = arg[1].toInt();        // arg[0] is the FL command, arg[1] is msec time ...
      f_operation[f_count] = arg[2].toInt();   // code for operation in this row of the flow, eg fo_moveAbs
      
      f_lShape1[f_count] = arg[3].toInt();     // type of line. initially, always fl_straight
      f_lShape2[f_count] = arg[4].toFloat();   // parameter to define line when it's a parabola, ellipse,...
      f_lShape3[f_count] = arg[5].toFloat();   // more line parameters
      f_lShape4[f_count] = arg[6].toFloat();
      
      f_legX[f_count][1] = arg[7].toFloat();   // X coordinate or delta value for leg 1
      f_legY[f_count][1] = arg[8].toFloat();   // Y coordinate or delta value for leg 1
      f_legZ[f_count][1] = arg[9].toFloat();   // Z coordinate or delta value for leg 1
 
      f_legX[f_count][2] = arg[10].toFloat();   // X coordinate or delta value for leg 2
      f_legY[f_count][2] = arg[11].toFloat();   // Y coordinate or delta value for leg 2
      f_legZ[f_count][2] = arg[12].toFloat();   // Z coordinate or delta value for leg 2

      f_legX[f_count][3] = arg[13].toFloat();   // X coordinate or delta value for leg 3
      f_legY[f_count][3] = arg[14].toFloat();   // Y coordinate or delta value for leg 3
      f_legZ[f_count][3] = arg[15].toFloat();   // Z coordinate or delta value for leg 3

      f_legX[f_count][4] = arg[16].toFloat();   // X coordinate or delta value for leg 4
      f_legY[f_count][4] = arg[17].toFloat();   // Y coordinate or delta value for leg 4
      f_legZ[f_count][4] = arg[18].toFloat();   // Z coordinate or delta value for leg 4

      f_legX[f_count][5] = arg[19].toFloat();   // X coordinate or delta value for leg 5
      f_legY[f_count][5] = arg[20].toFloat();   // Y coordinate or delta value for leg 5
      f_legZ[f_count][5] = arg[21].toFloat();   // Z coordinate or delta value for leg 5

      f_legX[f_count][6] = arg[22].toFloat();   // X coordinate or delta value for leg 6
      f_legY[f_count][6] = arg[23].toFloat();   // Y coordinate or delta value for leg 6
      f_legZ[f_count][6] = arg[24].toFloat();   // Z coordinate or delta value for leg 6

      f_count ++;             // advance to next entry in flow arrays
                              // f_count now contains the number of flow rows that have been defined
                              // it's reset by the FLOW_GO command
      return true;
   } // if cmd = flow

// FLOW_GO command to start up motion as previously defined in the flow arrays using the FLOW command
// the FLOW command builds arrays describing the desired movement
// the FLOW_GO command starts the movement and controls repetitions, resets, etc
//
// format: FLOW_GO, <action>,<msecPerFrame>
// action: 1 - start the flow currently defined in the flow arrays
//         0 - reset the current flow, and empty the flow arrays
// msecPerFrame: duration of each frame (fraction of a position) in millis. this determines f_framesPerPosn
//               - if omitted, it defaults to f_msecPerFrameDefault, which defaults to 20 msec

   if(cmd == "FLOW_GO" || cmd == "FG")
   // ==== can this stay unchanged?
   {
      int f_action = arg[1].toInt();      // decode the first argument - either start flow, or reset it
      if(f_action == 0)                   // zero means reset
      {  f_flowing = false;
         f_count = 0;
         f_active = 0;
         return true;
      }
      if(f_action == 1)                // 1 means start up the currently define flow
      {  Serial.println("<flow_go> saw action = 1");
         if(f_count == 0)              // is there a flow defined to run?
         {  Serial.println("<flow_go>: tried to run flow, but none defined");
            return false;
         }
         f_flowing = 1;                // we're now executing a flow
         f_active = 0;                 // starting at the 0th entry in the flow arrays

         f_msecPerFrame = f_msecPerFrameDefault;  // if not given in FG command, use the default
         if(argN > 1)                  // if there were at least 2 numeric args to FG command
         {                             // ... 2nd one is msecPerFrame
            f_msecPerFrame = arg[2].toInt();  // 2nd number is millis per frame
            if(f_msecPerFrame<10 || f_msecPerFrame>200) {f_msecPerFrame = f_msecPerFrameDefault;}
         }
         if(argN>2) {toeMoveAction = arg[3].toInt();} // binary coded options for toe moves

      } // if action = 1
      else
      {   Serial.println("<flow_go>: invalid action in MQTT flow_go command");
          return false;
      }
   return true;
   } // if cmd = flow_go

// ================================== end of quick and dirty transplant

   Log.warningln("<processCmd> Warning - unrecognized command."); 
   return false;
} // processCmd()

/** 
 * @brief Return the MQTT broker IP address.
 * =================================================================================*/
IPAddress getMqttBrokerIP()
{
   return brokerIP;
} // getMqttBrokerIP()

/** 
 * @brief Check to see if any MQTT commands have come in from the broker.
 * =================================================================================*/
void checkMqtt()
{
// ====    either check for highest priority first (20 msec move) or use FREERTOS pre-emptive multitasking
   String cmd = mqtt.getCmd();
   if(cmd != "")
   {
      Log.noticeln("<checkMqtt> cmd = %s.", cmd.c_str());
      bool allIsWell = processCmd(cmd);
      if(allIsWell)
      {
         Log.noticeln("<checkMqtt> All went well.");
      } // if 
      else
      {
         Log.warningln("<checkMqtt> Something went wrong.");
      } // if 
   } // if   
} // checkMqtt()

#endif // End of precompiler protected code block