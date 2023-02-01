//
// Copyright (c) 2023 Manuel Tischhauser.
//
// See the documentation for more information.
//
// Distributed under the MIT License (See accompanying file LICENSE).
//

#ifndef MATI_HARDWARE_ABSTRACTION_GPIO_H
#define MATI_HARDWARE_ABSTRACTION_GPIO_H

#include <functional>

namespace mati::hardware_abstraction {

class Gpio {
  public:
    virtual void write(bool level) noexcept = 0;
    virtual bool read() noexcept = 0;
    virtual void setRisingEdgeCallback(std::function<void(void)>&& callback) noexcept = 0;
};

} // mati::hardware_abstraction

#endif // MATI_HARDWARE_ABSTRACTION_GPIO_H