#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

#include "CanStuff.h"
#include "Control.h"

#define ELEVATOR_DEFAULT_SPEED 0.7
#define ELEVATOR_ZERO_SPEED 0
#define ELEVATOR_MAX 3400

#define ELEVATOR_BallTower0 0
#define ELEVATOR_BallTower1 1658
#define ELEVATOR_BallTower2 3206
#define ELEVATOR_HatchTower0 277//was 418
#define ELEVATOR_HatchTower1 1870
#define ELEVATOR_HatchTower2 3520

class RobotElevator {
    public:
        RobotElevator(Control *control);
        void Periodic();
        void SetIdealPos(int);
    private:
        WPI_TalonSRX *Elevator0;
        WPI_VictorSPX *Elevator1;
        Control *control;
        frc::Solenoid *brake;
        void ElevatorThread();
        double idealPosition;
        void RunMotorSafe(double speed);
        frc::DigitalInput *LimitSwitch;
        bool manualElevator;
};