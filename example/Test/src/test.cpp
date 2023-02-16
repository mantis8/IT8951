#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "IT8951.h"
#include "Spi.h"
#include "Gpio.h"

// TODO: make usefuls testcases
TEST_CASE("sadfd") {

    mati::hardware_abstraction::Spi spi{};
    mati::hardware_abstraction::Gpio resetPin{8, mati::hardware_abstraction::Gpio::Functionality::output};
    mati::hardware_abstraction::Gpio busyPin{24, mati::hardware_abstraction::Gpio::Functionality::input};
    
    mati::IT8951<300> it8951{spi, resetPin, busyPin}; 

    CHECK(true);
}