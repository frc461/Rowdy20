#pragma once

#include <string>

#include <frc/WPILib.h>

#include "Control.h"
#include "Elevator.h"
#include "DriveTrain.h"
#include "IntakeArm.h"
#include "Tacoh.h"
#include "Iris.h"
#include "CamServo.h"
#include "Climber.h"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  Control *control;
  RobotElevator *elevator;
  DriveTrain *driveTrain;
  IntakeArm *intakeArm;
  Tacoh *tacoh;
  Iris *iris;
  CamServo *camServo;
  Climber *climber;
};
