#define NOTE_C3 131
#define NOTE_D3 147
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_G3 196
#define NOTE_A3 220
#define NOTE_B3 247
#define NOTE_C4 262

int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

int melody[] = 
{
  NOTE_B3,NOTE_A3,NOTE_G3,NOTE_A3,NOTE_B3,NOTE_B3,NOTE_B3
};

int noteDurations[] =
{
  4,4,4,4,4,4,4
};
int thisNote = -1,noteDuration = 0;
long previousTime = 0,
     presentTime = 0,
     pauseBetweenNotes = 0;

void setup() {
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(2,INPUT_PULLUP);
}

void checkToPlay(){

  presentTime = millis();
  if(presentTime-previousTime>=pauseBetweenNotes){
    thisNote+=1;
    if(thisNote>=8){
      thisNote=-1;
      pauseBetweenNotes=100;
      previousTime=millis();
    }else{
      noteDuration=500/noteDurations[thisNote];
      tone(9,melody[thisNote],noteDuration);
      pauseBetweenNotes=noteDuration*1.2;
      previousTime = millis();
    }
  }
    
}




byte colDataMatrix[8] = {
   B11111110,
   B11111101,
   B11111011,
   B11110111,
   B11101111,
   B11011111,
   B10111111,
   B01111111
}; //掃描
  

byte rowDataMatrix[8] = {
   B00011000,
   B00100100,
   B01000010,
   B10000001,
   B10000001,
   B01000010,
   B00100100,
   B00011000
}; //圖案
byte row1DataMatrix[8] = {
   B00000000,
   B00100100,
   B00100100,
   B00111100,
   B00111100,
   B00100100,
   B00100100,
   B00000000
}; //圖案


 byte previous_buttonState=1,present_buttonState=1,patternNumber=0;

void loop() {
  


  present_buttonState=digitalRead(2);
  if( present_buttonState==0 && previous_buttonState==1){
      patternNumber++; 
      if(patternNumber>1) patternNumber=0;
    }
 if( patternNumber==0){
        for(int i = 0; i < 8 ; i++){
    	digitalWrite(latchPin,LOW);
    	shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
    	shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix[i]);
    	digitalWrite(latchPin,HIGH);
        checkToPlay();
    	delay(1);
    	}
  }
   if(patternNumber==1){
      for(int i = 0; i < 8 ; i++){
   	digitalWrite(latchPin,LOW);
    	shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
    	shiftOut(dataPin, clockPin, MSBFIRST, row1DataMatrix[i]);
    	digitalWrite(latchPin,HIGH);
       checkToPlay();
    	delay(1);
    	}
   }
   
  
  delay(2);
  
  previous_buttonState= present_buttonState;
  
}










