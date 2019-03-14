#include "Elevator2.h"

Elevator::Elevator(Control* control) {
    Elevator0 = new WPI_TalonSRX(CanChain::elevator0);
    Elevator1 = new WPI_VictorSPX(CanChain::elevator1);
    this->control = control;
}

void Elevator::Periodic() {
    
}