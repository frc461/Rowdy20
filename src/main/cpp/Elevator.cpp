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
    manualElevator = true;
    // std::thread elevatorThread(ElevatorThread);
    // elevatorThread.detach();
}

void RobotElevator::Periodic() {

    switch(control->RequestedPosition()) {
        case Control::ElevatorPosition::BallTower0:
            idealPosition = ELEVATOR_BallTower0;
            manualElevator = false;
            //std::cout << "BallTower0" << std::endl;
            break;
        case Control::ElevatorPosition::BallTower1:
            idealPosition = ELEVATOR_BallTower1;
            manualElevator = false;
            break;
        case Control::ElevatorPosition::BallTower2:
            idealPosition = ELEVATOR_BallTower2;
            manualElevator = false;
            break;
        case Control::ElevatorPosition::HatchTower0:
            idealPosition = ELEVATOR_HatchTower0;
            manualElevator = false;
            break;
        case Control::ElevatorPosition::HatchTower1:
            idealPosition = ELEVATOR_HatchTower1;
            manualElevator = false;
            break;
        case Control::ElevatorPosition::HatchTower2:
            idealPosition = ELEVATOR_HatchTower2;
            manualElevator = false;
            break;
        case Control::ElevatorPosition::CargoShip0:
            idealPosition = ELEVATOR_CargoShip0;
            manualElevator = false;
            break;
        case Control::manual:
            idealPosition = 0;
            manualElevator = true;
            break;
        default:
            break;
    }

    //Run motor with joystick, run to a position if it is not in use
    if((control->ElevatorOverrideJoystick() > 0.1 || control->ElevatorOverrideJoystick() < -0.1) && control->RequestedPosition() == 0){
        //manualElevator = true;
        RunMotorSafe((control->ElevatorOverrideJoystick() < -0.1) ? control->ElevatorOverrideJoystick() * 0.8 : control->ElevatorOverrideJoystick() * 1.8);
    }else {
        //std::cout << "manual override" << std::endl;

        if(manualElevator){
            //std::cout << "manual override enabled" << std::endl;
            RunMotorSafe(0);
        }else {
            //std::cout << "back to buttonbox mode" << std::endl;
            ElevatorThread();
            
        }
        
    }

    //Reset at Limit Switch
    if(!LimitSwitch->Get()){
        ////std::cout << "Limit Switch Reset" << std::endl;
        Elevator0->SetSelectedSensorPosition(0,0);
        // brake->Set(0);
        // RunMotorSafe(0);p
    }
    // std::cout << "Encoder" << Elevator0->GetSelectedSensorPosition() << std::endl;
}

void RobotElevator::RunMotorSafe(double speed) {
    speed = speed * -1;
//    std::cout << "Speed: " << speed << std::endl;
    if((speed < 0.1) && (speed > -0.1)){
     //   //std::cout << "speed in deadband, enable brake run motor safe" << std::endl;
        brake->Set(0); //Apply the brake if we are not going down
        Elevator0->Set(0);
       // //std::cout << "Dont run down" << std::endl;
    }else {
        
        if((!LimitSwitch->Get()) && ((speed) > 0)){//abs????????????????
           // //std::cout << "limit switch set" << std::endl;
            Elevator0->Set(0);
        }else {
            ////std::cout << "disable brake, drive elevator" << std::endl;
            brake->Set(1); 
            Elevator0->Set(speed);
        }
    }
}

void RobotElevator::ElevatorThread() {
    double currentPosition = Elevator0->GetSelectedSensorPosition();
    double topSlow = 0;
    double bottomSlow = 0;

    ////std::cout << "Encoder" << currentPosition << std::endl;
   /* 
    if(abs(ELEVATOR_MAX - currentPosition)/ELEVATOR_MAX > 0.9){
        topSlow = 1 - abs(ELEVATOR_MAX - currentPosition)/ELEVATOR_MAX;
    }
    */


    // if((currentPosition)/ELEVATOR_MAX < 0.2){
    if(currentPosition < ELEVATOR_HatchTower0 && manualElevator) {
        bottomSlow = 0.0;
    }

    // if(topSlow != 0 || bottomSlow != 0) {
    //     std::cout << "Top Slow: " << topSlow  << std::endl;
    //     std::cout << "Bottom Slow: " << bottomSlow<< std::endl;
    // }
    
    if((idealPosition - currentPosition) > 100){
       // //std::cout << "Less" << std::endl;
        RunMotorSafe(ELEVATOR_DEFAULT_SPEED + (idealPosition - currentPosition)/(ELEVATOR_MAX)*1.0 - bottomSlow);

    } else if((idealPosition - currentPosition) < -100) {
      //  //std::cout << "UDown" << std::endl;
        RunMotorSafe(-1 * ELEVATOR_DEFAULT_SPEED * 0.65 + 0.2);
    } else {
       // //std::cout << "None" << std::endl;
        RunMotorSafe(0);
    }
}

void RobotElevator::SetIdealPos(int PositionNum) {
    switch(PositionNum) {
        case Control::ElevatorPosition::BallTower0:
            idealPosition = ELEVATOR_BallTower0;
            manualElevator = false;
           // //std::cout << "BallTower0" << std::endl;
            break;
        case Control::ElevatorPosition::BallTower1:
            idealPosition = ELEVATOR_BallTower1;
            manualElevator = false;
            break;
        case Control::ElevatorPosition::BallTower2:
            idealPosition = ELEVATOR_BallTower2;
            manualElevator = false;
            break;
        case Control::ElevatorPosition::HatchTower0:
            idealPosition = ELEVATOR_HatchTower0;
            manualElevator = false;
            break;
        case Control::ElevatorPosition::HatchTower1:
            idealPosition = ELEVATOR_HatchTower1;
            manualElevator = false;
            break;
        case Control::ElevatorPosition::HatchTower2:
            idealPosition = ELEVATOR_HatchTower2;
            manualElevator = false;
            break;
        case Control::ElevatorPosition::CargoShip0:
            // idealPosition = 
            manualElevator = false;
            break;
        case Control::manual:
            idealPosition = 0;
            manualElevator = true;
            break;
        default:
            break;
    }
}

double RobotElevator::EncoderValue() {
    return Elevator0->GetSelectedSensorPosition();
}