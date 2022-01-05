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
#define sp1s(_b)     \
   Serial.print(_b); \
   Serial.print(" ");
#define sp2(x, y)   \
   Serial.print(x); \
   Serial.print(y);
#define sp2s(x, y)    \
   Serial.print(x);   \
   Serial.print(" "); \
   Serial.print(y);   \
   Serial.print(" ");
#define sp2l(x, y)  \
   Serial.print(x); \
   Serial.println(y);
#define sp2sl(x, y)   \
   Serial.print(x);   \
   Serial.print(" "); \
   Serial.println(y);
#define sp3s(a,b,c)   \
   Serial.print(a);   \
   Serial.print(" "); \
   Serial.print(b);   \
   Serial.print(" "); \
   Serial.print(c);   \
   Serial.print(" ");
#define sp3sl(a,b,c)   \
   Serial.print(a);   \
   Serial.print(" "); \
   Serial.print(b);   \
   Serial.print(" "); \
   Serial.println(c);   \

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
   if (tmpPingResult == true)
   {
      mqtt.connect(brokerIP, uniqueName);
      bool x = false;
      while (x == false)
      {
         x = mqtt.publishMQTT(healthTopicTree, "End-to-end network services estabished");
         delay(1);
      } //while
   }    //if
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
   for (byte i = 0; i < str.length(); i++)
   {
      if (!isDigit(str.charAt(i)))
      {
         return false;
      } //if
   }    // for
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
   return (uint32_t)numToConvert;
} // convertStrToUint32_t()

/**
 * @brief Converts a string variable to a uint8_t variable.
 * @param var is the string to be converted.
 * @return The convereted value. 
 * =================================================================================*/
uint8_t convertStrToUint8_t(String var)
{
   unsigned long numToConvert = strtoul(var.c_str(), NULL, 10);
   return (uint8_t)numToConvert;
} // convertStrToUint8_t()

/**
 * @brief Converts a string variable to a int8_t variable.
 * @param var is the string to be converted.
 * @return The convereted value. 
 * =================================================================================*/
int8_t convertStrToInt8_t(String var)
{
   unsigned long numToConvert = strtoul(var.c_str(), NULL, 10);
   return (int8_t)numToConvert;
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
   if (argN == numArgumentsRequired) // Right number of arguments?
   {
      Log.verboseln("<checkNumArg> Correct number of arguments received.");
      for (int8_t i = 1; i <= numArgumentsRequired; i++) // Are the three arguments valid numbers.
      {
         if (isValidNumber(arg[i])) // If current argument is a valid number.
         {
            Log.verboseln("<checkNumArg> arg[%d] = %s and is a valid number.", i, arg[i]);
         }    // if
         else //  If current argument is not a valid number.
         {
            Log.warningln("<checkNumArg> Ignoring command. arg[%d] = %s and is not a valid number.", i, arg[i]);
            return false;
         } // if
      }    // for
   }       // if
   else    // Wrong number of arguments
   {
      Log.warningln("<checkNumArg> Ignoring command. SET_CUST_RGB_CLR requires %d arguments but received %i.", numArgumentsRequired, argN);
      return false;
   } // else
   return true;
} // checkNumArg()

/**
 * @brief Process the incoming command.
 * @param payload Command received from MQTT broker.
 * @return True is the command is known. False if the cmmand is unknown.
 * =================================================================================*/
