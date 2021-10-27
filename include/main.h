/*******************************************************************************
 * @file main.h  
 *******************************************************************************/
#ifndef main_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define main_h // Precompiler macro used for precompiler check.

/*******************************************************************************
 * @section mainIncludes Included libraries.
 *******************************************************************************/
#include <Arduino.h> // Arduino Core for ESP32. Comes with PlatformIO.
#include <aaChip.h> // Core (CPU) details that the code running on.
#include <aaNetwork.h> // Wifi functions. 
#include <aaWebService.h> // Realtime web-based network config and OTA code updates.
#include <aaFlash.h> // Use Flash memory to store values that persist past reboot.
#include <aaMqtt.h> // Use MQTT for remote management and monitoring.
#include <known_networks.h> // String arrays of known Access Points and their passwords.
#include <InverseK.h> // https://github.com/cgxeiji/CGx-InverseK.
#include <Wire.h> // Required for I2C communication.
#include <Adafruit_PWMServoDriver.h> // https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library.
#include <ArduinoLog.h> // https://github.com/thijse/Arduino-Log.
#include <Adafruit_GFX.h> // OLED graphics
#include <Adafruit_SH110X.h> // OLED text
#include <hexbot_gpio_pins.h> // GPIO pin uses

/*******************************************************************************
 * @section mainVars Global variable definitions.
 * @details In order to get rid of "error: 'xxx' was not declared in this scope"
 * compiler errors list a function from any of the include files here. 
 *******************************************************************************/
