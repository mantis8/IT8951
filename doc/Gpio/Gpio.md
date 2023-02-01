# _mati::hardware_abstraction::_ **Gpio**

Defined in header [`Gpio.h`](../../lib/src/Gpio.h).

```cpp
class Gpio;
```

Defines the GPIO functionality needed to access the IT8951. It's the same interface for input and output pins.

## Member functions

- [write](write.md) 
- [read](read.md)
- [setRisingEdgeCallback](setRisingEdgeCallback.md)

## Notes

Every target should provide its own implementation. Each pin has its own instance of the derived class.