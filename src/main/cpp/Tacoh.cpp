#include "Tacoh.h"

#include <iostream>

// bool IntakeTemp;
// double IntakeTempT;
// bool downTemp;
// bool downTempSinglePress;

bool counterState;

Tacoh::Tacoh(Control *control, Hatch *hatch,  std::shared_ptr<nt::NetworkTable> HUD) {
    this->control = control;
    TacohIntake = new WPI_VictorSPX(CanChain::taco);
    TacohExtend = new frc::Solenoid(Pneumatics::TacoP);
    //IrisControl = new frc::Solenoid();
    // this->iris = iris;
    this->hatch = hatch;
    DownHasRun = false;
    Counter = 50;
    // Counter2 = 0;
    // IntakeTemp = false;
    // IntakeTempT = 0;
    // downTemp = false;
    // downTempSinglePress = false;

    tacohSwitch = new frc::DigitalInput(1);

    ntTacoh = HUD->GetEntry("tacoh");
    ntTacohSwitch = HUD->GetEntry("tacohHatch");
}

void Tacoh::Periodic() {
    if(control->TacohDown()){
        // control->ElevatorSmallMoveSet(1);
        // iris->Shrink();
        // hatch->Shrink();
        // IrisControl->Set(1);[]
        TacohExtend->Set(1);
        TacohIntake->Set(0.8);
        // DownHasRun = false;
    }else if(control->TacohOut()){
        // control->ElevatorSmallMoveSet(1);
        TacohExtend->Set(1);
        TacohIntake->Set(-0.8);
        // DownHasRun = false;
    } else {
        // control->ElevatorSmallMoveSet(0);
        // std::cout << DownHasRun << std::endl;
        // if(Counter == 0 && Counter2 == 0){
        //     TacohExtend->Set(0);
        // }
        // if (control->IntakeDown()) {
        //     downTempSinglePress = true;
        //     if(!DownHasRun){
        //          Counter = 0;
        //         Counter2 = 0;
        //         DownHasRun = true;
        //     }
        // }
        // }else if(!control->IntakeDown()){
        //     // std::cout << downTemp << std::endl;
        //     if(downTempSinglePress) {
        //         downTempSinglePress = false;
        //         // downTemp = true;
        //         DownHasRun = true;
        //     }
        // }   
        // if(DownHasRun){
        //     std::cout << Counter << std::endl;
        //     TacohExtend->Set(1);
        //     if(Counter > 50) {
        //         TacohExtend->Set(0);
                
        //         // iris->Expand();
        //         // hatch->Expand();
        //         //TODO: Run iris
        //         // if(!control->IntakeDown()) {
        //             DownHasRun = false;
        //             // Counter = 0;
        //         // }
        //     }else {
        //         Counter++;
        //     }
        // } else if(downTemp) {
        // //     TacohExtend->Set(1);
        //     // std::cout << downTemp << std::endl;
        //     if(Counter2 > 50) {
        //         TacohExtend->Set(0);
        //         Counter2 = 0;
        //         downTemp = false;
        //     }else {
        //         Counter2++;
        //     }
        // } else {
        //     TacohExtend->Set(0);
        //     TacohIntake->Set(0);
        // }

        if(control->IntakeDown()) {
            if(counterState == 0) {
                Counter = 0;
                counterState = 1;
            } else {
                Counter++;
            }
        }else if(!control->IntakeDown()) {
            if(counterState == 1) {
                Counter = 0;
                counterState = 0;
            } else {
                Counter++;
            }
        }
        if(Counter < 50){
            TacohExtend->Set(1);
            TacohIntake->Set(0);
        }else {
            TacohExtend->Set(0);
            TacohIntake->Set(0);
        }
    }

    if(TacohExtend->Get()){
        ntTacoh.SetBoolean(true);
    }else {
        ntTacoh.SetBoolean(false);
    }

    ntTacohSwitch.SetBoolean(!tacohSwitch->Get());
    // std::cout << tacohSwitch->Get() << std::endl;
}