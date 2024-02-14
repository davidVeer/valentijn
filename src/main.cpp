#include <Arduino.h>
#include <IRremote.h>

// ir reciever declaration
IRrecv irrecv (8);
decode_results results;

// attribute declaration
int irSignal;
boolean irPressed;
String password;
String input;
int lastValue;
int currentValue;

//function declaration
void readInfrared();
void updateIRSignal(int);
char convertSignal();

//running code
void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);

  password = "180622";
  input = "";
  pinMode(9, OUTPUT);
}

void loop() {
  boolean lastIrPressed = false;
  while (!input.equals(password)){
    readInfrared();

    if (irPressed && lastIrPressed != irPressed){
      input += convertSignal();
      Serial.println(input);
    }

    for (int i = 0; i < input.length()-1; i++)
    {
      if (input.charAt(i) != password.charAt(i)){
        input = "";
      }
    }
    lastIrPressed = irPressed;
    lastValue = currentValue;
  }

}

void updateIRSignal(int value){
  irSignal = value & 0xff;
}

void readInfrared(){
  if (irrecv.decode(&results)){
    updateIRSignal(results.value);
    irrecv.resume();
    irPressed = true;
    digitalWrite(9, true);
  }
  else {
    irPressed = false;
    digitalWrite(9,false);
  }
  if (irPressed){
    currentValue = irSignal;
  }

}

char convertSignal(){
  switch (irSignal)
  {
  case 0x1:
    return '1';
  case 0x2:
    return '2';
  case 0x3:
    return '3';
  case 0x4:
    return '4';
  case 0x5:
    return '5';
  case 0x6:
    return '6';
  case 0x7:
    return '7';
  case 0x8:
    return '8';
  case 0x9:
    return '9';
  case 0x0:
    return '0';
  default:
    return ' ';
  }
}
