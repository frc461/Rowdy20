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

	Taco = new WPI_VictorSPX(CanChain::taco);
	TacoPos = new Solenoid(TacoP);

	Intake = new WPI_VictorSPX(CanChain::intake);
	IntakePos = new Solenoid(IntakeP);

	Iris = new Solenoid(IrisP);
	IrisGrabber = new WPI_VictorSPX(iris);
	IrisSensor = new AnalogInput(IrisSense);

	LEDHeight = new AnalogOutput(LEDheight);
	LEDProgram = new AnalogOutput(LEDPrograms);

	Climber = new Solenoid(ClimberP);

	rightSide = new SpeedControllerGroup(*RMotor0,*RMotor1,*RMotor2);
	leftSide = new SpeedControllerGroup(*LMotor0, *LMotor1, *LMotor2);
	elevator = new SpeedControllerGroup(*Elevator0, *Elevator1);

	driveTrain = new DifferentialDrive(*rightSide, *leftSide);

	ElevatorEncoder = new Encoder(ElevateEncoderA, ElevateEncoderB, false, Encoder::EncodingType::k4X);
	ElevatorEncoder->Reset();

	// pdp = new PowerDistributionPanel();
}

void Robot::AutonomousInit() {
}
void Robot::AutonomousPeriodic() {
}
void Robot::TeleopInit() {
}

void Robot::TeleopPeriodic() {

	frc::SmartDashboard::PutNumber("Rate of Elevator Encoder(units/sec)", ElevatorEncoder->GetRate());

	driveTrain->ArcadeDrive(-rightJoystick->GetRawAxis(yAxisJS), leftJoystick->GetRawAxis(xAxisJS));

	//std::cout << "Elevator Encoder MAX: " << ElevatorEncoder->Get() << std::endl;

	elevator->Set(operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisRightStickY)*0.5-0.1);
	
	if (operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisRightStickY) < 0 && ElevatorEncoder->Get()/ELEVATOR_MAX < 0.1 && TacoPos->Get() == false)
	{
		Taco->Set(0.75);
	}
	/*if (ElevatorTop->Get() && operatingControl->GetRawAxis(XboxAxisRightStickY) > 0)
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
	}*/

	if (operatingControl->GetRawButton(XboxJoystickButton::XboxButtonLeftBumper)) {
		Taco->Set(0.75);
	}
	else if (operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisLeftTrigger)>0.3) {
		Taco->Set(-0.75);
	}
	else {
		Taco->Set(0);
	}

	if (operatingControl->GetRawButton(XboxButtonA))
	{
		IntakePos->Set(true);
		TacoPos->Set(true);
	}
	else if (operatingControl->GetRawButton(XboxButtonY))
	{
		TacoPos->Set(false);
	}

	if (operatingControl->GetRawButton(XboxButtonX) && IntakePos->Get() == false)
	{
		Iris->Set(true);
	}
	else if (operatingControl->GetRawButton(XboxButtonB))
	{
		Iris->Set(false);
	}
	if (!(operatingControl->GetRawButton(XboxButtonX) && Iris->Get() == true))
	{
		Iris->Set(false);
	}

	if (operatingControl->GetRawButton(XboxButtonBack))
	{
		TacoPos->Set(true);
		//IntakePos->Set(true);
	}
	if (operatingControl->GetRawButton(XboxButtonStart))
	{
		IntakePos->Set(false);
	}

	if (operatingControl->GetRawButton(XboxJoystickButton::XboxButtonRightBumper)) {
		Intake->Set(1);
	}
	else if (operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisRightTrigger)>0.3) {
		IntakePos->Set(true);
		Intake->Set(-0.75);
	}
	else {
		IntakePos->Set(false);
		Intake->Set(0);
	}

	if(IntakePos->Get()){
		std::cout << "intake down";
	}

	IrisGrabber->Set(operatingControl->GetRawAxis(XboxAxisLeftStickX));
	std::cout << "Iris Sensor: " << IrisSensor->GetVoltage() << std::endl;

	// std::cout << pdp->GetCurrent(1) << std::endl;

	//LED routine
	LEDHeight->SetVoltage((ElevatorEncoder->Get()/ELEVATOR_MAX) * 5);

	if (ElevatorEncoder->Get()/ELEVATOR_MAX >= 0.98) {
		LEDProgram->SetVoltage(5);
	}
}

void Robot::TestPeriodic() {}

START_ROBOT_CLASS(Robot)
