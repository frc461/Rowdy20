#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

#include "Control.h"
#include "PneumaticsStuff.h"
#include "CanStuff.h"
#include "Hatch.h"

class Tacoh {
    public:
        Tacoh(Control *control, Hatch *hatch);
        void Periodic();
    private:
        Control *control;
        WPI_VictorSPX *TacohIntake;
        frc::Solenoid *TacohExtend;
        //frc::Solenoid *IrisControl
        bool DownHasRun;
        int Counter;
        Hatch *hatch;
};