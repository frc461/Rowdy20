#include "Hatch.h"

Hatch::Hatch(Control *control) {
    this->control = control;

    iris = new frc::DoubleSolenoid(Pneumatics::Iris0P, Pneumatics::Iris1P);
    irisExtend = new frc::Solenoid(Pneumatics::IrisExtendP);

    state = false;
}

void Hatch::Periodic() {
    if(state) {
        iris->Set(frc::DoubleSolenoid::Value::kForward);
    } else {
        iris->Set(frc::DoubleSolenoid::Value::kReverse);
    }

    if(control->IrisExpand()){
        Hatch::Expand();
    }else if(control->IrisShrink()) {
        Hatch::Shrink();
    }

    if(control->IrisExtend()){
        irisExtend->Set(1);
    }else {
        irisExtend->Set(0);
    }
}

void Hatch::Expand() {
    state = true;
}

void Hatch::Shrink() {
    state = false;
}