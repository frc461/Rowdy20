#include "Elevator.h"

#include <iostream>

RobotElevator::RobotElevator(Control *control) {
    Elevator0 = new WPI_TalonSRX(CanChain::elevator0);
    Elevator1 = new WPI_VictorSPX(CanChain::elevator1);
    brake = new frc::Solenoid(3);
    Elevator1->Follow(*Elevator0);
    this->control = control;
    idealPosition = 0;
    LimitSwitch = new frc::DigitalInput(0); //0 is the GPIO port the limit switch is plugged into

    // std::thread elevatorThread(ElevatorThread);
    // elevatorThread.detach();
}

void RobotElevator::Periodic() {

    std::cout << "Controller: " << control->RequestedPosition() << std::endl;
    std::cout << "Ideal Pos: " << idealPosition << std::endl;
    std::cout << "Current Pos: " << Elevator0->GetSelectedSensorPosition() << std::endl;;
    std::cout << "Brake State: " << brake->Get() << std::endl;


    // Elevator0->Set(control->ElevatorOverrideJoystick());

    // // control->ElevatorOverrideJoystick() > 0.1 || control->ElevatorOverrideJoystick() < -0.1
    // if(Elevator0->Get() == 0){
    //     std::cout << "Speed Zero" << std::endl;
    //     brake->Set(1);
    // } else{
    //     brake->Set(0);
    // }


    switch(control->RequestedPosition()) {
        case Control::ElevatorPosition::BallTower0:
            idealPosition = ELEVATOR_BallTower0;
            break;
        case Control::ElevatorPosition::BallTower1:
            idealPosition = ELEVATOR_BallTower1;
            break;
        case Control::ElevatorPosition::BallTower2:
            idealPosition = ELEVATOR_BallTower2;
            break;
        case Control::ElevatorPosition::HatchTower0:
            idealPosition = ELEVATOR_HatchTower0;
            break;
        case Control::ElevatorPosition::HatchTower1:
            idealPosition = ELEVATOR_HatchTower1;
            break;
        case Control::ElevatorPosition::HatchTower2:
            idealPosition = ELEVATOR_HatchTower2;
            break;
        default:
            break;
    }

    if(control->ElevatorSmallMoveGet()){
        idealPosition = ELEVATOR_HatchTower1;
    }

    //Run motor with joystick, run to a position if it is not in use
    if(control->ElevatorOverrideJoystick() > 0.1 || control->ElevatorOverrideJoystick() < -0.1){
        RunMotorSafe(control->ElevatorOverrideJoystick() * ELEVATOR_DEFAULT_SPEED);
    }else {
        ElevatorThread();
    }

    //Reset at Limit Switch
    if(!LimitSwitch->Get()){
        Elevator0->SetSelectedSensorPosition(0,0);
        // brake->Set(0);
        RunMotorSafe(0);
    }
}

void RobotElevator::RunMotorSafe(double speed) {
    speed = speed * -1;
    if(speed == 0){
        brake->Set(0); //Apply the brake if we are not going down
        Elevator0->Set(0);
        std::cout << "Dont run down" << std::endl;
    }else {
        if(LimitSwitch->Get() && speed > 0){
            Elevator0->Set(0);
        }else {
            std::cout << "Speed: " << speed << std::endl;
            brake->Set(1); 
            Elevator0->Set(speed);
        }
    }
}

void RobotElevator::ElevatorThread() {
    double currentPosition = Elevator0->GetSelectedSensorPosition();
    double topSlow = 0;
    double bottomSlow = 0;

    if(abs(ELEVATOR_MAX - currentPosition)/ELEVATOR_MAX > 0.9){
        topSlow = 1 - abs(ELEVATOR_MAX - currentPosition)/ELEVATOR_MAX;
    }


    if(abs(0 - currentPosition)/ELEVATOR_MAX < 0.1){
        bottomSlow = abs(0 - currentPosition)/ELEVATOR_MAX;
    }

    if((idealPosition - currentPosition) > 100){
        RunMotorSafe(ELEVATOR_DEFAULT_SPEED - 0.1 + abs(idealPosition - currentPosition)/(ELEVATOR_MAX * 4) - topSlow - bottomSlow);
    } else if((idealPosition - currentPosition) < -100) {
        RunMotorSafe(-1 * ELEVATOR_DEFAULT_SPEED/2 + 0.2 + topSlow + bottomSlow);
    } else {
        RunMotorSafe(0);
    }
}