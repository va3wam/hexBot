// This is file flows.h
// which provides variable definitions and global storage related to leg movement flows
// reference: flows-compiler.ods in the hexbot docs directory
// TODO: document on coordinate systems with diagrams

#ifndef flows_h   // precompiler check to avoid dupicating this code block.
#define flows_h  // Precompiler macro used for precompiler check.

#include <main.h>          // get all our header files
/*
// quick and dirty easily typed debug commands
   #define sp1(x) Serial.print(x);
   #define sp1l(_x) Serial.println(_x);
   #define sp1s(x) Serial.print(x); Serial.print(" ");
   #define sp2(x,y) Serial.print(x); Serial.print(y);
   #define sp2s(x,y) Serial.print(x); Serial.print(" ");Serial.print(y);
   #define sp2l(x,y) Serial.print(x); Serial.println(y);
   #define sp2sl(x,y) Serial.print(x); Serial.print(" ");Serial.println(y);
   #define sp3sl(_x,_y,_z) sp1s(_x);sp1s(_y);sp1l(_z);
   #define sp Serial.print(" ");
   #define nl Serial.println();
*/

//
// A flow is a series of leg positions, as defined by a group of arrays. 
// A specific index into these arrays ( called a "flow row") defines a position
// for each of the 6 legs, and the characteristics of the movement from
// the previous position to this position.

// The position of a given leg can be described in various ways:
//    - as an absolute location, using the global coordinate position
//    - as an absolute location, expressed as a delta (for each axis) from the leg's home position
//    - as a relative location, expressed as a delta (for each axis) from the leg's previous position
//   (going to neural position is equivalent to going to offset (0,0,0) from home position)
// 
// The first position in a flow is a special case, since there is no previous position.
// There are 2 cases for the first position:
//     - treat it as a starting point, and simply move directly to that position, ignoring time
//     - treat the last position in the last flow that was executed as the previous position
//
// Flows can be set to repeat, with these variations:
//     - execute fow exactly once
//     - execute flow for a particular number of repetitions
//     - execute the flow for a specified time duration
//
// These are the arrays that contain the flow currently being executed

#define flowLength  200          // maximum number of positions in a flow
//  -----------------------------// start of flow row arraysq
int f_msecs[flowLength];         // time duration in milliseconds for movement to this location

int f_operation[flowLength];     // type of operation specified for this position
   const int fo_moveAbs = 1;     // move to absolute location, coords are in global system
   const int fo_moveLocal = 2;   // move to location given in local coords
   const int fo_moveGRelHome = 3; // move to loc'n relative to home, coords = GLOBAL deltas relative to home position
   const int fo_moveLRelHome = 4; // move to loc'n relative to home, coords = LOCAL deltas relative to home position
   const int fo_moveRelLast = 5; // move to loc'n relative to last position, coords = deltas w.r.t. last position

   const int fo_startAbs = 6;    // start of flow - go directly to an absolute location
   const int fo_startRelHome=7;  // start of flow - go directly to a position relative to home position
   const int fo_startPrev = 8;   // start flow, treating end of last flow as previous position
   const int fo_markCycleStart=9;  // note this flow row number as the beginning of a numbered cycle within the flow
   const int fo_markCycleEnd =10;  // note this flow row number as the end of a numbered cycle within the flow
   const int fo_doCycle = 11;  // execute the specified cycle for the specified number of iterations.

int f_lShape1[flowLength];    // description of type of line to follow between last position and this one
   const int fl_straight = 10;   // straight line
   const int fl_parabola = 11;   // parabola
   const int fl_ellipse = 12;    // ellipse, (including circle)
                                 // when operation is a flow cycle command, this contains a time, or interation count
float f_lShape2[flowLength];  // parameters defining the geometry of a non-straight line path
float f_lShape3[flowLength];
float f_lShape4[flowLength];

float f_legX[flowLength] [7];    // X coord for each of 6 legs, 2nd index is leg number. meaning varies per operation
float f_legY[flowLength] [7];    // Y coord for each of 6 legs, 2nd index is leg number
float f_legZ[flowLength] [7];    // size 7 means indices 0 - 6, so can number legs from 1 to 6
//  -----------------------------// end of flow row arrays

