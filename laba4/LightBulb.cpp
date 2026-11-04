/**
 * @file LightBulb.cpp
 * @brief Реализация класса LightBulb.
 */
#include "LightBulb.h"
#include <sstream>
#include <stdexcept>

using namespace std;

LightBulb::LightBulb(const string& name, double power, int brightness, const string& color): PoweredDevice(name, power), brightness(0), color(color) {
    setBrightness(brightness);
}

LightBulb::LightBulb(const LightBulb& other): PoweredDevice(other), brightness(other.brightness), color(other.color) {}
LightBulb& LightBulb::operator=(const LightBulb& other) {
    if (this != &other) {
        PoweredDevice::operator=(other);
        brightness = other.brightness;
        color = other.color;
    }
    return *this;
}

void LightBulb::setBrightness(int value) {
    if (value < 0 || value > 100) {
        throw invalid_argument("Яркость должна быть от 0 до 100 процентов");
    }
    const bool wasOn = on;
    if (wasOn) {
        turnOff();
    }
    brightness = value;
    if (wasOn) {
        turnOn();
    }
}

double LightBulb::getPowerUsage() const {
    return PoweredDevice::getPowerUsage() * (brightness / 100.0);
}

string LightBulb::getStatus() const {
    ostringstream out;
    out << "Лампа " << (on ? "включена" : "выключена") << ", " << powerConsumption << " Вт, яркость=" << brightness << "%, цвет=" << color;
    return out.str();
}
