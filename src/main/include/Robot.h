#pragma once

#include <string>

#include <frc/WPILib.h>
#include <frc/Preferences.h>

#include "Control.h"
#include "Elevator.h"
#include "DriveTrain.h"
#include "IntakeArm.h"
#include "Tacoh.h"
#include "CamServo.h"
#include "Climber.h"
// #include "Iris.h"
#include "Hatch.h"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;
  void DisabledPeriodic() override;
  void DisabledInit() override;

 private:
  Control *control;
  RobotElevator *elevator;
  DriveTrain *driveTrain;
  IntakeArm *intakeArm;
  Tacoh *tacoh;
  CamServo *camServo;
  // Iris *iris;
  Climber *climber;
  Hatch *hatch;
  frc::Preferences *Climber_Values;
  double FrontSpeed;
  double BackSpeed;

  frc::Compressor *compressor;
  nt::NetworkTableEntry ntCompressor;
};
