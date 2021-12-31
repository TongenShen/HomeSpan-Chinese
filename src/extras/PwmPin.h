
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                ----- PWM Pin Control -----
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Wrappers around the ESP-IDF ledc library to control PWM-based devices:
//
// LedPin(pin) - controls a Dimmable LED on specified pin with frequency=5000 Hz
//             - use set(level) to set brightness from 0-100%
//
// ServoPin(pin) - controls a Servo Motor on specified pin with frequency=50 Hz
//               - use set(degrees) to set position to degrees
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <Arduino.h>
#include <driver/ledc.h>

#define DEFAULT_PWM_FREQ     5000

/////////////////////////////////////

class LedC {

  protected:
    static ledc_channel_config_t *channelList[LEDC_CHANNEL_MAX][LEDC_SPEED_MODE_MAX];
    static ledc_timer_config_t *timerList[LEDC_TIMER_MAX][LEDC_SPEED_MODE_MAX];
    
    ledc_channel_config_t *channel=NULL;
    ledc_timer_config_t *timer;
    
    LedC(uint8_t pin, uint16_t freq);

  public:
    int getPin(){return(channel?channel->gpio_num:-1);}               // returns the pin number

    operator bool(){         // override boolean operator to return true/false if creation succeeded/failed
      return(channel);    
    }    
    
};
  
/////////////////////////////////////

class LedPin : public LedC {

  public:
    LedPin(uint8_t pin, float level=0, uint16_t freq=DEFAULT_PWM_FREQ);   // assigns pin to be output of one of 16 PWM channels initial level and frequency
    void set(float level);                                                  // sets the PWM duty to level (0-100)
    
    static void HSVtoRGB(float h, float s, float v, float *r, float *g, float *b );       // converts Hue/Saturation/Brightness to R/G/B
};

/////////////////////////////////////

class ServoPin : public LedC {
  uint16_t minMicros;
  uint16_t maxMicros;
  double minDegrees;
  double microsPerDegree;

  public:
    ServoPin(uint8_t pin, double initDegrees, uint16_t minMicros, uint16_t maxMicros, double minDegrees, double maxDegrees);
    ServoPin(uint8_t pin, double initDegrees=0) : ServoPin(pin,initDegrees,1000,2000,-90,90) {};
    
    void set(double degrees);                               // sets the Servo to degrees, where degrees is bounded by [minDegrees,maxDegrees]  
};
