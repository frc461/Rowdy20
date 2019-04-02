#ifndef SRC_IRIS_H_
#define SRC_IRIS_H_

#include <frc/WPILib.h>

#include "Control.h"
#include "PneumaticsStuff.h"

#include <networktables/NetworkTableEntry.h>

class Hatch {
    public:
        Hatch(Control *control, std::shared_ptr<nt::NetworkTable> HUD);

        void Periodic();

        void Expand();
        void Shrink();

        bool TacohOverride();
    private:
        frc::DoubleSolenoid *iris;
        frc::Solenoid *irisExtend;

        Control *control;

        bool state;
        bool tacohOverride;

        nt::NetworkTableEntry ntHatch;
        nt::NetworkTableEntry ntExtend;

        frc::DigitalInput *hatchSwitch;  
};

#endif