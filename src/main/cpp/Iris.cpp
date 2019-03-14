#include "Iris.h"

#include<iostream>

Iris::Iris(Control *control){
    this->control = control;
    IrisM = new WPI_VictorSPX(CanChain::iris);
    LimitIn = new frc::DigitalInput(9);
    LimitOut = new frc::DigitalInput(8);
    IrisEject = new frc::Solenoid(Pneumatics::IrisP);
    pot = new frc::AnalogInput(0);
}

void Iris::Periodic(){
    //std::cout << "Voltage " << pot->GetVoltage() << std::endl;

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
    /*if(control->IrisExpand()){
        Expand();
    }else if(control->IrisShrink()){
        Shrink();
    }*/
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
   // std::cout << "LimitOut: " << LimitOut->Get() << std::endl;
    //std::cout << "LimitIn: " << LimitIn->Get() << std::endl;
    //std::cout << "State: " << state << std::endl;
}

// Limit switch Expanding
void Iris::Expand(){
   state = 1;
   //std::cout << "OUT" << std::endl;
}
//limit switch Shrinking
void Iris::Shrink(){
    state = 2;
}