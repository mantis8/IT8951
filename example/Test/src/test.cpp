#include <stdexcept>
#include <cstdint>
#include <tuple>
#include <thread>
#include <iostream>

#include "IT8951.h"
#include "Spi.h"
#include "Gpio.h"

int main() {
    try {
        mati::hardware_abstraction::Spi spi{};
        spi.setClockFrequency(5*1000*1000); // 5MHz

        mati::hardware_abstraction::Gpio resetPin{17, mati::hardware_abstraction::Gpio::Functionality::output};
        mati::hardware_abstraction::Gpio busyPin{24, mati::hardware_abstraction::Gpio::Functionality::input};   

        constexpr uint32_t displayWidth = 468;
        constexpr uint32_t displayHeight = 351;
        constexpr uint32_t dataSize = displayWidth * displayHeight / 4;

        constexpr uint32_t bufferSize = dataSize + 2;
        mati::IT8951<bufferSize> it8951{spi, resetPin, busyPin};

        it8951.reset();

        it8951.enableParameterPack();
        it8951.setVcom(-1.25f);

        auto info = std::get<1>(it8951.getDeviceInfo());

        std::cout << "Device info: " << std::endl
                  << "  width =                " << info.width << std::endl
                  << "  height =               " << info.height << std::endl
                  << "  image buffer address = " << std::hex << info.imageBufferAddress << std::dec << std::endl
                  << "  firmware version =     " << info.firmwareVersion << std::endl
                  << "  LUT version =          " << info.lutVersion << std::endl;
        
        // wait for display to be ready
        while (!std::get<1>(it8951.isDisplayReady())) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }

        it8951.clear(0, 0, 1872, 1404);

        // display grayscales
        std::array<uint16_t, dataSize> gray{};

        for (uint32_t i = 0; i < 16; i++) {
            uint16_t pixelValue = i*17;

            gray.fill(pixelValue<<8 | pixelValue);
            
            const uint32_t x = (i*displayWidth) % 1872;
            const uint32_t y = (i-i%4)*displayHeight/4;

            it8951.writeImage(info.imageBufferAddress, gray, x, y, displayWidth, displayHeight);  

            // wait for display to be ready
            while (!std::get<1>(it8951.isDisplayReady())) {
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
            }

            it8951.display(x, y, displayWidth, displayHeight);
        }
        
    } catch (std::runtime_error& e) {
        std::cout <<  "exception occured: " << std::string(e.what()) << std::endl; 
    }

    return 0;
}