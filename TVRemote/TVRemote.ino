/////////////////////////////////////////////////////////////////////////////
// MyOTAThing.ino
// COM3505 lab assessment: IRRemote Assignment;
// Idris Nigena & Luke Worgan
/////////////////////////////////////////////////////////////////////////////

#include "unphone.h"
#include <IRremote.h>
#define VAR_DECLS
#include "vars.h"
#include <string.h>

IRsend irsend;

// List buttons for each menu screen
char topMenulabels[5][11] = {"SamsungTV", "Sony TV", "CD Player", "DVDPlayer"};
char tvMenuLabels[7][6] = {"Power", "Up", "Mute", "Down", "Up", "Down", "Back"};
char cdMenuLabels[10][8] = {"Power", "Up", "Down", "Play", "Pause", "Stop", 
  "Shuffle","Prev", "Next", "Back"};
char dvdMenuLabels[13][7] = {"Power", "Play", "Up", "Pause", "Left", "Select", 
  "Right", "Stop", "Down", "Eject", "FF", "Rew", "Back"};

unsigned long tvIRCodes1[6] = {SamTV_power, SamTV_v_up, SamTV_mute, SamTV_v_down, 
  SamTV_c_up, SamTV_c_down};
unsigned long tvIRCodes2[6] = {SonyTV_power, SonyTV_v_up, SonyTV_mute, SonyTV_v_down, 
  SonyTV_c_up, SonyTV_c_down};
unsigned long cdIRCodes[9] = {SonyCD_power, SonyCD_v_up, SonyCD_v_down, SonyCD_play, 
  SonyCD_pause, SonyCD_stop, SonyCD_shuffle, SonyCD_next, SonyCD_prev};
unsigned long dvdIRCodes[12] = {DVD_power, DVD_play, DVD_up, DVD_pause, DVD_left,
  DVD_select, DVD_right, DVD_stop, DVD_down,0, DVD_ff, DVD_rew};
//unsigned long* ircodes[4] = {tvIRCodes1, tvIRCodes2,cdIRCodes,dvdIRCodes};

Adafruit_GFX_Button topMenuButtons[5];
Adafruit_GFX_Button tvMenuButtons[7];
Adafruit_GFX_Button cdMenuButtons[10];
Adafruit_GFX_Button dvdMenuButtons[13];

// Variables for Power and Button sizes
const int backButtonHeight = 40;
const int backButtonWidth = 260;
const int powerButtonHeight = 55;
const int powerButtonWidth = 260;
    
class Menu {
public:

  // Create main menu to select a device
  void init(Adafruit_HX8357& tft) {
    tft.fillScreen(HX8357_BLACK);
    tft.setCursor(0, 0);
    for (uint8_t x=0; x<4; x++) {
        topMenuButtons[x].initButton(&tft, 160, 60+(x*110),300,90,HX8357_WHITE,
          HX8357_BLACK,HX8357_WHITE,topMenulabels[x], 3); 
        topMenuButtons[x].drawButton();
    }
  }
  
  void tvMenu(Adafruit_HX8357& tft, char title[]) {
    tft.fillScreen(HX8357_BLACK);
    tft.setTextSize(3);
    tft.setCursor(80, 30);
    tft.setTextColor(HX8357_YELLOW);

    // Print text for the selected device
    tft.print(title);
    tft.setCursor(30, 155);
    tft.print("Volume");
    tft.setCursor(170, 155);
    tft.print("Channel");
    
    // Initalise power button
    tvMenuButtons[0].initButton(&tft, 160,100,powerButtonWidth,powerButtonHeight,
      HX8357_WHITE,HX8357_RED,HX8357_WHITE,tvMenuLabels[0], 4);
        
    // For loop to generate Volume Buttons
    int boxHeight = 60;
    int boxWidth = 90;
    int boxSpacing = boxHeight+10;
    for (uint8_t x=1; x<4; x++) {
      tvMenuButtons[x].initButton(&tft, 85,155+(boxSpacing*x),boxWidth,boxHeight,
        HX8357_BLUE,HX8357_BLACK,HX8357_CYAN,tvMenuLabels[x], 3);
    }
    
    // Channel Buttons
    tvMenuButtons[4].initButton(&tft, 225,245,boxWidth,boxHeight+10,HX8357_BLUE,
      HX8357_BLACK,HX8357_CYAN,tvMenuLabels[4], 3);
    tvMenuButtons[5].initButton(&tft, 225,335,boxWidth,boxHeight+10,HX8357_BLUE,
      HX8357_BLACK,HX8357_CYAN,tvMenuLabels[5], 3);
    // Back Button
    tvMenuButtons[6].initButton(&tft, 160,455,backButtonWidth,backButtonHeight,
      HX8357_WHITE,HX8357_WHITE,HX8357_BLACK,tvMenuLabels[6], 2); 
        
    // Draw all buttons      
    for (uint8_t x=0; x<7; x++) {
        tvMenuButtons[x].drawButton();
    }
  }
  
