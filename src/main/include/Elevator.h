#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

#include "CanStuff.h"
#include "Control.h"

class RobotElevator {
    public:
        RobotElevator(Control *control);
        void Periodic();
    private:
        WPI_TalonSRX *Elevator0;
        WPI_VictorSPX *Elevator1;
        Control *control;
        frc::Solenoid *brake;
};