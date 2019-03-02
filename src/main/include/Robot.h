#pragma once

#include <string>

#include <WPILib.h>

#include <Control.h>

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
  Controls *controls;
  Joystick *leftJoystick;
  Joystick *rightJoystick;
  Joystick *override;
  Joystick *operator;
};
