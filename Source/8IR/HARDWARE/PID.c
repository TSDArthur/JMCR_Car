#include "STC15.h"
#include "IO.h"
#include "MOTOR.h"
#include "SERVO.h"
#include "SENSOR.h"
#include "PID.h"

//PID Paras
float PID_KP;
float PID_KI;
float PID_KD;
int pid_e;
int pid_le;

//Data for Apply
u8 PID_ServoAngle = SERVO_MID_ANGLE;
int PID_LeftMotorPWM = MOTOR_MAX_PWM;
int PID_RightMotorPWM = MOTOR_MAX_PWM;

void PID_Setup(float kp, float ki, float kd)
{
	PID_KP = kp;
	PID_KI = ki;
	PID_KD = kd;
	pid_e = 0;
	pid_le = 0;
}

void PID_Calc(int sensorData)
{
	PID_LeftMotorPWM = MOTOR_MAX_PWM;
	PID_RightMotorPWM = MOTOR_MAX_PWM;
	pid_e = sensorData;
	PID_ServoAngle += (char)(PID_KP * (pid_e - pid_le) + PID_KI * pid_e);
	pid_le = pid_e;
	PID_ServoAngle = PID_ServoAngle > PID_MAX_ANGLE ? PID_MAX_ANGLE : (PID_ServoAngle < PID_MIN_ANGLE ? PID_MIN_ANGLE : PID_ServoAngle);
	//Motor Auto Suit
	PID_LeftMotorPWM -= absInt(PID_ServoAngle - SERVO_MID_ANGLE) / 2;
	PID_RightMotorPWM -= absInt(PID_ServoAngle - SERVO_MID_ANGLE) / 2;
}

