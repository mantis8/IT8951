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
#include <atomic>
#include <array>
#include <tuple>
#include <semaphore>
#include <thread>
#include <algorithm>
#include <limits>

#include "ISpi.h"
#include "IGpio.h"

namespace mati {

template<size_t BufferSize>
class IT8951 {
  public:
    enum class Status {
        ok = 0,
        busy,
        error
    };

    struct DeviceInfo {
        DeviceInfo() : 
            width{0}, height{0}, imageBufferAddress{0}, firmwareVersion{}, lutVersion{} {};

        uint16_t width;
        uint16_t height;
        uint32_t imageBufferAddress;
        std::string firmwareVersion;
        std::string lutVersion;
    };

    IT8951(hardware_abstraction::ISpi& spi, hardware_abstraction::IGpio& resetPin, hardware_abstraction::IGpio& busyPin);
    IT8951(const IT8951&) = delete;
    IT8951(IT8951&&) = delete;
    IT8951& operator=(const IT8951&) = delete;
    IT8951& operator=(IT8951&&) = delete;

    Status wakeUp();
    Status standby();
    Status sleep();
    void reset();
    std::tuple<Status, DeviceInfo> getDeviceInfo();   
    Status setVcom(const float vcom);
    std::tuple<Status, float> getVcom();
    Status writeImage(const std::span<uint16_t> image, const uint16_t xCoordinate, const uint16_t yCoordinate, const uint16_t width, const uint16_t height);
    Status display(const uint16_t xCoordinate, const uint16_t yCoordinate, const uint16_t width, const uint16_t height);
    Status clear(const uint16_t xCoordinate, const uint16_t yCoordinate, const uint16_t width, const uint16_t height);

  private:
    // IT8951 SPI preambles
    static constexpr uint16_t cWriteCommand_{0x6000};
    static constexpr uint16_t cWriteData_{0x0000};
    static constexpr uint16_t cReadData_{0x1000};
    // IT8951 commands
    static constexpr uint16_t cWakeUp_{0x0001};
    static constexpr uint16_t cStandby_{0x0002};
    static constexpr uint16_t cSleep_{0x0003};
    static constexpr uint16_t cReadRegister_{0x0010};
    static constexpr uint16_t cWriteRegister_{0x0011};
    static constexpr uint16_t cLoadImageArea_{0x0021};
    static constexpr uint16_t cEndLoadImage_{0x0022};
    static constexpr uint16_t cDisplayArea_{0x0034};
    static constexpr uint16_t cSetVcom_{0x0039};
    static constexpr uint16_t cGetDeviceInfo_{0x0302};

    Status writeCommand(const uint16_t command);
    Status writeCommand(const uint16_t command, const std::span<uint16_t> parameters);
    Status writeData(const std::span<uint16_t> buffer);
    Status readData(const std::span<uint16_t> buffer);
    Status writeRegister(const uint16_t address, const uint16_t value);
    Status readRegister(const uint16_t address, uint16_t& value);
    void waitUntilIdle();
    Status enablePackedMode(); // TODO: is this needed?
    Status disablePackedMode(); // TODO: is this needed?

