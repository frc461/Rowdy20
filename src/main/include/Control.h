#ifndef SRC_CONTROL_H_
#define SRC_CONTROL_H_

#include <frc/WPILib.h>
#include "Control/ButtonBox.h"
#include "Control/XboxJoystickMap.h"
#include "Control/THRSTMSTRmap.h"

class Control {
    public:
        enum ElevatorPosition {
          manual = 0,
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
        bool IntakeDown();
        bool IntakeSpit();
        bool TacohDown();
        bool TacohOut();
        bool IrisExpand();
        bool IrisShrink();
        void ElevatorSmallMoveSet(bool move);
        bool ElevatorSmallMoveGet();
        bool getIrisExpand();
        bool getIRisShrink();
        Control();
    private:
        bool ElevatorSmallMove;
        frc::Joystick *leftJoystick;
        frc::Joystick *rightJoystick;
        frc::Joystick *overrideJoystick;
        frc::Joystick *operatorControl;
};

#endif 