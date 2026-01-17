#include "gpio_mcal.h"

void GPIO_MCAL::pinMode(uint8_t pin, uint8_t mode) {
    ::pinMode(pin, mode == GPIO_OUTPUT ? OUTPUT : INPUT);
}

void GPIO_MCAL::digitalWrite(uint8_t pin, uint8_t value) {
    ::digitalWrite(pin, value == GPIO_HIGH ? HIGH : LOW);
}

uint8_t GPIO_MCAL::digitalRead(uint8_t pin) {
    return ::digitalRead(pin) == HIGH ? GPIO_HIGH : GPIO_LOW;
}

void GPIO_MCAL::analogWrite(uint8_t pin, uint8_t value) {
    ::analogWrite(pin, value);
}

uint16_t GPIO_MCAL::analogRead(uint8_t pin) {
    return ::analogRead(pin);
}
