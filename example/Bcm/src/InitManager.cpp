#include <stdexcept>

#include "InitManager.h"
#include "bcm2835.h"

namespace mati::hardware_abstraction {

InitManager InitManager::instance_;

InitManager& InitManager::getInstance() {
    return instance_;
}

InitManager::InitManager() {
    if(1 != bcm2835_init()) {
        throw std::runtime_error("bcm library initialization failed");
    }
}

InitManager::~InitManager() {
    // is called when terminating main
    (void)bcm2835_close();
}

} // mati::hardware_abstraction