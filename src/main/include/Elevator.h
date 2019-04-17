#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

#include "CanStuff.h"
#include "Control.h"

#define ELEVATOR_DEFAULT_SPEED 0.40
#define ELEVATOR_ZERO_SPEED 0
#define ELEVATOR_MAX 3400

#define ELEVATOR_BallTower0 0
#define ELEVATOR_BallTower1 1658
#define ELEVATOR_BallTower2 3216
#define ELEVATOR_HatchTower0 277//was 418
#define ELEVATOR_HatchTower1 1895
#define ELEVATOR_HatchTower2 3530
#define ELEVATOR_CargoShip0 851


#ifndef SRC_ELEVATOR_H_
#define SRC_ELEVATOR_H_
class RobotElevator {
    public:
        RobotElevator(Control *control);
        void Periodic();
        void SetIdealPos(int);

        double EncoderValue();
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

#endif