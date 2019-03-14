#include <ctre/Phoenix.h>

#include "CanStuff.h"
#include "Control.h"

#define ELEVATOR_DEFAULT_SPEED 0.7
#define ELEVATOR_MAX 3400

#define ELEVATOR_BallTower0 0
#define ELEVATOR_BallTower1 1658
#define ELEVATOR_BallTower2 3206
#define ELEVATOR_HatchTower0 468//was 418
#define ELEVATOR_HatchTower1 2080
#define ELEVATOR_HatchTower2 3520

class Elevator
{
public:
    Elevator(Control* control);
    void Periodic();
private:
    WPI_TalonSRX *Elevator0;
    WPI_VictorSPX *Elevator1;
    Control *control;
    frc::Solenoid *brake;
    frc::DigitalInput *LimitSwitch;
};