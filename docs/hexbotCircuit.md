# PCB

This page has details about the PCB used for the Hexbot robot. At present we are using a breadboard because we have not designed or manufactured the PCB. Here are the details regarding the breadboard.  

## Design

The circuitry for the Hexbot robot is designed in Eagle CAD.

## Fabrication

The PCB is fabricated using a third party service. 

## Design

The circuitry for the Hexbot robot is designed in Eagle CAD.

## Fabrication

The PCB is fabricated using a third party service. 

## Breadboard wiring

<table>
   <caption>Dev Board Pinout Diagram</caption>
   <tr>
      <td align ="left"> 
         <figure>
            <img src="/img/pinoutDOIT32devkitv1.png" alt="Dev board pinout" width="300" height="200"><br>
            <figcaption>Fig.1 - Dev board pinout.</figcaption>
         </figure> 
      </td>
   </tr>
   <tr>
      <td>
         <code>
         Note that for some silly reason this diagram uses the same numbers on the left and right so to differentiate them we put an L for left and R for right infront of the physical pin numbers.
         </code>
      </td>
   </tr>
   <tr>
      <td align ="left"> 
         <table>
            <caption>Dev Board Pin Usage</caption>
            <tr>
               <th>Label</th>
               <th>Physical</th>
               <th>GPIO</th>
               <th>Use</th>
            </tr>
            <tr>
               <td>D21</td>
               <td>R11</td>
               <td>21</td>
               <td>I2C SDA</td>
            </tr>
            <tr>
               <td>D22</td>
               <td>R14</td>
               <td>22</td>
               <td>I2C SCL</td>
            </tr>
            <tr>
               <td>D14</td>
               <td>L5</td>
               <td>14</td>
               <td>Monitor right motor driver PMW freq.</td>
            </tr>
            <tr>
               <td>D12</td>
               <td>L4</td>
               <td>12</td>
               <td>Monitor left motor driver PMW freq.</td>
            </tr>
         </table>
      </td>
  </tr> 
  <tr>
     <td>
         <table>
            <caption>Breadboard Fritzing Diagram</caption>
            <tr>
               <td align ="center">     
                  <img src="/img/hexbotBreadboard_bb.png" alt="Breadboard" width="300" height="200"><br>
                  <figcaption>Fig.2 - Breadboard.</figcaption>
               </td>
            </tr>
        </table>
     </td>
   </tr>
</table>
