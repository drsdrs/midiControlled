byte readKeyPad() {
  PORTF =  B01011010; // setPullups
  DDRF =   B10100101; // set InpuOutput // zero==input
  
  static byte pressed = 0;
  byte activeRow = 0;
  byte activeCol = 0;
  byte f = PINF;

  if(f==B01011010){ // keypress
     pressed = 0;
     //Serial.println("clear");
  } else if(pressed==0){ // release
      pressed = 1;
      if(f==82){ activeRow = 1;
      } else if(f==74){ activeRow = 2;
      } else if(f==88){ activeRow = 3;
      } else if(f==26){ activeRow = 4;
      }
  
      
      PORTF =  B10100101; // setPullups
      DDRF =   B01011010; // set InpuOutput // zero==input
      PINF = PINF; 
      f = PINF;
      
      if(f==164){ activeCol = 1;
      } else if(f==161){ activeCol = 2;
      } else if(f==133){ activeCol = 3;
      } else if(f==37){ activeCol = 4;
      }
  
    }

    return activeRow|(activeCol<<4);
}

