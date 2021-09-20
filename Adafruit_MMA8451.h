/*!
 * @file     Adafruit_MMA8451.h
 */

#ifndef _ADAFRUIT_MMA8451_H_
#define _ADAFRUIT_MMA8451_H_

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Adafruit_I2CDevice.h>

#define USE_SENSOR //!< Support the sensor library; comment out to compile/run
                   //!< without sensor library.
#ifdef USE_SENSOR
#include <Adafruit_Sensor.h>
#endif

/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
#define MMA8451_DEFAULT_ADDRESS                                                \
  (0x1D) //!< Default MMA8451 I2C address, if A is GND, its 0x1C
/*=========================================================================*/

#define MMA8451_REG_OUT_X_MSB 0x01 //!< Read-only device output register
#define MMA8451_REG_SYSMOD 0x0B    //!< SYSMOD system mode register
#define MMA8451_REG_WHOAMI 0x0D    //!< WHO_AM_I device ID register
#define MMA8451_REG_XYZ_DATA_CFG                                               \
  0x0E //!< XYZ_DATA_CFG register, sets dynamic range and high-pass filter for
       //!< output data
#define MMA8451_REG_PL_STATUS                                                  \
  0x10 //!< PL_STATUS portrait/landscape status register
#define MMA8451_REG_PL_CFG 0x11 //!< Portrait/landscape configuration register
#define MMA8451_REG_CTRL_REG1 0x2A //!< CTRL_REG1 system control 1 register
#define MMA8451_REG_CTRL_REG2 0x2B //!< CTRL_REG2 system control 2 register
#define MMA8451_REG_CTRL_REG4 0x2D //!< CTRL_REG4 system control 4 register
#define MMA8451_REG_CTRL_REG5 0x2E //!< CTRL_REG5 system control 5 register

///@{
//* Different portrait and landscape settings */
#define MMA8451_PL_PUF 0
#define MMA8451_PL_PUB 1
#define MMA8451_PL_PDF 2
#define MMA8451_PL_PDB 3
#define MMA8451_PL_LRF 4
#define MMA8451_PL_LRB 5
#define MMA8451_PL_LLF 6
#define MMA8451_PL_LLB 7
///@}

/*!
 * @brief Different range settings
 */
typedef enum {
  MMA8451_RANGE_8_G = 0b10, // +/- 8g
  MMA8451_RANGE_4_G = 0b01, // +/- 4g
  MMA8451_RANGE_2_G = 0b00  // +/- 2g (default value)
} mma8451_range_t;

/*! Used with register 0x2A (MMA8451_REG_CTRL_REG1) to set bandwidth */
typedef enum {
  MMA8451_DATARATE_800_HZ = 0b000,  //  800Hz
  MMA8451_DATARATE_400_HZ = 0b001,  //  400Hz
  MMA8451_DATARATE_200_HZ = 0b010,  //  200Hz
  MMA8451_DATARATE_100_HZ = 0b011,  //  100Hz
  MMA8451_DATARATE_50_HZ = 0b100,   //   50Hz
  MMA8451_DATARATE_12_5_HZ = 0b101, // 12.5Hz
  MMA8451_DATARATE_6_25HZ = 0b110,  // 6.25Hz
  MMA8451_DATARATE_1_56_HZ = 0b111, // 1.56Hz

  MMA8451_DATARATE_MASK = 0b111
} mma8451_dataRate_t;

class Adafruit_MMA8451
#ifdef USE_SENSOR
    : public Adafruit_Sensor
#endif
/*!
 * @brief Adafruit MMA8451 compount
 */
{
public:
  /*!
   * @brief Adafruit MMA8451 object
   * @param id MMA8451 ID
   */
  Adafruit_MMA8451(int32_t id = -1);

  /*!
   * @brief Connects with the MMA8451
   * @param addr Address of the MMA8451
   * @param theWire TwoWire bus to use
   * @return Returns a boolean
   */
  bool begin(uint8_t addr = MMA8451_DEFAULT_ADDRESS, TwoWire *theWire = &Wire);

  void read(); //!< @brief Reads data from the sensor

  void
  setRange(mma8451_range_t range); //!< @param range Desired range of sensor
  mma8451_range_t
  getRange(void); //!< @return Range of sensor, either 0b10, 0b01, or 0b00, 8G,
                  //!< 4G, and 2G respectively

  /*!
   * @param dataRate Data rate of the sensor
   */
  void setDataRate(mma8451_dataRate_t dataRate);
  mma8451_dataRate_t getDataRate(void); //!< @return Data rate, binary value

#ifdef USE_SENSOR
  /*!
   * @param *event Event
   * @return Returns a boolean
   */
  bool getEvent(sensors_event_t *event);
  /*!
   * @param *sensor Sensor
   */
  void getSensor(sensor_t *sensor);
#endif

  uint8_t getOrientation(void); //!< @return 3 axis tuple

  ///@{
  //* X, Y, and Z values */
  int16_t x, y, z;
  ///@}
  ///@{
  //* X, Y, and Z acceleration values */
  float x_g, y_g, z_g;
  ///@}

  /*!
   * @brief Writes to 8 bit register
   * @param reg Register to write to
   * @param value Value to write
   */
  void writeRegister8(uint8_t reg, uint8_t value);

protected:
  /*!
   * @brief Reads from 8 bit register
   * @param reg Register
   * @return Returns the contents of Register8
   */
  uint8_t readRegister8(uint8_t reg);

private:
  int32_t _sensorID;
  Adafruit_I2CDevice *i2c_dev = NULL; ///< Pointer to I2C bus interface
};

#endif
