var Thread = Java.type("java.lang.Thread");
function execute() {
// myBot = "Hexbot3C61054ADD98/commands" // Dougs Robot
myBot = "Hexbot3C61054ADD98/commands" // Andrew's robot 
send("NEW_FLOW")
send("Flow,1000,MLRH,10,0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0")
send("Flow,1000,MLRH,10,0,0,0, 0,2,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0")
send("Flow,1000,MLRH,10,0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0")
send("DO_FLOW,49,50")
action.setExitCode(0);
action.setResultText("done.");
out("Parameter parameter set up complete");
return action;
 }
 function send(cmd){
 mqttManager.publish(myBot, cmd);
  Thread.sleep(200); 
 }
  function out(message){
  output.print(message);
 }
