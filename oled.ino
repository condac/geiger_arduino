void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  //u8g.drawBox(100,12,28,30);
  
  
  //u8g.drawStr( 0, 62, "Banan!");
  
  drawBattery(5);
  drawText();
  drawHistory();
  u8g.setColorIndex(1);
}

void drawText() {
  int th = 11; // text height 10+1
  //lcd.clear();
    //lcd.setCursor( 0, 0 );
    //lcd.print( total5 );
  u8g.setPrintPos(0, th); 
  u8g.print(total5);
    //lcd.setCursor( 7, 0 );
    //lcd.print( count );
  u8g.print("  ");
  u8g.print(count);
    
    //lcd.setCursor( 14, 0 );
    //lcd.print( atime );
  u8g.setPrintPos(112, th+7); 
  u8g.print(atime);
  
    //lcd.setCursor( 0, 1 );
    //lcd.print( total );
  u8g.setPrintPos(0, th*2);
  u8g.print(total60);
  
  u8g.print("  ");
  u8g.setPrintPos(0, th*3);
  u8g.print(sivert);
  u8g.print("uSv/h ");
  float bat = battery * 0.005;
  u8g.print(bat);
    //lcd.setCursor( 7, 1 );
    //lcd.print( sivert );
    //lcd.setCursor( 11, 1 );
    //lcd.write(8); // µ
    //lcd.print( "Sv/h" );
}

void drawBattery(int value) {
  
  int x = 118;
  int y = 0;
  int level = (battery - 655) / 38; // 778 is 3.55v, 3v is around 657 max of 4.2 is 920
                       // Max integer for battery is 7
              
  if (level < 0) {
    // Battery to low
    level = 0;
  }    
  u8g.drawBox(x+1,y+0,9,1);
  u8g.drawBox(x+8-level,y+2,level,2); // level meter
  u8g.drawBox(x+1,y+5,9,1);
  u8g.drawBox(x+9,y+0,1,5);
  u8g.drawBox(x+0,y+1,1,4);
  u8g.drawPixel(x+1,y+1);
  u8g.drawPixel(x+1,y+4);
}

void drawHistory() {
  
  for (int i=0;i<60;i++) {
    int temp = avgArray[i];
    if (temp>20) {
      temp=20;
    }
    u8g.drawVLine(i,63-temp,temp);
  }
  
    for (int i=0;i<60;i++) {
    int temp = (avgArray60[i] -43) / 2;
    if (temp>40) {
      temp=40;
    }
    if (temp < 0) {
      temp = 0;
    }
    
    u8g.drawVLine(68+i,63-temp,temp);
  }
}
