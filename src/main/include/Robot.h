#pragma once

#include <string>

#include <WPILib.h>

#include "Control.h"
#include "Elevator.h"
#include "DriveTrain.h"

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
};
