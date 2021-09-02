# Wiring Motors

There are 18 motors that need to be connected to 2 different motor drivers. The purpose of this document is to ensure that your Hexbot's motor wiring is done the same way that the code in this repository expects it to be.

 <figure>
  <img src="/img/hexbotMotorWiring.png" alt="Motor wiring" style="width:100%">
  <figcaption>Fig.1 - Hexbot servo motor wiring reference.</figcaption>
</figure> 

## Wiring Chart

Please refer to figure 1 to understand the references made in this chart. Once you have the motors set up you will need to sort out the <a href="/docs/hexbotCircuit.md">circuitry</a>.

<table>
   <tr>
      <th>Left Side</th>
      <th>Right Side</th>
   </tr> 
   <tr>
      <td>
         <table>
            <tr>
               <th align="center">Leg</th>
               <th align="center">Motor</th>
               <th align="center">Driver 1 Port</th>
            </tr>
            <tr>
               <th rowspan="3">L1</th>
               <th align="center">H1</th>
               <td align="center">0</td>
             </tr>
             <tr>
                <th align="center">K1</th>
                <td align="center">1</td>
             </tr>
             <tr>
                <th align="center">A1</th>
                <td align="center">2</td>
             </tr>
             <tr>
               <th rowspan="3">L2</th>
               <th align="center">H2</th>
               <td align="center">3</td>
             </tr>
             <tr>
                <th align="center">K2</th>
                <td align="center">4</td>
             </tr>
             <tr>
                <th align="center">A2</th>
                <td align="center">5</td>
             </tr>
             <tr>
               <th rowspan="3">L3</th>
               <th align="center">H3</th>
               <td align="center">6</td>
             </tr>
             <tr>
                <th align="center">K3</th>
                <td align="center">7</td>
             </tr>
             <tr>
                <th align="center">A3</th>
                <td align="center">8</td>
             </tr>
         </table> 
      </td> 
      <td>  
         <table>
            <tr>
               <th align="center">Leg</th>
               <th align="center">Motor</th>
               <th align="center">Driver 2 Port</th>
            </tr>
            <tr>
               <th rowspan="3">L4</th>
               <th align="center">H4</th>
               <td align="center">0</td>
             </tr>
             <tr>
                <th align="center">K4</th>
                <td align="center">1</td>
             </tr>
             <tr>
                <th align="center">A4</th>
                <td align="center">2</td>
             </tr>
             <tr>
               <th rowspan="3">L5</th>
               <th align="center">H5</th>
               <td align="center">3</td>
             </tr>
             <tr>
                <th align="center">K5</th>
                <td align="center">4</td>
             </tr>
             <tr>
                <th align="center">A5</th>
                <td align="center">5</td>
             </tr>
             <tr>
               <th rowspan="3">L6</th>
               <th align="center">H6</th>
               <td align="center">6</td>
             </tr>
             <tr>
                <th align="center">K6</th>
                <td align="center">7</td>
             </tr>
             <tr>
                <th align="center">A6</th>
                <td align="center">8</td>
             </tr>
         </table>        
      </td>
   </tr>
</table> 
     
