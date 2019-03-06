#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {
  control = new Control();
  elevator = new RobotElevator(control);
  driveTrain = new DriveTrain(control);
  intakeArm = new IntakeArm(control);
  tacoh = new Tacoh(control);
}

void Robot::RobotPeriodic() {
  
}

void Robot::AutonomousInit() {
}

void Robot::AutonomousPeriodic() {
  elevator->Periodic();
  driveTrain->Periodic();
  tacoh->Periodic();
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
  elevator->Periodic();
  driveTrain->Periodic();
  tacoh->Periodic();
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
