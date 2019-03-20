#include "Iris.h"

#include<iostream>

Iris::Iris(Control *control){
    this->control = control;
    IrisM = new WPI_VictorSPX(CanChain::iris);
    LimitIn = new frc::DigitalInput(9);
    LimitOut = new frc::DigitalInput(8);
    IrisEject = new frc::Solenoid(Pneumatics::IrisP);
}

void Iris::Periodic(){

    if (control->IrisExpand())
    {
        Expand();
    }
    else if (control->IrisShrink())
    {
        Shrink();
    }
    else {
        state = 3;
    }
    if(state == 1) {
        if(LimitOut->Get()){
            IrisM->Set(-0.5);
        }
    } 
    else if (state == 2){
        if(LimitIn->Get()){
            IrisM->Set(0.5);
        }
    }
    else {
        IrisM->Set(0);
    }
    // Iris Extend
    if (control->IrisExtend()){
        IrisEject->Set(1);
    }
    else{
        IrisEject->Set(0);
    }
    if (LimitOut->Get()){
        //std::cout << "LimitOut" << std::endl;
    }
    else if (LimitIn->Get()){
        //std::cout << "LimitIn" << std::endl;
    }
}

// Limit switch Expanding
void Iris::Expand(){
   state = 1;
}
//limit switch Shrinking
void Iris::Shrink(){
    state = 2;
}