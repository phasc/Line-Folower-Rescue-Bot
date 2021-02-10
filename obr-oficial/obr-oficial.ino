#define dS0 8
#define dS1 9
#define dS2 10
#define dS3 11
#define dOut 6
#define eS0 22//preto
#define eS1 23//amarelo
#define eS2 24//vermelho
#define eS3 25//marrom
#define eOut 26//laranja
  
int porta1 = 2; 
int porta2 = 3; 
int porta3 = 4;
int porta4 = 5;
int portaB = 12;
int portaA = 13;
int irDir = 42;
int irEsq = 43;

int pwm = 400;
int eFrequency = 0;
int dFrequency = 0;
long t;
int d;

bool detectarLinha(int sensor){
  int value = digitalRead(sensor);
  bool linha;
   if(value == HIGH){
      //preto
    linha = true;  
    }
  else{
    //branco
    linha = false;   
  }
  return linha; 
}

float pegarDistancia(){
  digitalWrite(portaA,LOW);
  delayMicroseconds(2);
  digitalWrite(portaA,HIGH);
  delayMicroseconds(10);
  digitalWrite(portaA,LOW);
  t = pulseIn(portaB,HIGH);
  d = 0.0170*t;
  Serial.print("Distancia medida: ");
  Serial.print(d);
  Serial.println("cm");
  return d;
}

float eVerde(){
  digitalWrite(eS2,HIGH);
  digitalWrite(eS3,HIGH);
  eFrequency = pulseIn(eOut, LOW);
  return eFrequency;
}

float dVerde(){
  digitalWrite(dS2,HIGH);
  digitalWrite(dS3,HIGH);
  dFrequency = pulseIn(dOut, LOW);
  return dFrequency;
}

void andarTras(int time=0){
  analogWrite(porta1, pwm);
  digitalWrite(porta2,LOW);
  analogWrite(porta3, pwm);
  digitalWrite(porta4,LOW);
  delay(time);
}

void andarFrente(int time=0){
  digitalWrite(porta1,LOW);
  analogWrite(porta2, pwm);
  digitalWrite(porta3,LOW);
  analogWrite(porta4, pwm);
  delay(time);
}

void girarEsquerda(int time=0){
  digitalWrite(porta1,LOW);
  analogWrite(porta2, pwm);
  analogWrite(porta3, pwm);
  digitalWrite(porta4,LOW);
  delay(time);
}

void girarDireita(int time=0){
  analogWrite(porta1,pwm);
  digitalWrite(porta2, LOW);
  digitalWrite(porta3, LOW);
  analogWrite(porta4,pwm);
  delay(time);
}

void verde(float dirverde, float esqverde){
  if((dirverde > 100) && (esqverde < 100)){
    girarDireita(100);
  }
  else if ((dirverde < 100) && (esqverde > 100)){
    girarDireita(100);
  }
}

void desviar(){
   girarDireita(425);
   andarFrente(750);
   girarEsquerda(350);
   andarFrente(750);
   girarEsquerda(330);
   andarFrente(750); 
   girarDireita(100);
   
}

void parar(int time=0){
  analogWrite(porta1, pwm);
  digitalWrite(porta2,LOW);
  digitalWrite(porta3,LOW);
  analogWrite(porta4, pwm);
  delay(time);
}

void seguirLinha(){
    if (!detectarLinha(irDir)&& !detectarLinha(irEsq)){
       andarFrente(10);
       Serial.println("branco");
  }
    else{
        if(detectarLinha(irDir)&& !detectarLinha(irEsq)){
          if((dVerde > 100) && (eVerde < 100)){
           girarDireita(100);//teste 90 graus
        }
          else{
           girarDireita(20);
        }
          Serial.println("Direito");
        }
        if(!detectarLinha(irDir)&& detectarLinha(irEsq)){   
           if((dVerde < 100) && (eVerde > 100)){
            girarEsquerda(100);
           }
           else{
            girarEsquerda(20);
        }
        }
            Serial.println("esquerdo");
       } 
       if(detectarLinha(irDir)&& detectarLinha(irEsq)){
           if((dVerde < 100) && (eVerde > 100)){
             girarDireita(100);
           }
          else{
            girarEsquerda(100);
          }         
          }
       }

void setup() {
  Serial.begin(9600);
  pinMode(portaA  , OUTPUT); 
  pinMode(portaB, INPUT);
  pinMode(eS0, OUTPUT);
  pinMode(eS1, OUTPUT);
  pinMode(eS2, OUTPUT);
  pinMode(eS3, OUTPUT);
  pinMode(eOut, INPUT);
  pinMode(dS0, OUTPUT);
  pinMode(dS1, OUTPUT);
  pinMode(dS2, OUTPUT);
  pinMode(dS3, OUTPUT);
  pinMode(dOut, INPUT);
  pinMode(porta1, OUTPUT);
  pinMode(porta2, OUTPUT);
  pinMode(porta3, OUTPUT);
  pinMode(porta4, OUTPUT);
  pinMode(irEsq, INPUT);
  pinMode(irDir, INPUT);
 
  digitalWrite(eS0,HIGH);
  digitalWrite(eS1,LOW);  
  digitalWrite(dS0,HIGH);
  digitalWrite(dS1,LOW);
 
}

void loop() {
 /* if (pegarDistancia()>15){
    andarFrente();sensor
  }
  else {
     desviar();
  }*/
 seguirLinha();
//verde(dVerde(),eVerde());
// detectarLinha(irDir);
//andarFrente();

}



 
