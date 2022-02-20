var Thread = Java.type("java.lang.Thread");

function execute() {
    out("hexbot-deep-pu-c4.js");
	
    myTWIPe = "Hexbot3C61054ADD98/commands"     // Doug's bot
//	myTWIPe = "calServoCC50E394F048/commands"     // Andrew's bot

    out(" ");
	send("NEW_FLOW")	// clear any previous flow
// this script will need safety box extensions to position legs low, 	
	// go to the  home position
	// since this is the first flow row, we jump to it directly, then pause for 340 msec
	send("fl,1000,MLRH,10,0,0,0,    0,0,0,      0,0,0,    0,0,0,     0,0,0,    0,0,0,     0,0,0")
		
//===== ripple reposition each leg 2 cm closer to bdy =======================================
// using local coordinates & offsets, raise legs 1 and 6, which are opposites
	send("fl,500,MLRH,10,0,0,0,     0,3,0,     0,0,0,    0,0,0,     0,0,0,    0,0,0,     0,3,0")
// put them back down, but 4 cm closer to the chassis (local X direction)
	send("fl,500,MLRH,10,0,0,0,    -4,0,0,     0,0,0,    0,0,0,     0,0,0,    0,0,0,    -4,0,0")
// do same thim for opposite legs 2 and 5
	send("fl,500,MLRH,10,0,0,0,    -4,0,0,      0,3,0,   0,0,0,     0,0,0,    0,3,0,    -4,0,0")
	send("fl,500,MLRH,10,0,0,0,    -4,0,0,     -4,0,0,   0,0,0,     0,0,0,   -4,0,0,    -4,0,0")
// and lastly do same for opposite legs 3 and 6
	send("fl,500,MLRH,10,0,0,0,    -4,0,0,     -4,0,0,    0,3,0,    0,3,0,   -4,0,0,    -4,0,0")
	send("fl,500,MLRH,10,0,0,0,    -4,0,0,     -4,0,0,   -4,0,0,    -4,0,0,   -4,0,0,    -4,0,0")
// stay in that position, with legs displaced 4 cm "inward" for 1 second		
	send("fl,1000,MLRH,10,0,0,0,    -4,0,0,     -4,0,0,   -4,0,0,    -4,0,0,   -4,0,0,   -4,0,0")
	
//====== 6 legged pushups ===========================================================================
// lower all legs 5 cm below home position's height, which raises robot
	send("fl,1000,MLRH,10,0,0,0,    -4,-5,0,     -4,-5,0,   -4,-5,0,    -4,-5,0,   -4,-5,0,    -4,-5,0")	
// go back to home position's height
	send("fl,1000,MLRH,10,0,0,0,    -4, 0,0,     -4, 0,0,   -4, 0,0,    -4, 0,0,   -4, 0,0,    -4, 0,0")
// raise al legs 2.3 cm (not quite belly on floor) which lowers robot. shorter travel, so less time allocated
	send("fl, 500,MLRH,10,0,0,0,    -4,2.3,0,    -4,2.3,0,  -4,2.3,0,   -4,2.3,0,  -4,2.3,0,   -4,2.3,0")	
// go back to home position's height
	send("fl, 500,MLRH,10,0,0,0,    -4, 0,0,     -4, 0,0,   -4, 0,0,    -4, 0,0,   -4, 0,0,    -4, 0,0")
// repeat last 4 commands, raising and lowering robot body again
	send("fl,1000,MLRH,10,0,0,0,    -4,-5,0,     -4,-5,0,   -4,-5,0,    -4,-5,0,   -4,-5,0,    -4,-5,0")	
	send("fl,1000,MLRH,10,0,0,0,    -4, 0,0,     -4, 0,0,   -4, 0,0,    -4, 0,0,   -4, 0,0,    -4, 0,0")
	send("fl, 500,MLRH,10,0,0,0,    -4,2.3,0,    -4,2.3,0,  -4,2.3,0,   -4,2.3,0,  -4,2.3,0,   -4,2.3,0")	
	send("fl, 500,MLRH,10,0,0,0,    -4, 0,0,     -4, 0,0,   -4, 0,0,    -4, 0,0,   -4, 0,0,    -4, 0,0")

//==== lift L1, L3 & L5, and do pushups on other 3 legs ===========================================
// raise legs 1, 3, and 5 in gull wing fashion, so they're no longer in play	
	send("fl, 500,MLRH,10,0,0,0,    4.62, 9.9,0,  -4, 0,0,   4.62, 9.9,0,  -4, 0,0,   4.62, 9.9,0,  -4, 0,0")
// now, using only legs 2, 4 and 6, lower those legs 5 cm, which raises robot, doing a 3 legged pushuup	
	send("fl,1000,MLRH,10,0,0,0,    4.62, 9.9,0,  -4,-5,0,   4.62, 9.9,0,  -4,-5,0,   4.62, 9.9,0,  -4,-5,0")	
// then bring them back to home position height
	send("fl,1000,MLRH,10,0,0,0,    4.62, 9.9,0,  -4, 0,0,   4.62, 9.9,0,  -4, 0,0,   4.62, 9.9,0,  -4, 0,0")	
// like we did before, now raise the 3 legs 2.3 cm, which lowers the robot
	send("fl, 500,MLRH,10,0,0,0,    4.62, 9.9,0,  -4,2.3,0,  4.62, 9.9,0,  -4,2.3,0,  4.62, 9.9,0,  -4,2.3,0")	
// the back to hom position's height
	send("fl, 500,MLRH,10,0,0,0,    4.62, 9.9,0,  -4, 0,0,   4.62, 9.9,0,  -4, 0,0,   4.62, 9.9,0,  -4, 0,0")	
// oh what the heck, raise the robot once more just to show off
	send("fl,1000,MLRH,10,0,0,0,    4.62, 9.9,0,  -4,-5,0,   4.62, 9.9,0,  -4,-5,0,   4.62, 9.9,0,  -4,-5,0")	
// and go back to home position's height (but not the home position, because we're still pulled inward by 4 cm)
	send("fl,1000,MLRH,10,0,0,0,    4.62, 9.9,0,  -4, 0,0,  4.62, 9.9,0,   -4, 0,0,   4.62, 9.9,0,  -4, 0,0")	

//===== back to neutral, then back to belly ====================================================
// bring all legs back to home position, but pulled in 4 cm
	send("fl, 500,MLRH,10,0,0,0,    -4, 0,0,     -4, 0,0,   -4, 0,0,    -4, 0,0,   -4, 0,0,    -4, 0,0")
// do it again, just to be sure	
	send("fl, 500,MLRH,10,0,0,0,    -4, 0,0,     -4, 0,0,   -4, 0,0,    -4, 0,0,   -4, 0,0,    -4, 0,0")
// raise opposite legs 1 and 6 by 3 cm, and push the out to normal home position, undoing the 4 cm pull in	
	send("fl,500,MLRH,10,0,0,0,     0,3,0,    -4,0,0,   -4,0,0,    -4,0,0,   -4,0,0,     0,3,0")
// then put legs 1 and 6 down in the true home position
	send("fl,500,MLRH,10,0,0,0,     0,0,0,    -4,0,0,   -4,0,0,    -4,0,0,   -4,0,0,     0,0,0")
// do the same for legs 2 and 5
	send("fl,500,MLRH,10,0,0,0,     0,0,0,      0,3,0,  -4,0,0,    -4,0,0,    0,3,0,     0,0,0")
	send("fl,500,MLRH,10,0,0,0,     0,0,0,      0,0,0,  -4,0,0,    -4,0,0,    0,0,0,     0,0,0")
// lastly, do the same for legs 3 and 4
	send("fl,500,MLRH,10,0,0,0,     0,0,0,      0,0,0,    0,3,0,    0,3,0,    0,0,0,     0,0,0")
	send("fl,500,MLRH,10,0,0,0,     0,0,0,      0,0,0,    0,0,0,    0,0,0,    0,0,0,     0,0,0")
// and sit there for a bit		
	send("fl, 500,MLRH,10,0,0,0,    0,0,0,      0,0,0,    0,0,0,    0,0,0,    0,0,0,     0,0,0")

// leave bot in belly-on-the-floor position, to ease next start up
	send("fl,1000,MLRH,10,0,0,0,   0,3.0,0,   0,3.0,0,   0,3.0,0,   0,3.0,0,   0,3.0,0,   0,3.0,0,")
	
	// now that we've defined the flow, execute it
	send("DO_FLOW,1")          // start er up, 20 msec, move toes and don't print coords for each frame

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
