 //sensor de cor da direita
#define eS0 2
#define eS1 3
#define eS2 4
#define eS3 5
#define eOut 6 //saida do sensor

 //sensor de cor da esquerda
#define dS0 22
#define dS1 23
#define dS2 24
#define dS3 25
#define dOut 27 //saida do sensor
 
//motor da direita
int porta1 = 11; //negativo 
int porta2 = 10; //positivo

//motor da esquerda
int porta3 = 9; //negativo
int porta4 = 8; //positivo

//sensor de ultrassom
int portaB = 30; //echo (receptor)
int portaA = 31; //trigger (emissor)

//sensores de refletancia
int irDir = 42; //direita
int irEsq = 43; //esquerda

int pwm = 70; //regulador da potencia dos motores
int eFrequency = 0; //variavel para o nivel de verde no sensor da esquerda
int dFrequency = 0; //variavel para o nivel de verde no sensor da direita
long t; //variavel relativa ao tempo do echo do sensor de ultrassom
int d; //variavel relativa a distancia do robo a um objeto

//int status_robo = 

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

//variavel relativa a distancia do robo a um obstaculo
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

//variavel que indica o nivel de verde em baixo do sensor de cor da esquerda
float eVerde(){
  digitalWrite(eS2,HIGH);
  digitalWrite(eS3,HIGH);
  eFrequency = pulseIn(eOut, LOW);
  return eFrequency;
}

//variavel que indica o nivel de verde em baixo do sensor de cor da direita
float dVerde(){
  digitalWrite(dS2,HIGH);
  digitalWrite(dS3,HIGH);
  dFrequency = pulseIn(dOut, LOW);
  return dFrequency;
}

//funcao para desligar o robo
void desligar(int time=0){
  digitalWrite(porta1,LOW);
  digitalWrite(porta2, LOW);
  digitalWrite(porta3, LOW);
  digitalWrite(porta4,LOW);
  delay(time);
}

//funcao para frear o robo
void frear(int time=0){
  analogWrite(porta1,pwm);
  analogWrite(porta2, pwm);
  analogWrite(porta3, pwm);
  analogWrite(porta4,pwm);
  delayMicroseconds(time);
}

//funcao para andar para tras
void andarTras(int time=0){
  Serial.println("Dando ré");  
  analogWrite(porta1, pwm);
  digitalWrite(porta2,LOW);
  analogWrite(porta3, pwm+15);
  digitalWrite(porta4,LOW);
  delay(time);
}

//funcao para andar para frente
void andarFrente(int time=0){
  Serial.println("Andando para a frente");  
  digitalWrite(porta1,LOW);
  analogWrite(porta2, pwm);
  digitalWrite(porta3,LOW);
  analogWrite(porta4, pwm+15);
  delay(time); 
}

//funcao para girar para a direita
void girarEsquerda(int time=0){
  Serial.println("Girando para a direita");      
  digitalWrite(porta1,LOW);
  analogWrite(porta2, pwm);
  analogWrite(porta3, pwm+15);
  digitalWrite(porta4,LOW);
  delay(time);
}

 //funcao para girar para a esquerda
void girarDireita(int time=0){
  Serial.println("Girando para a esquerda");  
  analogWrite(porta1,pwm);
  digitalWrite(porta2, LOW);
  digitalWrite(porta3, LOW);
  analogWrite(porta4,pwm+15);
  delay(time);
}

//funcao para girar para o lado com o quadrado verde 
void verde(float dirverde, float esqverde){
  if((dirverde > 100) && (esqverde < 100)){
    girarDireita(100);
  }
  else if ((dirverde < 100) && (esqverde > 100)){
    girarDireita(100);
  }
}

 //funcao para desviar de um obstaculo
void desviar(){
   girarDireita(500);
   andarFrente(1200);
   girarEsquerda(400);
   andarFrente(1200);
   girarEsquerda(400);
   andarFrente(1200); 
   girarDireita(200);   
}

void desviar2(){
  girarDireita(425);
  while (!detectarLinha(irDir) || !detectarLinha(irEsq)){
  digitalWrite(porta1,LOW);
  analogWrite(porta2, pwm/3);
  digitalWrite(porta3,LOW);
  analogWrite(porta4, pwm);  
  }
}

 //funcao para seguir a linha preta no chao
void seguirLinha(){
    if (!detectarLinha(irDir)&& !detectarLinha(irEsq)){
       andarFrente(1);
       Serial.print ("frente");
  }
    else if (detectarLinha(irDir)&& !detectarLinha(irEsq)){
        girarDireita(1);
        Serial.print ("direita");
        }
        
    else if(!detectarLinha(irDir)&& detectarLinha(irEsq)){   
        girarEsquerda(1);
        Serial.print ("esquerda");
        }
        
    else if(detectarLinha(irDir)&& detectarLinha(irEsq)){
       //frear(10); 
       desligar(10);   
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

  //ativacao dos sensores de cor
  digitalWrite(eS0,HIGH);
  digitalWrite(eS1,LOW);  
  digitalWrite(dS0,HIGH);
  digitalWrite(dS1,LOW);

  //aumentando a frequência dos interruptores das portas 9 a 12 do Arduino para 31kHz
  TCCR1B |= 1;
  TCCR2B |= 1;  
}

void loop() {
  /*while (pegarDistancia()>15){  //se a distancia do robo a um objeto for maior que 15 cm...
    while ((dVerde() < 100) && (eVerde() < 100)){  //se nao houver a presenca da cor verde em baixo de ambos os sensores de cor...
      seguirLinha(); 
    }
    verde(dVerde(),eVerde()); //se houver a cor verde  
  }
  desviar(); //se a distancia do robo a um obstaculo for menor que 15 cm */
  
}
