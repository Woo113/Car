 #include <SoftwareSerial.h>

SoftwareSerial BT(2,3);
char a;
char b;
int right_IN3=9;
int right_IN4=11;
int right_pwm=12;
int left_IN1=13;
int left_IN2=4;
int left_pwm=10;

#define FORWARD 'F'
#define BACKWARD 'B'
#define LEFT 'L'
#define RIGHT 'R'
#define CIRCLE 'C'
#define CROSS 'X'
#define TRIANGLE 'T'
#define SQUARE 'S'
#define START 'A'
#define PAUSE 'P'

void setup() {
BT.begin(9600);
Serial.begin(9600);
  pinMode(5,INPUT);//左
  pinMode(7,INPUT);//右
  pinMode(8,INPUT);//中

  pinMode(4,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
}

void stop(){
  digitalWrite(left_IN1,LOW);
  digitalWrite(left_IN2,LOW);
  digitalWrite(right_IN3,LOW);
  digitalWrite(right_IN4,LOW);
  analogWrite(left_pwm,0);
  analogWrite(right_pwm,0); 
}//停

void move(){
  digitalWrite(left_IN1,HIGH);
  digitalWrite(left_IN2,LOW);
  digitalWrite(right_IN3,HIGH);
  digitalWrite(right_IN4,LOW);
  analogWrite(left_pwm,180);
  analogWrite(right_pwm,150);
}//動

void left(){
  digitalWrite(left_IN1,LOW);
  digitalWrite(left_IN2,LOW);
  digitalWrite(right_IN3,HIGH);
  digitalWrite(right_IN4,LOW);
  analogWrite(left_pwm,140);
  analogWrite(right_pwm,150);
}//左轉

void right(){
  digitalWrite(left_IN1,HIGH);
  digitalWrite(left_IN2,LOW);
  digitalWrite(right_IN3,LOW);
  digitalWrite(right_IN4,LOW);
  analogWrite(left_pwm,180);
  analogWrite(right_pwm,150);
}//右轉

void back(){
  digitalWrite(left_IN1,LOW);
  digitalWrite(left_IN2,HIGH);
  digitalWrite(right_IN3,LOW);
  digitalWrite(right_IN4,HIGH);
  analogWrite(left_pwm,180);
  analogWrite(right_pwm,150);
}//後退

 void search() {
  // 搜尋黑線邏輯
  for (int i = 0; i < 10; i++) {  // 向左找黑線
    left();
    delay(100);
    if (digitalRead(5) == 1 || digitalRead(8) == 1 || digitalRead(7) == 1) {
      return;  // 找到黑線就結束搜尋
    }
  }

  for (int i = 0; i < 10; i++) {  // 向右找黑線
    right();
    delay(100);
    if (digitalRead(5) == 1 || digitalRead(8) == 1 || digitalRead(7) == 1) {
      return;  // 找到黑線就結束搜尋
    }
  }
}

void excuteA(char a)
{
  switch(a)
  {
    case TRIANGLE:
    move();
    break;
    case BACKWARD:
    back();
    break;
    case LEFT:
    left();
    break;
    case RIGHT:
    right();
    break;
    default:
    stop();
    Serial.println("Unknown Command");
    break;
  }
}

void loop()
 {


if (Serial.available())
  {
    b=Serial.read();
    BT.print(b);
     
  }  

if (digitalRead(5) == 0 && digitalRead(7) == 0&&digitalRead(8)==1) {
    // 左右兩個感測器都偵測到 -> 停止
    move();
    delay(100);

  } 
if (digitalRead(5) == 1 && digitalRead(7) == 0) {
    // 右邊感測器偵測到黑線 -> 右轉
    stop();
    left();
    delay(100);
    stop();

  } 
if (digitalRead(5) == 0 && digitalRead(7) == 1) {
    // 左邊感測器偵測到黑線 -> 左轉
    stop();
    right();
    delay(100);
    stop();

  } 
if(digitalRead(5) == 0&&digitalRead(7) == 0&&digitalRead(8)==0){
  move();
}

if(digitalRead(5) == 1&&digitalRead(7) == 1){
    // 中間感測器偵測到黑線 -> 直行
    stop();
    while(true){
  if(BT.available()){
	a = BT.read();
	Serial.println(a);

  if (a ==TRIANGLE) {
      move();
    } else if (a== BACKWARD) {
      back();
    } else if (a == LEFT) {
      left();
    } else if (a == RIGHT) {
      right();
  
    } else {
      Serial.println("Unknown Command"); // 顯示未知指令
      stop(); // 停止小車
    }
} //讀取藍芽傳輸訊息
     }
  }

}