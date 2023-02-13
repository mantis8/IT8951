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

#include <string>
#include <cstdint>
#include <span>

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

    struct DeviceInfo() {
        DeviceInfo(uint16_t width, uint16_t height, uint32_t imageBufferAddress,
                   std::string firmwareVersion, std::string lutVersion) : 
                   width_{width}, height_{height}, imageBufferAddress_{imageBufferAddress},
                   firmwareVersion_{firmwareVersion}, lutVersion_{lutVersion} {};

        const uint16_t width_;
        const uint16_t height_;
        const uint16_t imageBufferAddress_;
        const std::string firmwareVersion_;
        const std::string lutVersion_;
    };

    IT8951(hardware_abstraction::ISpi& spi, hardware_abstraction::IGpio& resetGpo, hardware_abstraction::IGpio& busyGpi);
    IT8951(const IT8951&) = delete;
    IT8951(IT8951&&) = delete;
    operator=(const IT8951&) = delete;
    operator=(IT8951&&) = delete;

    Status wakeUp();
    Status standby();
    void reset();
    DeviceInfo getDeviceInfo();   
    Status setVcom(float vcom);
    // TODO: document the following
    Status writeData(const uint32_t imageBufferAddress, const std::span<uint16_t> data, const uint16_t yCoordinate,
                     const uint16_t, xCoordinate, const uint16_t width, const uint16_t height);
    Status display(const uint16_t xCoordinate, const uint16_t yCoordinate, const uint16_t width, const uint16_t height);
    
  
  private:
    float getVcom(); // TODO: is this needed?
    Status enablePackedMode();
    Status disablePackedMode(); // TODO: is this needed?

    hardware_abstraction::ISpi& spi;
    harware_abstraction::IGpio& resetGpo;
    hardware_abstraction::IGpio& busyGpi;

};
} // mati

#endif // MATI_IT8951_H