float f_lastLegX[7] ;              // working copy of coords for each leg
float f_lastLegY[7] ;
float f_lastLegZ[7] ;

float f_tmpX ;                  // temporary coord storage for do_flow processing
float f_tmpY ;
float f_tmpZ ;

float f_deltaX[7];         // distance in X direction to be travelled, in frames, in this flow row
float f_deltaY[7];
float f_deltaZ[7];

float f_endLegX[7] ;               // local coords of end poing of line for current flow row
float f_endLegY[7] ;               // used to calculate delta movements needed for each frame movement
float f_endLegZ[7] ;

float f_lastAngH[7];             // remember last angle for each servo so you can skip redundant ones
float f_lastAngK[7];
float f_lastAngA[7];

int f_cycleStart[10];         // starting flow row number for each of 10 repeatable cycles
int f_cycleEnd[10];           // ending flow row number for each of 10 repeatable cycles
bool f_cycling;               // true iff we're executing a repeating cycle
int f_cyclesLeft;             // counter for repeatable cycles
int f_resumeRow;              // flow row number to resume at after a repeatable cycle is completed


int f_count = 0;                 // counter as we process FLOW commands, accumulating flow rows, ends up as row count
int f_active = 0;                // what row number we're executing, after a FLOW_GO command
bool f_flowing = false;          // set to true if we're executing a fow
int f_frame = 0;                 // what frame number we're working on within a flow row
int f_msecPerFrame = 50;         // time slice length in msec for movement between positions
int f_msecPerFrameDefault = 50;  // unless specified in the FLOW_GO command, do 20 msec time slices
int f_framesPerPosn = 0;         // how many intermediary moves per flow row
bool f_goodData  ;               // used in flow processing do_flow() routine
int f_nextTime = 0;              // millis timestamp for next frame movement to be generated
float f_angH, f_angK, f_angA ;   // temp variables to hold servo angles
int L;                           // leg number use as a loop index in many places
float safeMaxPosX = 6;             // max allowed displacement on local axes from home position
float safeMaxNegX = 8;             // ..checking is done after local coords are calculated in PrepNextLine()
float safeMaxPosY = 17;            // ..can argue that safety limits should be per leg. Front legs have more room?
float safeMaxNegY = 6;
float safeMaxPosZ = 6;
float safeMaxNegZ = 8;           // raised for rotation script

int toeMoveAction = 8;           // binary coded action to take when you calculated next toe position (frame) in do_flow()
                                 // persists, but defaults to display local coords, set up in FLOW_GO MQTT command
   const int fa_moveServos = 1;  // feed calculated PWM values to servo motors so they move
   const int fa_dispAngles = 2;  // display the calculated servo angles (degrees) in serial monitor
   const int fa_dispPWM    = 4;  // display the calculated PWM values
   const int fa_dispLocal  = 8;  // display the local coordinates of toe position
// fa_disGlobal  = 16;           // display the global coordinates of toe position <too hard to do, frames are in local coords

const float pi = 3.1415926 ;

   // hexbot body measurements
   const float BT = 2.915 ;   // thigh length (between hip and knee, horizontally)
   const float BS = 7.620 ;   // shin length (between knee and ankle)
   const float BF = 11.059;   // foot length (diagonal between ankle and toe)
   const float BTOA = 17.063; // toe offset angle = angle between ankle servo vertical, and toe, in degrees
   const float BTOD = 3.245;  // toe offset distance. perpendicular distance from toe to ankle servo vertical line

// coordinate system memory menmonic:
// if direction dude is riding the bot like a bronco, 
//     ...global X, Y, and Z follow the BLT rule:
// Belly button points to +x
// Left shoulder points to +y
// Top of his head points to +z

// if direction dude is standing on a leg's hip servo, facing away hexbot's center,
//      ...local X, Y, and Z follow the BTL rule:
// Belly button points to local +x
// Top of head points to local +y
// Left shoulder points to local +z


// home position of each leg, using global coords
float f_homeGlobX[7] ;         // X coord in global coords, for each of 6 legs
float f_homeGlobY[7] ;         //  initialized in setupFlows()
float f_homeGlobZ[7] ;

float f_localHomeX = 13.78;   // home position in local coordinates
float f_localHomeY = -10.60;  // (same for all legs)
float f_localHomeZ = 0.0;

