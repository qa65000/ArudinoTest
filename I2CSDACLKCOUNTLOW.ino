//#include <Wire.h>
const int ledPin =  13;
const int scl = 5;
const int sda = 4;
const int ODD = 6;
const int OTG = 7;
const int TRGIN = 8;

uint8_t SdaLowCount;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(ODD, OUTPUT);
  pinMode(OTG, OUTPUT);
  pinMode(0, INPUT_PULLUP);
  pinMode(sda, INPUT);
  pinMode(TRGIN, INPUT);
  pinMode(scl, INPUT);
 
attachInterrupt (digitalPinToInterrupt (scl), isr_scl, FALLING);
attachInterrupt (digitalPinToInterrupt (TRGIN), isr_trg, RISING);
  SdaLowCount = 4;
  SerialUSB.begin(115200);      // 9600bpsでシリアルポートを開く
  //Wire.begin(); // join i2c bus (address optional for master)
  SerialUSB.printf("Program Start!");
}


void isr_scl(){
  if(SdaLowCount)
  {
    SdaLowCount--;
  }
}
uint8_t toggle;

void isr_trg(){
  toggle++;
  if(toggle & 0x1)  digitalWrite(ODD,LOW);
  else   digitalWrite(ODD,HIGH);
  SdaLowCount =4;
}

byte x = 0;
uint8_t ButtonState;
uint8_t OLDState;
uint8_t SdaLow;

void HexPinrt(uint8_t Hex)
{
   if((Hex & 0xf0) == 0)
   {
       SerialUSB.print("0");
   }
   SerialUSB.print(Hex,HEX);
}
void loop()
{
  ButtonState = digitalRead(0);

  if(OLDState != ButtonState)
  {
    OLDState = ButtonState;
    if(ButtonState == 0)
    {
      if(SdaLowCount)
      SdaLowCount =0;
      else
      SdaLowCount =4;
    } 
  }
  if(SdaLowCount == 0)
  {
    digitalWrite(ledPin,HIGH);
    pinMode(sda, INPUT);
//  attachInterrupt (digitalPinToInterrupt (sda), isr_sda, FALLING);
  }
  else
  {
    SdaLow = 1;
    digitalWrite(ledPin,LOW);
    pinMode(sda, OUTPUT);
    digitalWrite(sda,LOW);
  }
}
