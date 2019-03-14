#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {  
  control = new Control();
  iris = new Iris(control);
  elevator = new RobotElevator(control);
  driveTrain = new DriveTrain(control);
  intakeArm = new IntakeArm(control);
  tacoh = new Tacoh(control, iris);
  camServo = new CamServo(control);
  climber = new Climber(control);
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
  iris->Periodic();
  intakeArm->Periodic();
  camServo->Periodic();
}

void Robot::TeleopInit() {
}

void Robot::TeleopPeriodic() {
  elevator->Periodic();
  driveTrain->Periodic();
  tacoh->Periodic();
  iris->Periodic();
  intakeArm->Periodic();
  camServo->Periodic();
  climber->Periodic();
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
