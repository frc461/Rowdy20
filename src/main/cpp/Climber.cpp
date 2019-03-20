#include "Climber.h"

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
        FrontClimb->Set(frontSpeed);
    }
    // Back Climber down
    if (control->ClimberBackDown()) {
        BackClimb->Set(backSpeed);
    }
    // Both F & B Climbers done
    if (control->ClimberBothDown()) {
        FrontClimb->Set(frontSpeed);
        BackClimb->Set(backSpeed);
    }

    // Front Climber back up 
    if (control->ClimberFrontUp()) {
        FrontClimb->Set(-frontSpeed);
    }
    //Back Climber back up
    if (control->ClimberBackUp()) {
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