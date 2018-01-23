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

LiquidCrystal lcd0(rs, en0, d4, d5, d6, d7);

void checkScreen0(){
  //lcd1.clear();
  if(screen0Displayed==1) return;
  screen0Displayed = 1;
  lcd0.noCursor();
  lcd0.setCursor(0,0); lcd0.print("BPM");
  lcd0.setCursor(6,0); lcd0.write((uint8_t)random(5)+3);
  lcd0.setCursor(8,0); lcd0.write((uint8_t)random(3));
  lcd0.setCursor(0,1); lcd0.print("0---1---2---3---");
  lcd0.cursor();
  lcd0.setCursor(((bpmCount)&15),1); // sequence thru steps
}
