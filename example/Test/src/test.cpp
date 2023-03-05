#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <stdexcept>
#include <cstdint>

#include "doctest.h"
#include "IT8951.h"
#include "Spi.h"
#include "Gpio.h"

// TODO: make usefuls testcases
TEST_CASE("sadfd") {
    try {
        mati::hardware_abstraction::Spi spi{};
        spi.setClockFrequency(2*1000*1000u);

        mati::hardware_abstraction::Gpio resetPin{17, mati::hardware_abstraction::Gpio::Functionality::output};
        mati::hardware_abstraction::Gpio busyPin{24, mati::hardware_abstraction::Gpio::Functionality::input};
    
        constexpr uint32_t bufferSize = 300;
        mati::IT8951<bufferSize> it8951{spi, resetPin, busyPin};

        it8951.reset();

        CHECK(mati::IT8951<bufferSize>::Status::ok == it8951.sleep());
        CHECK(mati::IT8951<bufferSize>::Status::ok == it8951.standby());
        CHECK(mati::IT8951<bufferSize>::Status::ok == it8951.wakeUp());


    } catch (std::runtime_error& e) {
        CHECK_MESSAGE(false, "exception occured: ", std::string(e.what())); 
    }

    CHECK(true);
}