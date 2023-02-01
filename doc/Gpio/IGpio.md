# _mati::hardware_abstraction::_ **IGpio**

Defined in header [`IGpio.h`](../../lib/src/IGpio.h).

```cpp
class IGpio;
```

Defines the GPIO functionality needed to access the IT8951. It's the same interface for input and output pins.

## Member functions

- [write](write.md) 
- [read](read.md)
- [setRisingEdgeCallback](setRisingEdgeCallback.md)

## Notes

Every target should provide its own implementation. Each pin has its own instance of the derived class.