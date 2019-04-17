#ifndef SRC_CONTROL_H_
#define SRC_CONTROL_H_

#include <frc/WPILib.h>
#include "Control/ButtonBox.h"
#include "Control/XboxJoystickMap.h"
#include "Control/THRSTMSTRmap.h"

#define ELEVATOR_BallTower0 0
#define ELEVATOR_BallTower1 1658
#define ELEVATOR_BallTower2 3206
#define ELEVATOR_HatchTower0 468//was 418
#define ELEVATOR_HatchTower1 2080
#define ELEVATOR_HatchTower2 3520
#define MANUAL_CONSTANT 200

class Control {
    public:
        enum ElevatorPosition {
          manual = 0,
          BallTower0,
          BallTower1,
          BallTower2,
          HatchTower0,
          HatchTower1,
          HatchTower2,
          CargoShip0
        }; 
        ElevatorPosition CurrentPosition;
        ElevatorPosition RequestedPosition();
        int RequestedPosition2();
        double ElevatorOverrideJoystick();
        double LeftJoystickArcade();
        double RightJoystickArcade();
        bool CameraUpButton();
        bool CameraDownButton();
        bool ClimberFrontDown();
        bool ClimberBackDown();
        bool ClimberFrontUp();
        bool ClimberBackUp();
        bool ClimberFrontDown3rd();
        bool ClimberBackDown3rd();
        bool IntakeDown();
        bool IntakeSpit();
        bool TacohDown();
        bool TacohOut();
        bool IrisExpand();
        bool IrisShrink();
        bool IrisExtend();
        //void ElevatorSmallMoveSet(bool move);
        //bool ElevatorSmallMoveGet();
        bool getIrisExpand();
        bool getIRisShrink();
        bool ResetClimbEncoders();
        bool Climb3PID();
        Control();
        int CurrentSetPoint;
    private:
        bool ElevatorSmallMove;
        frc::Joystick *leftJoystick;
        frc::Joystick *rightJoystick;
        frc::Joystick *overrideJoystick;
        frc::Joystick *operatorControl;
};

#endif 