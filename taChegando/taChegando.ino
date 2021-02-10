#include <Servo.h>
#include <LiquidCrystal.h>

//                rs, enable, d4, d5, d6, d7
LiquidCrystal lcd(48, 49, 50, 51, 52, 53);

Servo sd;
Servo se;

//sensor de cor da esquerda
#define eS0 28
#define eS1 29
#define eS2 30
#define eS3 31
#define eOut 32 //saida do sensor

 //sensor de cor da direita
#define dS0 22
#define dS1 23
#define dS2 24
#define dS3 25
#define dOut 27 //saida do sensor

bool bola(){
  if (pegarDistancia2() < 2){
    return true;
  }
  else if (pegarDistancia2 > 2){
    return false;
  }
}

int count = 0;
int adVerde = -480;
int aeVerde = -570;
int a2Verde = -550;

//sensor de ultrassom de cima
int echo = 35; //echo (receptor)
int trigger = 34; //trigger (emissor)

//sensor de ultrassom de baixo
int echo2 = 37; //echo (receptor)
int trigger2 = 36; //trigger (emissor)

//sensores de refletancia
int irFront = 39; //frente
int irDir2 = 41; //direita2
int irEsq2 = 40; //esquerda2
int irDir = 47; //direita
int irEsq = 43; //esquerda
int irCen = 42; //centro
int irCen2 = A8; //analogico

int eFrequency = 0; //variavel para o nivel de verde no sensor da esquerda
int dFrequency = 0; //variavel para o nivel de verde no sensor da direita
long t; //variavel relativa ao tempo do echo do sensor de ultrassom
int d; //variavel relativa a distancia do robo a um objeto

//variavel booleana para presenca (true) ou ausencia (false) de linha em baixo dos sensores de refletancia
bool detectarLinha(int sensor){ 
  int value = digitalRead(sensor);
  bool linha;
   if(value == 1){
    //preto
    linha = true;  
  }
  else{
    //branco
    linha = false;   
  }
  return linha; 
}

float prata = analogRead(irCen2);

//variavel relativa a distancia do robo a um obstaculo
float pegarDistancia(){
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(100);
  digitalWrite(trigger,LOW);
  t = pulseIn(echo,HIGH);
  d = 0.0170*t;
  Serial.print("Distancia medida: ");
  Serial.print(d);
  Serial.println("cm");
  return d;
}

float pegarDistancia2(){
  digitalWrite(trigger2,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger2,HIGH);
  delayMicroseconds(100);
  digitalWrite(trigger2,LOW);
  t = pulseIn(echo2,HIGH);
  d = 0.0170*t;
  Serial.print("Distancia medida: ");
  Serial.print(d);
  Serial.println("cm");
  return d;
}

//variavel que indica o nivel de verde em baixo do sensor de cor da esquerda
float eVerde(){
  digitalWrite(eS2,HIGH);
  digitalWrite(eS3,HIGH);
  eFrequency = pulseIn(eOut, LOW)*10;
  return eFrequency;
}

//variavel que indica o nivel de verde em baixo do sensor de cor da direita
float dVerde(){
  digitalWrite(dS2,HIGH);
  digitalWrite(dS3,HIGH);
  dFrequency = pulseIn(dOut, LOW)*10;
  return dFrequency;
}

//funcao para frear o robo
void frear(int time=0){
  sd.write(90);
  se.write(90);
  delayMicroseconds(time);
}

//funcao para andar para tras
void andarTras(int time=0){
  Serial.println("Andando para tras");
  sd.write(180);
  se.write(0);
  delayMicroseconds(time);
}

//funcao para andar para frente
void andarFrente(int time=0){
  Serial.println("Andando para frente");  
  sd.write(0);
  se.write(180);
  delayMicroseconds(time); 
}

void andarFrente2(int time=0){
  Serial.println("Andando para frente");  
  sd.write(65);
  se.write(115);
  delayMicroseconds(time); 
}

//funcao para girar para a esquerda
void girarEsquerda(int time=0){
  Serial.println("Girando para a esquerda");      
  sd.write(0);
  se.write(0);
  delay(time);
}

