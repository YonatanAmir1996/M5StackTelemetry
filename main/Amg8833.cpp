#include <M5CoreS3.h>
#include "Amg8833.h"


/** 
 * @brief Constructor for the Amg8833 class.
 * @details Initializes the Amg8833 object with a specific I2C address.
 */
Amg8833::Amg8833() :
PaHubDeviceAbs(AMG8833_I2C_ADDR)
{

}

/** 
 * @brief Destructor for the Amg8833 class.
 * @details Cleans up any allocated resources.
 */
Amg8833::~Amg8833()
{

}

/** 
 * @brief Begin the operation for the Amg8833 sensor.
 * @return true if the sensor started successfully, false otherwise.
 * @details This method tries to initialize the gridEye sensor several times and 
 *          returns the success of the operation.
 */
bool Amg8833::begin()
{
    uint8_t count = 0;

    switchPort();
    setFrequency(I2C_FREQ_100KHZ);
    while(count < NUMBER_OF_BEGIN_TRIES)
    {
      if(gridEye.begin())
      {
          break;
      }
      else
      {
          count++;
          delay(150);
      }
    }

    return (count < NUMBER_OF_BEGIN_TRIES);
}

/** 
 * @brief Update the pixel readings from the Amg8833 sensor.
 * @details Reads the pixel values from the gridEye sensor and stores them in the pixels array.
 */
void Amg8833::update()
{
    setFrequency(I2C_FREQ_100KHZ);
    switchPort();
    gridEye.readPixels(pixels);
}

/** 
 * @brief Print the pixel readings to the M5 LCD.
 * @details This method prints the pixel values in rows of 8 to the M5 LCD screen.
 */
void Amg8833::print()
{
    M5.Lcd.clear();
    M5.Lcd.setCursor(0,0);
    M5.Lcd.setTextFont(1);
    M5.Lcd.printf("GridEye:\n");
    for(uint8_t i = 0; i < AMG88xx_PIXEL_ARRAY_SIZE; i += 8)
    {
        // prints 8 pixels (one row)
        M5.Lcd.printf("[%3.1f, %3.1f, %3.1f, %3.1f, %3.1f, %3.1f, %3.1f, %3.1f]\n",
                       pixels[i],     pixels[i + 1], pixels[i + 2], pixels[i + 3],
                       pixels[i + 4], pixels[i + 5], pixels[i + 6], pixels[i + 7]);
    }
}

uint32_t Amg8833::writeIntoTxBuffer(uint32_t offset)
{
    uint32_t deviceName             = DEVICE_AMG8833_GRID_EYE;
    uint32_t deviceNumOfBytesToRead = sizeof(deviceName) + sizeof(pixels);

    update();

    memcpy(TxBuffer + offset, &deviceNumOfBytesToRead, sizeof(deviceNumOfBytesToRead));
    offset += sizeof(deviceNumOfBytesToRead);
    memcpy(TxBuffer + offset, &deviceName, sizeof(deviceName));
    offset += sizeof(deviceName);
    memcpy(TxBuffer + offset, &pixels, sizeof(pixels));

    return deviceNumOfBytesToRead + sizeof(deviceNumOfBytesToRead);
}