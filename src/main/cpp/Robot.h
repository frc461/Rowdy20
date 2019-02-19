/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "frc/WPILib.h"
#include <string>

#include <frc/TimedRobot.h>
#include <SmartDashboard/SendableChooser.h>
#include <ctre/Phoenix.h>
#include "THRSTMSTRmap.h"
#include "XboxJoystickMap.h"
#include "ElevatorPIDOutput.h"
#include "ElevatorPIDSource.h"
#include <sys/timeb.h>
#include <iostream>
#include "ButtonBox.h"

#define ELEVATOR_MAX 3150
#define ELEVATOR_MAX_BUFFER 2500
#define ELEVATOR_MIN 1
#define ELEVATOR_MIN_BUFFER 400
#define IRIS_VOL_MAX 1.9
#define IRIS_VOL_MIN 1.5
#define VOLTAGE_IN 5
#define PROGRAM_NUM 8
#define IRIS_SPEED 0.3
#define BallTower0_H 0
#define BallTower1_H 1558
#define BallTower2_H 3106
#define HatchTower0_H 418
#define HatchTower1_H 2080
#define HatchTower2_H 3310
#define V_MAX 1024
#define CURRENT_STRIKE 900

using namespace frc;

class Robot : public frc::TimedRobot {
public:
	void RobotInit() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestPeriodic() override;

private:
	frc::SendableChooser<std::string> m_chooser;
	const std::string kAutoNameDefault = "Default";
	const std::string kAutoNameCustom = "My Auto";
	std::string m_autoSelected;

	double elevatorJoystick();

	WPI_TalonSRX *RMotor0;
	WPI_VictorSPX *RMotor1;
	WPI_VictorSPX *RMotor2;

	WPI_TalonSRX *LMotor0;
	WPI_VictorSPX *LMotor1;
	WPI_VictorSPX *LMotor2;

	WPI_TalonSRX *Elevator0;
	WPI_VictorSPX *Elevator1;

	WPI_VictorSPX *Taco;
	frc::Solenoid *TacoPos;

	WPI_VictorSPX *Intake;
	frc::Solenoid *IntakePos;

	Joystick *leftJoystick;
	Joystick *rightJoystick;
	Joystick *operatingControl;
	Joystick *ButtonBox;

	SpeedControllerGroup *leftSide;
	SpeedControllerGroup *rightSide;
	SpeedControllerGroup *elevator;

	DifferentialDrive *driveTrain;

	DigitalInput *ElevatorDown;

	Encoder *ElevatorEncoder;

	frc::Solenoid *Iris;
	WPI_VictorSPX *IrisGrabber;

	frc::Solenoid *ClimberWedge1;

	WPI_TalonSRX *Climb0;
	WPI_VictorSPX *Climb1;

	PowerDistributionPanel *pdp;

	AnalogOutput *LEDHeight;

	AnalogOutput *LEDProgram;

	AnalogInput *IrisPot;

	nt::NetworkTableEntry *hudElevatorLimit;

	PIDController *ElevatorPID;

	ElevatorPIDOutput *elevatorPIDOutput;

	ElevatorPIDSource *elevatorPIDSource;

	int intakeBuffer;

	double elevatorSpeed;

	double ElevatorLimitCheck(double in);

	enum AnalogIO {
		IrisPott,
		LEDheight,
		LEDPrograms
	};

	enum DigitalIO {
		ElevateDown,
		ElevateEncoderA,
		ElevateEncoderB
	};

	enum CanChain {
		L_Motor0 = 1,
		L_Motor1,
		L_Motor2,
		R_Motor0,
		R_Motor1,
		R_Motor2,
		elevator0,
		elevator1,
		intake,
		taco,
		iris,
		Climb_0,
		Climb_1
	};

	enum Pneumatics {
		IrisP,
		TacoP,
		IntakeP,
		ClimberP1,
	
	};
};
