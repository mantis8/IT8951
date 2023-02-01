//
// Copyright (c) 2023 Manuel Tischhauser
//
// Distributed under the MIT Software License
// See accompanying file LICENSE or copy at
// https://opensource.org/licenses/MIT
//
// See the documentation for more information
//

#ifndef MATI_HARDWARE_ABSTRACTION_IGPIO_H
#define MATI_HARDWARE_ABSTRACTION_IGPIO_H

#include <functional>

namespace mati::hardware_abstraction {

class IGpio {
  public:
    virtual void write(bool level) noexcept = 0;
    virtual bool read() noexcept = 0;
    virtual void setRisingEdgeCallback(std::function<void(void)>&& callback) noexcept = 0;
};

} // mati::hardware_abstraction

#endif // MATI_HARDWARE_ABSTRACTION_IGPIO_H