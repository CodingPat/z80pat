//fournit clock et reset
// lit l'adresse demandée

#define CLKDELAY 40

// pins adresse
#define B_ADDRESS0 A0
#define B_ADDRESS1 A1
#define B_ADDRESS2 A2
#define B_ADDRESS3 A3
#define B_ADDRESS4 A4

//pins signaux contrôle OUT
#define B_MREQ 13
#define B_READ 12
#define B_M1 11

//pins signaux contrôle IN
#define B_CLOCK 10
#define B_RESET 9


//impulsion clock
void doClock(unsigned int n){
  for(int i=0;i<n;i++){
    digitalWrite(B_CLOCK,HIGH);
    delay(CLKDELAY);
    digitalWrite(B_CLOCK,LOW);
    delay(CLKDELAY);
  }
    
  }

// reset
void doReset(){
  Serial.begin(9600);
  digitalWrite(B_RESET,LOW);
  doClock(5);
  digitalWrite(B_RESET,HIGH);
  }

void setup() {
  // put your setup code here, to run once:
  pinMode(B_CLOCK,OUTPUT);
  pinMode(B_RESET,OUTPUT);
  
  pinMode(B_MREQ,INPUT);
  pinMode(B_READ,INPUT);
  pinMode(B_M1,INPUT);
  
  
  doReset();  

}

void readAddress(){
  Serial.print("Address bus : ");
  Serial.print("XXXX");
  Serial.print(digitalRead(B_ADDRESS3));
  Serial.print(digitalRead(B_ADDRESS2));
  Serial.print(digitalRead(B_ADDRESS1));
  Serial.println(digitalRead(B_ADDRESS0));
  
  }

void readSignals(){
  Serial.println("Control signals");
  Serial.print("MREQ :");
  Serial.print(digitalRead(B_MREQ));
  Serial.print(" - ");
  Serial.print("READ :");
  Serial.print(digitalRead(B_READ));
  Serial.print(" - ");
  Serial.print("M1 :");
  Serial.println(digitalRead(B_M1));
  
  }

// boucle principale
void loop() {
  doClock(1);
  readSignals();  
  readAddress();

}
