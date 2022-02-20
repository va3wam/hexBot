var Thread = Java.type("java.lang.Thread");

function execute() {
    out("Hexapod goto home position. File: 01__hexbot-goto-home.js");
	
    myTWIPe = "Hexbot3C61054ADD98/commands"     // Doug's bot
//	myTWIPe = "calServoCC50E394F048/commands"     // Andrew's bot

	// clear any previous flow
	send("NEW_FLOW")
		// go to the  home position
	// since this is the first flow row, we jump to it directly, then pause for 340 msec
	send("fl,1000,MLRH,10,0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0")

	// now that we've defined the flow, execute it
	send("DO_FLOW,49")          // start er up, 20 msec, move toes and don't print coords for each frame

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
