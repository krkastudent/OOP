/**
 * @file SmartOutlet.cpp
 * @brief Реализация класса SmartOutlet.
 */
#include "SmartOutlet.h"
#include <sstream>

using namespace std;

SmartOutlet::SmartOutlet(const string& name, double power, double voltage): PoweredDevice(name, power), voltage(voltage) {}
SmartOutlet::SmartOutlet(const SmartOutlet& other): PoweredDevice(other), ISensor(other), voltage(other.voltage) {}
SmartOutlet& SmartOutlet::operator=(const SmartOutlet& other) {
    if (this != &other) {
        PoweredDevice::operator=(other);
        voltage = other.voltage;
    }
    return *this;
}

double SmartOutlet::getCurrentVoltage() const { return voltage; }
void SmartOutlet::setVoltage(double value) { voltage = value; }
string SmartOutlet::getStatus() const {
    ostringstream out;
    out << "Розетка " << (on ? "включена" : "выключена") << ", " << powerConsumption << " Вт, напряжение=" << voltage << " В";
    return out.str();
}