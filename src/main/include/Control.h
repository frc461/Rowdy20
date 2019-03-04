#ifndef SRC_CONTROL_H_
#define SRC_CONTROL_H_

#include <frc/WPILib.h>
#include "Control/ButtonBox.h"
#include "Control/XboxJoystickMap.h"
#include "Control/THRSTMSTRmap.h"

class Control {
    public:
        enum ElevatorPosition {
          manual,
          BallTower0,
          BallTower1,
          BallTower2,
          HatchTower0,
          HatchTower1,
          HatchTower2  
        }; 
        ElevatorPosition RequestedPosition();
        double ElevatorOverrideJoystick();
        double LeftJoystickArcade();
        double RightJoystickArcade();
        Control();
    private:
        frc::Joystick *leftJoystick;
        frc::Joystick *rightJoystick;
        frc::Joystick *overrideJoystick;
        frc::Joystick *operatorControl;
};

#endif 