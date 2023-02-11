//
// Copyright (c) 2023 Manuel Tischhauser
//
// Distributed under the MIT Software License
// See accompanying file LICENSE or copy at
// https://opensource.org/licenses/MIT
//
// See the documentation for more information
//

#ifndef MATI_IT8951_H
#define MATI_IT8951_H

#include "ISpi.h"
#include "IGpio.h"

namespace mati {

template<uint32_t BufferSize>
class IT8951 {
  public:
    enum class Status {
        ok = 0,
        busy,
        error
    };

    IT8951(hardware_abstraction::ISpi& spi, hardware_abstraction::IGpio& resetGpo, hardware_abstraction::IGpio& busyGpi);
    IT8951(const IT8951&) = delete;
    IT8951(IT8951&&) = delete;
    operator=(const IT8951&) = delete;
    operator=(IT8951&&) = delete;

    Status wakeUp();
    Status standby();
    void reset();
    // TODO DeviceInfo    
    Status setVcom(float vcom);
    
  
  private:

};
} // mati

#endif // MATI_IT8951_H