// Config related variables
const char* HOST_NAME_PREFIX = "Hexbot"; // Prefix for our unique network name.
aaChip appCpu; // Access information about the ESP32 application microprocessor (Core1).
aaNetwork network(HOST_NAME_PREFIX); // WiFi session management.
bool networkConnected = false;
bool mqttBrokerConnected = false;
bool oledConnected = false;
bool motorController1Connected = false;
bool motorController2Connected = false;
bool mobilityStatus = false;
int8_t displayPage = 1;
// MQTT related variables.
aaFlash flash; // Non-volatile memory management. 
aaMqtt mqtt; // Publish and subscribe to MQTT broker. 
IPAddress brokerIP; // IP address of the MQTT broker.
char uniqueName[HOST_NAME_SIZE]; // Character array that holds unique name for Wifi network purposes. 
char *uniqueNamePtr = &uniqueName[0]; // Pointer to first address position of unique name character array.
char healthTopicTree[50] = ""; // Char array to hold full health topic tree name.
char helpTopicTree[50] = ""; // Char array to hold full health topic tree name.
String result[2] = {"false","true"}; // Provide english lables for true and flase return codes.
// RGB OLED related variabes.
const uint8_t numColoursSupported = 9; // Number of colours LED can be set to.
const bool commonAnode = true; // Set to true if RGB LED has a common anode, false for common cathode.
const uint8_t RED = 0; // Reset button LED red. 
const uint8_t GREEN = 1; // Reset button LED green. 
const uint8_t BLUE = 2; // Reset button LED blue. 
const uint8_t YELLOW = 3; // Reset button LED YELLOW. 
const uint8_t ORANGE = 4; // Reset button LED PINK.
const uint8_t PINK = 5; // Reset button LED PINK.
const uint8_t AQUA = 6; // Reset button LED aqua. 
const uint8_t WHITE = 7; // Reset button LED white. 
const uint8_t BLACK = 8; // Reset button LED white. 
const double_t PWM_FREQ = 500; // 500Hz.
const uint8_t PWM_RESOLUTION = 8; // ESP32 can go up to 8 bit PWM resolution.
#define PWM_RED_CHANNEL 0 // ESP32 has 16 channels which can generate 16 independent waveforms. Use 0 for RGB red.
#define PWM_GREEN_CHANNEL 1 // ESP32 has 16 channels which can generate 16 independent waveforms. Use 1 for RGB green.
#define PWM_BLUE_CHANNEL 2 // ESP32 has 16 channels which can generate 16 independent waveforms. Use 2 for RGB blue.
typedef struct
{
   String name; // Name associated with colour properties
   uint32_t redDutyCycle; // Up time of the PWM signal. Ranges from 0-256. 127 is a 50% duty cycle for example.
   uint32_t greenDutyCycle; // Up time of the PWM signal. Ranges from 0-256. 127 is a 50% duty cycle for example.
   uint32_t blueDutyCycle; // Up time of the PWM signal. Ranges from 0-256. 127 is a 50% duty cycle for example.
}struct_Colour; 
struct_Colour statusColour[numColoursSupported]; // Array of colours.
struct_Colour memColour; // Used to switch back RGB LED colour when it is temporarily changed.
// DAE Inverted kinematic related variables.
const uint8_t footLen = 11; // Distance from ankle to toe (foot) is 11cm. 
const uint8_t shinLen = 7.5; // Distance from knee to ankle (shin) is 7.5cm.
const uint8_t toeOffset = 17; // Angle that toe is offset from 90deg of ankle joint is 17 degrees.
const uint8_t origXOffset = 2.92; // Distance the knee is offset from the origin along the x axis.
// I2C related variables.
#define I2C_BUS0_SPEED 400000 // Define speed of I2C bus 2. Note 400KHz is the upper speed limit for ESP32 I2C
#define I2C_BUS1_SPEED 100000 // Define speed of I2C bus 2. Note 100KHz is the upper speed limit for ESP32 I2C
#define MPU6050_I2C_ADD 0x68 // GY521 I2C address.
#define leftOLED_I2C_ADD 0x3D // OLED used for robot's left eye I2C adddress.
#define rightOLED_I2C_ADD 0x3C // OLED used for robot' right eye I2C address.
#define dcMotorController 0xB0 >> 1 // Wire Library only uses 7 bit addresses so you need to shift address one bit to the right.
#define LCD16x2 0x3F // Liquid Crystal Display.
#define PCA9685ServoDriverAllCall 0x70 // Global I2C address for all servo drivers.
#define PCA9685ServoDriver1 0x40 // I2C address for first servo driver.
#define PCA9685ServoDriver2 0x41 // I2C address for second servo driver.
#define PCA9685ServoDriver3 0x42 // I2C address for third servo driver.
#define PCA9685ServoDriver4 0x43 // I2C address for fourth servo driver.
#define PCA9685ServoDriver5 0x44 // I2C address for fifth servo driver.
#define PCA9685ServoDriver6 0x45 // I2C address for sixth servo driver.
#define PCA9685ServoDriver7 0x46 // I2C address for seventh servo driver.
// Define OLED related variables.
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);
bool buttonA_flag = false; // Flag used by hardware ISR for button A.
bool buttonB_flag = false; // Flag used by hardware ISR for button B.
bool buttonC_flag = false; // Flag used by hardware ISR for button C.
uint8_t oledX = 128; // Screen width in pixels.
uint8_t oledY = 64; // Screen height in pixels.
uint8_t textBaseX = 6; // Smallest font width in pixels.
uint8_t textBaseY = 8; // Smallest font height in pixels.
uint8_t oledOrientation = 3; // Orientation of OLED. 
// Define servoLegs related variables.
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates.
#define servoMiddlePWM 300 // 90 degree or center position of servo motor.
#define servoUpDownSwing 100 // Up and down PWM range for leg. 
#define servoFrontBackSwing 100 // Up and down PWM range for leg. 
#define numLegs 6 // Number of legs robot has.
#define numDrivers 2 // Number of servo motor drivers robot has.
Adafruit_PWMServoDriver pwmDriver[numDrivers]; // Servo driver object.
uint16_t pwmClkStart = 0; // Start value of count-up PWM high signal.
uint32_t oscFreq = 27000000; // Frequency of oscilator on motor driver. 
float const _45degreesInRadians = 0.785398163; // 45 degrees in radians.
float const _135degreesInRadians = 0.235619449; // 135 degrees in radians.
float hipAngle, kneeAngle, ankleAngle, toeAngle; // Holds results of last calcAngles.
typedef struct
{
      String description = "01234567890abcdefghi"; 
      int8_t driverAdd;
      int8_t hipPinNum;
      int8_t kneePinNum;
      int8_t anklePinNum;
      int16_t maxUp;
      int16_t maxDown;
      int16_t maxFront;
      int16_t maxBack;
      float const hipJointDist = 0; // Hip joint is origin so distance is 0mm.
      float const kneeJointDist = 0; // Knee joint is also origin so distance is 0mm.
      float const ankleJointDist = 76.19977; // Ankle joint to origin in mm.
      float const toeJointDist = 110.67793; // Toe joint to origin in mm.
      float const hipMinAngle = 0; // Min angle of hip joint in radians.
      float const hipMaxAngle = 0; // Max angle of knee joint in radians.
      float const kneeMinAngle = _45degreesInRadians; // Min angle of knee joint in radians.
      float const kneeMaxAngle = _135degreesInRadians; // Max angle of knee joint in radians.
      float const ankleMinAngle = _45degreesInRadians; // Min angle of ankle joint in radians.
      float const ankleMaxAngle = _135degreesInRadians; // Max angle of ankle joint in radians.
      float const toeMinAngle = 0; // Min angle of toe in radians.
      float const toeMaxAngle = 0; // Max angle of toe in radians.
      Link hip; // Declare hip as key link point along leg. 
      Link knee; // Declare knee as key link point along leg.
      Link ankle; // Declare ankle as key link point along leg.
      Link toe; // Declare toe as key link point along leg.
}legStruct;
legStruct leg[numDrivers][numLegs];
int8_t legDirIndex = 0; // What the legs are currently doing.
int8_t const legDirCnt = 10; // Number of things legs know how to do.
#define HOME_POSITION 0 // Stance 0 = home position. 
#define STAND_POSITION 1 // Stance 1 = stand position.
#define CROUCH_POSITION 2 // Stance 2 = crouch position.
#define LEAN_LEFT 3 // Stance 3 = lean left position.
#define LEAN_RIGHT 4 // Stance 4 = lean right position.
#define LEAN_FORWARD 5 // Stance 5 = lean forward position.
#define LEAN_BACKWARD 6 // Stance 6 = lean backwrd position.
String legDirExpl[legDirCnt]; // Explanation of what each directive means.
// Define terminal related variables.
unsigned long serialBaudRate = 115200; // Serial terminal baud rate.
// Define local web server related variables.
bool isWebServer; // True is web server running.
const char* WEB_APP_TITLE = "Hexbot"; // App name for web page titles.
aaWebService localWebService(WEB_APP_TITLE); // Webserver hosted by microcontroller.

