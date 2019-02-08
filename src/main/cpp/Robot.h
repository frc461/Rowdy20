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

#define ELEVATOR_MAX 100
#define ELEVATOR_MIN 0
#define VOLTAGE_IN 5
#define PROGRAM_NUM 8

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

	SpeedControllerGroup *leftSide;
	SpeedControllerGroup *rightSide;
	SpeedControllerGroup *elevator;

	DifferentialDrive *driveTrain;

	DigitalInput *ElevatorTop;
	DigitalInput *ElevatorBottom;

	Encoder *ElevatorEncoder;

	frc::Solenoid *Iris;
	WPI_VictorSPX *IrisGrabber;
	AnalogInput *IrisSensor;

	frc::Solenoid *Climber;

	PowerDistributionPanel *pdp;

	AnalogOutput *LEDHeight;

	AnalogOutput *LEDProgram;

	enum AnalogIO {
		IrisSense,
		LEDheight,
		LEDPrograms
	};

	enum DigitalIO {
		ElevateTop,
		ElevateBottom,
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
		iris
	};

	enum Pneumatics {
		IrisP,
		TacoP,
		IntakeP,
		ClimberP
	};
};
