var Thread = Java.type("java.lang.Thread");

function execute() {
    out("hexbot-deep-pu-c4.js");
// ******* note following WARNING ******************	
	out("**** WARNING **** - if your both is tethered with cables,")
	out("  prepare them for a 192 degree robot rotation in this script")
	
    myTWIPe = "Hexbot3C61054ADD98/commands"     // Doug's bot
//	myTWIPe = "calServoCC50E394F048/commands"     // Andrew's bot

    out(" ");
	send("NEW_FLOW")	// clear any previous flow

	// since this is the first flow row, we jump to it directly, then pause for 340 msec
	send("fl,0500,MLRH,10,0,0,0,    0,0,0,      0,0,0,    0,0,0,     0,0,0,    0,0,0,     0,0,0")
// refer to VSC.../docs/rotation-12degrees.ods to examine following flow row number calculations

// ============= start of repeatable section ==================================
// start with odd legs down touchng floor at home position, even legs up in the air at end of a 12 degree clockwise (CW) twisr
// (starting even legs at end of 12 degree range like this makes the flow sequence repeatable to be able to do more than 12 degrees)
	send("fl,050,MGC,10,0,0,0, 18.62,-14.79,-10.60, -4.31,-20.26,-9.60,-18.62,-14.79,-10.60,21.29,10.60,-9.60,0.00,20.72,-10.60,-15.14,18.34,-9.60")
// move odd numbered legs (the ones touching floor) 4 degrees CW, which moves robot 4 degrees CCW
// at the same time, move even numbered legs (up in the air) 4 degrees CCW, on the way back to their home position
	send("fl,200,MGC,10,0,0,0, 17.54,-16.05,-10.60, -2.88,-20.51,-9.60, -19.61,-13.46,-10.60, 20.50,12.06,-9.60, 1.45,20.67,-10.60, -16.38,17.24,-9.60")
// do another 4 degrees, for both odd and even legs, as above
	send("fl,200,MGC,10,0,0,0, 16.38,-17.24,-10.60, -1.44,-20.66,-9.60, -20.50,-12.06,-10.60, 19.61,13.46,-9.60, 2.88,20.52,-10.60, -17.54,16.05,-9.60")
// and do it one more time, so we've moved a total of 12 degrees.
// after this, the odd legs are 12 degrees CW from home, and even legs are back to home position
	send("fl,200,MGC,10,0,0,0, 15.14,-18.34,-10.60,  0.00,-20.71,-9.60, -21.29,-10.60,-10.60, 18.62,14.79,-9.60, 4.31,20.27,-10.60, -18.62,14.79,-9.60")
// now reverse the odd / even leg roles. raise the odds legs, and lower the even legs
// get the even legs on the ground before you raise the odds, or the bot dips down inbetween
	send("fl,050,MGC,10,0,0,0, 15.14,-18.34,-10.60,  0.00,-20.71,-10.60, -21.29,-10.60,-10.60, 18.62,14.79,-10.60, 4.31,20.27,-10.60, -18.62,14.79,-10.60")
	send("fl,050,MGC,10,0,0,0, 15.14,-18.34,-9.60,   0.00,-20.71,-10.60, -21.29,-10.60,-9.60, 18.62,14.79,-10.60, 4.31,20.27,-9.60, -18.62,14.79,-10.60")
// move even legs (the ones touching floor) 4 degrees CW, which moves robot 4 degrees CCW
// at the same time, move odd legs (up in the air) 4 degrees CCW, on the way back to their home position
	send("fl,200,MGC,10,0,0,0, 16.38,-17.24,-9.60,  -1.44,-20.66,-10.60, -20.50,-12.06,-9.60, 19.61,13.46,-10.60, 2.88,20.52,-9.60, -17.54,16.05,-10.60")
	// do another 4 degrees, for both odd and even legs, as above
	send("fl,200,MGC,10,0,0,0, 17.54,-16.05,-9.60,  -2.88,-20.51,-10.60, -19.61,-13.46,-9.60, 20.50,12.06,-10.60, 1.45,20.67,-9.60, -16.38,17.24,-10.60")
// and do it one more time, so we've moved a total of 12 degrees.
// at this point, even legs are 12 degrees CW from home, and odd legs are back to home position	
	send("fl,200,MGC,10,0,0,0, 18.62,-14.79,-9.60,  -4.31,-20.26,-10.60, -18.62,-14.79,-9.60, 21.29,10.60,-10.60, 0.00,20.72,-9.60, -15.14,18.34,-10.60")
// get all the legs on the ground before you lift different ones, to a void a dip inbetween	
	send("fl,050,MGC,10,0,0,0, 18.62,-14.79,-10.60,  -4.31,-20.26,-10.60, -18.62,-14.79,-10.60, 21.29,10.60,-10.60, 0.00,20.72,-10.60, -15.14,18.34,-10.60")
// we've now moved through 12 degrees 	
// we're now at the point where we can repeat the above sequence, starting by	
// ============= end of repeatable section ====================================

// ============= start of repeatable section as cycle # 5 =====================

// start by flagging the start of a repeatable cycle
	send("fl,050,MCS,5,0,0,0, ")
	// msec = 050 (ignored)
	// operation = 9 = fo_markCycleStart
	// param1 = 5 = cycle identifier

// then do regular flow commands (actually the same as commented section above). . .
	send("fl,050,MGC,10,0,0,0, 18.62,-14.79,-10.60, -4.31,-20.26,-9.60,-18.62,-14.79,-10.60,21.29,10.60,-9.60,0.00,20.72,-10.60,-15.14,18.34,-9.60")
	send("fl,200,MGC,10,0,0,0, 17.54,-16.05,-10.60, -2.88,-20.51,-9.60, -19.61,-13.46,-10.60, 20.50,12.06,-9.60, 1.45,20.67,-10.60, -16.38,17.24,-9.60")
	send("fl,200,MGC,10,0,0,0, 16.38,-17.24,-10.60, -1.44,-20.66,-9.60, -20.50,-12.06,-10.60, 19.61,13.46,-9.60, 2.88,20.52,-10.60, -17.54,16.05,-9.60")
	send("fl,200,MGC,10,0,0,0, 15.14,-18.34,-10.60,  0.00,-20.71,-9.60, -21.29,-10.60,-10.60, 18.62,14.79,-9.60, 4.31,20.27,-10.60, -18.62,14.79,-9.60")
	send("fl,050,MGC,10,0,0,0, 15.14,-18.34,-10.60,  0.00,-20.71,-10.60, -21.29,-10.60,-10.60, 18.62,14.79,-10.60, 4.31,20.27,-10.60, -18.62,14.79,-10.60")
	send("fl,050,MGC,10,0,0,0, 15.14,-18.34,-9.60,   0.00,-20.71,-10.60, -21.29,-10.60,-9.60, 18.62,14.79,-10.60, 4.31,20.27,-9.60, -18.62,14.79,-10.60")
	send("fl,200,MGC,10,0,0,0, 16.38,-17.24,-9.60,  -1.44,-20.66,-10.60, -20.50,-12.06,-9.60, 19.61,13.46,-10.60, 2.88,20.52,-9.60, -17.54,16.05,-10.60")
	send("fl,200,MGC,10,0,0,0, 17.54,-16.05,-9.60,  -2.88,-20.51,-10.60, -19.61,-13.46,-9.60, 20.50,12.06,-10.60, 1.45,20.67,-9.60, -16.38,17.24,-10.60")
	send("fl,200,MGC,10,0,0,0, 18.62,-14.79,-9.60,  -4.31,-20.26,-10.60, -18.62,-14.79,-9.60, 21.29,10.60,-10.60, 0.00,20.72,-9.60, -15.14,18.34,-10.60")
	send("fl,050,MGC,10,0,0,0, 18.62,-14.79,-10.60, -4.31,-20.26,-10.60, -18.62,-14.79,-10.60, 21.29,10.60,-10.60, 0.00,20.72,-10.60, -15.14,18.34,-10.60")

// then flag the end of the cycle
	send("fl,050,MCE,5,0,0,0, ")
	// msec = 050 (ignored)
	// operation = 10=9 = fo_markCycleEnd
	// param1 = 5 = cycle identifier
	
// ============= end of repeatable section ====================================

// ============= request 6 repetitions of this cycle ==========================
	send("fl,050,DC,5,6,0,0, ")
	// msec = 050 (ignored)
	// operation = 11 = fo_doCycle
	// param1 = 5 = cycle identifier
	// param2 = 6 = number of repetitions requested

// ============= end of repeatable section ====================================

/*  use this style of comment to limit what robot does for testing
*/

	// leave bot in belly-on-the-floor position, to ease next start up
	send("fl,0500,MLRH,10,0,0,0,   0,0,0,     0,0,0,     0,0,0,     0,0,0,     0,0,0,     0,0,0,")
	send("fl,0500,MLRH,10,0,0,0,   0,3.0,0,   0,3.0,0,   0,3.0,0,   0,3.0,0,   0,3.0,0,   0,3.0,0,")
	
	// now that we've defined the flow, execute it
	send("DO_FLOW,1")          // start er up, 50 msec/frame (== 20 frames/sec), move toes and don't print coords for each frame

    action.setExitCode(0);
    action.setResultText("done.");
    out("Parameter parameter set up complete");
    return action;
}
function send(cmd){
	out(cmd);
	mqttManager.publish(myTWIPe, cmd);
	Thread.sleep(100);
}
function out(message){
     output.print(message);
}
