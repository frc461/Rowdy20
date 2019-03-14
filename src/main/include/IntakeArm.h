#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

#include "Control.h"
#include "CanStuff.h"
#include "PneumaticsStuff.h"


#define IDLE_SPEED -0.1
#define INTAKE_IN_SPEED -1
#define INTAKE_OUT_SPEED 0.6

class IntakeArm {
    public:
        IntakeArm(Control *control);

        void Periodic();
    private:
        WPI_VictorSPX *Intake;
        frc::Solenoid *IntakeExtend;

        Control *control;
};