void girarEsquerda2(int time=0){
  Serial.println("Girando para a esquerda");      
  sd.write(83);
  se.write(83);
  delayMicroseconds(time);
}

 //funcao para girar para a diereita
void girarDireita(int time=0){
  Serial.println("Girando para a direita");  
  sd.write(180);
  se.write(180);
  delay(time);
}

void girarDireita2(int time=0){
  Serial.println("Girando para a direita");  
  sd.write(98);
  se.write(98);
  delayMicroseconds(time);
}

//funcao para girar para o lado com o quadrado verde 
void verde2(float dVerde, float eVerde){
  if(dVerde - eVerde > adVerde){
    sd.write(180);
    se.write(180);
    delay(750);
    andarFrente(100000);
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print ("direita");
    
  }
  else if (dVerde - eVerde < aeVerde){
    girarEsquerda(900);
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print ("esquerda");
  }
  
  else if (a2Verde + 50 > dVerde - eVerde > a2Verde - 50){
    sd.write(180);
    se.write(180);
    delay(1500);
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print ("meia volta");
  }
  else{
    andarFrente(100);
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print ("frente");
  }
}

void verde(float dVerde, float eVerde){
  if((dVerde > 135) && (eVerde < 650)){
    girarDireita(300000);
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print ("direita");
    
  }
  else if ((dVerde < 135) && (eVerde > 650)){
    girarEsquerda(300000);
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print ("esquerda");
  }
  
  else if ((dVerde > 135) && (eVerde > 650)){
    girarEsquerda(2000000);
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print ("meia volta");
  }
  else{
    
  }
}

void verde3(){
  if(count == 0){
    andarFrente(100000);
    count = count++;
  }
  else if(count == 1){   
    girarDireita(400);
    count = count++;
  }
  else if(count == 2){
    girarEsquerda(400);
    count = count++;
  }
  else if(count>4){
    
  }
  delay(100);
}

 //funcao para desviar de um obstaculo
void desviar(){
   girarDireita(1100000);
   andarFrente(2000000);
   girarEsquerda(1200000);
   andarFrente(4000000);
   girarEsquerda(1100000);
   andarFrente(2000000); 
   girarDireita(1100000);  
}

void desviar2(){
  frear(1000);
  sd.write(120);
  se.write(120);
  delay(850);
  while(!detectarLinha(irCen)){
  sd.write(0);
  se.write(103);
  delayMicroseconds(1);  
  }
  sd.write(60);
  se.write(120);
  delay(300);
  sd.write(180);
  se.write(180);
  delay(200);     
}

void garra(){
  // ... desce, fecha e sobe a garra
}

void garra2(){
  // ... desce meio, abre e sobe a garra
}

//funçao p pegar a bolinha
void pegarBola(){
  void garra();
  while(pegarDistancia2 > 3){
    andarFrente();
  }
  girarDireita(900);
  for(int i = 0; i < 4; i++){
    while(pegarDistancia2 > 3){
      andarFrente(); 
    }
    if(detectarLinha(irFront)){
      garra2();
      break;
    }
    else if(!detectarLinha(irFront)){
      girarDireita(900);
    }
    delay(1);
  }
}

//funçao p detectar a bolinha
void bolinha2(){
  int count2 = 0;
  int x = count2 % 2;
  while(!bola){
    if (pegarDistancia() > 3){
      andarFrente();
    }
    else if (pegarDistancia() < 3){
      if (x == 0){
        girarDireita(900);
        andarFrente(200);
        girarDireita(900);
        count2 = count2++;  
      }
      else if (x == 1){
        girarEsquerda(900);
        andarFrente(200);
        girarEsquerda(900);
        count2 = count2++;  
      }
    }
  }
  pegarBola();
}

//funçao p detectar a bolinha
void bolinha(){
  int diferenca = pegarDistancia() - pegarDistancia2();
  while(diferenca < 2){
    girarDireita();   
  }
    while(pegarDistancia2() > 2){
      andarFrente(); 
    }
      pegarBola();  
}


 //funcao para seguir a linha preta no chao
