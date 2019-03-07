#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

#include "Control.h"
#include "PneumaticsStuff.h"
#include "CanStuff.h"
#include "Iris.h"

class Tacoh {
    public:
        Tacoh(Control *control, Iris *iris);
        void Periodic();
    private:
        Control *control;
        WPI_VictorSPX *TacohIntake;
        frc::Solenoid *TacohExtend;
        bool DownHasRun;
        int Counter;
        Iris *iris;
};