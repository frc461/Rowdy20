#include "DriveTrain.h"

DriveTrain::DriveTrain(Control *control){
    this->control = control;
    RMotor0 = new WPI_TalonSRX(CanChain::R_Motor0);
    RMotor1 = new WPI_VictorSPX(CanChain::R_Motor1);
    RMotor2 = new WPI_VictorSPX(CanChain::R_Motor2);

    LMotor0 = new WPI_TalonSRX(CanChain::L_Motor0);
    LMotor1 = new WPI_VictorSPX(CanChain::L_Motor1);
    LMotor2 = new WPI_VictorSPX(CanChain::L_Motor2);

    BottomWheels = new frc::PWMVictorSPX(1);

    DTLeft = new frc::SpeedControllerGroup(*LMotor0, *LMotor1, *LMotor2);
    DTRight = new frc::SpeedControllerGroup(*RMotor0, *RMotor1, *RMotor2);

    driveTrain = new frc::DifferentialDrive(*DTLeft, *DTRight);
}

void DriveTrain::Periodic() {
    driveTrain->ArcadeDrive(control->RightJoystickArcade(), control->LeftJoystickArcade());
    BottomWheels->Set(control->RightJoystickArcade()); 
}