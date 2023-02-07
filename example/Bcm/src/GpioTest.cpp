// TODO: remove

#include <iostream>
#include <thread>

#include "Gpio.h"

int main() {
    using namespace mati::hardware_abstraction;

    const uint8_t resetPin = 17;
    const uint8_t busyPin = 24;

    try {
        Gpio output{resetPin, TFunctionality::output};
        Gpio input{busyPin, TFunctionality::input};

        // first rising edge
        std::cout << "set output low..." << std::endl;
        output.write(false);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << "input state = " << input.read() << std::endl;

        std::cout << "set output high..." << std::endl;
        output.write(true);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << "input state = " << input.read() << std::endl;

        // second rising edge
        input.setRisingEdgeCallback([](){std::cout << "rising edge detected" << std::endl;});

        std::cout << "set output low..." << std::endl;
        output.write(false);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << "input state = " << input.read() << std::endl;

        std::cout << "set output high..." << std::endl;
        output.write(true);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << "input state = " << input.read() << std::endl;

        // third rising edge
        input.setRisingEdgeCallback([](){std::cout << "another rising edge detected" << std::endl;});

        std::cout << "set output low..." << std::endl;
        output.write(false);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << "input state = " << input.read() << std::endl;
        
        std::cout << "set output high..." << std::endl;
        output.write(true);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << "input state = " << input.read() << std::endl;

    } catch(...) {
        std::cout << "Exception caught!" << std::endl;
    }
    

    return 0;
}