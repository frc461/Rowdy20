#include "Control.h"

#include <iostream>

Control::Control() {
    leftJoystick= new frc::Joystick(0);
    rightJoystick = new frc::Joystick(1);
    overrideJoystick = new frc::Joystick(2);
    operatorControl = new frc::Joystick(3);
    ElevatorPosition CurrentPosition = ElevatorPosition::manual;
    //ElevatorSmallMoveSet(0);
}

Control::ElevatorPosition Control::RequestedPosition() {
    if (overrideJoystick->GetRawAxis(XboxJoystickAxis::XboxAxisRightStickY) < -0.1 || overrideJoystick->GetRawAxis(XboxJoystickAxis::XboxAxisRightStickY) > 0.1)
        CurrentPosition = ElevatorPosition::manual;
    else if(operatorControl->GetRawButton(buttonbox::hatchL0)){
        CurrentPosition = ElevatorPosition::HatchTower0;
    } else if(operatorControl->GetRawButton(buttonbox::hatchL1)){
        CurrentPosition = ElevatorPosition::HatchTower1;
    } else if(operatorControl->GetRawButton(buttonbox::hatchL2)){
        CurrentPosition = ElevatorPosition::HatchTower2;
    } else if (operatorControl->GetRawButton(buttonbox::cargoL0)){
         CurrentPosition = ElevatorPosition::BallTower0;
    } else if (operatorControl->GetRawButton(buttonbox::cargoL1)){
         CurrentPosition = ElevatorPosition::BallTower1;
    } else if (operatorControl->GetRawButton(buttonbox::cargoL2)){
         CurrentPosition = ElevatorPosition::BallTower2;
    } 
    // else if (operatorControl->GetRawButton(buttonbox::undefined0){
        // CurrentPosition = ElevatorPosition::BallPosition4;
    // }
    else if(Control::TacohOut()) {
        CurrentPosition = ElevatorPosition::BallTower0;
    }
    return CurrentPosition;
}

double Control::ElevatorOverrideJoystick(){
    return operatorControl->GetRawAxis(0) * -0.5;
}

double Control::RightJoystickArcade() {
    return rightJoystick->GetRawAxis(ThrustJoystickAxis::yAxisJS);
}

double Control::LeftJoystickArcade() {
    return leftJoystick->GetRawAxis(ThrustJoystickAxis::xAxisJS);
}

bool Control::ClimberFrontDown() {
    // std::cout << "Front Down" << std::endl;
    return rightJoystick->GetRawButton(ThrustJoystickButtons::thumbSwitch); // BUTTON ?
}

bool Control::ClimberBackDown() {
    // std::cout << "Back Down" << std::endl;
    return leftJoystick->GetRawButton(ThrustJoystickButtons::thumbSwitch); // BUTTON ?
}

bool Control::ClimberFrontUp() {
    // std::cout << "Front Up" << std::endl;
    return rightJoystick->GetRawButton(ThrustJoystickButtons::rightButton); // BUTTON ?
}

bool Control::ClimberBackUp() {
    // std::cout << "Back Up" << std::endl;
    return leftJoystick->GetRawButton(ThrustJoystickButtons::leftButton); // BUTTON ?
}

bool Control::ClimberFrontDown3rd() {
    // std::cout << "Both Down" << std::endl;
    return rightJoystick->GetRawButton(ThrustJoystickButtons::leftButton);
}

bool Control::ClimberBackDown3rd() {
    return leftJoystick->GetRawButton(ThrustJoystickButtons::rightButton);
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

// bool Control::IrisExpand(){
//     // reutrn operatorControl->GetRawButton(buttonbox::iirs)
// }
/*
bool Control::ElevatorSmallMoveGet(){
    return ElevatorSmallMove;
}

void Control::ElevatorSmallMoveSet(bool move){
    //std::cout << "SmallMove" << std::endl;
    ElevatorSmallMove = move;
}*/

bool Control::IrisExpand(){
    return operatorControl->GetRawButton(buttonbox::irisopen);
}

bool Control::IrisShrink(){
    return operatorControl->GetRawButton(buttonbox::irisclosed);
}

bool Control::IrisExtend(){
    return operatorControl->GetRawButton(buttonbox::irisextend);
    
}

bool Control::ResetClimbEncoders() {
    return rightJoystick->GetRawButton(ThrustJoystickButtons::trigger);
}

bool Control::Climb3PID() {
    return leftJoystick->GetRawButton(ThrustJoystickButtons::trigger);
}

