#include "Gpio.h"

#include <stdexcept>

#include "InitManager.h"
#include "bcm2835.h"

namespace mati::hardware_abstraction {

Gpio::Gpio(const uint32_t pin, const Functionality functionality) : pin_{pin}, callback_{[](){}}, edgeDetector_{}, isRunning_{false} {
    // initialize the bcm library
    (void)InitManager::getInstance();

    switch (functionality) {
      case Functionality::input:        
        bcm2835_gpio_fsel(pin_, BCM2835_GPIO_FSEL_INPT);
        break;

      case Functionality::output:
        bcm2835_gpio_fsel(pin_, BCM2835_GPIO_FSEL_OUTP);
        break;

      default:
        throw std::runtime_error("invalid gpio functionality");
        break;
    }

    bcm2835_gpio_set_pud(pin_, BCM2835_GPIO_PUD_OFF);

    isRunning_ = true;
    edgeDetector_ = std::thread{&Gpio::detectRisingEdge, this};
}

Gpio::~Gpio() {
    isRunning_ = false;
    edgeDetector_.join();
}

void Gpio::write(const bool level) noexcept {     
    // true = high, false = low;
    if (level) {
        bcm2835_gpio_set(pin_);
    } else {
        bcm2835_gpio_clr(pin_);
    }
}

bool Gpio::read() noexcept {
    uint8_t level = bcm2835_gpio_lev(pin_);

    if (HIGH == level) {
        return true;
    } else {
        return false;
    }    
}

void Gpio::setRisingEdgeCallback(std::function<void(void)>&& callback) noexcept {
    callback_ = std::move(callback);
}

void Gpio::detectRisingEdge() {
    while (isRunning_) {
        if (!read()) {
            while (!read()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
            }
            callback_();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

} // mati::hardware_abstraction