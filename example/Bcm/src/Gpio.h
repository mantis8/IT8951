//
// A class which provides GPIO access.
//

#ifndef MATI_HARDWARE_ABSTRACTION_GPIO_H
#define MATI_HARDWARE_ABSTRACTION_GPIO_H

#include <cstdint>
#include <functional>
#include <thread>

#include "IGpio.h"

namespace mati::hardware_abstraction {

class Gpio : public IGpio {
  public:
    enum class Functionality {
        input = 0,
        output   
    };

    Gpio(const uint32_t pin, const Functionality functionality);

    void write(const bool level) noexcept override;
    bool read() noexcept override;
    void setRisingEdgeCallback(std::function<void(void)>&& callback) noexcept override;

  private:
    void detectRisingEdge();

    const uint32_t pin_;
    std::function<void(void)> callback_;
    std::thread edgeDetector_;
};

} // mati::hardware_abstraction

#endif // MATI_HARDWARE_ABSTRACTION_GPIO_H