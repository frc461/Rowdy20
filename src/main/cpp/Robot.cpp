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

	leftJoystick = new Joystick(0);
	rightJoystick = new Joystick(1);
	operatingControl = new Joystick(2);
	ButtonBox = new Joystick(3);

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

	ClimberWedge1 = new Solenoid(ClimberP1);	


	Iris = new Solenoid(IrisP);
	IrisGrabber = new WPI_VictorSPX(iris);
	IrisPot = new AnalogInput(IrisPott);

	LEDHeight = new AnalogOutput(LEDheight);
	// LEDProgram = new AnalogOutput(AnalogIO::LEDPrograms);

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

	ElevatorPID = new PIDController(0.0005, 0.000009, 0.0000040, elevatorPIDSource, elevatorPIDOutput, 0.05);
	ElevatorPID->SetContinuous(true);
	ElevatorPID->SetOutputRange(-1, 1);

	ElevatorPID->SetSetpoint(0);

	ElevatorPID->Enable();

	ClimberWedge1->Set(false);

	SmartDashboard::PutNumber("Elevator Speed", Elevator0->Get());
	SmartDashboard::PutNumber("Elevator PID Setpoint", ElevatorPID->GetSetpoint());
	SmartDashboard::PutNumber("Elevator PID kP", ElevatorPID->GetP());
	SmartDashboard::PutNumber("Elevator PID kI", ElevatorPID->GetI());
	SmartDashboard::PutNumber("Elevator PID kD", ElevatorPID->GetD());

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
	intakeBuffer = frc::GetTime() - 3000;
}

double Robot::ElevatorLimitCheck(double in){
	return (!ElevatorDown->Get() && in < 0) ? 0 : in;
}

