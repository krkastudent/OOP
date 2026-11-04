/**
 * @file LightBulb.h
 * @brief Объявление класса LightBulb.
 */
#pragma once
#include "PoweredDevice.h"

using namespace std;

/**
 * @brief Умная лампа: третий уровень иерархии.
 * @details Потребление зависит от яркости.
 */
class LightBulb : public PoweredDevice {
    int brightness; ///< Яркость лампы от 0 до 100 процентов.
    string color; ///< Цвет лампы; строка копируется независимо.
public:
    /**
     * @brief Создаёт выключенную лампу.
     * @param name Имя лампы.
     * @param power Номинальная мощность в ваттах.
     * @param brightness Яркость от 0 до 100 процентов.
     * @param color Цвет лампы.
     * @throws invalid_argument Если мощность или яркость недопустима.
     */
    LightBulb(const string& name, double power, int brightness, const string& color);
    /**
     * @brief Создаёт независимую копию состояния и параметров.
     * @param other Копируемый объект.
     */
    LightBulb(const LightBulb& other);
    /**
     * @brief Присваивает состояние и параметры другого объекта.
     * @param other Объект-источник.
     * @return Ссылка на текущий объект.
     * @details Самоприсваивание сохраняет объект без изменений.
     */
    LightBulb& operator=(const LightBulb& other);
    /**
     * @brief Изменяет яркость лампы.
     * @param value Яркость от 0 до 100 процентов.
     * @throws invalid_argument Если значение вне диапазона [0, 100].
     * @details Для включённой лампы сначала учитывает расход с прежней яркостью и начинает новый интервал.
     */
    void setBrightness(int value);
    /**
     * @brief Переопределяет расчёт мощности с учётом яркости.
     * @return Номинальная мощность * яркость / 100 при включении, иначе 0; единица - ватт.
     */
    double getPowerUsage() const override;
    /**
     * @brief Формирует строку с типом, состоянием и параметрами устройства.
     * @return Строка состояния.
     */
    string getStatus() const override;
};