float f_hipX[7];           //global X coordinate for hip, for each leg
float f_hipY[7];           // and Y, init'd in flows.cpp setupFlows()

// symbols for key x, y position coordinates for leg movements
float fp_frontToeHomeX = 3.82739 + 20.91875 * .707107;   // 707107 is sin of 45 degrees
float fp_frontToeHomeY = 20.91875 * .707107;
float fp_sideToeHomeX = 0;
float fp_sideToeHomeY = 6.9423 + 2.9165 + 7.61998 + 3.23019;

float fp_frontHipX = 3.82739 + 7.13528 * .707107;
float fp_frontHipY = 5.04750;
float fp_sideHipX = 0;
float fp_sideHipY = 6.9423;

int legIndexDriver[7];     // for a lookup based on leg # to get driver number ( could just use int(leg/3)
int legIndexHipPin[7];      // for a lookup based on leg # to get pin number for hip ( could just use 3*(mod(leg-1,3))
                           // knee pin is 1 more than hip, ankle is 2 more
                           // these are initialized in flows.cpp:setupFlows()
String legNum[7];          // lookup table to convert leg# to corresponding string

// defines for routines acessed from elsewhere
bool globCoordsToLocal(int legNumber, float gx, float gy, float gz, float *lx, float *ly, float *lz);
int32_t mapDegToPWM(float degrees, float centerDeg);
void anglesToCoords(float hip, float knee, float ankle, float *toeX, float *toeY, float *toeZ);
void coordsToAngles(float Tx, float Ty, float Tz) ;
void do_flow();

// precalculate the computationally expensive trig values used in coordinate translation   
   float sin_p45 = +.707107;      // sin( + 45 degrees)
   float sin_m45 = -.707107;      // sin( - 45 degrees)
   float cos_p45 = +.707107;      // cos( + 45 degrees) 
   float cos_m45 = +.707107;     // cos( - 45 degrees)

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

#define sp3sl(a,b,c)  \
   Serial.print(a);   \
   Serial.print(" "); \
   Serial.print(b);   \
   Serial.print(" "); \
   Serial.println(c);

#define sp4s(a,b,c,d)   \
   Serial.print(a);   \
   Serial.print(" "); \
   Serial.print(b);   \
   Serial.print(" "); \
   Serial.print(c);   \
   Serial.print(" "); \
   Serial.print(d);   \
   Serial.print(" ");

#define sp4sl(a,b,c,d)   \
   Serial.print(a);   \
   Serial.print(" "); \
   Serial.print(b);   \
   Serial.print(" "); \
   Serial.print(c);   \
   Serial.print(" "); \
   Serial.println(d);

#define sp5s(a,b,c,d,e)   \
   Serial.print(a);   \
   Serial.print(" "); \
   Serial.print(b);   \
   Serial.print(" "); \
   Serial.print(c);   \
   Serial.print(" "); \
   Serial.print(d);   \
   Serial.print(" "); \
   Serial.print(e);   \
   Serial.print(" ");

#define sp5sl(a,b,c,d,e)   \
   Serial.print(a);   \
   Serial.print(" "); \
   Serial.print(b);   \
   Serial.print(" "); \
   Serial.print(c);   \
   Serial.print(" "); \
   Serial.print(d);   \
   Serial.print(" "); \
   Serial.println(e);

#define sp6s(a,b,c,d,e,f)   \
   Serial.print(a);   \
   Serial.print(" "); \
   Serial.print(b);   \
   Serial.print(" "); \
   Serial.print(c);   \
   Serial.print(" "); \
   Serial.print(d);   \
   Serial.print(" "); \
   Serial.print(e);   \
   Serial.print(" "); \
   Serial.print(f);   \
   Serial.print(" ");

#define sp6sl(a,b,c,d,e,f)   \
   Serial.print(a);   \
   Serial.print(" "); \
   Serial.print(b);   \
   Serial.print(" "); \
   Serial.print(c);   \
   Serial.print(" "); \
   Serial.print(d);   \
   Serial.print(" "); \
   Serial.print(e);   \
   Serial.print(" "); \
   Serial.println(f);

#define sp Serial.print(" ");
#define nl Serial.println();


// routine call templates
bool prepNextLine();
bool prepNextLine1();   
#endif // End of precompiler protected code block
