#ifndef SRC_IRIS_H_
#define SRC_IRIS_H_

#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

#include "Control.h"
#include "PneumaticsStuff.h"
#include "CanStuff.h"

#define IRIS_MinVal 1.7
#define IRIS_MaxVal 2.1

class Iris {
    public:
        Iris(Control *control);

        void Periodic();
        void Expand();
        void Shrink();
    private:
        WPI_VictorSPX *IrisM;
        frc::Solenoid *IrisEject;

        frc::AnalogInput *pot;

        bool state;

        Control *control;
};

#endif