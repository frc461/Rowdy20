#include "IntakeArm.h"

IntakeArm::IntakeArm(Control *control){
    this->control = control;

    Intake = new WPI_VictorSPX(CanChain::intake);
    IntakeExtend = new frc::Solenoid(Pneumatics::IntakeP);
}

void IntakeArm::Periodic(){
    if(control->IntakeDown()){
        Intake->Set(INTAKE_IN_SPEED);
        IntakeExtend->Set(1);
    }else if (control->IntakeSpit()){
        Intake->Set(INTAKE_OUT_SPEED);
        IntakeExtend->Set(0);
    } else {
        Intake->Set(IDLE_SPEED);
        IntakeExtend->Set(0);
    }
}