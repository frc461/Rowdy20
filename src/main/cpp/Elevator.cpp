#include "Elevator.h"

#include <iostream>

RobotElevator::RobotElevator(Control *control) {
    Elevator0 = new WPI_TalonSRX(CanChain::elevator0);
    Elevator1 = new WPI_VictorSPX(CanChain::elevator1);
    brake = new frc::Solenoid(3);
    Elevator1->Follow(*Elevator0);
    this->control = control;
}

void RobotElevator::Periodic() {
    Elevator0->Set(control->ElevatorOverrideJoystick());
    // control->ElevatorOverrideJoystick() > 0.1 || control->ElevatorOverrideJoystick() < -0.1
    if(Elevator0->Get() == 0){
        std::cout << "Speed Zero" << std::endl;
        brake->Set(1);
    } else{
        brake->Set(0);
    }
}