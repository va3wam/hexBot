/******************************************************************************
 * @file aaWeb.cpp
 *
 * @mainpage the Aging Apprentice flash memory class 
 * 
 * @section intro_sec Introduction
 *
 * This is an Arduino class that uses a web interface to facilitate configuring
 * the IP address of the MQTT broker as well as Over The Air firmware updates. 
 * This is part of a series of classes made to support a standard set of APIs 
 * for robot platforms. 
 *
 * @section dependencies Dependencies
 * 
 * This class depends on on <a href="https://github.com/espressif/arduino-esp32">
 * Arduino.h</a> being present on your system. This is the Arduino core library
 * that comes bundled with PlatformIO.
 *
 * @section author Author(s)
 *
 * Written by Old Squire for the Aging Apprentice.
 *
 * @section license license
 *
 * Copyright 2021 the Aging Apprentice 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions: The above copyright
 * notice and this permission notice shall be included in all copies or 
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.  
 *****************************************************************************/
#include <aaWeb.h> // Header file for linking.

/**
 * @section constants Define global constants and variables.
 ============================================================================*/
static const char* optionMessage; // Message to put at bottom of option web page. 
static const char* titleName; // Name to use in web page titles.
static bool haveNewBrokerIp; // Flag indicatng that a new Mqtt broker IP is available.
static IPAddress newBrokerIp; // Contains validated new broker IP address.

/**
 * @class Set MQTT broker IP and do OTA firmware updates. 
 ============================================================================*/
aaWeb::aaWeb() 
{
   Serial.println("<aaWeb::aaWeb> Default constructor running.");
} // aaWeb::aaWeb()

/**
 * @class Set MQTT broker IP and do OTA firmware updates. 
 * @param char* The name to be used in the titles of each web page.
 ============================================================================*/
aaWeb::aaWeb(const char* nameForTitles)
{
   optionMessage = "";
   titleName = nameForTitles;
   _defineStyleSheet(); // Define up cascading stye sheet for all web pages.
   _defineLoginPage(nameForTitles); // Define login page.
   _defineOptionPage(nameForTitles); // Define  
   _defineCfgPage(nameForTitles); // Define 
   _defineOtaPage(nameForTitles); // Define 
} //aaWebService::aaWebService()

/**
 * @brief This is the destructor for this class.
 =============================================================================*/
aaWeb::~aaWeb() 
{
   Serial.println("<aaWeb::aaWeb> Destructor running.");
} // aaWeb::aaWeb()

/**
 * @brief Start web server.
 * @param char* The unique name that this MCU will be known as on the network.
 * @return bool true if the web service starts successfully, false if it fails.
 =============================================================================*/
bool aaWeb::start(char *uniqueNamePtr)
{
   Serial.print("<aaWebService::start> Configuring web service with name ");
   Serial.println(uniqueNamePtr);
   if(!MDNS.begin(uniqueNamePtr)) // Use MDNS for host name resolution
   { 
      Serial.println("<aaWebService::start> Error setting up MDNS responder. Local web server not running.");
      return false; // No web server
   } //if
   Serial.println("<aaWebService::start> mDNS responder started.");
   _cfgLoginPageHandler(); // Define event handler for login (root) web page.
   _cfgOptionPageHandler(); // Define event handler for action option web page.
   _cfgCfgPageHandler(); // Define event handler for configuration web page.
   _cfgOtaPageHandler(); // Define event handler for Over The Air upload web page.
   _cfgSetMqttPageHandler(); // Define event handler for incoming post messages with new broker IP.
   _cfgSelectBinaryPageHandler(); // Define event handler for selecting binary file.
   server.begin(); // Start web server
   return true;
} // aaWeb::start() 

/**
 * @brief Check for web client requests.
 * @return bool true if there is a request waiting, false if there is not.
 =============================================================================*/
bool aaWeb::checkForClientRequest()
{
   server.handleClient();
   if(haveNewBrokerIp == true)
   {
      haveNewBrokerIp = false;
      return true;
   } //if
   return false;
} // aaWeb::checkForClientRequest()

/**
 * @brief Handle new IP address for broker from web.
 * @param char* IP address of the MQTT broker.
 * @return bool true if the name is set successfully, false if it fails.
 =============================================================================*/
