//
// Copyright (c) 2023 Manuel Tischhauser.
//
// See the documentation for more information.
//
// Distributed under the MIT License (See accompanying file LICENSE).
//

#ifndef MATI_HARDWARE_ABSTRACTION_SPI_H
#define MATI_HARDWARE_ABSTRACTION_SPI_H

#include <span>
#include <cstint>

namespace mati::hardware_abstraction {

class Spi {
  public:
    virtual bool transfer(std::span<uint16_t> txBuffer, const std::span<uint16_t> rxBuffer) noexcept = 0;
};

} // mati::hardware_abstraction

#endif // MATI_HARDWARE_ABSTRACTION_SPI_H