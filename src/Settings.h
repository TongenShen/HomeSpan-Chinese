/*********************************************************************************
 *  MIT License
 *  
 *  Copyright (c) 2020-2021 Gregg E. Berman
 *  
 *  https://github.com/HomeSpan/HomeSpan
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *  
 ********************************************************************************/
 
// USER-DEFINED SETTINGS AND REFERENCE ENUMERATION CLASSES

#pragma once

//////////////////////////////////////////////////////
//              HomeSpan Version                    //

#define     HS_MAJOR  1
#define     HS_MINOR  2
#define     HS_PATCH  1

#define     STRINGIFY(x) _STR(x)
#define     _STR(x) #x

#define     HOMESPAN_VERSION    STRINGIFY(HS_MAJOR) "." STRINGIFY(HS_MINOR) "." STRINGIFY(HS_PATCH)

#define     VERSION(major,minor,patch) major*10000+minor*100+patch

#ifndef REQUIRED
  #define REQUIRED 0
#endif

#if (REQUIRED>VERSION(HS_MAJOR,HS_MINOR,HS_PATCH))
  #error THIS SKETCH REQUIRES A LATER VERISON OF THE HOMESPAN LIBRARY
#endif            

//////////////////////////////////////////////////////
//                DEFAULT SETTINGS                  //  

#define     DEFAULT_CATEGORY          Category::Lighting  // change with optional first argument in homeSpan.begin()
#define     DEFAULT_DISPLAY_NAME      "HomeSpan Server"   // change with optional second argument in homeSpan.begin()
#define     DEFAULT_HOST_NAME         "HomeSpan"          // change with optional third argument in homeSpan.begin()
#define     DEFAULT_MODEL_NAME        "HomeSpan-ESP32"    // change with optional fourth argument in homeSpan.begin()

#define     DEFAULT_SETUP_CODE        "46637726"          // changed during network setup or with 'S' command

#define     DEFAULT_QR_ID             "HSPN"              // change with homeSpan.setQRID(qrID);

#define     DEFAULT_CONTROL_PIN       21                  // change with homeSpan.setControlPin(pin)
#define     DEFAULT_STATUS_PIN        13                  // change with homeSpan.setStatusPin(pin)

#define     DEFAULT_AP_SSID           "HomeSpan-Setup"   // change with homeSpan.setApSSID(ssid)
#define     DEFAULT_AP_PASSWORD       "homespan"         // change with homeSpan.setApPassword(pwd)
#define     DEFAULT_OTA_PASSWORD      "homespan-ota"     // change with 'O' command

#define     DEFAULT_AP_TIMEOUT        300                 // change with homeSpan.setApTimeout(nSeconds)
#define     DEFAULT_COMMAND_TIMEOUT   120                 // change with homeSpan.setCommandTimeout(nSeconds)

#define     DEFAULT_LOG_LEVEL         0                   // change with homeSpan.setLogLevel(level)

#define     DEFAULT_MAX_CONNECTIONS   8                   // change with homeSpan.setMaxConnections(num);
#define     DEFAULT_TCP_PORT          80                  // change with homeSpan.setPort(port);


/////////////////////////////////////////////////////
//              STATUS LED SETTINGS                //

#define     LED_WIFI_NEEDED       300,0.5,1,2700      // slow single-blink
#define     LED_PAIRING_NEEDED    300,0.5,2,2400      // slow double-blink
#define     LED_ALERT             100                 // rapid flashing
#define     LED_WIFI_CONNECTING   2000                // slow flashing
#define     LED_AP_STARTED        100,0.5,2,300       // rapid double-blink
#define     LED_AP_CONNECTED      300,0.5,2,400       // medium double-blink     
#define     LED_OTA_STARTED       300,0.5,3,400       // medium triple-blink

/////////////////////////////////////////////////////
//      Message Log Level Control Macros           //
//       0=Minimal, 1=Informative, 2=All           //

#define LOG1(x) if(homeSpan.logLevel>0)Serial.print(x)
#define LOG2(x) if(homeSpan.logLevel>1)Serial.print(x)
   

//////////////////////////////////////////////////////
//   Types of Accessory Categories                  //
//   Reference: HAP Section 13                      //

enum class Category {
  Other=1,
  Bridges=2,
  Fans=3,
  GarageDoorOpeners=4,
  Lighting=5,
  Locks=6,
  Outlets=7,
  Switches=8,
  Thermostats=9,
  Sensors=10,
  SecuritySystems=11,
  Doors=12,
  Windows=13,
  WindowCoverings=14,
  ProgrammableSwitches=15,
  IPCameras=17,
  VideoDoorbells=18,
  AirPurifiers=19,
  Heaters=20,
  AirConditioners=21,
  Humidifiers=22,
  Dehumidifiers=23,
  Sprinklers=28,
  Faucets=29,
  ShowerSystems=30
};
