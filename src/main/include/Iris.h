#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

#include "Control.h"
#include "PneumaticsStuff.h"
#include "CanStuff.h"

class Iris {
    private:
        Iris(Control *control);

        void Periodic();
    public:
        WPI_VictorSPX *IrisM;
        frc::Solenoid *IrisEject;

        Control *control;
};