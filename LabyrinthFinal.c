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
	Motor[frontLeftMotor] = a;
  motor[frontRightMotor] = b;
  motor[backRightMotor] = c;
  motor[backLeftMotor] = d;
}

/*
	Function to go forward an amount of inches
	Negative distance values go backwards
	float rightSideSpeedFactor is a compensation value to make sure the robot goes straight.
	It sets the speed of the right side to a factor of the speed of the left side.
	For no compensation, rightSideSpeedFactor should be equal to 1.0
*/
void goInches(int inches, float rightSideSpeedFactor) {
	// constant distance compensation value to calibrate the measurement
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

/*
	Function to do a right turn
	float angleComp is a compensation value to calibrate the turn angle
	For no compensation, angleComp should be equal to 1.0
*/
void rightTurn(float angleComp) {
  SensorValue[rightEncoder] = 0;
  SensorValue[leftEncoder] = 0;
	 while((SensorValue[leftEncoder] < 227*angleComp) && (SensorValue[rightEncoder] > -227*angleComp)){
	   	multipleMotors(63,-63,-63,63);
	 }
   multipleMotors(0,0,0,0);
}

// main task
task main() {
	// go 25 inches
	goInches(25, 1);
	// wait 2 seconds
	wait1Msec(2000);
	// right turn
	rightTurn(1);
	// wait 2 seconds
	wait1Msec(2000);

	// go 30 inches backwards
	// right side compensation factor 0.8
	goInches(-30,0.8);
	// wait 2 seconds
	wait1Msec(2000);
	// right turn
	// angle compensation factor 0.94
	rightTurn(0.94);
	// wait 2 seconds
	wait1Msec(2000);

	// go 18 inches backwards
	goInches(-18,1);
	// wait 2 seconds
	wait1Msec(2000);
	// right turn
	// angle compensation factor 0.95
	rightTurn(0.95);
	// wait 2 seconds
	wait1Msec(2000);
	// go 12 inches backwards
	goInches(-12,1);

	// END
}
