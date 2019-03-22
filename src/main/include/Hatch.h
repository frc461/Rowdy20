#ifndef SRC_IRIS_H_
#define SRC_IRIS_H_

#include <frc/WPILib.h>

#include "Control.h"
#include "PneumaticsStuff.h"

class Hatch {
    public:
        Hatch(Control *control);

        void Periodic();

        void Expand();
        void Shrink();
    private:
        frc::DoubleSolenoid *iris;
        frc::Solenoid *irisExtend;

        Control *control;

        bool state;
};

#endif