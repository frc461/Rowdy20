#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {  
  control = new Control();
  elevator = new RobotElevator(control);
  driveTrain = new DriveTrain(control);
  intakeArm = new IntakeArm(control);
  tacoh = new Tacoh(control, iris);
  camServo = new CamServo(control);
  iris = new Iris(control);

  // Shuffle Board
  Climber_Values = frc::Preferences::GetInstance();
  FrontSpeed = Climber_Values->GetDouble("FrontSpeed", 0);
  BackSpeed = Climber_Values->GetDouble("BackSpeed", 0);

  climber = new Climber(control, -1, 0.9);
}

void Robot::RobotPeriodic() {
}

void Robot::AutonomousInit() {
 // control->ElevatorSmallMoveSet(false);
}

void Robot::AutonomousPeriodic() {
  elevator->Periodic();
  driveTrain->Periodic();
  tacoh->Periodic();
  intakeArm->Periodic();
  camServo->Periodic();
  iris->Periodic();
}

void Robot::TeleopInit() {
  
}

void Robot::TeleopPeriodic() {
  elevator->Periodic();
  driveTrain->Periodic();
  tacoh->Periodic();
  intakeArm->Periodic();
  camServo->Periodic();
  climber->Periodic();
  iris->Periodic();
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
