#include "ElevatorPIDSource.h"

ElevatorPIDSource::ElevatorPIDSource() {

}

void ElevatorPIDSource::Set(double value) { 
    sensor_value = value;
}
    
double ElevatorPIDSource::PIDGet() {
    return sensor_value;
}