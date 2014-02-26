// Bengt R 2014
// geiger pulse input on pin2
// speaker output pulse on pin 11
// LCD shield for display


#include <Wire.h>
//#include <LiquidCrystal.h>
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(12, 11, 10, 9, 3);	// SW SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_SSD1306_128X64 u8g(10, 9);		// HW SPI Com: CS = 10, A0 = 9 (Hardware Pins are  SCK = 13 and MOSI = 11)
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);	// I2C / TWI 

//LiquidCrystal lcd( 8, 9, 4, 5, 6, 7 );

int led = 13;
long count = 0;
long count2 = 0;
long count3 = 0;
long time = 0;
int atime = 0;
int atime5 = 0;
int btime = 0;
long avgArray[61];
long avgArray5[6];
float sivert;
long total5;
long total60;
long avgArray60[61];
int battery;

// micro sign
byte newChar8[8] = {
  B00000,
  B00000,
  B00000,
  B10010,
  B10010,
  B10010,
  B11100,
  B10000
};


// the setup routine runs once when you press reset:
void setup() { 
  //lcd.createChar(8, newChar8); 
  //lcd.begin(16, 2);
  //lcd.print("startup");  
  Serial.begin(9600);
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  pinMode(5, OUTPUT);  
  //pinMode(4, OUTPUT); 
  pinMode(2, INPUT);
  digitalWrite(2, LOW); 
  //digitalWrite(4, HIGH); 
  attachInterrupt(0, countPulse, FALLING); // o är pin 2 
  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
}

// the loop routine runs over and over again forever:
void loop() {
  if (count>count2) {
    count2 = count;
    klick();
  }
  long test = millis();
  test;
  // picture loop
  
  
  if (time < test) { // test one second delay
  
    time = test+1000; // set one second delay
    long res = count - count3;
    avgArray[atime] = res;
    avgArray5[atime5] = res;
    atime++;
    if (atime>59) {
      atime=0;
      avgArray60[btime] = total60;
      btime++;
      if (btime>59) {
        btime=0;
      }
    }
    atime5++;
    if (atime5>4) {
      atime5=0;
    }
    int total = 0;
    for (int i=0;i<60;i++) {
      total = total+avgArray[i];
      
    }
    total60 = total;
    total5 = 0; // clear total5 before calculation
    for (int i=0;i<5;i++) { // estimated CPM from a 5s time frame
      total5 = total5+avgArray5[i];
      Serial.println(avgArray5[i]);
      
    }
    total5 = total5*(long)12;
    sivert = total * 0.0057;
    count3 = count;
    
    battery = analogRead(A0);
  Serial.print("count: ");
  Serial.print(count);
  Serial.print(" count/s: ");
  Serial.print(res);
  Serial.print(" count/m: ");
  Serial.println(total);
    //lcd.clear();
    //lcd.setCursor( 0, 0 );
    //lcd.print( total5 );
    //lcd.setCursor( 7, 0 );
    //lcd.print( count );
    
    //lcd.setCursor( 14, 0 );
    //lcd.print( atime );
    
    //lcd.setCursor( 0, 1 );
    //lcd.print( total );
    
    //lcd.setCursor( 7, 1 );
    //lcd.print( sivert );
    //lcd.setCursor( 11, 1 );
    //lcd.write(8); // µ
    //lcd.print( "Sv/h" );
    u8g.firstPage();  
    do {
      draw();
    } while( u8g.nextPage() );
  }
}
void klick() {
  digitalWrite(led, HIGH);
  digitalWrite(5, HIGH);  // turn the LED on (HIGH is the voltage level)
  delayMicroseconds(50);               
  digitalWrite(led, LOW);
  digitalWrite(5, LOW);  // turn the LED off by making the voltage LOW
  
}

void countPulse() {
  count++;
}
