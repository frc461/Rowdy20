#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

#include "CanStuff.h"
#include "Control.h"
//#include "Robot.h"
#include "Control/THRSTMSTRmap.h"


class CamServo
{   
public:
    CamServo(Control* control);
    void Periodic();
private:
    frc::Servo *camServo;
    Control* control;
};