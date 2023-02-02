add_library(Bcm STATIC src/Spi.cpp
                       src/Gpio.cpp
                       src/InitManager.cpp
                       thirdparty/bcm2835.c)

target_include_directories(Bcm PRIVATE thirdparty
                               PUBLIC src)

target_link_libraries(Bcm PUBLIC Interfaces)                              