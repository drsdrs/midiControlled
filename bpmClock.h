// variables for bpm and sequencers
volatile unsigned int bpmCount = 0;
volatile byte screen0Displayed = 0;

unsigned long microFromBpm(int bpm){
  return (60*1000000)/bpm;
}

void countBpm(){ // interrupt event
  bpmCount++;
  screen0Displayed = 0;
}
