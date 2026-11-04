#pragma once
#include "PoweredDevice.h"

class LightBulb : public PoweredDevice {
    int brightness;
    std::string color;
public:
    LightBulb(const std::string& name, double power, int brightness, const std::string& color);
    LightBulb(const LightBulb& other);
    LightBulb& operator=(const LightBulb& other);
    void setBrightness(int value);
    double getPowerUsage() const override;
    std::string getStatus() const override;
};
