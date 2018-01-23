#define NUMBER_LAYOUT 0
#define NOTE_LAYOUT 1

byte getFromLayout(byte keys, byte keyLayout) {
  static char keyLayoutNUMBERS[] = {
       -1, 7, 8, 9,
       -1, 4, 5, 6,
       -1, 1, 2, 3,
       -1, -1, 0,-1 
  };

  static char keyLayoutNOTES[] = {
       -1, 9, 10, 11,
       20, 6, 7, 8,
       30, 3, 4, 5,
       40, 0, 1,2 
  };
  
  byte col = 3-((keys&15)-1);
  byte row = ((keys>>4)&15)-1;
  if(keyLayout==NUMBER_LAYOUT)    return keyLayoutNUMBERS[(col*4)+row];
  else if(keyLayout==NOTE_LAYOUT) return keyLayoutNOTES[(col*4)+row];
  else return 666;
  
}
