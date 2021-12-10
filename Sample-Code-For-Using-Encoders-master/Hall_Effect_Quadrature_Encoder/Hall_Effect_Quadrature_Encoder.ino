/* Geared DC motor with Hall Effect Quadrature Encoder 
 * L298N Motor Driver
 * 
 * Wiring:
 * VCC -> 5V
 * GND -> GND
 * OUT A -> D2 
 * OUT B -> D3 
 * M1 -> Motor Driver A
 * M2 -> Motor Driver B
 * Motor Driver Input 1 -> 10
 * Motor Driver Input 2 -> 11
 */     
 
#define encoderA 2    //for encoder A phase
#define encoderB 3     //for encoder B phase
#define motorA 10      //input 1 of motor driver
#define motorB 11      //input 2 of motor driver
#define speede 9       //enable1 of motor driver

volatile int countA = 0;
volatile int countB = 0;
int Dir = 0;  // 1 = CW
              // 0 = Stationary
              // -1 = CCW

void setup() {
  Serial.begin(9600);
  pinMode(encoderA, INPUT);
  pinMode(encoderB, INPUT);
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
  pinMode(speede,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(encoderA), pulseA, RISING);
  attachInterrupt(digitalPinToInterrupt(encoderB), pulseB, RISING);
  digitalWrite(motorA, HIGH);
  digitalWrite(motorB, LOW);
  analogWrite(speede,100);

}
void loop() {
  Serial.print(digitalRead(encoderA));      // uncomment to see squarewave output
  Serial.print('\t');
  Serial.print(digitalRead(encoderB)+2);    // +2 shifts output B up so both A and B are visible 
  Serial.print('\t');
  Serial.print(Dir);
  Serial.print('\t');
  Serial.print(countA);
  Serial.print('\t');
  Serial.print(countB);
  Serial.println();  
}

void checkDirection(){
  if(digitalRead(encoderB) ==  HIGH){                             
    Dir = 1;  
  }
  else{
    Dir = -1;
  }
}

void pulseA(){  
  checkDirection();
  countA += Dir;
}

void pulseB(){  
  countB += Dir;
}
