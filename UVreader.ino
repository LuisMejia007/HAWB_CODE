#include <SD.h>
#include <Time.h>

#define UVPIN 10

File myFile;

void setup() {

  /*
   * 
   * 
   * 
   * 
   */
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(UVPIN, INPUT); 
  //avoid crash
  if(!SD.begin(UVPIN)){
    Serial.println("SD initialization failed!");
    return;
  }
  /*
   * 
   * 
   * 
   */ 
   myFile = SD.open("UVindex.csv", FILE_WRITE);

   if(myFile)
      myFile.write(" \"UVindex\" \n ");
}


void loop() {
  // put your main code here, to run repeatedly:

  int UVreading_input = analogRead(UVPIN);
  int UVindex = (UVreading_input * (5.0 / 102.4));

  myFile = SD.open("UVindex.csv", FILE_WRITE);
  if(myFile){
    
    myFile.write(UVindex);
    myFile.write("\n");
    
  }
  else{
    Serial.println("ERROR could not open file");
  }

  myFile.close();
  
  //delay(1000); //1000 miliseconds = 1 second
  
}
