#include "Control.h"

Control::Control() {
    leftJoystick= new frc::Joystick(0);
    rightJoystick = new frc::Joystick(1);
    overrideJoystick = new frc::Joystick(2);
    operatorControl = new frc::Joystick(3);
}

Control::ElevatorPosition Control::RequestedPosition() {
    ElevatorPosition RequestedPosition = ElevatorPosition::manual;
    if(operatorControl->GetRawButton(buttonbox::hatchL0)){
        RequestedPosition = ElevatorPosition::HatchTower0;
    } else if(operatorControl->GetRawButton(buttonbox::hatchL1)){
        RequestedPosition = ElevatorPosition::HatchTower1;
    } else if(operatorControl->GetRawButton(buttonbox::hatchL2)){
        RequestedPosition = ElevatorPosition::HatchTower2;
    }
    return RequestedPosition;
}

double Control::ElevatorOverrideJoystick(){
    return overrideJoystick->GetRawAxis(XboxJoystickAxis::XboxAxisLeftStickY) * 0.5;
}

double Control::RightJoystickArcade() {
    return rightJoystick->GetRawAxis(ThrustJoystickAxis::yAxisJS);
}

double Control::LeftJoystickArcade() {
    return leftJoystick->GetRawAxis(ThrustJoystickAxis::xAxisJS);
}

bool Control::IntakeDown(){
    return operatorControl->GetRawButton(buttonbox::intakeout);
}

bool Control::IntakeSpit(){
    return operatorControl->GetRawButton(buttonbox::intakein);
}

bool Control::TacohDown(){
    return operatorControl->GetRawButton(buttonbox::tacoin);
}

bool Control::TacohOut(){
    return operatorControl->GetRawButton(buttonbox::tacoout);
}