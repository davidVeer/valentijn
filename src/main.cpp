#include <Arduino.h>
#include <IRremote.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// lcd declatation
LiquidCrystal_I2C lcd(0x27, 16,2);

// ir reciever declarations
IRrecv irrecv (8);
decode_results results;

// attribute declarations
int irSignal;
boolean irPressed;
String password;
String input;
int lastValue;
int currentValue;
int cycle;

//function declarations
void readInfrared();
void updateIRSignal(int);
char convertSignal();
void printCycle();

//running code
void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);

  lcd.begin();
  lcd.backlight();

  password = "180622";
  input = "";
  pinMode(9, OUTPUT);
  cycle = 0;
}

void loop() {
  boolean lastIrPressed = false;
  while (!input.equals(password)){
    lcd.clear();
    readInfrared();

    if (irPressed && lastIrPressed != irPressed){
      input += convertSignal();
      lcd.println(input);
      Serial.println(input);
    }

    for (int i = 0; i < input.length()-1; i++)
    {
      if (input.charAt(i) != password.charAt(i)){
        input = "";
      }
    }
    lastIrPressed = irPressed;
  }
  digitalWrite(9, true);
  readInfrared();
  if (irPressed && lastIrPressed != irPressed ){
  if (irSignal == 0x1){
    printCycle();
    if (cycle > 13){
      cycle = 0;
    }
  }
  }

  lastIrPressed = irPressed;
}



void updateIRSignal(int value){
  irSignal = value & 0xff;
}

void readInfrared(){
  if (irrecv.decode(&results)){
    updateIRSignal(results.value);
    irrecv.resume();
    irPressed = true;
  }
  else {
    irPressed = false;
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

void printCycle(){
  lcd.clear();
  cycle++;
  switch(cycle){
    case 1:
      lcd.print("hoi liefie");
      Serial.println("hoi liefie");
      break;
    case 2 : 
      lcd.print("ik hou heel veel van jou");
      Serial.println("ik hou heel veel van jou");
      break;
    case 3:
      lcd.print("maar ik heb niet super veel geld");
      Serial.println("maar ik heb niet super veel geld");
      break;
    case 4:
      lcd.print("ik wilde je alleen wel wat geven");
      Serial.println("ik wilde je alleen wel wat geven");
      break;
    case 5:
      lcd.print("iets persoonlijks");
      Serial.println("iets persoonlijks");
      break;
    case 6:
      lcd.print("dus ik wilde heel graag dit voor je maken");
      Serial.println("dus ik wilde heel graag dit voor je maken");
      break;
    case 7:
      lcd.print("je kan t (nog) niet houden en t werkt maar half");
      Serial.println("je kan t (nog) niet houden en t werkt maar half");
      break;
    case 8:
      lcd.print("en dat is  wel stom");
      Serial.println("en dat is  wel stom");
      break;
    case 9:
      lcd.print("daarom neem ik je snel een keertje mee uit eten");
      Serial.println("daarom neem ik je snel een keertje mee uit eten");
      break;
    case 10:
      lcd.print("en ik wil deze iets verder af maken zodat ik hem ook echt aan jou kan geven en zelfs nieuwe berrichten toe kan voegen");
      Serial.println("en ik wil deze iets verder af maken zodat ik hem ook echt aan jou kan geven en zelfs nieuwe berrichten toe kan voegen");
      break;
    case 11:
      lcd.print("dus dat gaat er nog aan komen");
      Serial.println("dus dat gaat er nog aan komen");
      break;
    case 12:
      lcd.print("sorry dat het niet een super groot cadeau was");
      Serial.println("sorry dat het niet een super groot cadeau was");
      break;
    case 13:
      lcd.print("ik hou van jou!");
      Serial.println("ik hou van jou!");
      break;
    default:
      lcd.print("het gaat nu opnieuw afspelen");
      Serial.println("het gaat nu opnieuw afspelen");
      break;
  }
}
