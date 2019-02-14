// Control a 8-bit bus using :
// MCP23017 = 16bit I/O expander (I2C)
// SN74HC245N = Octal bus transceiver with 3-state outputs

// Test = light 8 leds connected on port B of SN74HC245N
// Input = MCP23017 connected on port A of SN74HC245N
// Arduino connected to MCP23017 (I2C protocol)



#include <Wire.h>
#define DELAY 500 // delay ms between led toggles
#define BUS_DIR1 A2// pin tri-state direction
#define BUS_OE1 A3// pin tri-state output enable
#define BUS_DIR2 A0// pin tri-state direction
#define BUS_OE2 A1// pin tri-state output enable
 
#define ARD_LED 13 //arduino internal led (always flashing,to show that pgm is running when output is disabled)
#define MCP23017_BASE_ADDR 0x20
#define MCP23017_ADDR1 0x01
#define MCP23017_ADDR2 0x02
#define MCP23017_IODIRA 0x00
#define MCP23017_IODIRB 0x01
#define MCP23017_GPIOA 0x12
#define MCP23017_GPIOB 0x13


boolean toggle_led=0;//used to toggle arduino internal led
uint8_t valeur_switch=0; //=input sur mcp2
  
void setup() {
   // put your setup code here, to run once:
 
  Serial.begin(9600);
  Wire.begin();
  delay(100);

  //registre A mcp1 en output
  Wire.beginTransmission(MCP23017_BASE_ADDR | MCP23017_ADDR1);
  Wire.write(MCP23017_IODIRA);
  Wire.write(0x00);
  Wire.endTransmission();

  //registre B mcp2 en input (= valeur par défaut)
  Wire.beginTransmission(MCP23017_BASE_ADDR | MCP23017_ADDR2);
  Wire.write(MCP23017_IODIRB);
  Wire.write(0xFF);
  Wire.endTransmission();

  
  //pin modes on arduino
  pinMode(BUS_DIR1,OUTPUT);
  pinMode(BUS_OE1,OUTPUT);
  pinMode(BUS_DIR1,OUTPUT);
  pinMode(BUS_OE1,OUTPUT);

  pinMode(ARD_LED,OUTPUT);

  digitalWrite(BUS_DIR1,HIGH);// DIRECTION bus1 PORTA=>PORTB
  digitalWrite(BUS_OE1,LOW);// ~OE : output ENABLED
  
  digitalWrite(BUS_DIR2,LOW);// DIRECTION bus2 PORTB=>PORTA
  digitalWrite(BUS_OE2,LOW);// ~OE : output ENABLED
}

void loop() {
  
  // put your main code here, to run repeatedly:

  // allumer les leds
  for (int8_t i=0;i<8;i++){
    Wire.beginTransmission(MCP23017_BASE_ADDR | MCP23017_ADDR1);
    Wire.write(MCP23017_GPIOA);
    Wire.write(1<<i);
    Wire.endTransmission();
    toggle_led=!toggle_led;
    digitalWrite(ARD_LED,toggle_led);
    delay(DELAY);
    
    
    }

  // lire la valeur des switches
  Wire.beginTransmission(MCP23017_BASE_ADDR | MCP23017_ADDR2);
  Wire.write(MCP23017_GPIOB);
  Wire.endTransmission();
  Wire.requestFrom(MCP23017_BASE_ADDR | MCP23017_ADDR2,1);
  if (Wire.available()<=1)
    valeur_switch=Wire.read();
  Serial.print("Valeur switch = ");
  Serial.print(valeur_switch);
  Serial.print("\n");
  
    
  
  
    
  
    
}
