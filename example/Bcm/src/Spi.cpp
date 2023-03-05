#include "Spi.h"

#include <stdexcept>

#include "InitManager.h"
#include "bcm2835.h"

namespace mati::hardware_abstraction {

Spi::Spi() {
    // initialize the bcm library
    (void)InitManager::getInstance();

    if (1 != bcm2835_spi_begin()) {
        throw std::runtime_error("starting spi failed");
    }

    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
    bcm2835_spi_chipSelect(8u);
    bcm2835_spi_setChipSelectPolarity(8u, LOW);
    // default clock frequency = 2MHz
    setClockFrequency(2*1000*1000u);
}

Spi::~Spi() {
    (void)bcm2835_spi_end();
}

void Spi::setClockFrequency(const uint32_t frequency) {
    bcm2835_spi_set_speed_hz(frequency);
}

bool Spi::transfer(const std::span<uint16_t> txBuffer, std::span<uint16_t> rxBuffer) noexcept {
    if (txBuffer.size() != rxBuffer.size()) {
        return false;
    }

    const uint32_t numberOfBytes = txBuffer.size() * 2u;
    bcm2835_spi_transfernb(reinterpret_cast<char*>(txBuffer.data()), reinterpret_cast<char*>(rxBuffer.data()), numberOfBytes);

    return true;
}

} // mati::hardware_abstraction