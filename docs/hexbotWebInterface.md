# Hexbot Web Interface

Hexbot features a 2.4GHz 802.11n [WiFi radio](https://www.juniper.net/documentation/en_US/junos-space-apps/network-director3.1/topics/concept/wireless-radio-channel.html) that requires a WiFi access point capable of communicating at 150Mbps. Hexbot hosts a [web server](https://en.wikipedia.org/wiki/Web_server) that can be used to configure values stored in non volitile memory (NVRAM) as well as perform over-the-air (OTA) firmware updates via a web browser.

<code>
  One quirk of the web interface is that each screen opens up a seperate tab. For this reason you should get in thhe habit of closing the tabs once you are done with them or you will get overwhelmed by screens during a busy session.
</code>

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
        Security is a bit lax at present as the ID and password are hardcoded into the HTML sent to the client. With this in mind it is not too much of a security breach to tell you here that the login credentials are:
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
          <figcaption>Fig.4 - Config Updater Screen</figcaption>
       </figure> 
    </td>
    <td align ="left"> 
      If you selected the Config option on the Web Control screen then you will be presented with the Config Updater screen shown in figure 4. The ony thing that you can configure via this interface it the IP address Hexbot will use to access an MQTT broker. Here is an outline of the workflow: 
<br><br>
<ol>
  <li>Enter a valid IP address and click the Update button.</li>
  <li>Hexbot does a rudamentary validation of the IP address by pinging it.</li>
  <li>If the address can be reached then you will see the message *Broker IP successfuly uppdated* on the web page and Hexbot updates it's flash memory with this value. If you have a terminal session connected to Hexbot's USB port then you will also see the messages in your console. See figure 5 for these messages. Note that flash memory persists through power off.</li>
  <li>If the address cannot be reached then you will see the message *Broker IP rejected. Keeping old address* on the web page and Hexbot discards your input. If you have a terminal session connected to Hexbot's USB port then you will also see the messages in your console. See figure 5 for these messages.</li>
</ol>
      
<figure>
  <img src="/img/hexbotConsoleBrokerIPChange.png" alt="Console messages for broker IP change."><br>
  <figcaption>Fig.5 - Console messages for broker IP change</figcaption>
</figure> 
<br><br>      
<code>
  Normally you will only need to perform this task the first time that you change the network that Hexbot is connected to. It is a good idea to also check that the broker IP address is correct whenever you load new firmware onto your Hexbot.
</code>
    </td>
  </tr>  
</table>
