var Thread = Java.type("java.lang.Thread");

function execute() {
    out("Hexapod goto hips - back position. File: 01__hexbot-goto-hipsback.js");
	// each hip roughly 20 degrees towards the back of the bot, otherwise home position
	// used for testing coordinate translation routine fixes
	
    myTWIPe = "Hexbot3C61054ADD98/commands"     // Doug's bot
//	myTWIPe = "calServoCC50E394F048/commands"     // Andrew's bot

	// clear any previous flow
	send("new_flow")
		// go to the  home position
	// since this is the first flow row, we jump to it directly, then pause for 340 msec
	// use local coord offset from home
	send("fl,0,4,10,0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0")
	// odd numbered legs up
	send("fl,200,4,10,0,0,0, 0,3,0, 0,0,0, 0,3,0, 0,0,0, 0,3,0, 0,0,0")
	// then back down, twisted a bit towards the back
	send("fl,500,4,10,0,0,0, 0,0,-6, 0,0,0, 0,0,-6, 0,0,0, 0,0,6, 0,0,0")
	// same routine for the evens
	send("fl,200,4,10,0,0,0, 0,0,-6, 0,3,0, 0,0,-6, 0,3,0, 0,0,6, 0,3,0")
	// and down they go as well (z offset sign varies by side of robot)
	send("fl,500,4,10,0,0,0, 0,0,-6, 0,0,-6, 0,0,-6, 0,0,6, 0,0,6, 0,0,6")
	// stand there for a while
	send("fl,999,4,10,0,0,0, 0,0,-6, 0,0,-6, 0,0,-6, 0,0,6, 0,0,6, 0,0,6")
	

	// now that we've defined the flow, execute it
	send("do_flow,49,50")          // start er up, 50 msec, move toes...

    action.setExitCode(0);
    action.setResultText("done.");
    out("Parameter parameter set up complete");
    return action;
}
function send(cmd){
	out(cmd);
	mqttManager.publish(myTWIPe, cmd);
	Thread.sleep(300);
}
function out(message){
     output.print(message);
}