void seguirLinha(){
    if (!detectarLinha(irDir) && !detectarLinha(irEsq) && detectarLinha(irCen)){
       andarFrente();
       lcd.clear();
       lcd.setCursor(5,0);
       lcd.print ("frente");
    }
  
    else if (detectarLinha(irDir) && (!detectarLinha(irEsq) || !detectarLinha(irEsq2)) && !detectarLinha(irCen)){
        girarDireita2();
        lcd.clear();
        lcd.setCursor(5,0);
        lcd.print ("direita");
        }
        
    else if((!detectarLinha(irDir) || !detectarLinha(irDir2)) && detectarLinha(irEsq) && !detectarLinha(irCen)){   
        girarEsquerda2();
        lcd.clear();
        lcd.setCursor(5,0);
        lcd.print ("esquerda");
        }
        
    else if(!detectarLinha(irDir) && !detectarLinha(irEsq) && !detectarLinha(irCen)){
       //andarFrente2();
       //lcd.clear();
       //lcd.setCursor(5,0);
       //lcd.print ("frente");
       }
        
    else if((detectarLinha(irDir) && detectarLinha(irDir2) && detectarLinha(irEsq) && detectarLinha(irEsq2) && detectarLinha(irCen)) || (detectarLinha(irDir) && detectarLinha(irDir2) && !detectarLinha(irEsq) && !detectarLinha(irEsq2) && detectarLinha(irCen))  || (!detectarLinha(irDir) && !detectarLinha(irDir2) && detectarLinha(irEsq) && detectarLinha(irEsq2) && detectarLinha(irCen)) || (detectarLinha(irDir) && detectarLinha(irDir2) && detectarLinha(irEsq) && detectarLinha(irEsq2) && !detectarLinha(irCen))){
       frear(100); 
       lcd.setCursor(5,0);
       lcd.println ("cruzamento");
       //andarTras(1000);      
       //lcd.clear(); 
       //lcd.print ("d ");
       //lcd.print (dVerde());
       //lcd.print ("e ");
       //lcd.print (eVerde());      
       //verde2(dOut, eOut); 
       verde3();    
    }
}
     
void resgate(){
  for(int i=0; i < 10; i++){
    bolinha2();
    // ... alguma coisa para o canto de inicio da varredura
    delay(10);
  }
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); 
  pinMode(trigger, OUTPUT); 
  pinMode(echo, INPUT);
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
  pinMode(irEsq, INPUT);
  pinMode(irDir, INPUT);
  pinMode(irCen, INPUT);
  pinMode(irCen2, INPUT);
  

  //ativacao dos sensores de cor
  digitalWrite(eS0,HIGH);
  digitalWrite(eS1,LOW);  
  digitalWrite(dS0,HIGH);
  digitalWrite(dS1,LOW);

  sd.attach(2);
  se.attach(3);
  
  lcd.setCursor(2,0);
  lcd.print("koeh rapaziada");
  //delay(1000); 
  count = 0;
}

void loop() {
/*  int prata = detectaLinhaPrata();
  
  if (prata > 50 &&  prata < 150) {
      resgate();
  } else {
      if (pegarDistancia() < 15){
          desviar();
      }  else {
          seguirLinha();
      }  
  }
  
       
       lcd.clear(); 
       lcd.print ("d");
       lcd.print (dVerde());
       lcd.print ("  e");
       lcd.print (eVerde());
       delay(1000);
       
       lcd.clear(); 
       lcd.print (prata);
       delay(1000);*/
       
  if (pegarDistancia() < 5){
        lcd.clear();
        lcd.setCursor(5,0);
        lcd.print ("desviando");
        desviar2();
        }  
        else {
          seguirLinha();
      } 
       
     //Serial.println(detectarLinha(irDir2));
       
   // girarEsquerda2(10000000);
    //girarDireita2(10000000);
    //andarFrente(1000000); 
    //frear(1000000000000);
   
   
   //seguirLinha();
  //Serial.println(digitalRead(irCen));
   //desviar2();
   //frear(1000);
  //verde(dOut, eOut);
  //Serial.print("d");
  //Serial.println( dVerde());
 // Serial.print("e");
  //Serial.println( eVerde());
 // delay(1000);
    
    
    /* if (pegarDistancia() < 15){
          desviar();
      }  else {
          seguirLinha();
      }*/   
}
