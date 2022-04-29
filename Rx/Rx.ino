#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;


RF24 radio(9, 10); // CSN, CE
const byte address[6] = {0, 0, 0, 0, 2, 0};
int servo_pin1 = 3;
int servo_pin2 = 6;
int servo_pin3 = 5;
int servo_pin4 = 7;
int servo_pin5 = 8;
struct packet
{
  byte posx;
  byte posy;
  byte posz;
  byte posr;
  byte posp;
} State;

void setup() {
  Serial.begin(9600);
  radio.begin();
  servo1.attach (servo_pin1 ) ;
  servo2.attach (servo_pin2 ) ;
  servo3.attach (servo_pin3 ) ;
  servo4.attach (servo_pin4 ) ;
  servo5.attach (servo_pin5 ) ;
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available() > 0 )
  {
    radio.read(&State, sizeof(State));
    servo1.write(State.posx);
    servo2.write(State.posy);
    servo3.write(State.posz);
    servo4.write(State.posr);
    servo5.write(State.posp);
    Serial.print("posx: " );
    Serial.print(State.posx);
    Serial.print("  posy: ");
    Serial.print(State.posy);
    Serial.print("  posz: ");
    Serial.print(State.posz);
    Serial.print("  posr: ");
    Serial.print(State.posr);
    Serial.print("  posp: ");
    Serial.println(State.posp);
  }
}
