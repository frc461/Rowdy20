#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include <frc/Preferences.h>

#include "CanStuff.h"
#include "Control.h"

#define FRONT_SPEED 1
#define BACK_SPEED -0.9

class Climber
{
public:
    Climber(Control* control, double frontSpeed, double backSpeed);
    void Periodic();
private:
    WPI_TalonSRX* FrontClimb;
	WPI_VictorSPX* BackClimb;

    Control* control;

    double frontSpeed, backSpeed;
};