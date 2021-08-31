# OTA Update Web Interface

Hexbot allows you to perform firmware updates Over The Air (OTA) via it's web interface. This page walks you through the process.

## Login Screen

<table>
  <tr>
    <td align ="center"> 
       <figure>
          <img src="/img/hexbotWebLoginScreen.png" alt="Login Screen" width="300" height="200"><br>
          <figcaption>Fig.1 - Login Screen</figcaption>
       </figure> 
    </td>
    <td align ="left"> 
      In order to use Hexbot's web interface you must meet these conditions:
      <br><br>
      <ol>
        <li>Hexbot must be powered on and successfully connected to the local network.</li>
        <li>You will need the use of a web broswer on a computer that is also on the local network.</li>
        <li>You will need to know the IP address of Hexbot, which you can get using a couple of different methods.</li>
      </ol>
        Once you meet all of these conditions then open your web browser and enter Hexbot's IP address in the URL address field. You should be presented with the screen shown in figure 1. You are now talking directly to Hexbot via it's web interface. 
        <br><br>
        Secutiry is a bit lax at present as the ID and password are hardcoded into the HTML sent to the client. With this in mind it is not too much of a security breach to tell you here that the login credentials are:
      <ul>
        <li>ID: admin</li>
        <li>Password: admin</li>
      </li>   
    </td>
  </tr>  
</table>

## Web Control Screen

<table>
  <tr>
    <td align ="center"> 
       <figure>
          <img src="/img/hexbotWebControlScreen.png" alt="Hexbot Config Updater Screen" width="300" height="200"><br>
          <figcaption>Fig.2 - Web Control Screen</figcaption>
       </figure> 
    </td>
    <td align ="left"> 
      After successfully logging in you are prsented with the options menu shown in figure 2. There are minimal options available as this is a tool meant for initialization and maintenance tasks only. Your options are limited to:
      <br><br>
      <ol>
        <li>OTA - used to perform firmware updates.</li>
        <li>Config - used to tell Hexbot what the IP address of your network's MQTT broker is.</li>
      </ol>
    </td>
  </tr>  
</table>

## OTA Updater Screen

<table>
  <tr>
    <td align ="center"> 
       <figure>
          <img src="/img/hexbotWebConfigScreen.png" alt="Hexbot Config Updater Screen" width="300" height="200"><br>
          <figcaption>Fig.3 - Config Updater Screen</figcaption>
       </figure> 
    </td>
    <td align ="left"> 
      If you selected the OTA option on the Web Control screen then you will be presented with the Config Updater screen shown in figure 3. To perform OTA updates of Hexbot's firmware here is what you need to do.
      <br><br>
      <ol>
        <li>Find the firmware binary file that you want to upload. Normally you will find here: *<Hexbot project directory>/.pio/build/feather32/firmware.bin*. This example assumes that you are using the Huzzah32 development board. Note that when you pull source code from your [git remote origin](https://www.javatpoint.com/git-origin-master) this directory gets erased. To rebuild it simply run a build in PlatformIO.</li>
        <li>Click choose file. Navigate to the firmware.bin file.</li>
        <li>Click the Update button.</li>
        <li>You can watch the progress bar on the web page and/or watch the progress in a terminal window if you are hard wired into the Hexbot USB port.</li>
        <li>Check to see if the MQTT broker IP address is still OK. If not then reset it.</li>
      </ol>  
    </td>
  </tr>  
</table>

## Config Updater Screen

<table>
  <tr>
    <td align ="center"> 
       <figure>
          <img src="/img/hexbotWebConfigScreen.png" alt="Hexbot Config Updater Screen" width="300" height="200"><br>
          <figcaption>Fig.3 - Config Updater Screen</figcaption>
       </figure> 
    </td>
    <td align ="left"> 
      If you selected the Config option on the Web Control screen then you will be presented with the Config Updater screen shown in figure 4. The ony thing that you can configure via this interface it the IP address Hexbot will use to access an MQTT broker. Here is an outline of the workflow: 
<br><br>
<ol>
  <li>Enter a valid IP address and click the Update button.</li>
  <li>Hexbot does a rudamentary validation of the IP address by pinging it.</li>
  <li>If the address can be reached then you will see the message *Broker IP successfuly uppdated* and Hexbot updates it's flash memory with this value. Note that flash memory persists through power off.</li>
  <li>If the address cannot be reached then you will see the message *Broker IP rejected. Keeping old address* and Hexbot discards your input.</li>
</ol>
      
```Normally you will need to perform this task the first time you bring up Hexbot on a new network. Once you make this change you should reboot Hexbot to ensure thhat the new address is being used.```
    </td>
  </tr>  
</table>
