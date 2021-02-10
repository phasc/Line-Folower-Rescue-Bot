#include <Servo.h>
#include <LiquidCrystal.h>
 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo s1; // 78
Servo s2; // 89
Servo sgarra;
const int garrarest = 160;
const int garraup = 120;
const int garradown = 0;
int parverde =185;//160-185
int med1 = 7;
int med2 = 8;
int x =0;
int y=0;
int s1point0 = 85;
int s2point0 = 86;
int e = 90;
//
int pinoprata = A7;
int contador= 0;
bool prata = false;
bool virarBolinha;

int ls1p = 22;
int ls2p = 23;
int ls3p = 24;
int ls4p = 25;
int ls5p = 26;
int toquePin = 27;

int trigger1 = 53;
int trigger2 = 51;
int echo1 = 52;
int echo2 = 50;
long duration1;
float distance1;
long duration2;
float distance2;

//cor
int s0d = 32;
int s1d = 33;
int s2d = 34;
int s3d = 35;
int outd = 36;
int s0e = 37;
int s1e = 38;
int s2e = 39;
int s3e = 40;
int oute = 41;
int verdeE;
int verdeD;

bool leitura1;
bool leitura2;
bool leitura3;
bool leitura4;
bool leitura5;
bool sensorToque;

void setup() {
  lcd.clear();

  Serial.begin(9600);
  lcd.begin(16,2);

  lcd.print("GRRRRRRRRR");
 /* pinMode(A0, OUTPUT); // serpow1
  pinMode(A1, OUTPUT); // serpow2*/

  s1.attach(29); //3
  s2.attach(31); //4
  sgarra.attach(7);

  pinMode(trigger1, OUTPUT);
  pinMode(trigger2, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  
  pinMode(s0d, OUTPUT);
  pinMode(s1d, OUTPUT);
  pinMode(s2d, OUTPUT);
  pinMode(s3d, OUTPUT);
  pinMode(outd, INPUT);
  pinMode(s0e, OUTPUT);
  pinMode(s1e, OUTPUT);
  pinMode(s2e, OUTPUT);
  pinMode(s3e, OUTPUT);
  pinMode(oute, INPUT);

  digitalWrite(s0d, HIGH);  
  digitalWrite(s1d, LOW);  
  digitalWrite(s0e, HIGH);  
  digitalWrite(s1e, LOW);  
  
  s1.write(s1point0);
  s2.write(s2point0);
  sgarra.write(garrarest);
  
  pinMode(ls1p, INPUT);
  pinMode(ls2p, INPUT);
  pinMode(ls3p, INPUT);
  pinMode(ls4p, INPUT);
  pinMode(ls5p, INPUT);
  pinMode(toquePin, INPUT_PULLUP);
}

void frente(int tempo, int pwm) {
  s1.write(s1point0 + 4*pwm);
  s2.write(s2point0 - pwm);
  delay(tempo);
}

void tras(int tempo, int pwm) {
  s1.write(s1point0 - pwm);
  s2.write(s2point0 + pwm);
  delay(tempo);
}

void direita(int tempo, int pwm) {
  s1.write(s1point0 + pwm);
  s2.write(s2point0 + pwm);
  delay(tempo);
}

void esquerda(int tempo, int pwm) {
  s1.write(s1point0 - pwm);
  s2.write(s2point0 - pwm);
  delay(tempo);
}
void parar(int tempo){
  s1.write(s1point0);
  s2.write(s2point0);
  delay(tempo);
}

void desviarVerde(int value){
  contador=0;
  x=0;
  while(x==0){
    contador++;
    if(contador>7){
      tras(250, 30);
      contador=0;
    }
    digitalWrite(s2e, HIGH);
  digitalWrite(s3e, HIGH);
  digitalWrite(s2d, HIGH);
  digitalWrite(s3d, HIGH);
  //ler a frequência de saída
  verdeE = 4*pulseIn(oute, digitalRead(oute) == HIGH ? LOW : HIGH);
  verdeD = 4*pulseIn(outd, digitalRead(outd) == HIGH ? LOW : HIGH);
  
       if((verdeD > value) && (verdeE < value)){//Verde direito
      med1=1;
  }
  else if((verdeE > value) && (verdeD > value)){//verde esquerdo
      med1=2;
    }
    else if((verdeE > value) && (verdeD < value)){//verde esquerdo
      med1=3;
    }
    else if((value > verdeE)&&(value > verdeD)){//branco
      med1=4;
    }
    //frente(100,10);
    tras(50,40);
  //parar(500);
   //ligar os fotodiodos do sensor de cor verde
  digitalWrite(s2e, HIGH);
  digitalWrite(s3e, HIGH);
  digitalWrite(s2d, HIGH);
  digitalWrite(s3d, HIGH);
  //ler a frequência de saída
  verdeE = 4*pulseIn(oute, digitalRead(oute) == HIGH ? LOW : HIGH);
  verdeD = 4*pulseIn(outd, digitalRead(outd) == HIGH ? LOW : HIGH);
  
     if((verdeD > value) && (verdeE<value)){//Verde direito
      med2=1;
  }
  else if((verdeD > value) && (verdeE>value)){//Verde duplo
      med2=2;
  }
    else if((verdeE > value) && (verdeD<value)){//verde esquerdo
      med2=3;
    }
    else if((value > verdeE)&&(value > verdeD)){//branco
      med2=4;
    }
    frente(75, 30);
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(verdeE);
  lcd.setCursor(7,0);
  lcd.print(verdeD);
  /*Serial.print("cor esquerda: ");
  Serial.println(frequencyE);
  Serial.print("cor direita: ");
  Serial.print(frequencyD);*/
  lcd.setCursor(0,1);
  if(med1==1 && med2==1){
     // lcd.print(med1);
      //lcd.print(med2);
      lcd.print("direita");
      //parar(10000);
       direita(1000, 30);
       frente(200,50);
      x=1;
 }
  else if(med1==2 && med2==2){
  //  lcd.print(med1);
  //  lcd.print(med2);
   lcd.print("make rome great again");
  esquerda(2000, 30);
  frente(250,50);
    //parar(10000);
    x=1;
    }
    else if(med1==3 && med2==3){
  //  lcd.print(med1);
  //  lcd.print(med2);
   lcd.print("esquerda");
  esquerda(1000, 30);
  frente(200,50);
    //parar(10000);
    x=1;
    }
    else if(med1==4 && med2==4){
    //lcd.print(med1);
    //lcd.print(med2);
    frente(400,30);
    leitura1 = digitalRead(ls1p);
    leitura2 = digitalRead(ls2p);
    leitura3 = digitalRead(ls3p);
    leitura4 = digitalRead(ls4p);
    leitura5 = digitalRead(ls5p);
    if(leitura1 && leitura2 && leitura3 && leitura4 && leitura5){
      lcd.print("faixa");
      prata = true;
      frente(1000,50);
      direita(1000,50);
      //parar(10000);
    }
    else{
      frente(200,50);
    }
    //frente(5000, 100);
    x=1;
    }
  }
  }

void seguirLinha(){
  leitura1 = digitalRead(ls1p);
  leitura2 = digitalRead(ls2p);
  leitura3 = digitalRead(ls3p);
  leitura4 = digitalRead(ls4p);
  leitura5 = digitalRead(ls5p);
    frente(1,40);
  if (!leitura1 && !leitura2 && !leitura3 && !leitura4 && leitura5){
    direita(5,80);
  }
  else if (!leitura1 && !leitura2 && !leitura3 && leitura4 && leitura5){
    direita(5,60);
  }
  else if (!leitura1 && !leitura2 && !leitura3 && leitura4 && !leitura5){
    direita(5,40);
  }
  else if (!leitura1 && !leitura2 && leitura3 && leitura4 && !leitura5){
    direita(5,20);
  }
  else if (!leitura1 && !leitura2 && leitura3 && !leitura4 && !leitura5){
    frente(5,50);
  }
  else if (!leitura1 && leitura2 && leitura3 && !leitura4 && !leitura5){
    esquerda(10,20);
  }
  else if (!leitura1 && leitura2 && !leitura3 && !leitura4 && !leitura5){
    esquerda(10,40);
  }
  else if (leitura1 && leitura2 && !leitura3 && !leitura4 && !leitura5){
    esquerda(10,60);
  }
  else if (leitura1 && !leitura2 && !leitura3 && !leitura4 && !leitura5){
    esquerda(10,80);
  }
  else if (leitura1 && leitura2 && leitura3 && !leitura4 && !leitura5){
    esquerda(10,100);
  }
  else if(!leitura1 && !leitura2 && leitura3 && leitura4 && leitura5){
    direita(10,100);
  }
  else if(leitura1 && leitura2 && leitura3 && leitura4 && !leitura5){
    esquerda(10,100);
  }
  else if(!leitura1 && leitura2 && leitura3 && leitura4 && leitura5){
    direita(10,100);
  }
  else if(leitura1 && leitura2 && leitura3 && leitura4 && leitura5){
   frente(100,30);
   desviarVerde(parverde);
   //calibrarSensores(100);
  // parar(10000);
  }
  else if(leitura1 && leitura5){
   // parar(1000);
   direita(100,30);
   // desviarVerde(parverde);
  }
  else if(!leitura1 && !leitura2 && !leitura3 && !leitura4 && !leitura5){
    
  }
}

void desviar (){
  direita(900, 50);
  frente(1450, 20);
  esquerda(900, 50);
  frente(3000, 20);
  esquerda(500, 50);
  frente(1500, 20);
  calibrarSensores(10);
  while(!leitura5 && !leitura4){
    frente(10,100);
    calibrarSensores(10);
  }
  /*
  direita(1000, 50);
   s1.write(s1point0 + 10);
  s2.write(s2point0 - 200);
  delay(10000);*/
}

void detectarObj (){
  sensorToque = digitalRead(toquePin);
  if (sensorToque){
    seguirLinha();
    //frente(10,100);
  }
  else{
    if(!leitura1 && !leitura2 && !leitura3 && !leitura4 && !leitura5){
      prata = true;
    }
    else{
      tras(500,50);
      //parar(1000);
      desviar();
    }
  }
  
}
/*
void prata(){
  int x = analogRead(pinoprata);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(x);
  if(x>500 && x<700){
    frente(3000,100);
    parar(5000);
  }
  else{
    detectarObj();
  }
}
*/
void calibrarSensores(int tempo){
  leitura1 = digitalRead(ls1p);
  leitura2 = digitalRead(ls2p);
  leitura3 = digitalRead(ls3p);
  leitura4 = digitalRead(ls4p);
  leitura5 = digitalRead(ls5p);
  sensorToque = digitalRead(toquePin);
  digitalWrite(s2e, HIGH);
  digitalWrite(s3e, HIGH);
  digitalWrite(s2d, HIGH);
  digitalWrite(s3d, HIGH);
  verdeE = 4*pulseIn(oute, digitalRead(oute) == HIGH ? LOW : HIGH);
  verdeD = 4*pulseIn(outd, digitalRead(outd) == HIGH ? LOW : HIGH);
  Serial.print(leitura1);
  Serial.print(leitura2);
  Serial.print(leitura3);
  Serial.print(leitura4);
  Serial.println(leitura5);
  Serial.println(sensorToque);
  Serial.print(verdeE);
  Serial.print(" ");
  Serial.println(verdeD);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(leitura1);
  lcd.setCursor(1,0);
  lcd.print(leitura2);
  lcd.setCursor(2,0);
  lcd.print(leitura3);
  lcd.setCursor(3,0);
  lcd.print(leitura4);
  lcd.setCursor(4,0);
  lcd.print(leitura5);
  lcd.setCursor(0,1);
  lcd.print(verdeE);
  lcd.setCursor(7,1);
  lcd.print(verdeD);
  delay(tempo);
  //parar(2000);
}

float checkDistance1(){
  digitalWrite(trigger1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger1, LOW);
  duration1 = pulseIn(echo1, HIGH);
  distance1 = duration1*0.017;
  return distance1;
  }
float checkDistance2(){
  digitalWrite(trigger2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger2, LOW);
  duration2 = pulseIn(echo2, HIGH);
  distance2 = duration2*0.017;
  return distance2;
  }
int detectarDisparidade(){
 // int x = 0;

  float d1 = checkDistance1();
  delay(10);
  float d2 = checkDistance2();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(d1);
  lcd.setCursor(0,1);
  lcd.print(d2);
  if(d1 - d2 >= 4){
    //x++;
  /* direita(50,30);
    f(checkDistance2() - checkDistance1() >= 2){
      x++;
    }
   esquerda(100, 30);
    if(checkDistance2() - checkDistance1() >= 2) {
      x++;
    }*/
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("disp");
    Serial.println("disp");
    parar(2000);
    return 1;
  }
  else{
    Serial.println("ok");
      esquerda(50,50);
      
  }
  //return x;
}
void calibrarUltrassom(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(checkDistance1());
  lcd.setCursor(0,1);
  lcd.print(checkDistance2());
  delay(500);
}


void bolinha(){
  tras(200,50);
  direita(900, 100);
  parar(500);
  if(checkDistance1() > 23){
  sgarra.write((garradown+garraup)/2);
  delay(1000);
  sgarra.write(garradown);
  delay(1000);
  }
  while(checkDistance1() > 24){
    frente(50,50);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("esq");
  parar(500);
  sgarra.write((garradown+garraup)/2);
  delay(1000);
  sgarra.write(garraup);
  delay(4000);
  tras(500, 50);
  if(virarBolinha){
    direita(1300,30);
    virarBolinha = false;
  }
  else{
    esquerda(1300, 30);
    virarBolinha = true;
  }
  while((checkDistance1() - checkDistance2() < 5)){
    esquerda(10,30);
  }
  
  while(digitalRead(toquePin)){
    frente(50, 50);
  }
  if(checkDistance1() > 5){
    tras(1000,50);
    direita(2000,50);
    tras(500,50);
  }
  else{
    direita(1000,50);
  }
}
  
void loop() {
  if(prata){
    frente(1500,100);
    bolinha();
  }
  else{
 // calibrarSensores(500);
  //seguirLinha();
  //calibrarUltrassom();
  detectarObj();
  //bolinha();
  //prata();
  //frente(10,100);
  //parar(100);
  //desviar();
  //tras(10,50);
  //esquerda(10,20);
  //direita();
  //detectarDisparidade();
  }
}
