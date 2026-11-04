/**
 * @mainpage Устройства умного дома - вариант 5
 * @section hierarchy Иерархия
 * SmartDevice -> PoweredDevice -> LightBulb, Thermostat, SmartOutlet.
 * SmartOutlet дополнительно реализует интерфейс ISensor.
 * @section data Данные и тесты
 * Из devices.txt загружаются 4 лампы, 3 термостата и 3 розетки.
 * SmartDevice, PoweredDevice и ISensor абстрактные и отдельно не создаются.
 * Один tests.cpp используется для клиентов статической и динамической библиотек.
 * @section energy Учёт энергии и копирование
 * При выключении учитывается расход: Вт * секунды / 3600000 = кВт·ч.
 * Копии сохраняют состояние и параметры, но начинают собственный отсчёт времени.
 * string обеспечивает независимое владение строками.
 */
/**
 * @file tests.cpp
 * @brief Клиентский код двух тестовых программ.
 */
#ifdef _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "LightBulb.h"
#include "Thermostat.h"
#include "SmartOutlet.h"
#include <array>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <thread>


using namespace std;

/**
 * @brief Загружает десять устройств и выполняет проверки задания.
 * @details Проверяет полиморфизм, статическую статистику, копирование, присваивание,
 * независимость копий, множественное наследование и обработку исключения.
 * Входные данные читаются из devices.txt в текущей рабочей папке.
 * @return 0 при успехе, 1 при перехваченном исключении.
 * @note Неудачный assert аварийно завершает тест.
 */
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // Вывод кириллицы в консоли Windows.
#endif
    try {
        ifstream file("devices.txt");
        if (!file) {
            throw runtime_error("Не удалось открыть файл devices.txt");
        }
        array<unique_ptr<SmartDevice>, 10> devices;
        int bulbs = 0, thermostats = 0, outlets = 0;
        for (auto& device : devices) {
            string type, name;
            double power;
            int state;
            if (!(file >> type >> name >> power >> state) || (state != 0 && state != 1)) {
                throw runtime_error("Неверная запись об устройстве");
            }
            if (type == "ЛАМПА") {
                int brightness;
                string color;
                if (!(file >> brightness >> color)) {
                    throw runtime_error("Неверные данные лампы");
                }
                device = make_unique<LightBulb>(name, power, brightness, color);
                ++bulbs;
            } else if (type == "ТЕРМОСТАТ") {
                double temperature;
                string mode;
                if (!(file >> temperature >> mode)) {
                    throw runtime_error("Неверные данные термостата");
                }
                device = make_unique<Thermostat>(name, power, temperature, mode);
                ++thermostats;
            } else if (type == "РОЗЕТКА") {
                double voltage;
                if (!(file >> voltage)) {
                    throw runtime_error("Неверные данные розетки");
                }
                device = make_unique<SmartOutlet>(name, power, voltage);
                ++outlets;
            } else {
                throw runtime_error("Неизвестный тип устройства");
            }
            if (state) {
                device->turnOn();
            }
            cout << *device << '\n'; // Дружественная функция и виртуальный getStatus.
            device->turnOff();
        }
        assert(bulbs >= 3 && thermostats >= 3 && outlets >= 3);

        // Полиморфизм и общий расход за фактическое время между включением и выключением.
        const double before = PoweredDevice::getTotalEnergyConsumed();
        double watts = 0;
        const auto firstOn = chrono::steady_clock::now();
        for (auto& device : devices) {
            device->turnOn();
            watts += dynamic_cast<PoweredDevice&>(*device).getPowerUsage();
        }
        const auto lastOn = chrono::steady_clock::now();
        this_thread::sleep_for(chrono::milliseconds(20));
        const auto firstOff = chrono::steady_clock::now();
        for (auto& device : devices) {
            device->turnOff();
        }
        const auto lastOff = chrono::steady_clock::now();
        const double energy = PoweredDevice::getTotalEnergyConsumed() - before;
        const double minimum = watts * chrono::duration<double>(firstOff - lastOn).count() / 3600000;
        const double maximum = watts * chrono::duration<double>(lastOff - firstOn).count() / 3600000;
        assert(energy >= minimum - 1e-12 && energy <= maximum + 1e-12 && energy > 0);
        const double after = PoweredDevice::getTotalEnergyConsumed();
        for (auto& device : devices) {
            device->turnOff();
        }
        assert(PoweredDevice::getTotalEnergyConsumed() == after);
        cout << "Потреблено энергии: " << energy << " кВт·ч\n";

        // Копирование и присваивание лампы: состояние и все параметры сохраняются.
        auto& bulb = dynamic_cast<LightBulb&>(*devices[0]);
        bulb.turnOn();
        const string bulbState = bulb.getStatus();
        LightBulb bulbCopy(bulb), bulbAssigned("Копия", 1, 0, "красный");
        bulbAssigned = bulb;
        assert(bulbCopy.getStatus() == bulb.getStatus() && bulbAssigned.getStatus() == bulb.getStatus());
        assert(bulbCopy.isOn() && bulbAssigned.isOn());
        assert(abs(bulb.getPowerUsage() - 12.0) < 1e-12);
        bulb.setBrightness(10);
        assert(abs(bulb.getPowerUsage() - 1.2) < 1e-12);
        bulb.turnOff();
        assert(bulbCopy.getStatus() == bulbState && bulbAssigned.getStatus() == bulbState);
        bulbCopy.turnOff();
        bulbAssigned.turnOff();

        auto& thermostat = dynamic_cast<Thermostat&>(*devices[4]);
        thermostat.turnOn();
        const string thermostatState = thermostat.getStatus();
        Thermostat thermostatCopy(thermostat), thermostatAssigned("Копия", 1, 0, "выключен");
        thermostatAssigned = thermostat;
        assert(thermostatCopy.getStatus() == thermostat.getStatus());
        assert(thermostatAssigned.getStatus() == thermostat.getStatus());
        assert(thermostatCopy.isOn() && thermostatAssigned.isOn());
        thermostat.setTemperature(30);
        thermostat.turnOff();
        assert(thermostatCopy.getStatus() == thermostatState && thermostatAssigned.getStatus() == thermostatState);
        thermostatCopy.turnOff();
        thermostatAssigned.turnOff();

        auto& outlet = dynamic_cast<SmartOutlet&>(*devices[7]);
        outlet.turnOn();
        assert(outlet.getPowerUsage() == 200.0);
        const string outletState = outlet.getStatus();
        SmartOutlet outletCopy(outlet), outletAssigned("Копия", 1, 220);
        outletAssigned = outlet;
        assert(outletCopy.getStatus() == outlet.getStatus() && outletAssigned.getStatus() == outlet.getStatus());
        assert(outletCopy.isOn() && outletAssigned.isOn());
        outlet.setVoltage(210);
        outlet.turnOff();
        assert(outletCopy.getStatus() == outletState && outletAssigned.getStatus() == outletState);
        outletCopy.turnOff();
        outletAssigned.turnOff();

        // Вызов через второй базовый класс розетки — интерфейс ISensor.
        for (auto& device : devices) {
            if (auto* sensor = dynamic_cast<ISensor*>(device.get())) {
                assert(sensor->getCurrentVoltage() > 0);
                cout << "Напряжение: " << sensor->getCurrentVoltage() << " В\n";
            }
        }
        bool caught = false;
        try { bulb.setBrightness(150); }
        catch (const invalid_argument& error) {
            caught = true;
            cout << "Исключение обработано: " << error.what() << '\n';
        }
        assert(caught);
        cout << "Все проверки пройдены\n";
    } catch (const exception& error) {
        cerr << error.what() << '\n';
        return 1;
    }
}
