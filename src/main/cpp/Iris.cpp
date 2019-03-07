#include "Iris.h"

#include<iostream>

Iris::Iris(Control *control){
    this->control = control;
    IrisM = new WPI_VictorSPX(CanChain::iris);
    IrisEject = new frc::Solenoid(Pneumatics::IrisP);
    pot = new frc::AnalogInput(0);
}

void Iris::Periodic(){
    std::cout << "Voltage " << pot->GetVoltage() << std::endl;
    if(control->IrisExpand()){
        Expand();
    }else if(control->IrisShrink()){
        Shrink();
    }
    if(state) {
        if(IRIS_MaxVal > pot->GetVoltage()){
            IrisM->Set(0.2);
        }else {
            IrisM->Set(0);
        }
    } else {
        if(IRIS_MinVal <= pot->GetVoltage()){
            IrisM->Set(-0.2);
        }else {
            IrisM->Set(0);
        }
    }
}

void Iris::Expand(){
    state = 1;
}

void Iris::Shrink(){
    state = 0;
}