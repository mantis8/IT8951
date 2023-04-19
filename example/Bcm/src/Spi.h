//
// Copyright (c) 2023 Manuel Tischhauser
//
// Distributed under the GNU GENERAL PUBLIC LICENSE Version 3
// See accompanying file LICENSE-example or copy at
// https://www.gnu.org/licenses/gpl-3.0.html
//
// A class which provides SPI access.
//

#ifndef MATI_HARDWARE_ABSTRACTION_SPI_H
#define MATI_HARDWARE_ABSTRACTION_SPI_H

#include <atomic>

#include "ISpi.h"

namespace mati::hardware_abstraction {

class Spi : public ISpi {
  public:
    Spi();
    ~Spi();

    void setClockFrequency(const uint32_t frequency);
    bool transfer(std::span<uint16_t> txBuffer, std::span<uint16_t> rxBuffer) noexcept override;
};

} // namespace mati::hardware_abstraction

#endif // MATI_HARDWARE_ABSTRACTION_SPI_H