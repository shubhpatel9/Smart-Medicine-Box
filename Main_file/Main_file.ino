/* Development Board: Arduino MEGA2560 
* Project Name:   <Smart Medicine Box>
* Filename:       <Main_file.ino>
* Functions:       All functions are void type function:
*                 <displayTime, firstBoot, alarmCheck, DozeNo, medTime, playFirst, execute_CMD,
*                  setVolume, sendSMS, medTime, ir_sensor, timerIsr, encoderButton, readRotaryEncoder>
* 
* 
* Connection of the parts with the Arduino MEGA 2560
* lcd-i2c -> vcc,gnd,sda,scl
* rotary encoder ->clk,dt,sw,+,gnd == A0,A1,A2,vcc,gnd
* ir sensor ->vcc,gnd, out = pin3
* servo motor = pin 8&9
* sd card ->vcc,gnd,miso,mosi,sck,cs == vcc,gnd,50,51,52,53
* timer -> vcc,gnd,sca,sdl
* MP3 player -> Vcc(1)=VCC,GND(7)=GND,RX(2)=1K=18,TX(3)=19,SP1(6)= + ,SP2(8) = -
* GSM MODULE - rx = 15, tx = 14, gnd 
*/



//////////////////////////////////////////////////////////////////////////////////////////////////////
// Libraries used for the Project
#include <SoftwareSerial.h>     // for serial communication with the MP3 and GSM Module
#include <Arduino.h>
#include <DS3231.h>             // for DS3231 timer
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>  // 16x2 LCD_I2C
#include <EEPROM.h>             // for reading and writing to the Arduino EEPROM
#include <Wire.h>               // allows to communicate with the I2C
#include <ClickEncoder.h>       // for Rotary Encoder
#include <TimerOne.h>
#include <SPI.h>                // For SD card module    
#include <SD.h> 
#include <Servo.h>              // For Servo Motors
//////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Defining Variable for different components
 */

/////////////////////////////////////// 
//for rotary encoder pin connection

#define clk A0
#define dt A1
#define sw A2

ClickEncoder *encoder;    //object of rotary encoder
int16_t last, value;      

//booleans for reading the rotation and clicks from the rotary encoder
boolean up = false;
boolean down = false;
boolean middle = false;
boolean displaySwitch = false;

///////////////////////////////////////

///////////////////////////////////////
//for sd card

#define ChipSelect 53     
File file;              //sd card file object
//variables to write data to the sd card
int sd_x = 100;           //storing the set hour in the EEPROM address 100
int sd_y = 101;           //storing the set min in the EEPROM address 101
int dataHourTaken = 0; 
int dataMinuteTaken = 0;

///////////////////////////////////////


///////////////////////////////////////
//for timer

DS3231  rtc(SDA, SCL);    // Init the DS3231 using the hardware interface
Time  t;                  // Init a Time-data structure

///////////////////////////////////////
//for the LCD display (address, row, column)

LiquidCrystal_I2C lcd(0x27, 16, 2); 

//////////////////////////////////////////////////
//MP3 serial port connections and variables

SoftwareSerial mySerial(18, 19);
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00

//////////////////////////////////////////////////


//////////////////////////////////////////////////
// Configure software serial port of the GSM module

SoftwareSerial SIM900(14, 15);   //tx3,rx3

//////////////////////////////////////////////////


/////////////////////////////////////////////////
// create servo object to control a servo

Servo myservo1, myservo2;  
int pos = 0;              //variable to set the position of the servo motors

/////////////////////////////////////////////////


/////////////////////////////////////////////////
//variables used to hold EEPROM addresses, starting value is 1&2

int hourAddr = 1;
int minAddr  = 2;

/////////////////////////////////////////////////

int setHour;  // variable to set the hour by the Rotary encoder
int setMin;   // variable to set the minute by the Rotary encoder
int total=0;  // A global variable to check the total number of doses

//////////////////////////////////////////////////////////////////
  
  //defining all the functions in the main file
  
  void medTime(int j);
  void encoderButton();
  void readRotaryEncoder();
  int  alarmCheck();
  void displayTime();
  void firstBoot();
  void DozeNo();
  int  ir_sensor();
  void sendSMS();
  void execute_CMD(byte CMD, byte Par1, byte Par2);
  void setVolume(int volume);
  void playFirst();
  void timerIsr()
  {
    encoder->service();
  }
  
//////////////////////////////////////////////////////////////////

  void setup() {

    //// Initialization for Serial port connections (MP3 and GSM)
         mySerial.begin (9600);
         delay(2000);
         SIM900.begin (19200); 
         delay(2000); 
         Serial.begin(9600);
         
    //// initializing sd card
         pinMode(ChipSelect, OUTPUT);  
         digitalWrite(ChipSelect, HIGH);
         delay(1000);
         if (!SD.begin(ChipSelect)) {
            Serial.println("SD card initialization failed!");
            while (1);
         }
         Serial.println("SD card initialization is done.");

    //// initializing LCD display 
         lcd.begin();
         lcd.backlight();
         lcd.clear();

    //// initializing Timer, to set the time we can uncomment the lines and upload the code one time.   
         rtc.begin();
         //  rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
         //  rtc.setTime(10, 18, 00);     // Set the time to 12:00:00 (24hr format)
         //  rtc.setDate(17, 03, 2021);   // Set the date to January 1st, 2014
          
     //// initializations rotary encoder 
          encoder = new ClickEncoder(dt, clk, sw); 
          encoder->setAccelerationEnabled(false);
          last = encoder->getValue();
        
          Timer1.initialize(1000);
          Timer1.attachInterrupt(timerIsr); 
  
     //// initializations IR Sensor
          pinMode(3,INPUT); //IR sensor
    
     //// initializations Servo motors  
          myservo1.attach(9);  // attaches the servo on pin 8&9 to the servo object
          myservo2.attach(8);
        
          myservo1.write(0); //initialization of posiotions
          myservo2.write(0); 
  
    
    displayTime();    // this function displays the current time and date
    delay (6000);
    firstBoot();      
  }
  
  void loop() {   

    int val = 0;
    int i = alarmCheck(); 
    if(digitalRead (3) == LOW){
          val = ir_sensor();
          Serial.println ("IR sensor detects obstacle! Medicine is ready to drop.");
    }
          if (val == 1){
           file = SD.open ("file.txt", FILE_WRITE);
            if (file) 
            {
                String dataString = "Doze" + String (i) + " is taken at: " + String(rtc.getTimeStr()) + "->" + String(rtc.getDateStr()) + "." ;
                file.print(dataString);
                file.close();
                Serial.println (dataString);
            }
            else 
            {
                Serial.print ("could not open file (writing)");
            } 
         }
    
          else{
              Serial.println(rtc.getTimeStr());
          }
    
  delay(1000);
  }