/************************************************************************************
 * @section funcDeclare Declare functions found in the include files.
 * @details In order to get rid of "error: 'xxx' was not declared in this scope"
 * compiler errors list a function from any of the include files here. 
 ************************************************************************************/
void rotateDisplay(int8_t); 
void displaySplashScreen(String);
// Config ralted functions
void showCfgDetails();
void displayCfgDetails(int8_t);
void checkBoot();
// MQTT related functions
bool connectToMqttBroker(aaNetwork &);
boolean isValidNumber(String);
uint32_t convertStrToUint32_t(String);
uint8_t convertStrToUint8_t(String);
int8_t convertStrToInt8_t(String);
bool checkNumArg(int8_t, String *);
bool processCmd(String);
IPAddress getMqttBrokerIP();
void checkMqtt();
// RGB LED related functions.
void createPredefinedColours();
void saveRgbColour();
void loadRgbColour();
void setCustRgbColour(uint32_t, uint32_t, uint32_t);
void setStdRgbColour(uint8_t);
void setupStatusLed();
// DAE Inverted kinematic related functions.
int32_t mapDegToPWM(float *, float *);
void anglesToCoords(float, float, float, float *, float *, float *);
void coordsToAngles(float, float, float, float *, float *, float *);  
// I2C related functions.
void identifyDevice(int);
void scanBus0();
void scanBus1();
// Define OLED related functions.
void IRAM_ATTR ButtonA_ISR();
void IRAM_ATTR ButtonB_ISR();
void IRAM_ATTR ButtonC_ISR();
void placeTextVHcentre(String, uint8_t, uint16_t);
void placeTextHcentre(String, uint8_t, uint16_t);
void rotateDisplay(int8_t);
void displaySplashScreen(String);
void displayStatusScreen();
void checkOledButtons();
void initOled();
// Define servoLegs related functions.
void startPositionLegs(int8_t, int8_t);
void initServos();
void initLegs();
bool moveLeg(int8_t, int8_t, float, float, float);
void setupMobility();  
// Define terminal related functions.
void setupSerial();
// Define local web server related functions.
void monitorWebServer();
void startWebServer();

/*******************************************************************************
 * @section codeModules Functions put into files according to function.
 * @details Order functions here in a way that ensures that variables get 
 * declared in one function prior to being referenced by another function. 
 *******************************************************************************/
#include <huzzah32_gpio_pins.h> // Map pins on Adafruit Huzzah32 dev board to friendly names.
#include <hexbot_gpio_pins.h> // Map Hexbot specific pin naming to generic development board pin names. 
#include <terminal.cpp> // Serial port management.
#include <configDetails.cpp> // Show the environment details of this application.
#include <web.cpp> // Manage locally hosted web service. 
#include <rgbLed.cpp> // Control status LEDs.
#include <network.cpp> // Control networking activities.
#include <mqttBroker.cpp> // Establish connect to the the MQTT broker.
#include <i2c.cpp> // Scan I2C buses to see what devices are present.
#include <ikLibrary.cpp> // InverseK.h inverted kinematic functions.
#include <servoLegs.cpp> // Control leg servos.
#include <oled.cpp> // Control OLED.
#include <daeIK.cpp> // Doug's inverted kinetics functions. 

/************************************************************************************
 * @section mainDeclare Declare functions in main.cpp.
 ************************************************************************************/
void setup(); // Arduino mandatory function #1. Runs once at boot. 
void loop(); // Arduino mandatory function #2. Runs continually.

#endif // End of precompiler protected code block