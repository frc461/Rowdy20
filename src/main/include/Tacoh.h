#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

#include "Control.h"
#include "PneumaticsStuff.h"
#include ""

class Tacoh {
    public:
        Tacoh();
    private:
        WPI_VictorSPX *TacohIntake;
        frc::Solenoid *TacohExtend;
}