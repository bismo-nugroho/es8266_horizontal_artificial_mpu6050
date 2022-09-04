// This example is based on this tutorial
// https://www.instructables.com/id/Converting-Images-to-Flash-Memory-Iconsimages-for-/
// https://github.com/STEMpedia/eviveProjects/blob/master/imageToFlashMemoryIconsForTFT/

//Don't forget to change User_Setup.h inside TFT_eSPI library !

#include <Wire.h>              // Wire library (required for I2C devices)
#include <Adafruit_BMP280.h>   // Adafruit BMP280 sensor library
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define BMP280_I2C_ADDRESS  0x76

#include <TFT_eSPI.h>
//#include "bitmap.h" //(Bitmap generated with LCD Image Converter) https://sourceforge.net/projects/lcd-image-converter/
TFT_eSPI tft = TFT_eSPI();   // Invoke library


Adafruit_BMP280  bmp280;

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(9600);
  tft.setRotation(1);
  Serial.print("ST7789 TFT Bitmap Test");


    /* Default settings from datasheet. */
  bmp280.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */



  Wire.begin(D2, D1);  // set I2C pins [SDA = D2, SCL = D1], default clock is 100kHz
  
  if ( bmp280.begin(BMP280_I2C_ADDRESS) == 0 ) {
    // connection error or device address wrong!
    //tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);   // set text color to white and black background
    tft.setTextSize(10);      // text size = 4
    tft.setCursor(3, 88);    // move cursor to position (3, 88) pixel
    tft.print("Connection");
    tft.setCursor(63, 126);  // move cursor to position (63, 126) pixel
    tft.print("Error");
    while (1); // stay here
  }


 if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }


  tft.begin();     // initialize a ST7789 chip
  tft.setSwapBytes(true); // Swap the byte order for pushImage() - corrects endianness

  tft.fillScreen(TFT_BLACK);
  //tft.pushImage(0,0,240,240,mercy);

  setupahi();
}


void loop() {
  // put your main code here, to run repeatedly:


  // read temperature and pressure from BMP280 sensor
  float temp     = bmp280.readTemperature();   // get temperature
  float pressure = bmp280.readPressure();      // get pressure
  float altitude = bmp280.readAltitude(1019.66);

  // print temperature (in °C)
  // tft.setTextColor(ST77XX_RED, ST77XX_BLACK);  // set text color to yellow and black background
 // tft.setCursor(4, 11);
 // if (temp < 0)   // if temperature < 0
 //   tft.printf( "-%02u.%02u", (int)abs(temp), (int)(abs(temp) * 100) % 100 );
 // else            // temperature >= 0
 //   tft.printf( " %02u.%02u", (int)temp, (int)(temp * 100) % 100 );

  // 2: print pressure (in hPa)
  //tft.setTextColor(ST77XX_CYAN, ST77XX_BLACK);  // set text color to cyan and black background
//  tft.setCursor(4, 31 );
 // tft.printf( "%s", String(altitude) );



sensors_event_t a, g, temps;
  mpu.getEvent(&a, &g, &temps);


//   tft.setCursor(4, 51 );
 // tft.printf("Acceleration X,Y,Z : %s , %s, %s  ",String(a.acceleration.x),String(a.acceleration.y*10),String(a.acceleration.z*10));

 //    tft.setCursor(4, 71 );
 // tft.printf("Gyro X,Y,Z : %s , %s, %s ",String(a.acceleration.x),String(a.acceleration.y * 10),String(a.acceleration.z * 10));
  

  //  tft.setCursor(4, 91 );
 // tft.printf("Temperature : %s C ",String(temps.temperature));
  

  //  tft.drawCentreString("%RH", 120, 70, 4); // // Comment out to avoid font 4
  setRoll( (int) ( a.acceleration.y * 10 )  );
  setPitch((int)  ( a.acceleration.z * -10 ) );

  loopahi();
tft.setTextFont(2);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK); // Text with background
    tft.setCursor(4, 210 );
  tft.printf("Temp : %s °C ",String(temps.temperature));

      tft.setCursor(125, 210 );
  tft.printf( "Alt : %s m", String(altitude) );
}