  void cdPlayerMenu(Adafruit_HX8357& tft, char title[]) {
    tft.fillScreen(HX8357_BLACK);
    tft.setTextSize(3);
    tft.setCursor(80, 30);
    tft.setTextColor(HX8357_YELLOW);
    
    // Print text for the selected device
    tft.print(title);
    tft.setCursor(10, 150);
    tft.print("Volume");
    tft.setCursor(150, 150);
    tft.print("Controls");

    // Initalise power button
    cdMenuButtons[0].initButton(&tft, 160,100,powerButtonWidth,powerButtonHeight,
      HX8357_WHITE,HX8357_RED,HX8357_WHITE,cdMenuLabels[0], 4);

    int boxHeight = 65;
    int boxWidth = 85;
    int boxSpacing = 75;
    
    // Initalise Volume Buttons
    cdMenuButtons[1].initButton(&tft, 65,240,boxWidth,boxHeight,HX8357_BLUE,
      HX8357_BLACK,HX8357_CYAN,cdMenuLabels[1], 3);
    cdMenuButtons[2].initButton(&tft, 65,330,boxWidth,boxHeight,HX8357_BLUE,
      HX8357_BLACK,HX8357_CYAN,cdMenuLabels[2], 3);

    // For loop to generate Channel Buttons
    for (uint8_t x=1; x<4; x++){
      cdMenuButtons[(x*2)+1].initButton(&tft, 170,140+(x*boxSpacing),boxWidth,
        boxHeight,HX8357_BLUE,HX8357_BLACK,HX8357_CYAN,cdMenuLabels[(x*2)+1], 2);
      cdMenuButtons[(x*2)+2].initButton(&tft, 270,140+(x*boxSpacing),boxWidth,
        boxHeight,HX8357_BLUE,HX8357_BLACK,HX8357_CYAN,cdMenuLabels[(x*2)+2], 2);
    }

    // Back Button
    cdMenuButtons[9].initButton(&tft, 160,455,backButtonWidth,backButtonHeight,
      HX8357_WHITE,HX8357_WHITE,HX8357_BLACK,cdMenuLabels[9], 2);

    // Draw all buttons      
    for (uint8_t x=0; x<10; x++) {
        cdMenuButtons[x].drawButton();
    }
  }
  
  void dvdPlayerMenu(Adafruit_HX8357& tft, char title[]) {
    tft.fillScreen(HX8357_BLACK);
    tft.setTextSize(3);
    tft.setCursor(80, 30);
    tft.setTextColor(HX8357_YELLOW);
    // Print text for the selected device
    tft.print(title);
    
    // Initalise power button
    dvdMenuButtons[0].initButton(&tft, 160,100,powerButtonWidth,powerButtonHeight,
      HX8357_WHITE,HX8357_RED,HX8357_WHITE,dvdMenuLabels[0], 4);

    // For loop to generate dvd player buttons
    int boxHeight = 55;
    int boxWidth = 90;
    int xBoxSpacing = 100;
    int yBoxSpacing = 65;
    for(uint8_t col=0; col<3; col++){
      for(uint8_t row=0; row<3; row++){
        dvdMenuButtons[(row+1) +col*3].initButton(&tft, 60+(row*xBoxSpacing),
          170+(col*yBoxSpacing),boxWidth,boxHeight, HX8357_BLUE,
          HX8357_BLACK,HX8357_CYAN,dvdMenuLabels[(row+1) + col*3], 2);
      }
    }

    // Fastforward and rewind buttons
    dvdMenuButtons[10].initButton(&tft, 90,365,130,55,HX8357_BLUE,
      HX8357_BLACK,HX8357_CYAN,dvdMenuLabels[10], 2);
    dvdMenuButtons[11].initButton(&tft, 230,365,130,55,HX8357_BLUE,
      HX8357_BLACK,HX8357_CYAN,dvdMenuLabels[11], 2);

    // Back Button
    dvdMenuButtons[12].initButton(&tft, 160,455,backButtonWidth,backButtonHeight,
      HX8357_WHITE,HX8357_WHITE,HX8357_BLACK,dvdMenuLabels[12], 2);

    // Draw all buttons   
    for (uint8_t x=0; x<13; x++) {
        dvdMenuButtons[x].drawButton();
    }
  }
};
Menu m;

