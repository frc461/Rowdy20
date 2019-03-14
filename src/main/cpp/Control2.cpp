#include "Control.h"

#include <stdio.h>
#include <iostream>

Control::Control() {
    leftJoystick= new frc::Joystick(0);
    rightJoystick = new frc::Joystick(1);
    overrideJoystick = new frc::Joystick(2);
    operatorControl = new frc::Joystick(3);
    ElevatorPosition CurrentPosition = ElevatorPosition::manual;
    //ElevatorSmallMoveSet(0);
}

int Control::RequestedPosition2() { // ADD to .h
    if (operatorControl->GetRawButton(buttonbox::cargoL0)) {
        CurrentSetPoint = ELEVATOR_BallTower0;
    }
    else if (operatorControl->GetRawButton(buttonbox::cargoL1)) {
        CurrentSetPoint = ELEVATOR_BallTower1;
    }
    else if (operatorControl->GetRawButton(buttonbox::cargoL2)) {
        CurrentSetPoint = ELEVATOR_BallTower2;
    }
    else if (operatorControl->GetRawButton(buttonbox::hatchL0)) {
        CurrentSetPoint = ELEVATOR_HatchTower0;
    }
    else if (operatorControl->GetRawButton(buttonbox::hatchL1)) {
        CurrentSetPoint = ELEVATOR_HatchTower1;
    }
    else if (operatorControl->GetRawButton(buttonbox::hatchL2)) {
        CurrentSetPoint = ELEVATOR_HatchTower2;
    }
    else if (overrideJoystick->GetRawAxis(XboxAxisRightStickY) < -0.1 || overrideJoystick->GetRawAxis(XboxAxisRightStickY) > 0.1) {
        CurrentSetPoint -= overrideJoystick->GetRawAxis(XboxAxisRightStickY)*MANUAL_CONSTANT;
    }
    return CurrentSetPoint;
}

double Control::ElevatorOverrideJoystick(){
    return overrideJoystick->GetRawAxis(XboxJoystickAxis::XboxAxisRightStickY) * -0.5;
}

double Control::RightJoystickArcade() {
    return rightJoystick->GetRawAxis(ThrustJoystickAxis::yAxisJS);
}

double Control::LeftJoystickArcade() {
    return leftJoystick->GetRawAxis(ThrustJoystickAxis::xAxisJS);
}

bool Control::ClimberFrontDown() {
    return leftJoystick->GetRawButton(ThrustJoystickButtons::thumbSwitch); // BUTTON ?
}

bool Control::ClimberBackDown() {
    return rightJoystick->GetRawButton(ThrustJoystickButtons::thumbSwitch); // BUTTON ?
}

bool Control::ClimberFrontUp() {
    return leftJoystick->GetRawButton(ThrustJoystickButtons::rightButton); // BUTTON ?
}

bool Control::ClimberBackUp() {
    return rightJoystick->GetRawButton(ThrustJoystickButtons::leftButton); // BUTTON ?
}

bool Control::ClimberBothDown() {
    return leftJoystick->GetRawButton(ThrustJoystickButtons::leftButton);
}

bool Control::CameraUpButton() {
    return overrideJoystick->GetRawButton(XboxButtonB);
}
bool Control::CameraDownButton() {
    return overrideJoystick->GetRawButton(XboxButtonA);
}

bool Control::IntakeDown(){
    return operatorControl->GetRawButton(buttonbox::intakein);
}

bool Control::IntakeSpit(){
    return operatorControl->GetRawButton(buttonbox::intakeout);
}

bool Control::TacohDown(){
    return operatorControl->GetRawButton(buttonbox::tacoout);
}

bool Control::TacohOut(){
    return operatorControl->GetRawButton(buttonbox::tacoin);
}

bool Control::IrisExpand(){
    return operatorControl->GetRawButton(buttonbox::irisopen);
}

bool Control::IrisShrink(){
    return operatorControl->GetRawButton(buttonbox::irisclosed);
}

bool Control::IrisExtend(){
    return operatorControl->GetRawButton(buttonbox::irisextend);
    
}