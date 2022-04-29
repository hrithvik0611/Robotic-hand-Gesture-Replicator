#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CSN, CE
const byte address[6] = {0, 0, 0, 0, 2, 0};

int x_key = A0;
int y_key = A1;
int x_pos;
int y_pos;
struct packet {
  byte posx;
  byte posy;
  byte posz;
  byte posr;
  byte posp;
} State;
unsigned long lastSend;
const unsigned int sendInterval = 200;

void setup()
{
  radio.begin();
  Serial.begin(9600);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  pinMode (x_key, INPUT) ;
  pinMode (y_key, INPUT) ;
}

void loop()
{
  if (millis() - lastSend >= sendInterval)
  {
    lastSend = millis();
    State.posx = map(analogRead(A0), 0, 1023, 120, 30);
    Serial.print("posx: " );
    Serial.println(State.posx);
    State.posy = map(analogRead(A1), 0, 1023, 0, 180);
    Serial.print("posy: ");
    Serial.println( State.posy);
    State.posz = map(analogRead(A4), 0, 1023, 0, 180);
    Serial.print("posz: ");
    Serial.println( State.posz);
    State.posr = map(analogRead(A3), 0, 1023, 0, 180);
    Serial.print("posr: ");
    Serial.println( State.posr);
    State.posp = map(analogRead(A2), 0, 1023, 0, 181);
    Serial.print("posp: ");
    Serial.println( State.posp);
    radio.write(&State, sizeof(State));
  }



}
