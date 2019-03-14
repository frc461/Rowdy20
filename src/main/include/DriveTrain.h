#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

#include "CanStuff.h"
#include "Control.h"

class DriveTrain {
    public:
        DriveTrain(Control *control);

        void Periodic();
    private:
        WPI_TalonSRX *RMotor0;
        WPI_VictorSPX *RMotor1;
        WPI_VictorSPX *RMotor2;

        WPI_TalonSRX *LMotor0;
        WPI_VictorSPX *LMotor1;
        WPI_VictorSPX *LMotor2;

        frc::PWMVictorSPX* BottomWheels;

        frc::SpeedControllerGroup *DTLeft;
        frc::SpeedControllerGroup *DTRight;

        frc::DifferentialDrive *driveTrain;

        Control *control;
};