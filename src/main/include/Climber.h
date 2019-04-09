#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include <frc/Preferences.h>

#include "CanStuff.h"
#include "Control.h"

#define FRONT_SPEED 1
#define BACK_SPEED -0.9

#define FRONT_SPEED_DEFAULT 0.6
#define BACK_SPEED_DEFAULT 0.3

#define FRONT_MAX 795
#define BACK_MAX 850

class Climber
{
public:
    Climber(Control* control, double frontSpeed, double backSpeed);
    void Periodic();
private:
    WPI_VictorSPX* FrontClimb;
	WPI_TalonSRX* BackClimb;

    Control* control;

    frc::Encoder *frontEncoder;
    frc::Encoder *backEncoder;

    double frontSpeed, backSpeed;

    void ClimberPIDLoop();
};