#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

#include "Control.h"
#include "PneumaticsStuff.h"
#include "CanStuff.h"

class Tacoh {
    public:
        Tacoh(Control *control);
        void Periodic();
    private:
        Control *control;
        WPI_VictorSPX *TacohIntake;
        frc::Solenoid *TacohExtend;
        bool DownHasRun;
        int Counter;
};