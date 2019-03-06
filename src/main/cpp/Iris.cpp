#include "Iris.h"

Iris::Iris(Control *control){
    this->control = control;
    IrisM = new WPI_VictorSPX(CanChain::iris);
    IrisEject = new frc::Solenoid(Pneumatics::IrisP);
}

void Iris::Periodic(){
    // if()
}