void Robot::TeleopPeriodic() {

	frc::SmartDashboard::PutNumber("Rate of Elevator Encoder(units/sec)", ElevatorEncoder->GetRate());

	driveTrain->ArcadeDrive(-rightJoystick->GetRawAxis(yAxisJS), leftJoystick->GetRawAxis(xAxisJS));

	//Elevator Movement
	// elevator->Set((operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisRightStickY)*0.5-0.1) * ((operatingControl->GetRawAxis(XboxAxisRightStickY) > 0) ?  ElevatorDown->Get() : 1));
	
	// if (operatingControl->GetRawAxis((XboxJoystickAxis::XboxAxisLeftStickY) < 0 || ButtonBox->GetRawButton(buttonbox::tacoin) && ElevatorEncoder->Get()/ELEVATOR_MAX < 0.1 && TacoPos->Get() == false)
	// {
	// 	Taco->Set(0.75);
	// }

	// if(operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisLeftStickY) > 0.2 && Elevator0->GetSelectedSensorPosition() <= ELEVATOR_MIN_BUFFER){
	// 	std::cout << "Slow Elevator" << std::endl;
	// 	elevatorSpeed = Elevator0->GetSelectedSensorPosition()/ELEVATOR_MIN_BUFFER + 0.2;
	// } else if(operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisLeftStickY) < 0.2 && Elevator0->GetSelectedSensorPosition() >= ELEVATOR_MAX_BUFFER) {
	// 	elevatorSpeed = Elevator0->GetSelectedSensorPosition()/ELEVATOR_MAX_BUFFER + 0.2;
	// }
	// else{
	// 	elevatorSpeed = 1;
	// }

	//Reset Elevator Encoder on Limit Switch
	if(!ElevatorDown->Get()){
		Elevator0->SetSelectedSensorPosition(0,0);
	}

	// if(rightJoystick->GetRawButton(ThrustJoystickButtons::topRightRight)){
	// 	Elevator0->SetSelectedSensorPosition(0,0);
	// }

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

	// if(leftJoystick->GetRawButton(ThrustJoystickButtons::topRightRight)){
	// 	std::cout << "Thing" << std::endl;
	// 	ElevatorPID->SetSetpoint(1758);
	// } else if(leftJoystick->GetRawButton(ThrustJoystickButtons::topRightMiddle)){
	// 	ElevatorPID->SetSetpoint(0);
	// } else if(leftJoystick->GetRawButton(ThrustJoystickButtons::topRightLeft)){
	// 	ElevatorPID->SetSetpoint(3306);
	// }

	if(ButtonBox->GetRawButton(buttonbox::cargoL1)){ // Hatch 1 Button
		ElevatorPID->SetSetpoint(HatchTower0_H); 
	}else if(ButtonBox->GetRawButton(buttonbox::cargoL2)){ // Hatch 2 Button
		ElevatorPID->SetSetpoint(HatchTower1_H);	
	} else if(ButtonBox->GetRawButton(buttonbox::cargoL3)){ // Hatch 3 Button
		ElevatorPID->SetSetpoint(HatchTower2_H);
	} else if(ButtonBox->GetRawButton(buttonbox::hatchL1)){
		ElevatorPID->SetSetpoint(BallTower0_H);	
	} else if(ButtonBox->GetRawButton(buttonbox::hatchL2)){
		ElevatorPID->SetSetpoint(BallTower1_H);	
	}else if(ButtonBox->GetRawButton(buttonbox::hatchL3)){
		ElevatorPID->SetSetpoint(BallTower2_H);	
	}

	if(ButtonBox->GetRawButton(buttonbox::elevatorup)){
		elevatorSpeed = 0.5;
		ElevatorPID->SetSetpoint(Elevator0->GetSelectedSensorPosition());
	}else if(ButtonBox->GetRawButton(buttonbox::elevatordown)) {
		elevatorSpeed = -0.3;	
		ElevatorPID->SetSetpoint(Elevator0->GetSelectedSensorPosition());
	}else {
		elevatorSpeed = (elevatorPIDOutput->GetOutput() < 0) ? elevatorPIDOutput->GetOutput() * 0.6 : elevatorPIDOutput->GetOutput();
	}

	Elevator0->Set(-1 * ElevatorLimitCheck(elevatorSpeed));

	// else {
		// Elevator0->Set((operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisLeftStickY)*0.5-0.1) * elevatorSpeed * ((operatingControl->GetRawAxis(XboxAxisLeftStickY) > 0) ?  ElevatorDown->Get() : 1));
	// }


	//Robot speed reduction according to levator height
	// if (ElevatorEncoder->Get() >= ELEVATOR_MAX/2 )
	// {
	// 	elevator->Set((operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisRightStickY))*0.5);
	// }
	// Taco spit
	// if (operatingControl->GetRawButton(XboxJoystickButton::XboxButtonLeftBumper)) {
	// 	Taco->Set(0.75);
	// }
	// Taco in
	// else if (operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisLeftTrigger)>0.3) {
	// 	Taco->Set(-0.75);
	// }
	// else {
	// 	Taco->Set(0);
	// }

	// Taco position up
	// if (operatingControl->GetRawButton(XboxButtonA))
	// {
	// 	// IntakePos->Set(true);
	// 	TacoPos->Set(true);
	// }
	// // Taco position down
	// else if (operatingControl->GetRawButton(XboxButtonY))
	// {
	// 	TacoPos->Set(false);
	// }

	//TODO: PUT ME BACK!!! >:(

	if(ButtonBox->GetRawButton(buttonbox::tacoout)) {
		// TacoPos->Set(true);
		Taco->Set(0.75);
	} else if (ButtonBox->GetRawButton(buttonbox::tacoin)) {
		TacoPos->Set(true);
		Taco->Set(-0.75);
	} else{
		Taco->Set(0);
		TacoPos->Set(false);
	}

	// && IntakePos->Get() == false

	// Iris push
	if (operatingControl->GetRawButton(XboxButtonX) || ButtonBox->GetRawButton(buttonbox::irisextend))
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
	if (ButtonBox->GetRawButton(buttonbox::intakein)){
		IntakePos->Set(true);
		Intake->Set(-1);
		TacoPos->Set(false);
	}else {
		IntakePos->Set(false);
	}
	// if(operatingControl->GetRawButton(XboxButtonStart))
	// Intake position up
	if (operatingControl->GetRawButton(XboxButtonStart))
	{
		IntakePos->Set(false);
	}

	// Intake spit
	if (operatingControl->GetRawButton(XboxJoystickButton::XboxButtonRightBumper) || ButtonBox->GetRawButton(buttonbox::intakein)) {
		Intake->Set(-1);
	}
	// Intake in
	else if (operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisRightTrigger)>0.3 || ButtonBox->GetRawButton(buttonbox::intakeout)) {
		Intake->Set(0.75);
		std::cout << "Reset" << std::endl;
		intakeBuffer = frc::GetTime();
	}
	else {
		// if (frc::GetTime() <= intakeBuffer + 3000){
		// 	std::cout << "Run" << std::endl;
		// 	Intake->Set(-0.5);

		// }
		// else {
			Intake->Set(-0.05);
		// }
	}

	
    
	// Iris in 
	// if (IrisPot->GetVoltage() < IRIS_VOL_MIN && (operatingControl->GetRawAxis(XboxAxisRightStickX) < -0.3 || ButtonBox->GetRawButton(buttonbox::irisclosed))) {
	// 	IrisGrabber->Set(operatingControl->GetRawAxis(XboxAxisRightStickX) * IRIS_SPEED);
	// }
	// // Iris out
	// else if (IrisPot->GetVoltage() < IRIS_VOL_MAX && (operatingControl->GetRawAxis(XboxAxisRightStickX) > 0.3 || ButtonBox->GetRawButton(buttonbox::irisopen)))
	// {
	// 	IrisGrabber->Set(operatingControl->GetRawAxis(XboxAxisRightStickX) * IRIS_SPEED);
	if(ButtonBox->GetRawButton(buttonbox::irisclosed)){
		IrisGrabber->Set(0.4);
	}else if(ButtonBox->GetRawButton(buttonbox::irisopen)) {
		IrisGrabber->Set(-0.4);	
	}else {
		IrisGrabber->Set(0);
	}

	// ElevatorPID->SetSetpoint(1550);

	// std::cout << "Elevator Analog: " << IrisPot->GetVoltage() << std::endl;  
	// std::cout << "Voltage Elevator: " << Elevator0->GetVoltage() << std::endl;

	// std::cout << "Elevator Position: " << Elevator0->GetSelectedSensorPosition() << std::endl;
	// std::cout << "PID Run: " << elevatorPIDOutput->GetOutput() << std::endl;
	// std::cout << "Setpoint: " << ElevatorPID->GetSetpoint() << std::endl;
	//LED routine
	// LEDHeight->SetVoltage((ElevatorEncoder->Get()/ELEVATOR_MAX) * 5);

	// // Light switches according to position
	// if (ElevatorEncoder->Get()/ELEVATOR_MAX >= 0.98) {
	// 	LEDProgram->SetVoltage(5);
	// }

	// // hudElevatorLimit->SetBoolean(!ElevatorDown->Get());
	// ntHud->PutBoolean("elevatorLimit", false);

	// std::cout << "Current Time " << frc::GetTime() << std::endl;
	// std::cout << "Last Reset " << intakeBuffer << std::endl;
	// std::cout << "Time to Stop Running " << intakeBuffer + 3000 << std::endl;

	//TODO: Do not move elevator down after limit switch
	// Elevator0->Set(operatingControl->GetRawAxis(XboxAxisLeftStickY));

	if(operatingControl->GetRawAxis(XboxAxisLeftStickY) > 0.2) {
		ElevatorPID->SetSetpoint(ElevatorPID->GetSetpoint() - 10);
	} else if(operatingControl->GetRawAxis(XboxAxisLeftStickY) < -0.2){
		ElevatorPID->SetSetpoint(ElevatorPID->GetSetpoint() + 10);
	}

	
	
	if(rightJoystick->GetRawButton(ThrustJoystickButtons::topRightRight)) {
	 	std::cout << "Climb" << std::endl;
	 	Climb0->Set(0.5);
	}
	else if(rightJoystick->GetRawButton(ThrustJoystickButtons::topRightMiddle)) {
	 	Climb0->Set(-0.5);
	} 
	else {
	 	Climb0->Set(0);
	}
	if (rightJoystick->GetRawButton(ThrustJoystickButtons::bottomRightMiddle)) {
		std::cout << "Wedge down" << std::endl;
		ClimberWedge1->Set(true);
	}
	
	// SmartDashboard::PutNumber("Elevator Speed", Elevator0->Get());
	// SmartDashboard::PutNumber("Elevator PID Setpoint", ElevatorPID->GetSetpoint());
	// SmartDashboard::PutNumber("Elevator PID kP", ElevatorPID->GetP());
	// SmartDashboard::PutNumber("Elevator PID kI", ElevatorPID->GetI());
	// SmartDashboard::PutNumber("Elevator PID kD", ElevatorPID->GetD());

	SmartDashboard::UpdateValues();

	std::cout << SmartDashboard::GetNumber("Elevator PID kP", 10) << std::endl;

	// int numProgs = 8;
	// double Range = V_MAX/numProgs;
	// //LED routine
	// LEDHeight->SetVoltage(Elevator0->GetSelectedSensorPosition()/ELEVATOR_MAX * 5);

	// // Light switches according to position
	// if (IrisPot->GetVoltage() < IRIS_VOL_MAX && operatingControl->GetRawAxis(XboxAxisRightStickX) > 0.3)
	// {
	// 	LEDProgram->SetVoltage(Range*2); // Iris 2nd prograam
	// }
	// else if (operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisLeftTrigger)>0.3) 
	// {
	// 	LEDProgram->SetVoltage(Range*3); // Tacoh 3rd program
	// }
	// else if (pdp->GetCurrent(0) >= CURRENT_STRIKE) 
	// {
	// 	LEDProgram->SetVoltage(Range*4); // DiskAquired 4th program
	// }
	// else if (pdp->GetCurrent(0) >= CURRENT_STRIKE) 
	// {
	// 	LEDProgram->SetVoltage(Range*5); // BallAquired 5th program
	// }
	// else if (operatingControl->GetRawButton(XboxJoystickButton::XboxButtonRightBumper)) 
	// {
	// 	LEDProgram->SetVoltage(Range*6); // Celebration 6th program
	// }
	// else if (operatingControl->GetRawAxis(XboxJoystickAxis::XboxAxisRightTrigger)>0.3) 
	// {
	// 	LEDProgram->SetVoltage(Range*7); // Intake 7th program
	// }
	// else if (ElevatorEncoder->Get()/ELEVATOR_MAX >= 0.98) 
	// {
	// 	LEDProgram->SetVoltage(Range*8); // Warning 8th program
	// }
	// else 
	// {
	// 	LEDProgram->SetVoltage(Range); // Prematch 1st program
	// }

	// Climber->Set(false);
}

void Robot::TestPeriodic() {}

START_ROBOT_CLASS(Robot)
