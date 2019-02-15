#include "frc/WPILib.h"

class ElevatorPIDOutput : public frc::PIDOutput {
    public:
        double output;
        ElevatorPIDOutput();

        double GetOutput();

        void PIDWrite(double output);
};