    std::array<uint16_t, BufferSize> txBuffer_;
    std::array<uint16_t, BufferSize> rxBuffer_;
    std::atomic_flag busyFlag_;
    hardware_abstraction::ISpi& spi_;
    hardware_abstraction::IGpio& resetPin_;
    hardware_abstraction::IGpio& busyPin_;
};

template<size_t BufferSize>
IT8951<BufferSize>::IT8951(hardware_abstraction::ISpi& spi, hardware_abstraction::IGpio& resetPin, hardware_abstraction::IGpio& busyPin)
                           : txBuffer_{}, rxBuffer_{}, busyFlag_{}, spi_{spi}, resetPin_{resetPin}, busyPin_{busyPin} {
    static_assert(BufferSize >= 2, "BufferSize needs to be at least 2");

    busyFlag_.clear();
    resetPin_.write(true);
}

template<size_t BufferSize>
IT8951<BufferSize>::Status IT8951<BufferSize>::wakeUp() {
    return writeCommand(cWakeUp_); 
}

template<size_t BufferSize>
IT8951<BufferSize>::Status IT8951<BufferSize>::standby() {
    return writeCommand(cStandby_);
}

template<size_t BufferSize>
IT8951<BufferSize>::Status IT8951<BufferSize>::sleep() {
    return writeCommand(cSleep_);
}

template<size_t BufferSize>
void IT8951<BufferSize>::reset() {
    resetPin_.write(false);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    resetPin_.write(true);
}

template<size_t BufferSize>
std::tuple<typename IT8951<BufferSize>::Status, typename IT8951<BufferSize>::DeviceInfo> IT8951<BufferSize>::getDeviceInfo() {
    auto result = writeCommand(cGetDeviceInfo_);
    if (Status::ok != result) {
        return {result, DeviceInfo{}};
    }

    std::array<uint16_t, 20> buffer{};

    result = readData(buffer);
    if (Status::ok != result) {
        return {result, DeviceInfo{}};
    }

    DeviceInfo info{};

    info.width = buffer.at(0);
    info.height = buffer.at(1);

    info.imageBufferAddress = (static_cast<uint32_t>(buffer.at(3))<<16) |
                               static_cast<uint32_t>(buffer.at(2));

    info.firmwareVersion = std::string{reinterpret_cast<char*>(buffer.data()+4)};
    info.lutVersion = std::string{reinterpret_cast<char*>(buffer.data()+12)};

    return {Status::ok, info};
}

template<size_t BufferSize>
IT8951<BufferSize>::Status IT8951<BufferSize>::setVcom(const float vcom) {
    constexpr uint16_t maxValue = std::numeric_limits<uint16_t>::max();
    const bool inRange = (vcom >= static_cast<float>(maxValue) / -1000.0f) && (vcom < 0);

    if (!inRange) {
        return Status::error;
    }

    std::array<uint16_t, 2> parameters;

    parameters.at(0) = 0x0001; // parameter to 1 = set VCOM
    parameters.at(1) = static_cast<uint16_t>(vcom * (-1000.0f)); // the VCOM value converted as described in the programming guide

    return writeCommand(cSetVcom_, parameters);
}

template<size_t BufferSize>
std::tuple<typename IT8951<BufferSize>::Status, float> IT8951<BufferSize>::getVcom() {
    std::array<uint16_t, 1> parameters;
    parameters.at(0) = 0x0000; // parameter to 0 = get VCOM
    
    auto result = writeCommand(cSetVcom_, parameters);
    if (Status::ok != result) {
        return {result, 0.0f};
    }

    std::array<uint16_t, 1> buffer;

    result = readData(buffer);
    if (Status::ok != result) {
        return {result, 0.0f};
    }

    const float vcom = static_cast<float>(buffer.at(0)) / -1000.0f;

    return {Status::ok, vcom};
}

template<size_t BufferSize>
IT8951<BufferSize>::Status IT8951<BufferSize>::writeImage(const std::span<uint16_t> image, const uint16_t xCoordinate, const uint16_t yCoordinate, const uint16_t width, const uint16_t height) {
    // TODO
}

template<size_t BufferSize>
IT8951<BufferSize>::Status IT8951<BufferSize>::display(const uint16_t xCoordinate, const uint16_t yCoordinate, const uint16_t width, const uint16_t height) {
    // TODO
}

template<size_t BufferSize>
IT8951<BufferSize>::Status IT8951<BufferSize>::clear(const uint16_t xCoordinate, const uint16_t yCoordinate, const uint16_t width, const uint16_t height) {
    // TODO
}

template<size_t BufferSize>
IT8951<BufferSize>::Status IT8951<BufferSize>::writeCommand(const uint16_t command) {
    if (busyFlag_.test_and_set(std::memory_order_acquire)) {
        return Status::busy;
    }

    Status result{Status::ok};

    txBuffer_.at(0) = cWriteCommand_;
    txBuffer_.at(1) = command;

    waitUntilIdle();

    if (!spi_.transfer(std::span{txBuffer_}.subspan(0, 2), std::span{rxBuffer_}.subspan(0, 2))) {
        result = Status::error;    
    }

    busyFlag_.clear(std::memory_order_release);

    return result;
}

template<size_t BufferSize>
IT8951<BufferSize>::Status IT8951<BufferSize>::writeCommand(const uint16_t command, const std::span<uint16_t> parameters){
    if (busyFlag_.test_and_set(std::memory_order_acquire)) {
        return Status::busy;
    }

    Status result{Status::ok};

    txBuffer_.at(0) = cWriteCommand_;
    txBuffer_.at(1) = command;

    waitUntilIdle();

    if (!spi_.transfer(std::span{txBuffer_}.subspan(0, 2), std::span{rxBuffer_}.subspan(0, 2))) {
        result = Status::error;    
    }

    txBuffer_.at(0) = cWriteData_;

    for (const auto p : parameters) {
        txBuffer_.at(1) = p;

        waitUntilIdle();

        if (!spi_.transfer(std::span{txBuffer_}.subspan(0, 2), std::span{rxBuffer_}.subspan(0, 2))) {
            result = Status::error;    
        }
    }

    busyFlag_.clear(std::memory_order_release);

    return result;
}

template<size_t BufferSize>
IT8951<BufferSize>::Status IT8951<BufferSize>::writeData(const std::span<uint16_t> buffer) {
    if (busyFlag_.test_and_set(std::memory_order_acquire)) {
        return Status::busy;
    }

    const auto transferSize = buffer.size() + 1u; // +1 word preamble
    if (transferSize > BufferSize) { 
        return Status::error;
    }

    Status result{Status::ok};

    txBuffer_.at(0) = cWriteData_;

    std::copy(buffer.begin(), buffer.end(), txBuffer_.begin());
    
    waitUntilIdle();

    if (!spi_.transfer(std::span{txBuffer_}.subspan(0, transferSize), std::span{rxBuffer_}.subspan(0, transferSize))) {
        result = Status::error;    
    }

    busyFlag_.clear(std::memory_order_release);

    return result;
}

template<size_t BufferSize>
IT8951<BufferSize>::Status IT8951<BufferSize>::readData(const std::span<uint16_t> buffer) {
    if (busyFlag_.test_and_set(std::memory_order_acquire)) {
        return Status::busy;
    }

    const auto transferSize = buffer.size() + 2u; // +2 word preamble and dummy
    if (transferSize > BufferSize) { 
        return Status::error;
    }

    Status result{Status::ok};

    txBuffer_.at(0) = cReadData_;
    txBuffer_.at(1) = 0x0000; // dummy

    waitUntilIdle();

    if (!spi_.transfer(std::span{txBuffer_}.subspan(0, transferSize), std::span{rxBuffer_}.subspan(0, transferSize))) {
        result = Status::error;    
    }

    std::copy(rxBuffer_.begin() + 2, rxBuffer_.begin() + transferSize, buffer.begin()); // +2 word preamble and dummy

    busyFlag_.clear(std::memory_order_release);

    return result;    
}

template<size_t BufferSize>
IT8951<BufferSize>::Status IT8951<BufferSize>::writeRegister(const uint16_t address, const uint16_t value) {
    // TODO
}

template<size_t BufferSize>
IT8951<BufferSize>::Status IT8951<BufferSize>::readRegister(const uint16_t address, uint16_t& value) {
    // TODO
}

template<size_t BufferSize>
void IT8951<BufferSize>::waitUntilIdle() {
    while (!busyPin_.read()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

/*
    if (busyPin_.read()) {
        return;
    }

    std::binary_semaphore busySemaphore{0};
    bool busyRised = false;

    busyPin_.setRisingEdgeCallback([&busySemaphore, &busyRised](){   
        // release the semaphore only once
        if (!busyRised) {
            busySemaphore.release();
            busyRised = true;
        }       
    });

    // pin low = busy, pin high = idle
    if (!busyPin_.read()) {
        busySemaphore.acquire(); 
    }

    busyPin_.setRisingEdgeCallback([](){});*/
}

} // mati

#endif // MATI_IT8951_H