//fournit clock et reset
// lit l'adresse demandée

#define CLKDELAY 40

// pins adresse
#define B_ADDRESS0 A0
#define B_ADDRESS1 A1
#define B_ADDRESS2 A2
#define B_ADDRESS3 A3
#define B_ADDRESS4 A4

// pins data
#define B_DATA0 1
#define B_DATA1 0
#define B_DATA2 3
#define B_DATA3 6
#define B_DATA4 7
#define B_DATA5 5
#define B_DATA6 4
#define B_DATA7 2


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

  pinMode(B_DATA0,OUTPUT);
  pinMode(B_DATA1,OUTPUT);
  pinMode(B_DATA2,OUTPUT);
  pinMode(B_DATA3,OUTPUT);
  pinMode(B_DATA4,OUTPUT);
  pinMode(B_DATA5,OUTPUT);
  pinMode(B_DATA6,OUTPUT);
  pinMode(B_DATA7,OUTPUT);


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

void doInstruction(){
  digitalWrite(B_DATA0,1);
  digitalWrite(B_DATA1,1);
  digitalWrite(B_DATA2,1);
  digitalWrite(B_DATA3,1);
  digitalWrite(B_DATA4,1);
  digitalWrite(B_DATA5,1);
  digitalWrite(B_DATA6,1);
  digitalWrite(B_DATA7,1);
  
  }

// boucle principale
void loop() {
  doInstruction();
  doClock(1);
  readSignals();  
  readAddress();
  

}
