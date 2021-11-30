// This is file flows.h
// which provides variable definitions and global storage related to leg movement flows
// reference: flows-compiler.ods in the hexbot docs directory
// TODO: document on coordinate systems with diagrams

#ifndef flows_h   // precompiler check to avoid dupicating this code block.
#define flows_h  // Precompiler macro used for precompiler check.

#include <main.h>          // get all our header files
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

#define flowLength  100          // maximum number of positions in a flow

int f_msecs[flowLength];         // time duration in milliseconds for movement to this location

int f_operation[flowLength];     // type of operation specified for this position
   const int fo_moveAbs = 1;     // move to absolute location, coords are in  global system
   const int fo_moveRelHome = 2; // move to loc'n relative to home, coords = deltas relative to home position
   const int fo_moveRelLast = 3; // move to loc'n relative to last position, coords = deltas w.r.t. last position
   const int fo_startAbs = 4;    // start of flow - go directly to an absolute location
   const int fo_startRelHome = 5;// start of flow - go directly to a position relative to home position
   const int fo_startPrev = 6;   // start flow, treating end of last flow as previous position
   const int fo_cycleByCount = 7;// repeat this flow for number of cycles in LineShape1
   const int fo_cycleByTime = 8; // repeat this flow for number of milleseconds in LineShape1
   const int fo_markCycle = 9;   // next repeatable cycle starts at row after this one

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

float f_lastLegX[7] ;              // working copy of coords for each leg
float f_lastLegY[7] ;
float f_lastLegZ[7] ;

int f_count = 0;                 // counter as we process FLOW commands, accumulating flow rows, ends up as row count
int f_active = 0;                // what row number we're executing, after a FLOW_GO command
bool f_flowing = false;          // set to true if we're executing a fow
int f_msecPerFrame = 20;         // time slice length in msec for movement between positions
int f_msecPerFrameDefault = 20;  // unless specified in the FLOW_GO command, do 20 msec time slices
bool f_goodData  ;               // used in flow processing do_flow() routine

const float pi = 3.1415926 ;

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

// defines for routines acessed from elsewhere
bool globCoordsToLocal(int legNumber, float gx, float gy, float gz, float *lx, float *ly, float *lz);

// precalculate the computationally expensive trig values used in coordinate translation   
   float sin_p45 = +.707107;      // sin( + 45 degrees)
   float sin_m45 = -.707107;      // sin( - 45 degrees)
   float cos_p45 = +.707107;      // cos( + 45 degrees) 
   float cos_m45 = +.707107;     // cos( - 45 degrees)
#endif // End of precompiler protected code block