bool processCmd(String payload)
{
   Serial.println("<processCmd>");
   aaFormat format;
   String ucPayload = format.stringToUpper(payload);
   const int8_t maxArg = 30;                      // Allow 1 cmd and up to 29 args in an MQTT message.
   String arg[maxArg];                            // arg[0] = cmd, arg[1] = 1st argument, arg[2] = second ...
   int argN = 0;                                  // argument number that we're working on
   int argStart = 0;                              // character number where current argument starts
   int argEnd = ucPayload.indexOf(",", argStart); // position of comma at end of cmd
   // Parse comma delimited message into array elements
   while (argEnd >= 0) // .indexOf returns -1 if no string found
   {
      arg[argN] = ucPayload.substring(argStart, argEnd); // extract the current argument
      argN++;                                            // advance the argument counter
      argStart = argEnd + 1;                             // next arg starts after previous arg's delimiting comma
      argEnd = ucPayload.indexOf(",", argStart);         // find next arg's delimiting comma
   }                                                     // while
   arg[argN] = ucPayload.substring(argStart, argEnd);    // last argument has no comma
                                                         // delimiter. argN ends up as a
                                                         // count of the number of
                                                         // arguments, excluding the command
   String cmd = arg[0];                                  // first comma separated value in payload is the command
   
   // <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> start of new command
   
   // TEST command.
   if (cmd == "TEST")
   {
      Log.noticeln("<processCmd> Received test command.");
      return true;
   } // if
   
   // <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> start of new command
   
   // HELP command.
   if (cmd == "HELP")
   {
      Log.noticeln("<processCmd> Received help command.");
      bool x = false;
      while (x == false)
      {
         x = mqtt.publishMQTT(helpTopicTree, "TEST - Issues test message to terminal.");
         delay(1);
      } //while
      x = false;
      while (x == false)
      {
         x = mqtt.publishMQTT(helpTopicTree, "HELP - Lists valid commands to help topic tree.");
         delay(1);
      } //while
      x = false;
      while (x == false)
      {
         x = mqtt.publishMQTT(helpTopicTree, "SET_CUST_RGB_CLR,red,green,blue - Custom colour for RGB LED. (arg values 0-256).");
         delay(1);
      } //while
      x = false;
      while (x == false)
      {
         x = mqtt.publishMQTT(helpTopicTree, "SET_STD_RGB_CLR,colour - Standard colour for RGB LED. (arg values 0-8).");
         delay(1);
      } //while
      x = false;
      while (x == false)
      {
         x = mqtt.publishMQTT(helpTopicTree, "ROTATE_OLED,orientation - Orient text on OLED. (arg values 0-3).");
         delay(1);
      } //while
      Log.noticeln("<processCmd> List of valid MQTT commands sent to MQTT broker.");
      return true;
   } // if
 
   // <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> start of new command
   
   // SET_CUST_RGB_CLR command.
   if (cmd == "SET_CUST_RGB_CLR")
   {
      const int8_t numArgumentsRequired = 3; // How many arguments expected?
      if (checkNumArg(numArgumentsRequired, argN, &arg[0]))
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
   }    // if
   
   // <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> start of new command
   
   // SET_STD_RGB_CLR command.
    if (cmd == "SET_STD_RGB_CLR")
   {
      const int8_t numArgumentsRequired = 1; // How many arguments expected?
      if (checkNumArg(numArgumentsRequired, argN, &arg[0]))
      {
         uint8_t colour = convertStrToUint8_t(arg[1]);
         setStdRgbColour(colour);
         return true;
      } // if
      else
      {
         return false;
      } // else
   }    // if
   
   // <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> start of new command
   
   // ROTATE_OLED command.
   if (cmd == "ROTATE_OLED")
   {
      const int8_t numArgumentsRequired = 1; // How many arguments expected?
      if (checkNumArg(numArgumentsRequired, argN, &arg[0]))
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
   }    // if cmd = "ROTATE_OLED"

   // FLOW command for storing next position in a smooth motion flow between multiple positions
   // the flow command builds arrays describing the desired movement
   // the flow_go command starts the movement and controls repetitions, resets, etc

   if (cmd == "FLOW" || cmd == "FL")

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
   //   Serial.println("start processing flow command");

      // copy position description from MQTT flow command to next flow row
      // f_count starts at 0, which we use to store first position in row 0
      f_msecs[f_count] = arg[1].toInt();     // arg[0] is the FL command, arg[1] is msec time ...
      f_operation[f_count] = arg[2].toInt(); // code for operation in this row of the flow, eg fo_moveAbs

      f_lShape1[f_count] = arg[3].toInt();   // type of line. initially, always fl_straight
      f_lShape2[f_count] = arg[4].toFloat(); // parameter to define line when it's a parabola, ellipse,...
      f_lShape3[f_count] = arg[5].toFloat(); // more line parameters
      f_lShape4[f_count] = arg[6].toFloat();

      f_legX[f_count][1] = arg[7].toFloat(); // X coordinate or delta value for leg 1
      f_legY[f_count][1] = arg[8].toFloat(); // Y coordinate or delta value for leg 1
      f_legZ[f_count][1] = arg[9].toFloat(); // Z coordinate or delta value for leg 1

      f_legX[f_count][2] = arg[10].toFloat(); // X coordinate or delta value for leg 2
      f_legY[f_count][2] = arg[11].toFloat(); // Y coordinate or delta value for leg 2
      f_legZ[f_count][2] = arg[12].toFloat(); // Z coordinate or delta value for leg 2

      f_legX[f_count][3] = arg[13].toFloat(); // X coordinate or delta value for leg 3
      f_legY[f_count][3] = arg[14].toFloat(); // Y coordinate or delta value for leg 3
      f_legZ[f_count][3] = arg[15].toFloat(); // Z coordinate or delta value for leg 3

      f_legX[f_count][4] = arg[16].toFloat(); // X coordinate or delta value for leg 4
      f_legY[f_count][4] = arg[17].toFloat(); // Y coordinate or delta value for leg 4
      f_legZ[f_count][4] = arg[18].toFloat(); // Z coordinate or delta value for leg 4

      f_legX[f_count][5] = arg[19].toFloat(); // X coordinate or delta value for leg 5
      f_legY[f_count][5] = arg[20].toFloat(); // Y coordinate or delta value for leg 5
      f_legZ[f_count][5] = arg[21].toFloat(); // Z coordinate or delta value for leg 5

      f_legX[f_count][6] = arg[22].toFloat(); // X coordinate or delta value for leg 6
      f_legY[f_count][6] = arg[23].toFloat(); // Y coordinate or delta value for leg 6
      f_legZ[f_count][6] = arg[24].toFloat(); // Z coordinate or delta value for leg 6

      f_count++; // advance to next entry in flow arrays
                 // f_count now contains the number of flow rows that have been defined
                 // it's reset by the FLOW_GO command
      return true;
   } // if cmd = flow
   
   // <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> start of new command
   
      // FLOW_GO command to start up motion as previously defined in the flow arrays using the FLOW command
   // the FLOW command builds arrays describing the desired movement
   // the FLOW_GO command starts the movement and controls repetitions, resets, etc
   //
   // format: FLOW_GO, <action>,<msecPerFrame>
   // action: 1 - start the flow currently defined in the flow arrays
   //         0 - reset the current flow, and empty the flow arrays
   // msecPerFrame: duration of each frame (fraction of a position) in millis. this determines f_framesPerPosn
   //               - if omitted, it defaults to f_msecPerFrameDefault, which defaults to 20 msec

   if (cmd == "FLOW_GO" || cmd == "FG")
   // ==== can this stay unchanged?
   {
      int f_action = arg[1].toInt(); // decode the first argument - either start flow, or reset it
      if (f_action == 0)             // zero means reset
      {
         f_flowing = false;
         f_count = 0;
         f_active = 0;
         return true;
      }
      if (f_action == 1) // 1 means start up the currently define flow
      {
//         Serial.println("<flow_go> saw action = 1");
         if (f_count == 0) // is there a flow defined to run?
         {
            Serial.println("<flow_go>: tried to run flow, but none defined");
            return false;
         }
         f_flowing = 1; // we're now executing a flow
         f_active = 0;  // starting at the 0th entry in the flow arrays

         f_msecPerFrame = f_msecPerFrameDefault; // if not given in FG command, use the default
         if (argN > 1)                           // if there were at least 2 numeric args to FG command
         {                                       // ... 2nd one is msecPerFrame
            f_msecPerFrame = arg[2].toInt();     // 2nd number is millis per frame
            if (f_msecPerFrame < 10 || f_msecPerFrame > 200)
            {
               f_msecPerFrame = f_msecPerFrameDefault;
            }
         }
         if (argN > 2)
         {
            toeMoveAction = arg[3].toInt();
         } // binary coded options for toe moves

      } // if action = 1
      else
      {
         Serial.println("<flow_go>: invalid action in MQTT flow_go command");
         return false;
      }
      return true;
   } // if cmd = flow_go
   
   // <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> start of new command
   
   // MOVE_LEG command - move leg to coordinates that can be given in various ways
   if (cmd == "MOVE_LEG" || cmd == "ML")
   { // command format: ML, f_operation, leg, X, Y, Z
      //  f_operation is one of:
      //   fo_moveAbs = 1;     // move to absolute location, coords are in global system
      //   fo_moveLocal = 2;   // move to location given, interpreted as local coords
      //   fo_moveRelHome = 3; // move to loc'n relative to home, coords = deltas relative to home position
      float locX, locY, locZ; //
      if (argN != 5)          // did we get command pls 5 arguments?
      {                       // ignore command altogether
         sp1l("******* MOVE_LEG command didn't have 5 additional arguments");
         return false;
      }
      else // convert args to appropriate format
      {
         int argOp = arg[1].toInt();    // next arg is operations code
         int argLeg = arg[2].toInt();   // .. then leg #
         float argX = arg[3].toFloat(); // then X coord
         float argY = arg[4].toFloat(); // then Y
         float argZ = arg[5].toFloat(); // and finally, Z

         f_goodData = true;           // initially assume all will go well
         if (argOp == fo_moveGRelHome) // check if X, Y, Z are relative to home position
         {                            // we were given offsets relative to home position, so add in home coords
            //      sp1l("--global toe coords including offsets--");

            f_tmpX = argX + f_homeX[argLeg];
            f_tmpY = argY + f_homeY[argLeg];
            f_tmpZ = argZ + f_homeZ[argLeg];
            //         sp2s(f_tmpX[L],f_tmpY[L]); sp2l(" ",f_tmpZ[L]);

            // now convert final global coords to local coords we can feed to servos
            sp1l("--final local coords including offsets--");

            globCoordsToLocal(argLeg, f_tmpX, f_tmpY, f_tmpZ, &locX, &locY, &locZ);
            //          sp2s(locX,locY); sp2l(" ",locZ);
         }
         else if (argOp == fo_moveAbs)
         { // we were given absolute coords, and just need to convert to local coords
            globCoordsToLocal(argLeg, argX, argY, argZ, &locX, &locY, &locZ);
         }
         else if (argOp == fo_moveLocal)
         { // we were given local coords, just copy and use them directy
            locX = argX;
            locY = argY;
            locZ = argX;
         }
         else
         {                      // unsupported op code in nextfirst row - abort
            f_flowing = false;  // stop executing the flow
            f_goodData = false; // bypass rest of do_flow processing
            // need to avoid falling into following code. use a flag for "good data seen" ?
         }
         if (f_goodData) // continue only if we haven't aborted due to an error
         {
            // get here if we've been able to calculate local coordinates for next toe position
            // now we need to see if requested position is within "safe positions box"
            String badLegs = ""; // error message identifying unsafe positions
            if (locX - f_localHomeX > safeMaxPosX)  {badLegs = badLegs + legNum[argLeg] + "XP "; }
            if (f_localHomeX - locX > safeMaxNegX)  {badLegs = badLegs + legNum[argLeg] + "XN "; }
            if (locY - f_localHomeY > safeMaxPosY)  {badLegs = badLegs + legNum[argLeg] + "YP "; }
            if (f_localHomeY - locY > safeMaxPosY)  {badLegs = badLegs + legNum[argLeg] + "YN "; }
            if (locZ - f_localHomeZ > safeMaxPosZ)  {badLegs = badLegs + legNum[argLeg] + "ZP "; }
            if (f_localHomeZ - locZ > safeMaxPosZ)  {badLegs = badLegs + legNum[argLeg] + "ZN "; }

            if (badLegs != "") // if any safety violation ocurred..
            {
               f_goodData = false; // abort further processing of    f_flowing = false;         // and stop fow processing
               sp2l("****************** toe safety violation(s) [<leg><coord><positive or negative side> : ", badLegs);
            }               // if badLegs != ""
            if (f_goodData) // if there haven't been any fatal problems so far
            {               // translate the local coords to servo angles
               coordsToAngles(locX, locY, locZ);
               // and feed them to the servos on the selected leg
               sp2s("moving leg ", argLeg); sp2s("  to local coords (X,Y,Z) = ", locX); sp; sp2sl(locY, locZ);
               L = argLeg; // use leg specified in the MQTT MOVE_LEG command
               pwmDriver[legIndexDriver[L]].setPWM(legIndexHipPin[L],     pwmClkStart, mapDegToPWM(f_angH, 0));
               pwmDriver[legIndexDriver[L]].setPWM(legIndexHipPin[L] + 1, pwmClkStart, mapDegToPWM(f_angK, 0));
               pwmDriver[legIndexDriver[L]].setPWM(legIndexHipPin[L] + 2, pwmClkStart, mapDegToPWM(f_angA, 0));
            
               return true;
            }
         }
      } // else
   }    // if cmd = "MOVE_LEG"

   // declare variables for upcoming servo test commands
   int sr_deg, sr_pwm, sr_srv, sr_srv2;
   bool sr_OK;
   String sr_cause;

// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> start of new command

// SSD command = Set  Servo(s) to angle, expressed in degrees, zero is center of range
   if(cmd == "SSD")     // set servo(s) to degrees
   // command format: SSD, degrees, servo#, (optional end of range servo#)
   //    -90 <= degrees <= 90
   //    1 <= servo# <= 18
   //    servo #1 is hip for leg 1, the front right one

   {  sr_OK = true;           // optimistically assume no problems with the command
      if(argN!=2 && argN!=3) {sr_OK = false;sr_cause="bad arg count";}         // wrong number of args for command
      else
      {  sr_deg = arg[1].toInt();      // first arg is angle for servo
         if(sr_deg < -90 || sr_deg > 90 ) {sr_OK = false;sr_cause="bad degree value";}
         else
         {  sr_srv = arg[2].toInt();   // second arg is servo #
            sr_srv2 = sr_srv;          // assume no 3rd arg, and its a one servo range
            if(sr_srv < 1 || sr_srv > 18) {sr_OK = false;sr_cause="bad first servo #";}
            else
            {  if(argN == 3) {sr_srv2 = arg[3].toInt();}    // there was a second servo#
               if(sr_srv2 < sr_srv || sr_srv2 > 18 ) {sr_OK = false;sr_cause="bad second servo #";}
               else
               {  for(int srv=sr_srv2; srv>=sr_srv; srv--)
                  // now set the servo "srv" to an angle of sr_deg degrees
                  //use integer division ("/") and modulus ("%") to directly calculate driver#, and pin#
                  {  pwmDriver[(srv-1) / 9].setPWM((srv-1) % 9, pwmClkStart, mapDegToPWM(sr_deg, 0)); 
                  sp2s("sdd) argN, srv,srv2,sr_deg, index= ",argN);sp;sp2s(sr_srv,sr_srv2);sp;sp2sl(sr_deg,srv);
                  sp2s((srv-1)/9, (srv-1)%9);sp;sp1l(mapDegToPWM(sr_deg, 0));
                  delay(10);     // see if giving PWM drivers some breathing room helps
                  }
               }
            }
         }
      }
      if(sr_OK == false) { sp2sl("********* invalid SSD command: ",sr_cause);}
      return sr_OK;
   }  //if(cmd == "SSD") 

   // <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> start of new command

   // SSP command - Set Servo(s) to PWM value
   if(cmd == "SSP")     // set servo(s) to PWM value
   // command format: SSP, PWM, servo#, (optional end of range servo#)
   //    110 <= PWM <= 490
   //    1 <= servo# <= 18
   //    servo #1 is hip for leg 1, the front right one

   {  sr_OK = true;           // optimistically assume no problems with the command
      if(argN!=2 && argN!=3) {sr_OK = false;sr_cause="bad arg count";}         // wrong number of args for command
      else
      {  sr_pwm = arg[1].toInt();      // first arg is angle for servo
         if(sr_pwm < 110 || sr_pwm > 490 ) {sr_OK = false;sr_cause="bad PWM value";}
         else
         {  sr_srv = arg[2].toInt();   // second arg is servo #
            sr_srv2 = sr_srv;          // assume no 3rd arg, and its a one servo range
            if(sr_srv < 1 || sr_srv > 18) {sr_OK = false;sr_cause="bad first servo #";}
            else
            {  if(argN == 3) {sr_srv2 = arg[3].toInt();}    // there was a second servo#
               if(sr_srv2 < sr_srv || sr_srv2 > 18 ) {sr_OK = false;sr_cause="bad second servo #";}
               else
               {  for(int srv=sr_srv; srv<=sr_srv2; srv++)
                  // now set the servo "srv" to PWM value in sr_pwm
                  //use integer division ("/") and modulus ("%") to directly calculate driver#, and pin#
                  {  pwmDriver[(srv-1) / 9].setPWM((srv-1) % 9, pwmClkStart, sr_pwm);
                  }
               }
            }
         }
      }
      if(sr_OK == false) { sp2sl("********* invalid SSP command: ",sr_cause);}
      return sr_OK;
   } // if(cmd == "SSP")

// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><> start of new command

   // SSO command - Set Servo(s) to "OFF"
   if(cmd == "SSO")     // set servo(s) to OFF, where servo goes limp and draws no current
   // command format: SSO, servo#, (optional end of range servo#)
   //    1 <= servo# <= 18
   //    servo #1 is hip for leg 1, the front right one
   {  sr_OK = true;           // optimistically assume no problems with the command
      if(argN!=1 && argN!=2) {sr_OK = false;sr_cause="bad arg count";}         // wrong number of args for command
      else
      {  sr_srv = arg[1].toInt();   // first arg is servo #
         sr_srv2 = sr_srv;          // assume no 2nd arg, and its a one servo range
         if(sr_srv < 1 || sr_srv > 18) {sr_OK = false;sr_cause="bad first servo #";}
         else
         {  if(argN == 2) {sr_srv2 = arg[2].toInt();}    // there was a second servo#
            if(sr_srv2 < sr_srv || sr_srv2 > 18 ) {sr_OK = false;sr_cause="bad second servo #";}
            else
            {  for(int srv=sr_srv; srv<=sr_srv2; srv++)
               // now set the servo "srv" to OFF - servo should go to limp, and current to zero
               //use integer division ("/") and modulus ("%") to directly calculate driver#, and pin#
               {  pwmDriver[(srv-1) / 9].setPWM((srv-1) % 9, 4096, 0);
               }
            }
         }
         
      }
      if(sr_OK == false) { sp2sl("********* invalid SSO command: ",sr_cause);}
      return sr_OK;
   } // if(cmd == "SSO")

// add new commands above this comment, in this form, with one tab before "if"
//    if ( cmd == "COMMAND" || cmd == "SHORT-FORM")
//    {
//       code
//       return false;  // command rejected
//       code
//       return true;   // command succeeded
//    }    

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
      if (cmd != "")
      {
         //Log.noticeln("<checkMqtt> cmd = %s.", cmd.c_str());
         bool allIsWell = processCmd(cmd);
         if (allIsWell)
         {
            //Log.noticeln("<checkMqtt> All went well.");
         } // if
         else
         {
            Log.warningln("<checkMqtt> Something went wrong.");
         } // if
      }    // if
   }       // checkMqtt()

#endif // End of precompiler protected code block