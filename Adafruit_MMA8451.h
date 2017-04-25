/**************************************************************************/
/*!
    @file     Adafruit_MMA8451.h
    @author   K. Townsend (Adafruit Industries)
    @license  BSD (see license.txt)

    This is a library for the Adafruit MMA8451 Accel breakout board
    ----> https://www.adafruit.com/products/2019

    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!

    @section  HISTORY

    v1.0    - First release
    2017.04 - Add support for multiple I2C buses (Max Vilimpoc / unu GmbH)
*/
/**************************************************************************/

#ifndef _ADAFRUIT_MMA8451_H_
#define _ADAFRUIT_MMA8451_H_

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#if defined(CORE_TEENSY)
 // Teensy needs this to use multiple I2C buses.
 // When using with PlatformIO, make sure 'lib_ignore = Wire' is set in platformio.ini
 #include <i2c_t3.h>
 typedef i2c_t3 WireClass;
#else
 #include <Wire.h>
 typedef TwoWire WireClass;
#endif

#define USE_SENSOR    // Support the sensor library; comment out to compile/run without sensor library.
#ifdef USE_SENSOR
#include <Adafruit_Sensor.h>
#endif

/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
    #define MMA8451_DEFAULT_ADDRESS                 (0x1D)    // if A is GND, its 0x1C
/*=========================================================================*/

#define MMA8451_REG_OUT_X_MSB     0x01
#define MMA8451_REG_SYSMOD        0x0B
#define MMA8451_REG_WHOAMI        0x0D
#define MMA8451_REG_XYZ_DATA_CFG  0x0E
#define MMA8451_REG_PL_STATUS     0x10
#define MMA8451_REG_PL_CFG        0x11
#define MMA8451_REG_CTRL_REG1     0x2A
#define MMA8451_REG_CTRL_REG2     0x2B
#define MMA8451_REG_CTRL_REG4     0x2D
#define MMA8451_REG_CTRL_REG5     0x2E



#define MMA8451_PL_PUF            0
#define MMA8451_PL_PUB            1
#define MMA8451_PL_PDF            2
#define MMA8451_PL_PDB            3
#define MMA8451_PL_LRF            4
#define MMA8451_PL_LRB            5
#define MMA8451_PL_LLF            6
#define MMA8451_PL_LLB            7

typedef enum
{
  MMA8451_RANGE_8_G           = 0b10,   // +/- 8g
  MMA8451_RANGE_4_G           = 0b01,   // +/- 4g
  MMA8451_RANGE_2_G           = 0b00    // +/- 2g (default value)
} mma8451_range_t;


/* Used with register 0x2A (MMA8451_REG_CTRL_REG1) to set bandwidth */
typedef enum
{
  MMA8451_DATARATE_800_HZ     = 0b000, //  800Hz
  MMA8451_DATARATE_400_HZ     = 0b001, //  400Hz
  MMA8451_DATARATE_200_HZ     = 0b010, //  200Hz
  MMA8451_DATARATE_100_HZ     = 0b011, //  100Hz
  MMA8451_DATARATE_50_HZ      = 0b100, //   50Hz
  MMA8451_DATARATE_12_5_HZ    = 0b101, // 12.5Hz
  MMA8451_DATARATE_6_25HZ     = 0b110, // 6.25Hz
  MMA8451_DATARATE_1_56_HZ    = 0b111, // 1.56Hz

  MMA8451_DATARATE_MASK       = 0b111
} mma8451_dataRate_t;

class Adafruit_MMA8451
#ifdef USE_SENSOR
: public Adafruit_Sensor
#endif
{
 public:
  Adafruit_MMA8451(int32_t id = -1);

  // Allow using multiple I2C buses.
  Adafruit_MMA8451(WireClass & wire, uint8_t i2cAddress, int32_t id = -1);

  bool begin(uint8_t addr = MMA8451_DEFAULT_ADDRESS);

  bool setup();

  void read();

  void setRange(mma8451_range_t range);
  mma8451_range_t getRange(void);

  void setDataRate(mma8451_dataRate_t dataRate);
  mma8451_dataRate_t getDataRate(void);

#ifdef USE_SENSOR
  bool getEvent(sensors_event_t *event);
  void getSensor(sensor_t *sensor);
#endif

  uint8_t getOrientation(void);

  int16_t x, y, z;
  float x_g, y_g, z_g;

  void writeRegister8(uint8_t reg, uint8_t value);
 protected:
  uint8_t readRegister8(uint8_t reg);

  inline uint8_t i2cread(void);
  inline void i2cwrite(uint8_t x);

 private:
  WireClass & _wire;
  int32_t     _sensorID;
  int8_t      _i2caddr;
};

#endif
