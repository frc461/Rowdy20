#include "WPILib.h"

class ElevatorPIDSource : public frc::PIDSource {
    private:
        double sensor_value;
    public:
        ElevatorPIDSource();

        void Set(double value);
        double PIDGet();
};