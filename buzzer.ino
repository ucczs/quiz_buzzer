//**** define pin numbers ***************************
// validated!
const int modusPin = 7;
const int summerPin = 13;
const int ledBuzzer1Pin = 9;
const int ledBuzzer2Pin = 11;
const int ledCount1Pin = 2;
const int ledCount2Pin = 3;
const int ledCount3Pin = 4;
const int ledCount4Pin = 5;
const int ledCount5Pin = 6;
const int resetButtonPin = 8;
const int buzzerButton1Pin = 10;
const int buzzerButton2Pin = 12;

const int buzzer_width = 100;


//**** define variables ***************************
int           timeFactor = 0;
boolean       buttonPressedTrigger = false;
unsigned int  ledTimerStart = 0;
unsigned int  currentTime = 0;
boolean       resetButtonState = false;

// input variables
boolean modus = false;
boolean buzzerButton1 = false;
boolean buzzerButton2 = false;
//boolean resetButton = false;


//**** function prototypes ***************************
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
  pinMode(modusPin,        INPUT); 

//**** initialize external interrupt *************************** 
  attachInterrupt(resetButtonPin, reset_pressed, RISING);

//**** Serial Communication for Debugging **********************
  Serial.begin(9600);   
  
}

void loop() {

//**** modus ***************************
  // read modus switch
  modus = digitalRead(modusPin);

  // change time factor depending on switch
  if(modus) timeFactor = 1;
  else timeFactor = 5;

  Serial.print(timeFactor);
  Serial.print("\ntest\n");
  
  digitalWrite(ledBuzzer1Pin, HIGH);
  digitalWrite(ledBuzzer2Pin, HIGH);
  digitalWrite(summerPin, LOW);

//**** buzzer ***************************
  if(buttonPressedTrigger==false){
    // read buzzers
    buzzerButton1 = digitalRead(buzzerButton1Pin);
    buzzerButton2 = digitalRead(buzzerButton2Pin);
  
    if(buzzerButton1){
      digitalWrite(ledBuzzer1Pin, LOW);
      digitalWrite(summerPin,HIGH);
      buttonPressedTrigger = true;
    }
    else if(buzzerButton2){
      digitalWrite(ledBuzzer2Pin, LOW);
      digitalWrite(summerPin,HIGH);
      buttonPressedTrigger = true;
    }
  }

//**** led counter ***************************
  if(buttonPressedTrigger==true){
    buttonPressedTrigger=false;
    currentTime = 0;
    ledTimerStart = millis();
    
    while(modus==digitalRead(modusPin) and !resetButtonState and currentTime < 6000 * timeFactor){
      resetButtonState = digitalRead(resetButtonPin);
      
      currentTime = millis() - ledTimerStart;
      
      if(currentTime < 1000 * timeFactor){
        set_leds_counter(1,1,1,1,1);
        if(currentTime < 1000 * timeFactor - buzzer_width and currentTime > buzzer_width+50) digitalWrite(summerPin,LOW);
        else digitalWrite(summerPin,HIGH);
      }
      
      else if(currentTime < 2000 * timeFactor){
        set_leds_counter(1,1,1,1,0);
        if(currentTime < 2000 * timeFactor - buzzer_width) digitalWrite(summerPin,LOW);
        else digitalWrite(summerPin,HIGH);
      }   
      
      else if(currentTime < 3000 * timeFactor){
        set_leds_counter(1,1,1,0,0);
        if(currentTime < 3000 * timeFactor - buzzer_width) digitalWrite(summerPin,LOW);
        else digitalWrite(summerPin,HIGH);
      }
      else if(currentTime < 4000 * timeFactor){
        set_leds_counter(1,1,0,0,0);
        if(currentTime < 4000 * timeFactor - buzzer_width) digitalWrite(summerPin,LOW);
        else digitalWrite(summerPin,HIGH);
      }  
      else if(currentTime < 5000 * timeFactor){
        set_leds_counter(1,0,0,0,0);
        digitalWrite(summerPin,LOW);
      }  
      else if(currentTime < 6000 * timeFactor){
        set_leds_counter(0,0,0,0,0);
        digitalWrite(summerPin,HIGH);
        delay(500);
        digitalWrite(summerPin,LOW);
        break;
      }  
      
    } // while
    set_leds_counter(0,0,0,0,0);
    digitalWrite(summerPin,LOW);
    resetButtonState = false;
    
  } // if buttonPressedTrigger 
} // loop


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


