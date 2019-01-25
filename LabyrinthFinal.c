/*
		LabyrinthFinal.c
		Written by Ryan Davis on 1/25/19
*/

#pragma config(Sensor, dgtl1,  leftEncoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,         sensorQuadEncoder)
#pragma config(Motor,  port2,           frontLeftMotor, tmotorNormal, openLoop)
#pragma config(Motor,  port3,           frontRightMotor, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4,           backLeftMotor, tmotorNormal, openLoop)
#pragma config(Motor,  port5,           backRightMotor, tmotorNormal, openLoop, reversed)

void multipleMotors(int a, int b, int c, int d) {
	motor[frontLeftMotor] = a;
  motor[frontRightMotor] = b;
  motor[backRightMotor] = c;
  motor[backLeftMotor] = d;
}

void goInches(int inches, float rightSideSpeedFactor) {
	const float distComp = 1.6;
	int rot = inches/15.70796*360/2*distComp;
	SensorValue[rightEncoder] = 0;
  SensorValue[leftEncoder] = 0;
	if (inches > 0) {
		 while(SensorValue[leftEncoder]+SensorValue[rightEncoder] < rot*2) {
				multipleMotors(63,63*rightSideSpeedFactor,63*rightSideSpeedFactor,63);
		}
	} else {
		while(SensorValue[leftEncoder]+SensorValue[rightEncoder] > rot*2) {
				multipleMotors(-63,-63*rightSideSpeedFactor,-63*rightSideSpeedFactor,-63);
		}
	}
	multipleMotors(0,0,0,0);
}

void rightTurn(float comp) {
  SensorValue[rightEncoder] = 0;
  SensorValue[leftEncoder] = 0;
	 while((SensorValue[leftEncoder] < 227*comp) && (SensorValue[rightEncoder] > -227*comp)){
	   	multipleMotors(63,-63,-63,63);
	 }
   multipleMotors(0,0,0,0);
}

task main() {
	goInches(25, 1);
	wait1Msec(2000);
	rightTurn(1);
	wait1Msec(2000);

	goInches(-30,0.8);
	wait1Msec(2000);
	rightTurn(0.94);
	wait1Msec(2000);

	goInches(-18,1);
	wait1Msec(2000);
	rightTurn(0.95);
	wait1Msec(2000);
	goInches(-12,1);
}
