#include "CamServo.h"

#include <iostream>

CamServo::CamServo(Control *control) {
    camServo = new frc::Servo(0);
    this->control = control;
}

void CamServo::Periodic()
{
    //std::cout << "Camera Position: " << camServo->Get() << std::endl;

    // 11 top 16 bottom
    if (control->CameraUpButton()){
        camServo->Set(0.4);
    }
    else if (control->CameraDownButton()){
        camServo->Set(0);
    }
}