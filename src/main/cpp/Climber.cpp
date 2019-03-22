#include "Climber.h"

#include <iostream>

Climber::Climber(Control* control, double frontSpeed, double backSpeed) {
    FrontClimb = new WPI_TalonSRX(CanChain::Climb_0);
    BackClimb = new WPI_VictorSPX(CanChain::Climb_1);
    this->control = control;
    this->frontSpeed = frontSpeed;
    this->backSpeed = backSpeed;
}

void Climber::Periodic() {
    // Front Climber down
    if (control->ClimberFrontDown()) {
        ////std::cout << "Front Climber Down" << //std::endl;
        FrontClimb->Set(frontSpeed);
    }
    // Back Climber down
    if (control->ClimberBackDown()) {
        //std::cout << "Back Climber Down" << //std::endl;
        BackClimb->Set(backSpeed);
    }
    // Both F & B Climbers done
    if (control->ClimberBothDown()) {
        //std::cout << "F&B Climber Down" << //std::endl;
        FrontClimb->Set(-frontSpeed);
        BackClimb->Set(-backSpeed);
    }

    // Front Climber back up 
    if (control->ClimberFrontUp()) {
        //std::cout << "Front Climber Back Up" << //std::endl;
        FrontClimb->Set(-frontSpeed);
    }
    //Back Climber back up
    if (control->ClimberBackUp()) {
        //std::cout << "Back Climber Back Up" << //std::endl;
        BackClimb->Set(-backSpeed);
    }
    
    // Setting to zero if none of the front climber controlling buttons are pressed
    if (!control->ClimberFrontUp() && !control->ClimberFrontDown() && !control->ClimberBothDown()) {
        FrontClimb->Set(0);
    }
    // Setting to zero if none of the back climber controlling //////buttons are pressed
    if (!control->ClimberBackUp() && !control->ClimberBackDown() && !control->ClimberBothDown()) {
        BackClimb->Set(0);
    }
}