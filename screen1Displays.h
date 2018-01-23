#include <LiquidCrystal.h>
#define lcd0Pwm 12
#define lcd1Pwm 11
#define lcd0Contrast 10
#define lcd1Contrast 9
#define rs 51
#define en0 49
#define en1 53
#define d4 52
#define d5 50
#define d6 48
#define d7 46
LiquidCrystal lcd1(rs, en1, d4, d5, d6, d7);

// Global Variables ---- MENU //////
byte menuPos = 0;
byte menuPosOld = 0;

byte screen1Displayed = 0;

void dispMenu0(){
  lcd1.setCursor(0,0); lcd1.print("1: Seq    ");
  lcd1.setCursor(0,1); lcd1.print("2: Arp    ");
  lcd1.setCursor(0,2); lcd1.print("3: Lfo    ");
  lcd1.setCursor(0,3); lcd1.print("4: Setup  ");
  lcd1.setCursor(9,0); lcd1.print("5: Midi-Mon");
  lcd1.setCursor(9,1); lcd1.print("6: Arp5678");
  lcd1.setCursor(9,2); lcd1.print("7: Lfo9999");
  lcd1.setCursor(9,3); lcd1.print("8: Play");
}

void dispMenuX(){
  lcd1.clear();
  lcd1.setCursor(0,0); lcd1.print("    ||||||||||||");
  lcd1.setCursor(0,1); lcd1.print("     XX     XX");
  lcd1.setCursor(0,2); lcd1.print("         O");
  lcd1.setCursor(0,3); lcd1.print("    |_________|");
}

void dispMenuPLAY(){
  lcd1.clear();
  lcd1.setCursor(0,0); lcd1.print("Octave:");
  lcd1.setCursor(0,1); lcd1.print("Note:  ");
  lcd1.setCursor(0,2); lcd1.print("NoteNr:");
  lcd1.setCursor(0,3); lcd1.write(3);lcd1.write(4);lcd1.write(5);lcd1.write(6);lcd1.write(7);lcd1.write(8);lcd1.write(9);lcd1.write(3);lcd1.write(4);lcd1.write(5);lcd1.write(6);lcd1.write(7);lcd1.write(8);lcd1.write(9);lcd1.write(3);lcd1.write(4);lcd1.write(5);lcd1.write(6);lcd1.write(7);lcd1.write(8);
}

void checkScreen1(){
  if(screen1Displayed==0){
    if(menuPos==0){ dispMenu0(); }            // MAIN MENU
    else if(menuPos==7){ dispMenuPLAY(); }    // PLAY SCREEN
    else { dispMenuX(); }
    screen1Displayed = 1;
  }  
}
