#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

#include "Control.h"
#include "PneumaticsStuff.h"
#include "CanStuff.h"
#include "Hatch.h"
#include "Elevator.h"

#include <networktables/NetworkTableEntry.h>

class Tacoh {
    public:
        Tacoh(Control *control, Hatch *hatch,  RobotElevator *elevator, std::shared_ptr<nt::NetworkTable> HUD);
        void Periodic();
    private:
        Control *control;
        WPI_VictorSPX *TacohIntake;
        frc::Solenoid *TacohExtend;
        //frc::Solenoid *IrisControl
        bool DownHasRun;
        int Counter;
        Hatch *hatch;
        frc::DigitalInput *tacohSwitch;

        nt::NetworkTableEntry ntTacoh;
        nt::NetworkTableEntry ntTacohSwitch;

        RobotElevator  *elevator;
        
        bool AutoSwitchEnabled;
};