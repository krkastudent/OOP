/**
 * @file SmartDevice.h
 * @brief Объявление класса SmartDevice.
 */
#pragma once
#include <ostream>
#include <string>

using namespace std;

/**
 * @brief Абстрактное устройство умного дома: первый уровень иерархии.
 * @details Хранит имя и состояние включён/выключен. Самостоятельный экземпляр создать нельзя.
 */
class SmartDevice {
protected:
    string name; ///< Имя устройства; строка владеет своим содержимым.
    bool on;     ///< Состояние питания: true - включено.

    /**
     * @brief Создаёт выключенное устройство.
     * @param name Имя устройства.
     */
    SmartDevice(const string& name);

    /**
     * @brief Создаёт независимую копию состояния и параметров.
     * @param other Копируемый объект.
     */
    SmartDevice(const SmartDevice& other);

    /**
     * @brief Присваивает состояние и параметры другого объекта.
     * @param other Объект-источник.
     * @return Ссылка на текущий объект.
     * @details Самоприсваивание сохраняет объект без изменений.
     */
    SmartDevice& operator=(const SmartDevice& other);

public:
    /**
     * @brief Обеспечивает удаление наследников через базовый указатель.
     */
    virtual ~SmartDevice();

    /**
     * @brief Включает устройство.
     */
    virtual void turnOn() = 0;

    /**
     * @brief Выключает устройство.
     */
    virtual void turnOff() = 0;

    /**
     * @brief Формирует строку с типом, состоянием и параметрами устройства.
     * @return Строка состояния.
     */
    virtual string getStatus() const = 0;

    /**
     * @brief Проверяет состояние питания.
     * @return true, если устройство включено; иначе false.
     */
    bool isOn() const;

    /**
     * @brief Выводит имя и полиморфное описание устройства.
     * @param out Поток вывода.
     * @param device Выводимое устройство.
     * @return Переданный поток вывода.
     * @details Дружественная функция имеет доступ к защищённому имени.
     */
    friend ostream& operator<<(ostream& out, const SmartDevice& device);
};
