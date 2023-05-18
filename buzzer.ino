//**** define pin numbers ***************************
const int modus1Pin = 1;
const int summerPin = 10;
const int ledBuzzer1Pin = 3;
const int ledBuzzer2Pin = 4;
const int ledCount1Pin = 5;
const int ledCount2Pin = 6;
const int ledCount3Pin = 7;
const int ledCount4Pin = 8;
const int ledCount5Pin = 9;
const int resetButtonPin = 2;
const int buzzerButton1Pin = 11;
const int buzzerButton2Pin = 12;
const int modus2Pin = 13;


//**** define variables ***************************
int           timeFactor = 0;
boolean       buttonPressedTrigger = false;
unsigned int  ledTimerStart = 0;
unsigned int  currentTime = 0;
boolean       resetButtonState = false;

// input variables
boolean modus1 = false;
boolean modus2 = false;
boolean buzzerButton1 = false;
boolean buzzerButton2 = false;
boolean resetButton = false;


//**** function prototypes ***************************
void run_summer(int time_on, int sound_frequency=1000);
void set_leds_counter(boolean led1, boolean led2, boolean led3, boolean led4, boolean led5);
void reset_pressed();

void setup() {

//**** define output pins ***************************
  pinMode(summerPin,        OUTPUT);
  pinMode(ledBuzzer1Pin,    OUTPUT);
  pinMode(ledBuzzer2Pin,    OUTPUT);
  pinMode(ledCount1Pin,     OUTPUT);
  pinMode(ledCount2Pin,     OUTPUT);
  pinMode(ledCount3Pin,     OUTPUT);
  pinMode(ledCount4Pin,     OUTPUT);
  pinMode(ledCount5Pin,     OUTPUT);

//**** define input pins ***************************
  pinMode(resetButtonPin,   INPUT_PULLUP);
  pinMode(buzzerButton1Pin, INPUT);
  pinMode(buzzerButton2Pin, INPUT);
  pinMode(modus1Pin,        INPUT);
  pinMode(modus2Pin,        INPUT);  

//**** initialize external interrupt *************************** 
  attachInterrupt(resetButtonPin, reset_pressed, RISING); 
  
}

void loop() {

//**** modus ***************************
  // read modus switch
  modus1 = digitalRead(modus1Pin);
  modus2 = digitalRead(modus2Pin);

  // change time factor depending on switch
  if(modus1) timeFactor = 1;
  else if(modus2) timeFactor = 5;
  else timeFactor = 2;


//**** buzzer ***************************
  if(buttonPressedTrigger==false){
    // read buzzers
    buzzerButton1 = digitalRead(buzzerButton1Pin);
    buzzerButton2 = digitalRead(buzzerButton2Pin);
  
    if(buzzerButton1){
      digitalWrite(ledBuzzer1Pin, HIGH);
      run_summer(200);
      buttonPressedTrigger = true;
    }
    else if(buzzerButton2){
      digitalWrite(ledBuzzer2Pin, HIGH);
      run_summer(200);
      buttonPressedTrigger = true;
    }
  }

//**** led counter ***************************
  if(buttonPressedTrigger==true){
    ledTimerStart = millis();
    while(modus1==digitalRead(modus1Pin) and modus2==digitalRead(modus2Pin) and !resetButtonState){
      currentTime = millis() - ledTimerStart;
      if(currentTime < 1000 * timeFactor){
        set_leds_counter(1,1,1,1,1);
      }
      else if(currentTime < 2000 * timeFactor){
        set_leds_counter(1,1,1,1,0);
        run_summer(200);
      }   
      else if(currentTime < 3000 * timeFactor){
        set_leds_counter(1,1,1,0,0);
        run_summer(200);
      }     
      else if(currentTime < 4000 * timeFactor){
        set_leds_counter(1,1,0,0,0);
        run_summer(200);
      }  
      else if(currentTime < 5000 * timeFactor){
        set_leds_counter(1,0,0,0,0);
        run_summer(200);
      }  
      else if(currentTime < 6000 * timeFactor){
        set_leds_counter(0,0,0,0,0);
        run_summer(500);
        break;
      }  
      
    } // while
    set_leds_counter(0,0,0,0,0);
    resetButtonState = false;
    
  } // if buttonPressedTrigger 
} // loop


//**** sound generator function ***************************
void run_summer(int time_on, int sound_frequency){
  tone(summerPin, sound_frequency);
  delay(time_on);
  noTone(summerPin);
}

//**** led set function ***************************
void set_leds_counter(boolean led1, boolean led2, boolean led3, boolean led4, boolean led5){
  digitalWrite(ledCount1Pin, led1);
  digitalWrite(ledCount2Pin, led2);
  digitalWrite(ledCount3Pin, led3);
  digitalWrite(ledCount4Pin, led4);
  digitalWrite(ledCount5Pin, led5);  
}

//**** led set function ***************************
void reset_pressed(){
  resetButtonState = true;
}


