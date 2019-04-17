#include "Climber.h"

#include <iostream>

Climber::Climber(Control* control, double frontSpeed, double backSpeed) {
    FrontClimb = new WPI_VictorSPX(CanChain::Climb_1);
    BackClimb = new WPI_TalonSRX(CanChain::Climb_0);
    this->control = control;
    this->frontSpeed = frontSpeed;
    this->backSpeed = backSpeed;

    frontEncoder = new frc::Encoder(4,5);
    backEncoder = new frc::Encoder(2,3);

    frontEncoder->Reset();
    backEncoder->Reset();
}

void Climber::Periodic() {
    // std::cout << frontEncoder->Get() << std::endl;

    if(control->ResetClimbEncoders()){
        backEncoder->Reset();
    }

    // Front Climber down
    if (control->ClimberFrontDown()) {
        ////std::cout << "Front Climber Down" << //std::endl;
        FrontClimb->Set(frontSpeed);
    } 
    // Front Climber back up 
    else if (control->ClimberFrontUp()) {
        //std::cout << "Front Climber Back Up" << //std::endl;
        FrontClimb->Set(-frontSpeed);
    }else {
        FrontClimb->Set(0);
    }
    // Back Climber down
    if (control->ClimberBackDown()) {
        // std::cout << "Back Climber Down" << std::endl;
        BackClimb->Set(backSpeed);
        
    }
    //Back Climber back up
    else if (control->ClimberBackUp()) {
        // std::cout << "Back Climber Back Up" << std::endl;
        BackClimb->Set(-backSpeed);
    } else {
        BackClimb->Set(0);
    }

    
    
    // Level 3 Front Climber Down
    if (control->ClimberFrontDown3rd()) {
        FrontClimb->Set(frontSpeed);
    }
    // Level 3 Back Climber Down
    if (control->ClimberBackDown3rd()) {
        BackClimb->Set(backSpeed);
    }
    if (control->Climb3PID()) {
        /*
        if (FrontSensorValue - BackSensorValue > VALUE) {
            FrontClimb->Set(frontSpeed - ((BackSensorValue - FrontSensorValue) / MAX_SENSOR_VALUE)); // Decrease FrontSpeed
        }
        if (BackSensorValue - FrontSensorValue > VALUE) {
            BackClimb->Set(backSpeed - ((BackSensorValue - FrontSensorValue) / MAX_SENSOR_VALUE)); // Decrease BackSpeed
        }
        if (!control->ClimberFrontDown3rd()) {
            if (FrontSensorValue <= BottomHeight) {
                FrontClimb->Set(-FrontSpeed)
            }
        }
        */
       ClimberPIDLoop();
    }
    
    // // Setting to zero if none of the front climber controlling buttons are pressed
    // if (!control->ClimberFrontUp() && !control->ClimberFrontDown() && !control->ClimberFrontDown3rd()) {
    //     FrontClimb->Set(0);
    // }
    // // Setting to zero if none of the back climber controlling //////buttons are pressed
    // if (!control->ClimberBackUp() && !control->ClimberBackDown() && !control->ClimberBackDown3rd()) {
    //     BackClimb->Set(0);
    // }
}

void Climber::ClimberPIDLoop() {
    double frontPosition = frontEncoder->Get();
    double backPosition = backEncoder->Get();

    double frontError = 1.0*(FRONT_MAX - frontPosition)/FRONT_MAX;
    double backError = (BACK_MAX - backPosition)/BACK_MAX;

    if((FRONT_MAX - frontPosition) < -10) {
        FrontClimb->Set(backSpeed + frontError + ((backError - frontError) * 0.05));
    }else if((FRONT_MAX - frontPosition) > 10) {
        FrontClimb->Set(-1 * (backSpeed + 1.0*(FRONT_MAX - frontPosition)/FRONT_MAX));
     }  else {
        FrontClimb->Set(ControlMode::Position, FrontClimb->GetSelectedSensorPosition());
    }

    if((BACK_MAX - backPosition) > 10){
        BackClimb->Set(-frontSpeed + backError);
    }else if((BACK_MAX - backPosition) < -10) {
        BackClimb->Set(-1 * frontSpeed + (BACK_MAX - backPosition)/BACK_MAX);
    } else { 
        BackClimb->Set(ControlMode::Position, BackClimb->GetSelectedSensorPosition());
    }
}