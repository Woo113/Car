#ifndef CAR_H
#define CAR_H

#include <Arduino.h>
#include <SoftwareSerial.h>

// 定義指令
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

class Control {
private:
    int left_IN1, left_IN2, left_pwm;
    int right_IN3, right_IN4, right_pwm;
    int sensorLeft, sensorRight, sensorCenter;
    SoftwareSerial BT;

public:
    Control();
    Control():BT(2,3){}
    void setup();
    void stop();
    void move();
    void turnLeft();
    void turnRight();
    void back();
    void search();
    void executeCommand(char command);
    void lineFollowing();
};

#endif//CAR_H
