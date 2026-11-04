#include "SmartDevice.h"

SmartDevice::SmartDevice(const std::string& name) : name(name), on(false) {}
SmartDevice::SmartDevice(const SmartDevice& other) : name(other.name), on(other.on) {}
SmartDevice& SmartDevice::operator=(const SmartDevice& other) {
    if (this != &other) {
        name = other.name;
        on = other.on;
    }
    return *this;
}
SmartDevice::~SmartDevice() = default;
bool SmartDevice::isOn() const { return on; }

std::ostream& operator<<(std::ostream& out, const SmartDevice& device) {
    return out << device.name << ": " << device.getStatus();
}
