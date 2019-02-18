/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"


#include <SmartDashboard/SmartDashboard.h>
float MaxEncHeight;

double vIncrement = ((MaxEncHeight-0)/(VOLTAGE_IN-0))/PROGRAM_NUM;

std::shared_ptr<NetworkTable> ntHud;

void Robot::RobotInit() {

	elevatorSpeed = 1;

	TacoCurrentRead = new PowerDistributionPanel(0);
	IntakeCurrentRead = new PowerDistributionPanel(1);

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

	ElevatorDown = new DigitalInput(ElevateDown);

	ElevatorEncoder = new Encoder(ElevateEncoderA, ElevateEncoderB, false, Encoder::EncodingType::k4X);
	ElevatorEncoder->Reset();

	Taco = new WPI_VictorSPX(CanChain::taco);
	TacoPos = new Solenoid(TacoP);

	Intake = new WPI_VictorSPX(CanChain::intake);
	IntakePos = new Solenoid(IntakeP);

	Climb0 = new WPI_TalonSRX(CanChain::Climb_0);
	Climb1 = new WPI_VictorSPX(CanChain::Climb_1);

	Climb1->Follow(*Climb0);

	Iris = new Solenoid(IrisP);
	IrisGrabber = new WPI_VictorSPX(iris);
	IrisPot = new AnalogInput(IrisPott);

	LEDHeight = new AnalogOutput(LEDheight);
	LEDProgram = new AnalogOutput(LEDPrograms);

	Climber = new Solenoid(ClimberP);

	rightSide = new SpeedControllerGroup(*RMotor0,*RMotor1,*RMotor2);
	leftSide = new SpeedControllerGroup(*LMotor0, *LMotor1, *LMotor2);
	elevator = new SpeedControllerGroup(*Elevator0, *Elevator1);

	driveTrain = new DifferentialDrive(*rightSide, *leftSide);

	ntHud = nt::NetworkTableInstance::GetDefault().GetTable("hud");

	Elevator1->Follow(*Elevator0);

	Elevator0->SetSelectedSensorPosition(0,0);

	// PIDOutput elevatorPidOutpu\t;

	elevatorPIDSource = new ElevatorPIDSource();
	elevatorPIDOutput = new ElevatorPIDOutput();

	ElevatorPID = new PIDController(0.2, 0.1, 0.0, elevatorPIDSource, elevatorPIDOutput, 0.05);
	ElevatorPID->SetContinuous(true);
	ElevatorPID->SetOutputRange(-1, 1);

	ElevatorPID->SetSetpoint(0);

	ElevatorPID->Enable();

	// Elevator0->SelectProfileSlot(0);
	// Elevator0->SetPID(1000, 0, 0, 0);

	// hudElevatorLimit = ntHud->GetEntry("elevatorLimit");

	// pdp = new PowerDistributionPanel();
}

void Robot::AutonomousInit() {
}
void Robot::AutonomousPeriodic() {
}
void Robot::TeleopInit() {
	intakeBuffer = frc::GetTime();
}

