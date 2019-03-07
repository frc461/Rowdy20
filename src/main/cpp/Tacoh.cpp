#include "Tacoh.h"

Tacoh::Tacoh(Control *control, Iris *iris) {
    this->control = control;
    this->iris = iris;
    TacohIntake = new WPI_VictorSPX(CanChain::taco);
    TacohExtend = new frc::Solenoid(Pneumatics::TacoP);
    DownHasRun = false;
    Counter = 0;
}

void Tacoh::Periodic() {
    if(control->TacohDown()){
        //TODO: Shrink iris
        // control->ElevatorSmallMoveSet(1);
        TacohExtend->Set(1);
        TacohIntake->Set(0.8);
        DownHasRun = true;
    }else if(control->TacohOut()){
        // control->ElevatorSmallMoveSet(1);
        TacohExtend->Set(1);
        TacohIntake->Set(-0.8);
    }else {
        // control->ElevatorSmallMoveSet(0);
        TacohExtend->Set(0);
        TacohIntake->Set(0);
        if(DownHasRun){
            TacohExtend->Set(0);
            if(Counter > 500) {
                DownHasRun = false;
                iris->Expand();
                //TODO: Run iris
            }else {
                Counter++;
            }
        }
    }
}