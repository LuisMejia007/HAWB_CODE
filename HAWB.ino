#include <Wire.h>
#include <SD.h>
#include "Adafruit_Sensor.h"
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>

#define UVPIN 10

/* Assign a unique ID to the sensors */
Adafruit_10DOF                dof   = Adafruit_10DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified       bmp   = Adafruit_BMP085_Unified(18001);

/* Update this with the correct SLP for accurate altitude measurements */
float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
File myFile;

void initSensors()
{
  if(!accel.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
    while(1);
  }
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
  if(!bmp.begin())
  {
    /* There was a problem detecting the BMP180 ... check your connections */
    Serial.println("Ooops, no BMP180 detected ... Check your wiring!");
    while(1);
  }
}

void setup(void)
{
  Serial.begin(115200);
//  Serial.begin(9600);

  pinMode(UVPIN, INPUT); 
  //avoid crash
  if(!SD.begin(UVPIN)){
    Serial.println("SD initialization failed!");
    return;
  }
   
   myFile = SD.open("HAWB_Data.csv", FILE_WRITE);

   if(myFile)
      myFile.println(" \"UVindex\",\"Roll\",\"Pitch\",\"Heading\", \"Altitude(m)\", \"Temp(c)\"\n ");

     myFile.close();
  /* Initialise the sensors */
  
    initSensors();
  
}

void loop(void){
  
  sensors_event_t accel_event;
  sensors_event_t mag_event;
  sensors_event_t bmp_event;
  sensors_vec_t   orientation;

  String csv;

  int UVreading_input = analogRead(UVPIN);
  int UVindex = (UVreading_input * (5.0 / 102.4));

  csv = UVindex + ",";

  myFile = SD.open("UVindex.csv", FILE_WRITE);

  /* Calculate pitch and roll from the raw accelerometer data */
    accel.getEvent(&accel_event);
    if (dof.accelGetOrientation(&accel_event, &orientation))
    {
      /* 'orientation' should have valid .roll and .pitch fields */
      csv += orientation.roll;
      csv += ",";
      csv += orientation.pitch;
      csv +=",";
    }
    
    /* Calculate the heading using the magnetometer */
    mag.getEvent(&mag_event);
    if (dof.magGetOrientation(SENSOR_AXIS_Z, &mag_event, &orientation))
    {
      /* 'orientation' should have valid .heading data now */
      csv += orientation.heading;
      csv += ",";
    }
  
    /* Calculate the altitude using the barometric pressure sensor */
    bmp.getEvent(&bmp_event);
    if (bmp_event.pressure)
    {
      /* Get ambient temperature in C */
      float temperature;
      bmp.getTemperature(&temperature);
      
      /* Convert atmospheric pressure, SLP and temp to altitude    */
      csv += bmp.pressureToAltitude(seaLevelPressure,bmp_event.pressure,temperature);
      csv += ",";
      
      /* Display the temperature */
      csv += temperature;
      
     }
     
  if(myFile){

     myFile.println(csv);
     myFile.println("\n");
    
    }
  else{
    Serial.println("ERROR could not open file");
  }

  myFile.close();
  delay(1000);
}

