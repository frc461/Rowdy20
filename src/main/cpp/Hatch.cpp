#include "Hatch.h"

#include <iostream>

bool switchActivateOnce;

Hatch::Hatch(Control *control, std::shared_ptr<nt::NetworkTable> HUD) {
    this->control = control;

    iris = new frc::DoubleSolenoid(Pneumatics::Iris0P, Pneumatics::Iris1P);
    irisExtend = new frc::Solenoid(Pneumatics::IrisExtendP);

    ntHatch = HUD->GetEntry("hatch");
    ntExtend = HUD->GetEntry("hatchExtend");

    hatchSwitch = new frc::DigitalInput(8);

    state = false;
    tacohOverride = false;
    switchActivateOnce = false;
}

void Hatch::Periodic() {
    if(state) {
        iris->Set(frc::DoubleSolenoid::Value::kForward);
        ntHatch.SetBoolean(true);
    }  else {
        iris->Set(frc::DoubleSolenoid::Value::kReverse);
        ntHatch.SetBoolean(false);
    } 

    if(control->IrisExpand()){
        Hatch::Expand();
    }else if(control->IrisShrink()) {
        Hatch::Shrink();
    }else if(control->IntakeDown()) {
        Hatch::Shrink();
    }

    if(control->TacohDown() || control->TacohOut()){
        Hatch::Expand();
        ntHatch.SetBoolean(true);
    }

    if(control->IrisExtend()){
        irisExtend->Set(1);
        ntExtend.SetBoolean(true);
    }else {
        irisExtend->Set(0);
        ntExtend.SetBoolean(false);
    }

    if(!control->OverrideSW()) {
        if(!hatchSwitch->Get()) {
            //std::cout << hatchSwitch->Get() << std::endl;
            if(!switchActivateOnce) {
                switchActivateOnce = true;
                Hatch::Shrink();
            }
        } else {
            switchActivateOnce = false;
        }
    }
}

void Hatch::Expand() {
    state = true;
}

void Hatch::Shrink() {
    state = false;
}

bool Hatch::TacohOverride() {
    return tacohOverride;
}