//
// A helper to initialize the peripherals over the bcm2835 library avoiding free functions.
//

#ifndef MATI_HARDWARE_ABSTRACTION_INITMANAGER_H
#define MATI_HARDWARE_ABSTRACTION_INITMANAGER_H

namespace mati::hardware_abstraction {

class InitManager {
  public:
    static InitManager& getInstance();

  private:
    InitManager();
    ~InitManager();
    static InitManager instance_;
};


} // mati::hardware_abstraction

#endif // MATI_HARDWARE_ABSTRACTION_INITMANAGER_H