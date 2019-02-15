#include "ElevatorPIDOutput.h"
#include <iostream>

ElevatorPIDOutput::ElevatorPIDOutput() {
    output = 0;
}

double ElevatorPIDOutput::GetOutput() {
    return this->output;
}

void ElevatorPIDOutput::PIDWrite(double output) {
    this->output = output;
}

