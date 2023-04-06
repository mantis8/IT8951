//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <stdexcept>
#include <cstdint>
#include <tuple>
#include <thread>

//#include "doctest.h"
#include "IT8951.h"
#include "Spi.h"
#include "Gpio.h"


#include <iostream> // TODO remove

// TODO replace or find better name or move to lib
bool compare(float a, float b, float epsilon) {
    return std::abs(a - b) < epsilon;
}

int main() {
    try {
        mati::hardware_abstraction::Spi spi{};
        spi.setClockFrequency(2*1000*1000);

        mati::hardware_abstraction::Gpio resetPin{17, mati::hardware_abstraction::Gpio::Functionality::output};
        mati::hardware_abstraction::Gpio busyPin{24, mati::hardware_abstraction::Gpio::Functionality::input};   

        constexpr uint32_t bufferSize = (1872*1404 / 32) + 2; // 
        mati::IT8951<bufferSize> it8951{spi, resetPin, busyPin};

        it8951.enableParameterPack();
        it8951.setVcom(-1.25f);
 
        mati::IT8951<bufferSize>::Status result{mati::IT8951<bufferSize>::Status::error};
        mati::IT8951<bufferSize>::DeviceInfo info;
        std::tie(result, info) = it8951.getDeviceInfo();

        std::cout << "Device info: " << std::endl
                  << "  width =              " << info.width << std::endl
                  << "  height =             " << info.height << std::endl
                  << "  image buffer address = " << std::hex << info.imageBufferAddress << std::dec << std::endl
                  << "  firmware version =    " << info.firmwareVersion << std::endl
                  << "  LUT version =         " << info.lutVersion << std::endl;

        // display grayscales
        std::array<uint16_t, (468*351)/2> gray{};

        for (uint32_t i = 0; i < 16; i++) {           
            gray.fill((i*17));
            
            const uint32_t x = (i*468/2) % 1872;
            const uint32_t y = (i-i%4)*351/4;

            it8951.writeImage(info.imageBufferAddress, gray, x, y, 468/2, 351);  

            bool ready = false;
            std::tie(result, ready) = it8951.isDisplayReady();

            while (!ready) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                std::tie(result, ready) = it8951.isDisplayReady();
            }

            it8951.display(x, y, 468, 351);
        }
              


    } catch (std::runtime_error& e) {
        std::cout << "exception occured: " << std::string(e.what()) << std::endl; 
    }


    return 0;
}

/*


TEST_CASE("Full refresh") {


}


// TODO: make usefuls testcases
TEST_CASE("Case 1") {
    try {
        mati::hardware_abstraction::Spi spi{};
        spi.setClockFrequency(2*1000*1000);

        mati::hardware_abstraction::Gpio resetPin{17, mati::hardware_abstraction::Gpio::Functionality::output};
        mati::hardware_abstraction::Gpio busyPin{24, mati::hardware_abstraction::Gpio::Functionality::input};
    
        constexpr uint32_t bufferSize = 300;
        mati::IT8951<bufferSize> it8951{spi, resetPin, busyPin};

        it8951.reset();

        CHECK(mati::IT8951<bufferSize>::Status::ok == it8951.sleep());
        CHECK(mati::IT8951<bufferSize>::Status::ok == it8951.standby());

        it8951.reset();
        
        CHECK(mati::IT8951<bufferSize>::Status::ok == it8951.wakeUp());

        // device info
        mati::IT8951<bufferSize>::Status result;
        mati::IT8951<bufferSize>::DeviceInfo info;

        std::tie(result, info) = it8951.getDeviceInfo();
        
        CHECK(mati::IT8951<bufferSize>::Status::ok == result);
        CHECK(1872 == info.width);
        CHECK(1404 == info.height);
        CHECK(0x119F00 == info.imageBufferAddress);
        CHECK("SWv_0.1." == info.firmwareVersion);
        CHECK("M841_TFA5210" == info.lutVersion);

        // get/set VCOM
        float vcom = 0;
        std::tie(result, vcom) = it8951.getVcom();

        CHECK(mati::IT8951<bufferSize>::Status::ok == result);
        CHECK(compare(-2.6f, vcom, 1e-6));

        const float desiredVcom = -1.25;
        CHECK(mati::IT8951<bufferSize>::Status::ok == it8951.setVcom(desiredVcom));

        std::tie(result, vcom) = it8951.getVcom();

        CHECK(mati::IT8951<bufferSize>::Status::ok == result);
        CHECK(compare(desiredVcom, vcom, 1e-6));

        

    } catch (std::runtime_error& e) {
        CHECK_MESSAGE(false, "exception occured: ", std::string(e.what())); 
    }

    CHECK(true);
}*/