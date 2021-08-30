# Wiring Motors

There are 18 motors to wire up to 2 motor drivers. This document provides guidance to standardize how the leg servo motors are connectred to the motor drivers in order to allow 1 code base to predictably control all Hexbot robots in the same way.

 <figure>
  <img src="/img/hexbotMotorWiring.png" alt="Motor wiring" style="width:100%">
  <figcaption>Fig.1 - Hexbot servo motor wiring reference.</figcaption>
</figure> 

## Left Side

Please refer to figure 1 to understand the references mode in this chart.

 <table>
  <tr>
    <th>Leg</th>
    <th>Motor</th>
    <th>Driver 1 port</th>
  </tr>
  <tr>
     <th rowspan="3">L1</th>
     <th>H1</th>
     <th>K1</th>
     <th>A1</th>
     <td>0</td>
     <td>1</td>  
     <td>2</td>  
  </tr>
  <tr>
     <th rowspan="3">L2</th>
     <th>H2</th>
     <th>K2</th>
     <th>A2</th>
     <td>3</td>
     <td>4</td>  
     <td>5</td>  
  </tr>
  <tr>
     <th rowspan="3">L3</th>
     <th>H3</th>
     <th>K3</th>
     <th>A3</th>
     <td>6</td>
     <td>7</td>  
     <td>8</td>  
  </tr>
</table> 
