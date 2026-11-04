#pragma once
#include <ostream>
#include <string>

class SmartDevice {
protected:
    std::string name;
    bool on;
    SmartDevice(const std::string& name);
    SmartDevice(const SmartDevice& other);
    SmartDevice& operator=(const SmartDevice& other);

public:
    virtual ~SmartDevice();
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual std::string getStatus() const = 0;
    bool isOn() const;
    friend std::ostream& operator<<(std::ostream& out, const SmartDevice& device);
};
