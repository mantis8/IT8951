#include <stdexcept>

#include "Gpio.h"
#include "InitManager.h"
#include "bcm2835.h"

namespace mati::hardware_abstraction {

Gpio::Gpio(const uint32_t pin, const TFunctionality functionality) : pin_{pin}, callback_{[](){}}, edgeDetector_{} {
    // initialize the bcm library
    (void)InitManager::getInstance();

    switch (functionality) {
      case TFunctionality::input:        
        bcm2835_gpio_fsel(pin_, BCM2835_GPIO_FSEL_INPT);
        break;

      case TFunctionality::output:
        bcm2835_gpio_fsel(pin_, BCM2835_GPIO_FSEL_OUTP);
        break;

      default:
        throw std::runtime_error("invalid gpio functionality");
        break;
    }

    bcm2835_gpio_set_pud(pin_, BCM2835_GPIO_PUD_OFF);

    edgeDetector_ = std::thread{&Gpio::detectRisingEdge, this};
}

void Gpio::write(bool level) noexcept {     
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
    while (true) {
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