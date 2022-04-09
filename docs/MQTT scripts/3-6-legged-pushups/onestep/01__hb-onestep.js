var Thread = Java.type("java.lang.Thread");

function execute() {
    out("hexbot-onestep.js");
	
    myTWIPe = "Hexbot3C61054ADD98/commands"     // Doug's bot
//	myTWIPe = "calServoCC50E394F048/commands"     // Andrew's bot

// This script is documented in ...docs/MQTT scripts/creating-flows.odt, section 17

    out(" ");
	send("NEW_FLOW")	// clear any previous flow
//stage1: go directly to home position first, ignoring the 1000 msec, then pause for 340 msec
	send("FL, 1000, MGRH, 10,0,0,0,   0,0,0,   0,0,0,   0,0,0,   0,0,0,    0,0,0,     0,0,0")
//stage2:	
    send("FL, 1000, MGRH, 10,0,0,0,   0,0,2,   0,0,0,   0,0,2,   0,0,0,  0,0,2,   0,0,0")
//stage3:	
    send("FL, 1000, MGRH, 10,0,0,0,   0,0,2,  -4,0,0,   0,0,2,  -4,0,0,  0,0,2,  -4,0,0")
//stage4:	
    send("FL, 1000, MGRH, 10,0,0,0,   0,0,0,  -4,0,0,   0,0,0,  -4,0,0,  0,0,0,  -4,0,0")
//stage5:	
    send("FL, 1000, MGRH, 10,0,0,0,   0,0,0,  -4,0,2,   0,0,0,  -4,0,2,  0,0,0,  -4,0,2")
//stage6:	
    send("FL, 1000, MGRH, 10,0,0,0,  -4,0,0,   0,0,2,  -4,0,0,   0,0,2,  -4,0,0,  0,0,2")
//stage7:	
    send("FL, 1000, MGRH, 10,0,0,0,  -4,0,0,   0,0,0,  -4,0,0,   0,0,0,  -4,0,0,  0,0,0")
//stage8:	
    send("FL, 1000, MGRH, 10,0,0,0,  -4,0,2,   0,0,0,  -4,0,2,   0,0,0,  -4,0,2,  0,0,0")
//stage9:	
    send("FL, 1000, MGRH, 10,0,0,0,   0,0,2,  -4,0,0,  0,0,2,   -4,0,0,  0,0,2,  -4,0,0")

//27 leave bot in belly-on-the-floor position, to ease next start up
	send("fl,1000,MLRH,10,0,0,0,   0,3.0,0,   0,3.0,0,   0,3.0,0,   0,3.0,0,   0,3.0,0,   0,3.0,0,")
	
	// now that we've defined the flow, execute it
	send("DO_FLOW,49")          // start er up, 50 msec per frame,
								// toeMoveAction:
								// 1 - move toes (altho I sometimes test with 5V power offset)
								// 16 - print global X and Y coords for Excel graphing
								// 32 - at flow startup, print a nicely formatted, numbered flow listing

    action.setExitCode(0);
    action.setResultText("done.");
    out("Parameter parameter set up complete");
    return action;                                           
}
function send(cmd){
	out(cmd);
	mqttManager.publish(myTWIPe, cmd);
	Thread.sleep(200);  // occasionally lose a line if it's reduced to 100
}
function out(message){
     output.print(message);
}
