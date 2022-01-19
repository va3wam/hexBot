var Thread = Java.type("java.lang.Thread");

function execute() {
    out("hexbot-deep-pu-c4.js");
	
    myTWIPe = "Hexbot3C61054ADD98/commands"     // Doug's bot
//	myTWIPe = "calServoCC50E394F048/commands"     // Andrew's bot

    out(" ");
	send("fg,0,0")	// clear any previous flow
// this script will need safety box extensions to position legs low, 	
	// go to the  home position
	// since this is the first flow row, we jump to it directly, then pause for 340 msec
	send("fl,1000,4,10,0,0,0,    0,0,0,      0,0,0,    0,0,0,     0,0,0,    0,0,0,     0,0,0")
// refer to VSC.../docs/rotation-12degrees.ods to examine following flow rows
	send("fl,500,1,10,0,0,0,18.62,-14.79,-10.60,-4.31,-20.26,-7.60,-18.62,-14.79,-10.60,21.29,10.60,-7.60,0.00,20.72,-10.60,-15.14,18.34,-7.60")

	send("fl,500,1,10,0,0,0,17.54,-16.05,-10.60,-2.88,-20.51,-7.60,-19.61,-13.46,-10.60,20.50,12.06,-7.60,1.45,20.67,-10.60,-16.38,17.24,-7.60")
	send("fl,500,1,10,0,0,0,16.38,-17.24,-10.60,-1.44,-20.66,-7.60,-20.50,-12.06,-10.60,19.61,13.46,-7.60,2.88,20.52,-10.60,-17.54,16.05,-7.60")
	send("fl,500,1,10,0,0,0,15.14,-18.34,-10.60,0.00,-20.71,-7.60,-21.29,-10.60,-10.60,18.62,14.79,-7.60,4.31,20.27,-10.60,-18.62,14.79,-7.60")

	send("fl,500,1,10,0,0,0,15.14,-18.34,-7.60,0.00,-20.71,-10.60,-21.29,-10.60,-7.60,18.62,14.79,-10.60,4.31,20.27,-7.60,-18.62,14.79,-10.60")

	send("fl,500,1,10,0,0,0,16.38,-17.24,-7.60,-1.44,-20.66,-10.60,-20.50,-12.06,-7.60,19.61,13.46,-10.60,2.88,20.52,-7.60,-17.54,16.05,-10.60")
	send("fl,500,1,10,0,0,0,17.54,-16.05,-7.60,-2.88,-20.51,-10.60,-19.61,-13.46,-7.60,20.50,12.06,-10.60,1.45,20.67,-7.60,-16.38,17.24,-10.60")
	send("fl,500,1,10,0,0,0,18.62,-14.79,-7.60,-4.31,-20.26,-10.60,-18.62,-14.79,-7.60,21.29,10.60,-10.60,0.00,20.72,-7.60,-15.14,18.34,-10.60")		

	// leave bot in belly-on-the-floor position, to ease next start up
	send("fl,1000,4,10,0,0,0,   0,0,0,     0,0,0,     0,0,0,     0,0,0,     0,0,0,     0,0,0,")
	send("fl,1000,4,10,0,0,0,   0,3.0,0,   0,3.0,0,   0,3.0,0,   0,3.0,0,   0,3.0,0,   0,3.0,0,")
	
	// now that we've defined the flow, execute it
	send("fg,1,50,1")          // start er up, 20 msec, move toes and don't print coords for each frame

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
