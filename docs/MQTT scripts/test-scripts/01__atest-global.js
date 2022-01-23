var Thread = Java.type("java.lang.Thread");

function execute() {
    out("Hexapod goto home position. File: 01__hexbot-goto-home.js");
	
    myTWIPe = "Hexbot3C61054ADD98/commands"     // Doug's bot
//	myTWIPe = "calServoCC50E394F048/commands"     // Andrew's bot

	// clear any previous flow
	send("fg,0,0")
		// go to the  home position
	// since this is the first flow row, we jump to it directly, then pause for 340 msec
	send("fl,1000,3,10,0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0")
// using global coordinates, go to the home position again	
	send("fl,1000,1,10,0,0,0, 18.62,-14.79,-10.60, 0,-20.71,-10.60,-18.62,-14.79,-10.60,18.62,14.79,-10.60,0.00,20.72,-10.60,-18.62,14.79,-10.60")
// move each leg 4 cm in the plus X direction. for leg 1, this is from 18.62 to 22.62 for the X coordinate
	send("fl, 500,1,10,0,0,0, 22.62,-14.79,-10.60, 4,-20.71,-10.60,-14.62,-14.79,-10.60,22.62,14.79,-10.60,4.00,20.72,-10.60,-14.62,14.79,-10.60")
// move everything back to home position again
	send("fl,500,3,10,0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0")
// rince and repeat to allow observations in testing. 
// when testing started, legs 4, 5  and 6 moved in wrong directions. 3 bug fixes later, they do the right thing.
	
	send("fl,1000,1,10,0,0,0, 18.62,-14.79,-10.60, 0,-20.71,-10.60,-18.62,-14.79,-10.60,18.62,14.79,-10.60,0.00,20.72,-10.60,-18.62,14.79,-10.60")
	send("fl, 500,1,10,0,0,0, 22.62,-14.79,-10.60, 4,-20.71,-10.60,-14.62,-14.79,-10.60,22.62,14.79,-10.60,4.00,20.72,-10.60,-14.62,14.79,-10.60")
	send("fl,500,3,10,0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0")
	
	send("fl,1000,1,10,0,0,0, 18.62,-14.79,-10.60, 0,-20.71,-10.60,-18.62,-14.79,-10.60,18.62,14.79,-10.60,0.00,20.72,-10.60,-18.62,14.79,-10.60")
	send("fl, 500,1,10,0,0,0, 22.62,-14.79,-10.60, 4,-20.71,-10.60,-14.62,-14.79,-10.60,22.62,14.79,-10.60,4.00,20.72,-10.60,-14.62,14.79,-10.60")
	send("fl,500,3,10,0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0")
	
	send("fl,1000,1,10,0,0,0, 18.62,-14.79,-10.60, 0,-20.71,-10.60,-18.62,-14.79,-10.60,18.62,14.79,-10.60,0.00,20.72,-10.60,-18.62,14.79,-10.60")
	send("fl, 500,1,10,0,0,0, 22.62,-14.79,-10.60, 4,-20.71,-10.60,-14.62,-14.79,-10.60,22.62,14.79,-10.60,4.00,20.72,-10.60,-14.62,14.79,-10.60")
	send("fl,500,3,10,0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0")
	
	send("fl,1000,1,10,0,0,0, 18.62,-14.79,-10.60, 0,-20.71,-10.60,-18.62,-14.79,-10.60,18.62,14.79,-10.60,0.00,20.72,-10.60,-18.62,14.79,-10.60")
	// now that we've defined the flow, execute it
	send("fg,1,50,9")          // start er up, 20 msec, move toes and don't print coords for each frame

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