bool aaWeb::newMqttBrokerIp(const char* address)
{
   int8_t numPings = 1; // How many pings to send to verify IP address
   IPAddress tmpIp; 
   tmpIp.fromString(address);
   bool ret = Ping.ping(address, numPings);
   Serial.print("<aaWebService::newMqttBrokerIp> Sent "); Serial.print(numPings);
   Serial.print(" pings to new IP address "); Serial.print(tmpIp); 
   Serial.print(" and got the response "); Serial.println(ret);
   if(ret == 0)
   {
      Serial.println("<aaWebService::newMqttBrokerIp> New broker IP address is invalid and has been discarded.");
      optionMessage = "Broker IP rejected. Keeping Old Address";
   } //if
   else
   {
      Serial.print("<aaWebService::newMqttBrokerIp> MQTT broker IP will change to "); Serial.println(tmpIp);
      optionMessage = "Broker IP successfully updated";
      newBrokerIp = tmpIp; // Store new broker IP to be collected by main later.
      haveNewBrokerIp = true; // Signal that new broker IP is available.
   } //else
   return ret;
} // aaWeb::newMqttBrokerIp()

/**
 * @brief Get new broker IP address.
 * @return IPAddress Returns the current IPAddress setting for the MQTT broker.
 =============================================================================*/
IPAddress aaWeb::getBrokerIP()
{
   return newBrokerIp;
} // aaWeb::getBrokerIP()

/**
 * @brief Event handler for the login web page.
 =============================================================================*/
void aaWeb::_cfgLoginPageHandler()
{
   server.on("/", HTTP_GET, []() 
   {
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", _loginPage);
   });   
} // aaWeb::_cfgLoginPageHandler()

/**
 * @brief Event handler for the option web page.
 =============================================================================*/
void aaWeb::_cfgOptionPageHandler()
{
   server.on("/chooseAction", HTTP_GET, []() 
   {
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", _optionPage);
   });
} // aaWeb::_cfgOptionPageHandler()

/**
 * @brief Event handler for the configuration web page.
 =============================================================================*/
void aaWeb::_cfgCfgPageHandler()
{
   server.on("/cfgWebUpdate", HTTP_GET, []() 
   {
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", _cfgPage);
   });
} // aaWeb::_cfgCfgPageHandler()

/**
 * @brief Event handler for the OTA web page.
 =============================================================================*/
void aaWeb::_cfgOtaPageHandler()
{
   /*handling uploading firmware file */
   server.on("/update", HTTP_POST, []() 
   {
      server.sendHeader("Connection", "close");
      server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
      ESP.restart();
   }, // server.on("/update")
   []() 
   {
      HTTPUpload& upload = server.upload();
      if(upload.status == UPLOAD_FILE_START) 
      {
         Serial.printf("Update: %s\n", upload.filename.c_str());
         if(!Update.begin(UPDATE_SIZE_UNKNOWN)) 
         { //start with max available size
            Update.printError(Serial);
         } //if
      } //if 
      else if(upload.status == UPLOAD_FILE_WRITE) 
      {
         /* flashing firmware to ESP*/
         if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) 
         {
            Update.printError(Serial);
         } //if
      } //else if 
      else if (upload.status == UPLOAD_FILE_END) 
      {
         if (Update.end(true)) //true to set the size to the current progress
         { 
            Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
         } // if
         else 
         {
            Update.printError(Serial);
         } //else
      } //else if
   }); // []()
} // aaWeb::_cfgOtaPageHandler()

/**
 * @brief Event handler for the MQTT web page.
 =============================================================================*/
void aaWeb::_cfgSetMqttPageHandler()
{
   server.on("/setMqtt", HTTP_POST, []() 
   {
      const char* tmp = server.arg("mqttIp").c_str();
      newMqttBrokerIp(tmp);
      _defineOptionPage(titleName);
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", _optionPage);
   }); // Send CFG page to set new variiable's without needing to reboot
} // aaWeb::_cfgSetMqttPageHandler()

/**
 * @brief Event handler for the select binary web page.
 =============================================================================*/
void aaWeb::_cfgSelectBinaryPageHandler()
{
   // Send OTA page to select binary image to upload
   server.on("/otaWebUpdate", HTTP_GET, []() 
   {
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", _otaPage);
   });
} // aaWeb::_cfgSelectBinaryPageHandler()

/**
 * @brief Defines style sheet used for all web pages.
 =============================================================================*/
void aaWeb::_defineStyleSheet()
{
   Serial.println("<aaWebService::_defineStyleSheet> Defining style sheet for web pages.");
   _webPageStyle = "<style>#file-input,input{width:100%;height:44px;border-radius:4px;margin:10px auto;font-size:15px}"
                     "input{background:#f1f1f1;border:0;padding:0 15px}body{background:#3498db;font-family:sans-serif;font-size:14px;color:#777}"
                     "#file-input{padding:0;border:1px solid #ddd;line-height:44px;text-align:left;display:block;cursor:pointer}"
                     "#bar,#prgbar{background-color:#f1f1f1;border-radius:10px}#bar{background-color:#3498db;width:0%;height:10px}"
                     "form{background:#fff;max-width:258px;margin:75px auto;padding:30px;border-radius:5px;text-align:center}"
                     ".btn{background:#3498db;color:#fff;cursor:pointer}</style>"; 
} // aaWeb::_defineStyleSheet()

