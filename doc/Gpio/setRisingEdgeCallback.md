# _mati::hardware_abstraction::Gpio::_**setRisingEdgeCallback**

```cpp
virtual void setRisingEdgeCallback(std::function<void(void)>&& callback) noexcept = 0;
```

Sets the function which is called when a rising edge is detected on this pin.

## Parameters

- `callback` - The rising edge callback function.

## Return value
(none)