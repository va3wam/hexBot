# Hexbot Assembly Instructions

This document takes you through the steps neccessary to successfully assemble version 3 of the Hexbot robot.

## What you need

Before you start make sure that you have all [the hardware that you need](/docs/hexbotHardware.md).

## Step 1 - Assemble three right legs

Repeat the steps in this section three times in order to create the three right legs that we need. Make note of the orientation of the motors relative to the components that make up the leg in figure 1.

 <table>
  <tr>
    <td align ="left"> 
        <figure>
           <img src="/img/assembledRightLeg v2.png" alt="Right Leg"> </th>
           <figcaption>Fig.1 - Hexbot right leg assembly</figcaption>
        </figure> 
    </td>
    <td align ="left">
       <ol>  
          <li>Put horn on 3 motors.</li>  
          <li>Set the first motor to 90 degrees.</li>  
          <li>Screw the hip onto the first motor's horn.</li>  
          <li>Screw the second motor into the hip motor bracket.</li>  
          <li>Set the second motor to 90 degrees.</li>  
          <li>Screw one end of the upper leg to the horn of the second motor.</li>  
          <li>Set the third motor to 90 degrees.</li>  
          <li>Screw the third motor onto the other end of the upper leg.</li>  
          <li>Screw the lower leg onto the third motor via its motor bracket.</li> 
       </ol>  
    </td>
  </tr>  
</table> 

## Step 2 - Assemble three left legs

Repeat the steps in this section three times in order to create the three left legs that we need. Make note of the orientation of the motors relative to the components that make up the leg in figure 2.

 <table>
  <tr>
    <td align ="left"> 
        <figure>
           <img src="/img/assembledLeftLeg v2.png" alt="Left Leg"> </th>
           <figcaption>Fig.2 - Hexbot left leg assembly</figcaption>
        </figure> 
    </td>
    <td align ="left">
       <ol>  
          <li>Put horn on 3 motors.</li>  
          <li>Set the first motor to 90 degrees.</li>  
          <li>Screw the hip onto the first motor's horn.</li>  
          <li>Screw the second motor into the hip motor bracket.</li>  
          <li>Set the second motor to 90 degrees.</li>  
          <li>Screw one end of the upper leg to the horn of the second motor.</li>  
          <li>Set the third motor to 90 degrees.</li>  
          <li>Screw the third motor onto the other end of the upper leg.</li>  
          <li>Screw the lower leg onto the third motor via its motor bracket.</li> 
       </ol>  
    </td>
  </tr>  
</table> 

## Step 3 - Connect legs to the lower body

Repeat the steps in this section six times in order to attach all six legs to the robot. Make note of the orientation of the motors in figure 3. It is important to ensure that the three motors on each side of the robot body are oriented the same way. When you are done the direction that the servo horns are facing will be considered the front of the robot.

<table>
  <tr>
    <td align ="left"> 
       <figure>
          <img src="/img/hexapodFullAssembly-hybridRenderingWireframe.svg" alt="Full robot assembly" width="750" height="750"> 
          <figcaption>Fig.3 - Attaching legs to body</figcaption>
       </figure> 
    </td>
    <td align ="left">
       <ol>  
          <li>Insert a leg assemby into a servo bracket on the body.</li>  
          <li>Use four screws and nuts to secure the assembly in place.</li>  
       </ol> 
       You have now completed assembly of the lower body and legs. Next you need to assemble the electronics platform.
    </td>
  </tr>  
</table> 

## Step 4 - Mount the upper body and electronics

```We are still in the design phase for Hexbot's electronics so this part of the instructions calls for a bit more inginuiuty at present.```

<table>
  <tr>
    <td align ="left"> 
       <figure>
          <img src="/img/topBodyLayer.jpg" alt="top layer" width="500" height="300"> 
          <figcaption>Fig.4 - Top layer</figcaption>
       </figure> 
    </td>
    <td align ="left">
       <ol>  
          <li>Fabricate a 4 3/4" wide by 6 1/2" long rectangle out of a thin light material. A piece of 1/8" plexiglass would work well. We will refer to this as the top body layer.</li>
        <li>Fasten a ~2" by 6" breadboard to the top body layer. Be sure to centre it.</li> 
        <li>Cut the 4 corners of the top body layer off to allow for maximum clearance of the legs.</li>
        <li>Mount 2 motor drivers to the top body layer.</li>
        <li>Drill 1/8" holes in the top body layer. Be sure to align these holes with the nes that already exist in the bottom layer.</li>
        <li>Mount the top body layer to the bottom layer using ~1 1/2" standoffs bolted through the existing mounting holes.</li>
       </ol> 
       Congratulations, you now have a fully assembled Hexbot. From here you need to <a href="/docs/wireMotors.md">wire the motors</a>.
    </td>
  </tr>  
</table> 