/**
 * @brief Define login web page.
 * @param char* Name used in web page title.
 =============================================================================*/
void aaWeb::_defineLoginPage(const char* nameForTitles)
{
   _loginPage = "<head><meta charset='utf-8'/></head>"
                     "<form name=loginForm>"
                     "<h2>" + String(nameForTitles) + " Login</h2>"
                     "<input name=userid placeholder='User ID'> "
                     "<input name=pwd placeholder=Password type=Password> "
                     "<input type=submit onclick=check(this.form) class=btn value=Login></form>"
                     "<script>"
                     "function check(form) {"
                     "if(form.userid.value=='admin' && form.pwd.value=='admin')"
                     "{window.open('/chooseAction')}"
                     "else"
                     "{alert('Error Password or Username')}"
                     "}"
                     "</script>" + _webPageStyle; 
} // aaWeb::_defineLoginPage()

/**
 * @brief Define options web page.
 * @param char* Name used in web page title.
 =============================================================================*/
void aaWeb::_defineOptionPage(const char* nameForTitles)
{
   _optionPage = "<head><meta charset='utf-8'/></head>"
                     "<form name=optionForm>"
                     "<h2>" + String(nameForTitles) + " Web Control</h2>"
                     "<input type=submit onclick=ota() class=btn value=OTA>"
                     "<input type=submit onclick=cfg() class=btn value=Config>"
                     "<div>" + String(optionMessage) + "</div>"
                     "</form>"
                     "<script>"
                     "function ota() {"
                     "window.open('/otaWebUpdate')"
                     "}"
                     "function cfg() {"
                     "window.open('/cfgWebUpdate')"
                     "}"
                     "</script>" + _webPageStyle; 
} // aaWeb::_defineOptionPage() 

/**
 * @brief Define configuration web page.
 * @param char* Name used in web page title.
 =============================================================================*/
void aaWeb::_defineCfgPage(const char* nameForTitles)
{
   _cfgPage = "<head><meta charset='utf-8'/></head>"
                     "<form method='post' action='/setMqtt' name='configForm'>"
                     "<h2>" + String(nameForTitles) + " Config Updater</h2>"
                     "<input name=mqttIp placeholder='MQTT Broker IP'> "
                     "<input type=submit class=btn value=Update></form>"
                     + _webPageStyle; 
} // aaWeb::_defineCfgPage() 

/**
 * @brief Define OTA download web page.
 * @param char* Name used in web page title.
 =============================================================================*/
void aaWeb::_defineOtaPage(const char* nameForTitles)
{
   _otaPage = "<head><meta charset='utf-8'/></head>"
                     "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
                     "<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
                     "<h2>" + String(nameForTitles) + " OTA Web Updater</h2>"
                     "<input type='file' name='update' id='file' onchange='sub(this)' style=display:none>"
                     "<label id='file-input' for='file'>   Choose file...</label>"
                     "<input type='submit' class=btn value='Update'>"
                     "<br><br>"
                     "<div id='prg'></div>"
                     "<br><div id='prgbar'><div id='bar'></div></div><br></form>"
                     "<script>"
                     "function sub(obj){"
                     "var fileName = obj.value.split('\\\\');"
                     "document.getElementById('file-input').innerHTML = '   '+ fileName[fileName.length-1];"
                     "};"
                     "$('form').submit(function(e){"
                     "e.preventDefault();"
                     "var form = $('#upload_form')[0];"
                     "var data = new FormData(form);"
                     "$.ajax({"
                     "url: '/update',"
                     "type: 'POST',"
                     "data: data,"
                     "contentType: false,"
                     "processData:false,"
                     "xhr: function() {"
                     "var xhr = new window.XMLHttpRequest();"
                     "xhr.upload.addEventListener('progress', function(evt) {"
                     "if (evt.lengthComputable) {"
                     "var per = evt.loaded / evt.total;"
                     "$('#prg').html('progress: ' + Math.round(per*100) + '%');"
                     "$('#bar').css('width',Math.round(per*100) + '%');"
                     "}"
                     "}, false);"
                     "return xhr;"
                     "},"
                     "success:function(d, s) {"
                     "console.log('success!') "
                     "},"
                     "error: function (a, b, c) {"
                     "}"
                     "});"
                     "});"
                     "</script>" + _webPageStyle; 
} // aaWeb::_defineOtaPage()                