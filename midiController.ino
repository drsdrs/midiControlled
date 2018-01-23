#include <Encoder.h>
#include <MIDI.h>
#include <TimerThree.h>

#include "input.h"
#include "customCharArrays.h"
#include "bpmClock.h"
#include "keyLayout.h"
#include "screen0Displays.h"
#include "screen1Displays.h"


#define DEBUG 1

Encoder rotEnc1(18, 19);
Encoder rotEnc0(2, 3);


struct MidiSettings : public midi::DefaultSettings{
    static const unsigned SysExMaxSize = 32; // Accept SysEx messages up to 32(old_1024) bytes long.
};

MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial3, MIDI, MidiSettings);



String noteNames[] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "H" };


void setup() {
  analogWrite(lcd0Pwm, 128);
  analogWrite(lcd1Pwm, 128);
  analogWrite(lcd0Contrast, 80);
  analogWrite(lcd1Contrast, 50);

  lcd0.createChar(0, customCharPLAY);
  lcd0.createChar(1, customCharPAUSE);
  lcd0.createChar(2, customCharSTOP);
  
  lcd0.createChar(3, customCharMEN0);
  lcd0.createChar(4, customCharMEN1);
  lcd0.createChar(5, customCharMEN2);
  lcd0.createChar(6, customCharMEN3);
  lcd0.createChar(7, customCharMEN4);

  lcd1.createChar(3, customCharMEN0);
  lcd1.createChar(4, customCharMEN1);
  lcd1.createChar(5, customCharMEN2);
  lcd1.createChar(6, customCharMEN3);
  lcd1.createChar(7, customCharMEN4);
  
  lcd0.begin(16, 2);
  lcd1.begin(20, 4);
  lcd0.cursor();
  
  if(DEBUG){ Serial.begin(115200); }

  MIDI.setHandleNoteOn(false);
  MIDI.setHandleNoteOff(false);
  MIDI.setHandleControlChange(false);
  MIDI.setHandleClock(false);
  MIDI.setHandleStart(false);
  MIDI.setHandleContinue(false);
  MIDI.setHandleStop(false);
  MIDI.begin(MIDI_CHANNEL_OMNI);

  Timer3.initialize(microFromBpm(60));
  Timer3.attachInterrupt(countBpm);
}



void checkMenuPLAY(byte keys){
  
}





void checkMenuAction(byte keys){
  if(keys==0){ return;  }
  else if(keys==1){ menuPos = 0;}
  if(menuPos!=menuPosOld){ // render main screen if menuposition changed
    screen1Displayed = 0;
    menuPosOld = menuPos;
  }
  
  if(menuPos==0 ){              // MAIN MENU
    menuPos = getFromLayout(keys, NUMBER_LAYOUT);
  } else if(menuPos==7 ){       // PLAY SCREEN
    checkMenuPLAY(keys);
  } else {
    menuPos = 0;
  }
}


byte priorityCnt = 0;
byte priorityLevel1 = 15;
byte priorityLevel2 = 255;

void priority1Loop(){
  byte keys = readKeyPad();
  checkMenuAction(keys);
}

void priority2Loop(){
  checkScreen1();
  checkScreen0(); 
}


void loop() {
  MIDI.read(); // repeat fast as possible // level 0 priority
  if(priorityCnt&priorityLevel1==priorityLevel1){ priority1Loop(); }
  if(priorityCnt&priorityLevel2==priorityLevel2){ priority2Loop(); }

  priorityCnt++;
}



//////////////////////////////////////////////////////
////////////// For later use, or not. ///////////////
////////////////////////////////////////////////////

void debugInput(byte keys){
  if(keys>0){
    lcd1.setCursor(0,0);
    lcd1.print(keys&15);
    lcd1.setCursor(0,1);
    lcd1.print(keys>>4&15);
    lcd1.setCursor(9,0);
    lcd1.print(keys, BIN);
    lcd1.setCursor(9,1);
    lcd1.print(keys, DEC);
  }
    lcd1.setCursor(0,2);
    lcd1.print("    ");
    lcd1.setCursor(0,2);
    lcd1.print(rotEnc0.read());
    lcd1.setCursor(0,3);
    lcd1.print("    ");
    lcd1.setCursor(0,3);
    lcd1.print(rotEnc1.read());
}
