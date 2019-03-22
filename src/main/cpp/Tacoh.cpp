#include "Tacoh.h"

Tacoh::Tacoh(Control *control, Hatch *hatch) {
    this->control = control;
    TacohIntake = new WPI_VictorSPX(CanChain::taco);
    TacohExtend = new frc::Solenoid(Pneumatics::TacoP);
    //IrisControl = new frc::Solenoid();
    // this->iris = iris;
    this->hatch = hatch;
    DownHasRun = false;
    Counter = 0;
}

void Tacoh::Periodic() {
    if(control->TacohDown()){
        // control->ElevatorSmallMoveSet(1);
        // iris->Shrink();
        hatch->Shrink();
        // IrisControl->Set(1);[]
        TacohExtend->Set(1);
        TacohIntake->Set(0.8);
        DownHasRun = true;
    }else if(control->TacohOut()){
        // control->ElevatorSmallMoveSet(1);
        TacohExtend->Set(1);
        TacohIntake->Set(-0.8);
        DownHasRun = false;
    }else {
        // control->ElevatorSmallMoveSet(0);
        TacohExtend->Set(0);
        TacohIntake->Set(0);
        if(DownHasRun){
            TacohExtend->Set(0);
            if(Counter > 500) {
                DownHasRun = false;
                // iris->Expand();
                hatch->Expand();
                //TODO: Run iris
            }else {
                Counter++;
            }
        }
    }
}