void setup() {
  Wire.setClock(100000); // higher rates trigger an IOExpander bug
  UNPHONE_DBG = true;
  Serial.begin(115200);  // init the serial line

  // fire up I²C, and the unPhone's IOExpander library
  Wire.begin();
  IOExpander::begin();

  checkPowerSwitch(); // check if power switch is now off & if so shutdown
  delay(1000);

  // which board version are we running?
  int version = IOExpander::getVersionNumber(), spin;
  if(version == 7) spin = 4;
  Serial.printf("starting, running on spin %d\n", spin);
  
  if(! ts.begin()) { // init the touchscreen
    D("failed to start touchscreen controller");
    TestScreen::fail("TOUCH");
    delay(3000);
  } else {
    D("touchscreen started");
  }

  IOExpander::digitalWrite(IOExpander::BACKLIGHT, LOW);
  tft.begin(HX8357D);
  // Initialise main menu
  m.init(tft);
  IOExpander::digitalWrite(IOExpander::BACKLIGHT, HIGH);
  
  i2s_config(); // configure the I2S bus

  //pinMode(IR_LEDS, OUTPUT); // IR_LED pin
}

uint8_t screenNum = 0; // used to manage the screens
void loop() {
  bool usbPowerOn = checkPowerSwitch(); // shutdown if switch off

  int IR_LEDstate = digitalRead(IR_LEDS);
  //Serial.println(IR_LEDstate);

  TS_Point p;
  
  // retrieve a point
  if (ts.bufferSize()) {
    p = ts.getPoint(); 
  } else {
    // this is our way of tracking touch 'release'!
    p.x = p.y = p.z = -1;
  }

  if (p.z != -1) {
  // scale from ~0->4000 to tft.width using the calibration #'s
    p.x = map(p.x, TS_MAXX, TS_MINX, tft.width(), 0);
    p.y = map(p.y, TS_MAXY, TS_MINY, 0, tft.height());
  }
  //DDD(p.x);
  //DDD(p.y);
  /*Serial.print("("); Serial.print(p.x); Serial.print(", "); 
  Serial.print(p.y); Serial.print(", "); 
  Serial.print(p.z); Serial.println(") ");*/
  
  int sizeOfArray;
  // go thru all the buttons, checking if they were pressed
  if(screenNum == 0){
    sizeOfArray = sizeof(topMenuButtons)/sizeof(topMenuButtons[0]);
    for (uint8_t b=0; b<sizeOfArray; b++) {
      if (topMenuButtons[b].contains(p.x, p.y)) {
        DD("Pressing Button")
        DDD(b);
        if (!topMenuButtons[b].isPressed()){
          topMenuButtons[b].press(true);
          screenNum = b+1;
          int arraySize;
          switch(b) {
            case 0:
            case 1:
              m.tvMenu(tft, topMenulabels[b]);
              break;
            case 2:
              m.cdPlayerMenu(tft, topMenulabels[b]);
              break;
            default:
              m.dvdPlayerMenu(tft, topMenulabels[b]);
              break;
          }
        }
        else {
          topMenuButtons[b].press(false);
        }
      }
    }
  }
  else if(screenNum == 1){
    sizeOfArray = sizeof(tvMenuButtons)/sizeof(tvMenuButtons[0]);
    for (uint8_t b=0; b<sizeOfArray; b++) {
      if (tvMenuButtons[b].contains(p.x, p.y)) {
        D("Pressing Sub Menu Button");
        // Logic to slect IR code
        DDD(b);
        if (!tvMenuButtons[b].isPressed()){
          tvMenuButtons[b].press(true);
          if(b==sizeOfArray-1){
            D("Pressing Back Button");
            screenNum = 0;
            m.init(tft);
          }
          else{
            for (int i = 0; i < 3; i++) {
              D("Sending IR Code - Samsung TV");
              DDD(tvIRCodes1[b]);
              irsend.sendSAMSUNG(tvIRCodes1[b], Samsung_bits);
              delay(40);
            }
          }
        }
        else {
          tvMenuButtons[b].press(false);
        }
      }
    }
  }
  else if(screenNum == 2){
    sizeOfArray = sizeof(tvMenuButtons)/sizeof(tvMenuButtons[0]);
    for (uint8_t b=0; b<sizeOfArray; b++) {
      if (tvMenuButtons[b].contains(p.x, p.y)) {
        D("Pressing Sub Menu Button");
        // Logic to slect IR code
        tvMenuButtons[b].press(true);
        if(b==sizeOfArray-1){
          D("Pressing Back Button");
          screenNum = 0;
          m.init(tft);
        }
        else{
          for (int i = 0; i < 3; i++) {
            D("Sending IR Code - Sony TV");
            DDD(tvIRCodes2[b]);
            irsend.sendSony(tvIRCodes2[b], Sony_bits);
            delay(40);
          }
        }
      }
      else {
        tvMenuButtons[b].press(false);
      }
    }
  }
  else if(screenNum == 3){
    sizeOfArray = sizeof(cdMenuButtons)/sizeof(cdMenuButtons[0]);
    for (uint8_t b=0; b<sizeOfArray; b++) {
      if (cdMenuButtons[b].contains(p.x, p.y)) {
        D("Pressing Sub Menu Button");
        cdMenuButtons[b].press(true);
        if(b==sizeOfArray-1){
          D("Pressing Back Button");
          screenNum = 0;
          m.init(tft);
        }
        else{
          for (int i = 0; i < 3; i++) {
            D("Sending IR Code - Sony CD");
            DDD(cdIRCodes[b]);
            irsend.sendSony(cdIRCodes[b], Sony_bits);
            delay(40);
          }
        }
      }
      else {
        cdMenuButtons[b].press(false);
      }
    }
  }
  else if(screenNum == 4){
    sizeOfArray = sizeof(dvdMenuButtons)/sizeof(dvdMenuButtons[0]);
    for (uint8_t b=0; b<sizeOfArray; b++) {
      if (dvdMenuButtons[b].contains(p.x, p.y)) {
        D("Pressing Sub Menu Button");
        dvdMenuButtons[b].press(true);
        if(b==sizeOfArray-1){
          D("Pressing Back Button");
          screenNum = 0;
          m.init(tft);
        }
        else{
          for (int i = 0; i < 3; i++) {
            D("Sending IR Code - Panasonic DVD");
            DDD(dvdIRCodes[b]);
            irsend.sendPanasonic(dvdIRCodes[b], Panasonic_ID);
            delay(40);
          }
        }
      }
      else {
        dvdMenuButtons[b].press(false);
      }
    }
  }
  delay(100);
}