void Robot::TeleopPeriodic() {

	frc::SmartDashboard::PutNumber("Rate of Elevator Encoder(units/sec)", ElevatorEncoder->GetRate());

	driveTrain->ArcadeDrive(-rightJoystick->GetRawAxis(yAxisJS), leftJoystick->GetRawAxis(xAxisJS));

	//Elevator Movement
	// elevator->Set((operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisRightStickY)*0.5-0.1) * ((operatingControl->GetRawAxis(XboxAxisRightStickY) > 0) ?  ElevatorDown->Get() : 1));
	
	if (operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisLeftStickY) < 0 && ElevatorEncoder->Get()/ELEVATOR_MAX < 0.1 && TacoPos->Get() == false)
	{
		Taco->Set(0.75);
	}

	if(operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisLeftStickY) > 0.2 && Elevator0->GetSelectedSensorPosition() <= ELEVATOR_MIN_BUFFER){
		std::cout << "Slow Elevator" << std::endl;
		elevatorSpeed = Elevator0->GetSelectedSensorPosition()/ELEVATOR_MIN_BUFFER + 0.2;
	} else if(operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisLeftStickY) < 0.2 && Elevator0->GetSelectedSensorPosition() >= ELEVATOR_MAX_BUFFER) {
		elevatorSpeed = Elevator0->GetSelectedSensorPosition()/ELEVATOR_MAX_BUFFER + 0.2;
	}
	else{
		elevatorSpeed = 1;
	}

	//Reset Elevator Encoder on Limit Switch
	// if(!ElevatorDown->Get()){
	// 	Elevator0->SetSelectedSensorPosition(0,0);
	// }

	if(rightJoystick->GetRawButton(ThrustJoystickButtons::topRightRight)){
		Elevator0->SetSelectedSensorPosition(0,0);
	}

	elevatorPIDSource->Set(Elevator0->GetSelectedSensorPosition());


	// Elevator Max Limit
	// if (Elevator0->GetSelectedSensorPosition() >= ELEVATOR_MAX && operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisLeftStickY) < 0.2)
	// {
	// 	elevator->Set(0);
	// }
	// //Elevator Min Limit
	// else if (Elevator0->GetSelectedSensorPosition() <= ELEVATOR_MIN && operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisLeftStickY) > 0.2)
	// {
	// 	// std::cout << "Stop down" << std::endl;
	// 	elevator->Set(0);
	// } else if(rightJoystick->GetRawButton(ThrustJoystickButtons::topRightMiddle)){
	// 	elevator->Set(operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisLeftStickY)*0.5-0.1);
	// } else 	  else {
	// 	// std::cout << "Default Value" << std::endl;
	// 	
	// }

	if(leftJoystick->GetRawButton(ThrustJoystickButtons::topRightRight)){
		std::cout << "Thing" << std::endl;
		ElevatorPID->SetSetpoint(1358);
	}

	// else {
		// Elevator0->Set((operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisLeftStickY)*0.5-0.1) * elevatorSpeed * ((operatingControl->GetRawAxis(XboxAxisLeftStickY) > 0) ?  ElevatorDown->Get() : 1));
	// }


	//Robot speed reduction according to levator height
	// if (ElevatorEncoder->Get() >= ELEVATOR_MAX/2 )
	// {
	// 	elevator->Set((operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisRightStickY))*0.5);
	// }
	// Taco spit
	if (operatingControl->GetRawButton(XboxJoystickButton::XboxButtonLeftBumper)) {
		Taco->Set(0.75);
	}
	// Taco in
	else if (operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisLeftTrigger)>0.3) {
		Taco->Set(-0.75);
	}
	else {
		Taco->Set(0);
	}

	// Taco position up
	if (operatingControl->GetRawButton(XboxButtonA))
	{
		// IntakePos->Set(true);
		TacoPos->Set(true);
	}
	// Taco position down
	else if (operatingControl->GetRawButton(XboxButtonY))
	{
		TacoPos->Set(false);
	}

	// && IntakePos->Get() == false

	// Iris push
	if (operatingControl->GetRawButton(XboxButtonX) )
	{
		Iris->Set(true);
	}else {
		Iris->Set(false);
	}
	// // Iris retract
	// else if (operatingControl->GetRawButton(XboxButtonB))
	// {
	// 	Iris->Set(false);
	// }
	// Iris retract
	// if (!(operatingControl->GetRawButton(XboxButtonX) && Iris->Get() == true))
	// {
	// 	Iris->Set(false);
	// }

	// Intake position down
	if (operatingControl->GetRawButton(XboxButtonBack))
	{
		TacoPos->Set(true);
		IntakePos->Set(true);
	}else if(operatingControl->GetRawButton(XboxButtonStart)){
		IntakePos->Set(false);
	}
	// // Intake position up
	// if (operatingControl->GetRawButton(XboxButtonStart))
	// {
	// 	IntakePos->Set(false);
	// }

	// Intake spit
	if (operatingControl->GetRawButton(XboxJoystickButton::XboxButtonRightBumper)) {
		Intake->Set(1);
	}
	// Intake in
	else if (operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisRightTrigger)>0.3) {
		Intake->Set(-0.75);
		intakeBuffer = frc::GetTime();
	}
	else {
		if (frc::GetTime() >= intakeBuffer + 3000){
			Intake->Set(-0.5);
		}
		else {
			Intake->Set(0);
		}
	}

	
    
	// Iris in 
	if (IrisPot->GetVoltage() > IRIS_VOL_MIN && operatingControl->GetRawAxis(XboxAxisRightStickX) < -0.3)
	{
		IrisGrabber->Set(operatingControl->GetRawAxis(XboxAxisRightStickX) * IRIS_SPEED);
	}
	// Iris out
	else if (IrisPot->GetVoltage() < IRIS_VOL_MAX && operatingControl->GetRawAxis(XboxAxisRightStickX) > 0.3)
	{
		IrisGrabber->Set(operatingControl->GetRawAxis(XboxAxisRightStickX) * IRIS_SPEED);
	}else {
		IrisGrabber->Set(0);
	}

	// ElevatorPID->SetSetpoint(1550);

	// std::cout << "Elevator Analog: " << IrisPot->GetVoltage() << std::endl;  
	// std::cout << "Voltage Elevator: " << Elevator0->GetVoltage() << std::endl;

	// std::cout << Elevator0->GetSelectedSensorPosition() << std::endl;
	int numProgs = 8;
	//Analog Version:
	//Get the range for each program slice
	double Range = V_MAX/numProgs;
	//LED routine
	LEDHeight->SetVoltage((ElevatorEncoder->Get()/ELEVATOR_MAX) * 5);

	// Light switches according to position
	if (IrisPot->GetVoltage() < IRIS_VOL_MAX && operatingControl->GetRawAxis(XboxAxisRightStickX) > 0.3)
	{
		LEDProgram->SetVoltage(Range*2); // Iris 2nd prograam
	}
	else if (operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisLeftTrigger)>0.3) 
	{
		LEDProgram->SetVoltage(Range*3); // Tacoh 3rd program
	}
	else if (TacoCurrentRead->GetCurrent() >= CURRENT_STRIKE) 
	{
		LEDProgram->SetVoltage(Range*4); // DiskAquired 4th program
	}
	else if (IntakeCurrentRead->GetCurrent() >= CURRENT_STRIKE) 
	{
		LEDProgram->SetVoltage(Range*5); // BallAquired 5th program
	}
	else if (operatingControl->GetRawButton(XboxJoystickButton::XboxButtonRightBumper)) 
	{
		LEDProgram->SetVoltage(Range*6); // Celebration 6th program
	}
	else if (operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisRightTrigger)>0.3) 
	{
		LEDProgram->SetVoltage(Range*7); // Intake 7th program
	}
	else if (ElevatorEncoder->Get()/ELEVATOR_MAX >= 0.98) 
	{
		LEDProgram->SetVoltage(Range*8); // Warning 8th program
	}
	else 
	{
		LEDProgram->SetVoltage(Range); // Prematch 1st program
	}

	// hudElevatorLimit->SetBoolean(!ElevatorDown->Get());
	ntHud->PutBoolean("elevatorLimit", false);

	std::cout << "Encoder " << Elevator0->GetSelectedSensorPosition() << std::endl;
	std::cout << "PID " << elevatorPIDOutput->GetOutput() << std::endl;

	//TODO: Do not move elevator down after limit switch
	Elevator0->Set(operatingControl->GetRawAxis(XboxAxisLeftStickY));

	if(rightJoystick->GetRawButton(ThrustJoystickButtons::topRightRight)) {
		std::cout << "Climb" << std::endl;
		Climb0->Set(0.5);
	}else if(rightJoystick->GetRawButton(ThrustJoystickButtons::topRightMiddle)) {
		Climb0->Set(-0.5);
	} else {
		Climb0->Set(0);
	}


	Climber->Set(false);
}

void Robot::TestPeriodic() {}

START_ROBOT_CLASS(Robot)
