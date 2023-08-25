# **Science Projects Terminal Smart Glove Beta**
#### _Document Version:Original-Alpha 1.0  Editing date:2023/08/25_  
_(CATION:This document didn't be verified,just for referring,if you are necessary to refer this document seriously,waiting for next Verified Version if exists please!)_
***

># **NEW:**
> In the Alpha version,the glove can read gyro and acceleration data via MPU6050 from DMP directly and can communicate with the other ESP chip then send it those data in need.  
Although,there are some questions in Alpha program.For example,the data read from DMP directly almost is a big number and also changes frequently.  
Obviously,it isn't accurate and convenient.It's necessary to adjust the program to make the result more accurate.
> *  To be franking,there are a number of varied data processing method such as ***Kalman Filter***,***First-order Complementarity***,they are always be used in drone flight control program,although they could be so difficult or effective,they owns a same goal is make the result sensor read more accurate.**But anyway,we are designing a glove rather than a mini drone,make the result too accurate is meaningless,we never intend make the glove fly.** 
># ***Zero Bias Calibration*** 
>1. So we designed a simple process to calculate those numbers and make they more accurate,we named it as ***Zero Bias Calibration***.  
Firstly,we make the MPU6050 collect all the sensor result for much times(It could be 30 times,50 times even 100 times) and add them up, to be divided by the sense times then we get the essential value: **Zero Bias Point**, saving it in flash by program.  
This process we call it **Zero Bias Generating**,we will make LED on chip blink frequently to indicate that Zero Bias Point is generating now.  
In fact,during this process, it is necessary to keep MPU6050 stable as far as possible so that get a value accurate enough.In other words,you need to make glove on your hand stable enough and keep this pose for a moment until LED on chip no longer blink frequently.      
>2. After this,chip got into formal working process.  
Main program will use Zero Bias Point in calculation for next result processing,next sensor result need to subtract zero bias point first then get the comparatively more accurate result in the end.

***

> # **CODE:**
```C++
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include <ESP8266WiFi.h>
#include <espnow.h>

//Receiver's MAC address.(Slaves',this could be multiple for situation that there are many device need to contact.)
uint8_t broadcastAddress[] = {0x48,0x55,0x19,0x7A,0x9F,0xE8};

//Data sending's structure body.
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  String d;
  bool e;
  int16_t f;
} struct_message;

//Create a new type variable
struct_message myData;

//This is a callback function,it will works while message sending.
//In this situation,whether the message sending successfully or not,this will print out in serial.
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;
//#define LED_PIN 13
//bool blinkState = false;

void setup() {
    Wire.begin();
    Serial.begin(115200);
    pinMode(LED_BUILTIN,OUTPUT);
    Serial.println("Initializing I2C devices...");
    mpu.initialize();
    Serial.println("Testing device connections...");
    Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

     //Set device as Wi-Fi station.
  WiFi.mode(WIFI_STA);

  //Starting initializing ESP.
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  //Set ESP8266's role  ESP_NOW_ROLE_CONTROLLER， ESP_NOW_ROLE_SLAVE， 
  //ESP_NOW_ROLE_COMBO， ESP_NOW_ROLE_MAX。
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);

  esp_now_register_send_cb(OnDataSent);
  
  //Being paired with the other ESP-NOW device to send data out.
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

}
//Create the Zero Bias Generating times variable.
int times = 0;
void loop() {
     
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);
    
    //Create all the variables we need.
    int16_t Zax = 0;
    int16_t Zay = 0;
    int16_t Zaz = 0;
    int16_t Zgx = 0;
    int16_t Zgy = 0; 
    int16_t Zgz = 0;
    int16_t Ax = 0;
    int16_t Ay = 0;
    int16_t Az = 0;
    int16_t Gx = 0;
    int16_t Gy = 0; 
    int16_t Gz = 0;

    //Starting calculating the Zero Bias Points,this process will takes about 5s,keep stable during this as far as possible.
    while (times<=50){
    Zax = Zax + ax;
    Zay = Zay + ay;
    Zaz = Zaz + az;
    Zgx = Zgx + gx;
    Zgy = Zgy + gy;
    Zgz = Zgz + gz;
    times = times + 1;
    digitalWrite(LED_BUILTIN, HIGH); 
    delay(100);
    digitalWrite(LED_BUILTIN, LOW); 
    }
    //Those are all the data's Zero Bias Points value.
    Zax = Zax/50;
    Zay = Zay/50;
    Zaz = Zaz/50;
    Zgx = Zgx/50;
    Zgy = Zgy/50;
    Zgz = Zgz/50;

    //Calculate original data with Zero Bias Points up.
    Ax = ax-Zax;
    Ay = ay-Zay;
    Az = az-Zaz;
    Gx = gx-Zgx;
    Gy = gy-Zgy;
    Gz = gz-Zgz;

    Serial.print("a/g:\t");
    Serial.print(Ax); Serial.print("\t");
    Serial.print(Ay); Serial.print("\t");
    Serial.print(Az); Serial.print("\t");
    Serial.print(Gx); Serial.print("\t");
    Serial.print(Gy); Serial.print("\t");
    Serial.println(Gz);
    delay(5000); 

     //Set the value will send.
  strcpy(myData.a, "THIS IS A CHAR");
  myData.b = random(1,20); //Random
  myData.c = 1.2;
  myData.d = "Hello";
  myData.e = false;
  myData.f = Gx;

  //Send message out.
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  //Delay for 2s.
  delay(100);
}
```
***
> # END
> * After we get the sensor more accurate,we can refer different axles' value to judge glove or rather our hand's action or pov.

##### Completed time:2023/08/25-16:52 Version Alpha 1.0