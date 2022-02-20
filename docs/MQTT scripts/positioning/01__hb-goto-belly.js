var Thread = Java.type("java.lang.Thread");

function execute() {
    out("Hexapod go to Belly position.  File= 01__hexbot-go-to-belly.js");
	
    myTWIPe = "Hexbot3C61054ADD98/commands"     // Doug's bot
//	myTWIPe = "calServoCC50E394F048/commands"     // Andrew's bot
	
	// clear any previous flow
	send("nf")
	
	// go to the lying on belly position, with legs 3.5 cm above home position
	// since this is the first flow row, we jump to it directly, then pause for 340 msec
	// start with neutral position, to avoid crashing to floor
	send("fl,300,MLRH,10,0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0")
	send("fl,1000,MGRH,10,0,0,0, 0,0,3.5, 0,0,3.5, 0,0,3.5, 0,0,3.5, 0,0,3.5, 0,0,3.5")
	//
	// now that we've defined the flow, execute it
	send("df,1")          // start er up, 20 msec, move toes and don't print coords for each frame

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
