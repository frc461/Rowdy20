#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

#include "CanStuff.h"
#include "Control.h"

#define ELEVATOR_DEFAULT_SPEED 0.4
#define ELEVATOR_MAX 3200

#define ELEVATOR_BallTower0 0
#define ELEVATOR_BallTower1 1558
#define ELEVATOR_BallTower2 3106
#define ELEVATOR_HatchTower0 418
#define ELEVATOR_HatchTower1 2080
#define ELEVATOR_HatchTower2 3310

class RobotElevator {
    public:
        RobotElevator(Control *control);
        void Periodic();
    private:
        WPI_TalonSRX *Elevator0;
        WPI_VictorSPX *Elevator1;
        Control *control;
        frc::Solenoid *brake;
        void ElevatorThread();
        double idealPosition;
        void RunMotorSafe(double speed);
        frc::DigitalInput *LimitSwitch;
};