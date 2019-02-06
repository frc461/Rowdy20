/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <SmartDashboard/SmartDashboard.h>

float MaxEncHeight;

double vIncrement = ((MaxEncHeight-0)/(VOLTAGE_IN-0))/PROGRAM_NUM;

void Robot::RobotInit() {

	leftJoystick = new Joystick(0);
	rightJoystick = new Joystick(1);
	operatingControl = new Joystick(2);

	RMotor0 = new WPI_TalonSRX(CanChain::R_Motor0);
	RMotor1 = new WPI_VictorSPX(CanChain::R_Motor1);
	RMotor2 = new WPI_VictorSPX(CanChain::R_Motor2);

	LMotor0 = new WPI_TalonSRX(CanChain::L_Motor0);
	LMotor1 = new WPI_VictorSPX(CanChain::L_Motor1);
	LMotor2 = new WPI_VictorSPX(CanChain::L_Motor2);

	Elevator0 = new WPI_TalonSRX(CanChain::elevator0);
	Elevator1 = new WPI_VictorSPX(CanChain::elevator1);

	ElevatorTop = new DigitalInput(ElevateTop);
	ElevatorBottom = new DigitalInput(ElevateBottom);

	Taco = new WPI_TalonSRX(CanChain::taco);
	TacoPos = new DoubleSolenoid(TacoA, TacoB);

	Intake = new WPI_VictorSPX(CanChain::intake);
	IntakePos = new DoubleSolenoid(IntakeA, IntakeB);

	Iris = new DoubleSolenoid(IrisA, IrisB);

	rightSide = new SpeedControllerGroup(*RMotor0,*RMotor1,*RMotor2);
	leftSide = new SpeedControllerGroup(*LMotor0, *LMotor1, *LMotor2);
	elevator = new SpeedControllerGroup(*Elevator0, *Elevator1);

	driveTrain = new DifferentialDrive(*rightSide, *leftSide);

	ElevatorEncoder = new Encoder(ElevateEncoderA, ElevateEncoderB, false, Encoder::EncodingType::k4X);
	ElevatorEncoder->Reset();

	pdp = new PowerDistributionPanel();
}

void Robot::AutonomousInit() {
}
void Robot::AutonomousPeriodic() {
}
void Robot::TeleopInit() {
}

void Robot::TeleopPeriodic() {
	frc::SmartDashboard::PutNumber("Rate of Elevator Encoder(units/sec)", ElevatorEncoder->GetRate());

	driveTrain->ArcadeDrive(rightJoystick->GetRawAxis(yAxisJS), leftJoystick->GetRawAxis(xAxisJS));

	std::cout << "Elevator Encoder MAX: " << ElevatorEncoder->Get() << std::endl;

	elevator->Set(operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisRightStickY));
	if (ElevatorTop->Get() && operatingControl->GetRawAxis(XboxAxisRightStickY) > 0)
	{
		elevator->Set(0);
	}
	else if (ElevatorBottom->Get() && operatingControl->GetRawAxis(XboxAxisRightStickY) < 0)
	{
		elevator->Set(0);
	}
	if (ElevatorEncoder->Get() >= ELEVATOR_MAX )
	{
		elevator->Set(0);
	}
	else if (ElevatorEncoder->Get() <= ELEVATOR_MIN)
	{
		elevator->Set(0);
	}
	if (ElevatorEncoder->Get() >= ELEVATOR_MAX/2 )
	{
		elevator->Set((operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisRightStickY))*0.5);
	}

	if (operatingControl->GetRawButton(XboxJoystickButton::XboxButtonLeftBumper)) {
		Taco->Set(0.75);
	}
	else if (operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisLeftTrigger)>0.3) {
		Taco->Set(-0.75);
	}
	else {
		Taco->Set(0);
	}

	if (operatingControl->GetRawButton(XboxButtonY))
	{
		TacoPos->Set(DoubleSolenoid::kForward);
	}
	else if (operatingControl->GetRawButton(XboxButtonA))
	{
		TacoPos->Set(DoubleSolenoid::kReverse);
	}

	if (operatingControl->GetRawButton(XboxButtonX))
	{
		Iris->Set(DoubleSolenoid::kForward);
	}
	else if (operatingControl->GetRawButton(XboxButtonB))
	{
		Iris->Set(DoubleSolenoid::kReverse);
	}

	if (operatingControl->GetRawButton(XboxButtonBack))
	{
		IntakePos->Set(DoubleSolenoid::kForward);
	}
	if (operatingControl->GetRawButton(XboxButtonStart))
	{
		IntakePos->Set(DoubleSolenoid::kReverse);
	}


	if (operatingControl->GetRawButton(XboxJoystickButton::XboxButtonRightBumper)) {
			Intake->Set(0.75);
		}
		else if (operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisRightTrigger)>0.3) {
			Intake->Set(-0.75);
		}
		else {
			Intake->Set(0);
		}

	std::cout << pdp->GetCurrent(1) << std::endl;

}

void Programs()
{

}



void Robot::TestPeriodic() {}

START_ROBOT_CLASS(Robot)
