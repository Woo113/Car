#include "car.h"

Control::Control() {
    left_IN1 = 13;
    left_IN2 = 4;
    left_pwm = 10;
    right_IN3 = 9;
    right_IN4 = 11;
    right_pwm = 12;
    sensorLeft = 5;
    sensorRight = 7;
    sensorCenter = 8;
}

void Control::setup() {
    BT.begin(9600);
    Serial.begin(9600);
    pinMode(sensorLeft, INPUT);
    pinMode(sensorRight, INPUT);
    pinMode(sensorCenter, INPUT);

    pinMode(left_IN1, OUTPUT);
    pinMode(left_IN2, OUTPUT);
    pinMode(left_pwm, OUTPUT);
    pinMode(right_IN3, OUTPUT);
    pinMode(right_IN4, OUTPUT);
    pinMode(right_pwm, OUTPUT);
}

void Control::stop() {
    digitalWrite(left_IN1, LOW);
    digitalWrite(left_IN2, LOW);
    digitalWrite(right_IN3, LOW);
    digitalWrite(right_IN4, LOW);
    analogWrite(left_pwm, 0);
    analogWrite(right_pwm, 0);
}

void Control::move() {
    digitalWrite(left_IN1, HIGH);
    digitalWrite(left_IN2, LOW);
    digitalWrite(right_IN3, HIGH);
    digitalWrite(right_IN4, LOW);
    analogWrite(left_pwm, 180);
    analogWrite(right_pwm, 150);
}

void Control::turnLeft() {
    digitalWrite(left_IN1, LOW);
    digitalWrite(left_IN2, LOW);
    digitalWrite(right_IN3, HIGH);
    digitalWrite(right_IN4, LOW);
    analogWrite(left_pwm, 140);
    analogWrite(right_pwm, 150);
}

void Control::turnRight() {
    digitalWrite(left_IN1, HIGH);
    digitalWrite(left_IN2, LOW);
    digitalWrite(right_IN3, LOW);
    digitalWrite(right_IN4, LOW);
    analogWrite(left_pwm, 180);
    analogWrite(right_pwm, 150);
}

void Control::back() {
    digitalWrite(left_IN1, LOW);
    digitalWrite(left_IN2, HIGH);
    digitalWrite(right_IN3, LOW);
    digitalWrite(right_IN4, HIGH);
    analogWrite(left_pwm, 180);
    analogWrite(right_pwm, 150);
}

void Control::search() {
    for (int i = 0; i < 10; i++) { 
        turnLeft();
        delay(100);
        if (digitalRead(sensorLeft) == 1 || digitalRead(sensorCenter) == 1 || digitalRead(sensorRight) == 1) {
            return;
        }
    }
    for (int i = 0; i < 10; i++) {
        turnRight();
        delay(100);
        if (digitalRead(sensorLeft) == 1 || digitalRead(sensorCenter) == 1 || digitalRead(sensorRight) == 1) {
            return;
        }
    }
}

void Control::executeCommand(char command) {
    switch (command) {
        case TRIANGLE:
            move();
            break;
        case BACKWARD:
            back();
            break;
        case LEFT:
            turnLeft();
            break;
        case RIGHT:
            turnRight();
            break;
        default:
            stop();
            Serial.println("Unknown Command");
            break;
    }
}

void RobotControl::lineFollowing() {
    if (digitalRead(sensorLeft) == 0 && digitalRead(sensorRight) == 0 && digitalRead(sensorCenter) == 1) {
        move();
        delay(100);
    } else if (digitalRead(sensorLeft) == 1 && digitalRead(sensorRight) == 0) {
        stop();
        turnLeft();
        delay(100);
        stop();
    } else if (digitalRead(sensorLeft) == 0 && digitalRead(sensorRight) == 1) {
        stop();
        turnRight();
        delay(100);
        stop();
    } else if (digitalRead(sensorLeft) == 0 && digitalRead(sensorRight) == 0 && digitalRead(sensorCenter) == 0) {
        move();
    } else if (digitalRead(sensorLeft) == 1 && digitalRead(sensorRight) == 1) {
        stop();
        while (true) {
            if (BT.available()) {
                char command = BT.read();
                Serial.println(command);
                executeCommand(command);
            }
        }
    }
}
