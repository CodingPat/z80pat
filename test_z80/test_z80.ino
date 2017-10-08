#define CLKDELAY 40
#define B_CLOCK 6
#define B_RESET 7

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
  digitalWrite(B_RESET,LOW);
  doClock(5);
  digitalWrite(B_RESET,HIGH);
  }

void setup() {
  // put your setup code here, to run once:
  pinMode(B_CLOCK,OUTPUT);
  pinMode(B_RESET,OUTPUT);
  doReset();  

}

// boucle principale
void loop() {
  doClock(1);

}