// Unable to implement the following functions
// Unable to pass the array of GFX Buttons to the function
/*void checkForButtonPress(Adafruit_GFX_Button buttons[], unsigned long* codes, TS_Point p){
  DD("Size:");
  DDD(sizeof(buttons));
  DD("End");
  for (uint8_t b=0; b<sizeof(buttons); b++) {
      if (buttons[b].contains(p.x, p.y)) {
        D("Pressing Sub Menu Button");
        // Logic to slect IR code
        if (!buttons[b].isPressed()){
          buttons[b].press(true);
          if(b==sizeof(buttons)){
            D("Pressing Back Button");
            screenNum = 0;
            m.init(tft);
          }
          else{
            sendIRSignal(product, codes[b]);
          }
        }
      }
  }
}

void sendIRSignal(char* p, unsigned long code){
  D("Sending IR Code");
  DDD(code)
  for (int i = 0; i < 3; i++) {     // Sony protocol requires three repeats of each command
    if(strcmp(p,"SamTV")==0){
      D("Sony Device");
      irsend.sendSAMSUNG(code, Samsung_bits);
    }
    else if((strcmp(p,"SonyTV")==0) ||(strcmp(product,"SonyCD")==0)){
      D("Sony Device");
      irsend.sendSony(code, Sony_bits);
    }
    else if(strcmp(p,"PanasonicDVD")==0){
      D("Panasonic Device");
      irsend.sendPanasonic(code, Panasonic_ID);
    }
    delay(40);
  }
}*/
