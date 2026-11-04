#include "SmartOutlet.h"
#include <sstream>

SmartOutlet::SmartOutlet(const std::string& name, double power, double voltage)
    : PoweredDevice(name, power), voltage(voltage) {}
SmartOutlet::SmartOutlet(const SmartOutlet& other)
    : PoweredDevice(other), ISensor(other), voltage(other.voltage) {}
SmartOutlet& SmartOutlet::operator=(const SmartOutlet& other) {
    if (this != &other) {
        PoweredDevice::operator=(other);
        voltage = other.voltage;
    }
    return *this;
}
double SmartOutlet::getCurrentVoltage() const { return voltage; }
void SmartOutlet::setVoltage(double value) { voltage = value; }
std::string SmartOutlet::getStatus() const {
    std::ostringstream out;
    out << "SmartOutlet " << (on ? "ON" : "OFF") << ", " << powerConsumption
        << " W, voltage=" << voltage;
    return out.str();
}
