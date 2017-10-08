//fournit clock et reset
// gère signal wait (dès demande /RD ou /WR)
// lit l'adresse demandée
//renvoie les données

#define CLKDELAY 40

// pins adresse
#define ADDRESS0 2
#define ADDRESS1 3
#define ADDRESS2 4
#define ADDRESS3 5


// pins data
#define DATA0 6
#define DATA1 7
#define DATA2 8
#define DATA3 9
#define DATA4 10
#define DATA5 11
#define DATA6 12
#define DATA7 13


//pins signaux contrôle
#define RD A0
#define WR A1
#define WAIT A2
#define RESET A3
#define CLOCK A4


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
  pinMode(CLOCK,OUTPUT);
  pinMode(RESET,OUTPUT);
  pinMode(WAIT,OUTPUT);

  pinMode(DATA0,OUTPUT);
  pinMode(DATA1,OUTPUT);
  pinMode(DATA2,OUTPUT);
  pinMode(DATA3,OUTPUT);
  pinMode(DATA4,OUTPUT);
  pinMode(DATA5,OUTPUT);
  pinMode(DATA6,OUTPUT);
  pinMode(DATA7,OUTPUT);


  pinMode(READ,INPUT);
  pinMode(WRITE,INPUT);
  
  digitalWrite(WAIT,1);
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
