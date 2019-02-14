// Contrôle de bus 8-bit utilisant :
// MCP23017 = 16bit I/O expander (I2C)
// SN74HC245N = Octal bus transceiver with 3-state outputs

// Arduino connecté à deux MCP23017 (input/output) via protocole I2C
// INPUT = 8 interrupteurs connectés à un 3-state transceiver
// OUTPUT = 8 leds connectée à un 3-state transceiver


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
uint8_t choix=0; // choix menu activation bus (O/N)


  
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
  digitalWrite(BUS_OE1,HIGH);// ~OE : output DISABLED
  
  digitalWrite(BUS_DIR2,LOW);// DIRECTION bus2 PORTB=>PORTA
  digitalWrite(BUS_OE2,LOW);// ~OE : output ENABLED

  //Menu pour activer/désactiver l'interface au bus des leds
  Serial.println("Activer le bus (O/N) ? ");
  

}


void loop() {
  
  // put your main code here, to run repeatedly:
  // lire la valeur des switches
  Wire.beginTransmission(MCP23017_BASE_ADDR | MCP23017_ADDR2);
  Wire.write(MCP23017_GPIOB);
  Wire.endTransmission();
  Wire.requestFrom(MCP23017_BASE_ADDR | MCP23017_ADDR2,1);
  if (Wire.available()<=1)
    valeur_switch=Wire.read();
  
  // allumer les leds
  Wire.beginTransmission(MCP23017_BASE_ADDR | MCP23017_ADDR1);
  Wire.write(MCP23017_GPIOA);
  Wire.write(valeur_switch);
  Wire.endTransmission();
 
    
 // flasher la led interne arduino pour vérifier fonctionnement quand 
 // le 3-state transceiver n'est pas activé ~OE1=HIGH
 toggle_led=!toggle_led;
    digitalWrite(ARD_LED,toggle_led);
    delay(DELAY);


 // traiter options reçues via moniteur série
  if(Serial.available()>0){
      choix=Serial.read();
      
      //vider le buffer pour ne pas tenir compte de CR/LF
      while(Serial.available()>0){
        Serial.read();
      }


     if (choix==79 or choix==111){
    Serial.println("Activation du bus ...");
    digitalWrite(BUS_OE1,LOW);// ~OE : output ENABLED
    }
    else if (choix==78 or choix==110){
      Serial.println("Désactivation du bus ...");
      digitalWrite(BUS_OE1,HIGH);// ~OE : output DISABLED
    }
  
  
  
    } 
    
   
     
}
