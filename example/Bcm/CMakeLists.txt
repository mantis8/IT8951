add_library(Bcm STATIC src/Spi.cpp
                       src/Gpio.cpp
                       src/InitManager.cpp
                       thirdparty/bcm2835.c)

target_include_directories(Bcm PRIVATE thirdparty
                               PUBLIC src)

target_link_libraries(Bcm PUBLIC Interfaces)   


# TODO: remove
add_executable(GpioTest src/GpioTest.cpp)
target_link_libraries(GpioTest PRIVATE Bcm) 