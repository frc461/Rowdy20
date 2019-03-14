#include "Climber.h"

#include <iostream>

using namespace std;

Climber::Climber(Control* control) {
    FrontClimb = new WPI_TalonSRX(CanChain::Climb_0); // Port # ?
    BackClimb = new WPI_VictorSPX(CanChain::Climb_1);

    this->control = control;
}

void Climber::Periodic() {
    if (control->ClimberFrontDown()) {
        cout << "Front Climb Down" << endl;
        FrontClimb->Set(FRONT_SPEED);
    }
    if (control->ClimberBackDown()) {
        cout << "Back Climb Down" << endl;
        BackClimb->Set(BACK_SPEED);
    }
    else if (control->ClimberBothDown()) {
        FrontClimb->Set(FRONT_SPEED);
        BackClimb->Set(BACK_SPEED);
    }
    else {
        FrontClimb->Set(0);
        BackClimb->Set(0);
    }

    if (control->ClimberFrontUp()) {
        cout << "Front Climb Up" << endl;
        FrontClimb->Set(-FRONT_SPEED);
    }
    if (control->ClimberBackUp()) {
        cout << "Back Climb Up" << endl;
        BackClimb->Set(-BACK_SPEED);
    }
    else {
        FrontClimb->Set(0);
        BackClimb->Set(0);        
    }

}