/*************************************************************************************************************************************
 * @file aaWebService.cpp
 * @author theAgingApprentice
 * @brief Common API for retrieving ESP32 chip configuration information. 
 * @details Retrieve chip configuration details from both FreeRTOS and the ESP32 Arduino framework.
 * @copyright Copyright (c) 2021 the Aging Apprentice
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files 
 * (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, 
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished 
 * to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE 
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 * YYYY-MM-DD Dev        Description
 * ---------- ---------- -------------------------------------------------------------------------------------------------------------
 * 2021-03-28 Old Squire Fixed path to OTA web page.
 * 2021-03-17 Old Squire Program created.
 *************************************************************************************************************************************/
#include <aaWebService.h> // Header file for linking.
static const char* optionMessage; // Message to put at bottom of option web page. 
static const char* titleName; // Name to use in web page titles.
static bool haveNewBrokerIp; // Flag indicatng that a new Mqtt broker IP is available.
static IPAddress newBrokerIp; // Contains validated new broker IP address.
/**
 * @brief This is the default constructor for this class.
===================================================================================================*/
aaWebService::aaWebService() 
{

} //aaWebService::aaWebService()

/**
 * @brief This is the second form of the constructor for this class.
===================================================================================================*/
aaWebService::aaWebService(const char* nameForTitles)
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
===================================================================================================*/
aaWebService::~aaWebService() 
{
   Serial.println("<aaWebService::aaWebService> aaNetwork destructor running.");
} //aaWebService::aaWebService()

/**
 * @brief Define the style sheet used to format all web pages.
===================================================================================================*/
void aaWebService::_defineStyleSheet()
{
   Serial.println("<aaWebService::_defineStyleSheet> Defining style sheet for web pages.");
   _webPageStyle = "<style>#file-input,input{width:100%;height:44px;border-radius:4px;margin:10px auto;font-size:15px}"
                     "input{background:#f1f1f1;border:0;padding:0 15px}body{background:#3498db;font-family:sans-serif;font-size:14px;color:#777}"
                     "#file-input{padding:0;border:1px solid #ddd;line-height:44px;text-align:left;display:block;cursor:pointer}"
                     "#bar,#prgbar{background-color:#f1f1f1;border-radius:10px}#bar{background-color:#3498db;width:0%;height:10px}"
                     "form{background:#fff;max-width:258px;margin:75px auto;padding:30px;border-radius:5px;text-align:center}"
                     ".btn{background:#3498db;color:#fff;cursor:pointer}</style>"; 
} //aaWebService::_defineStyleSheet()

/**
 * @brief Define the login web page page that is used to secure the application.
===================================================================================================*/
void aaWebService::_defineLoginPage(const char* nameForTitles)
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
} //aaWebService::_defineLoginPage()

/**
 * @brief Define the options web page that is used to indicate what action the user wants to take.
===================================================================================================*/
void aaWebService::_defineOptionPage(const char* nameForTitles)
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

} //aaWebService::_defineOptionPage()

/**
 * @brief Define the configuaration page that allows the user to make network config changes.
===================================================================================================*/
void aaWebService::_defineCfgPage(const char* nameForTitles)
{
   _cfgPage = "<head><meta charset='utf-8'/></head>"
                     "<form method='post' action='/setMqtt' name='configForm'>"
                     "<h2>" + String(nameForTitles) + " Config Updater</h2>"
                     "<input name=mqttIp placeholder='MQTT Broker IP'> "
                     "<input type=submit class=btn value=Update></form>"
                     + _webPageStyle; 
} //aaWebService::_defineCfgPage()

/**
 * @brief Define the page that allows the user to perform OTA code uploads.
===================================================================================================*/
void aaWebService::_defineOtaPage(const char* nameForTitles)
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
} //aaWebService::_defineOtaPage()

/**
 * @brief Start up the local web service.
 * @details Set up the web pages and event handlers for incoming client requests. Once that is done
 * start the actual web service.
 * @param char *uniqueNamePtr unique network name.
 * @return bool where true means a conneciton was made and false means no connectioon was made.
===================================================================================================*/
bool aaWebService::start(char *uniqueNamePtr)
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
} //aaWebService::start()

/**
 * @brief Configure login (root) web page handler.
===================================================================================================*/
void aaWebService::_cfgLoginPageHandler()
{
   server.on("/", HTTP_GET, []() 
   {
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", _loginPage);
   });   
} //aaWebService::_cfgMainPageHandler()

/**
 * @brief Configure action option web page handler.
===================================================================================================*/
void aaWebService::_cfgOptionPageHandler()
{
   server.on("/chooseAction", HTTP_GET, []() 
   {
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", _optionPage);
   });
} //aaWebService::_cfgOptionPageHandler()

/**
 * @brief Configure network configuration web page handler.
===================================================================================================*/
void aaWebService::_cfgCfgPageHandler()
{
   server.on("/cfgWebUpdate", HTTP_GET, []() 
   {
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", _cfgPage);
   });
} //aaWebService::_cfgCfgPageHandler()

/**
 * @brief Configure Over The Air code update web page handler and handle file uploads.
===================================================================================================*/
void aaWebService::_cfgOtaPageHandler()
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
} //aaWebService::_cfgOtaPageHandler()

/**
 * @brief Configure HTTP post of new MQTT broker IP address handler.
===================================================================================================*/
void aaWebService::_cfgSetMqttPageHandler()
{
   server.on("/setMqtt", HTTP_POST, []() 
   {
      const char* tmp = server.arg("mqttIp").c_str();
      newMqttBrokerIp(tmp);
      _defineOptionPage(titleName);
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", _optionPage);
   }); // Send CFG page to set new variiable's without needing to reboot
} //aaWebService::_cfgSetMqttPageHandler()

/**
 * @brief Configure select binary image handler.
===================================================================================================*/
void aaWebService::_cfgSelectBinaryPageHandler()
{
   // Send OTA page to select binary image to upload
   server.on("/otaWebUpdate", HTTP_GET, []() 
   {
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", _otaPage);
   });
} //aaWebService::_cfgSendBinaryPageHandler()

/**
 * @brief Check for pending client requests and service them as required.
===================================================================================================*/
bool aaWebService::newMqttBrokerIp(const char* address) // Handle new IP address for broker from web.
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
} //aaWebService::newMqttBrokerIp()

/**
 * @brief Get new broker IP address.
===================================================================================================*/
IPAddress aaWebService::getBrokerIP() 
{
   return newBrokerIp;
} //aaWebService::getBrokerIP()

/**
 * @brief Check for pending client requests and service them as required.
===================================================================================================*/
bool aaWebService::checkForClientRequest()
{
   server.handleClient();
   if(haveNewBrokerIp == true)
   {
      haveNewBrokerIp = false;
      return true;
   } //if
   return false;
} //aaWebService::checkForClientRequest()

/**
 * @brief Returns the status of the WiFi connection.
 * @return bool WiFi.isConnected(), true if there is a connection and false if there is not.
===================================================================================================*/
bool aaWebService::connectStatus()
{
   return WiFi.isConnected();
} // amNetwork::connectStatus()