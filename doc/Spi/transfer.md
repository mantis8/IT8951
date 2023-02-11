# _mati::hardware_abstraction::ISpi::_**transfer**

```cpp
virtual bool transfer(const std::span<uint16_t> txBuffer, std::span<uint16_t> rxBuffer) noexcept = 0;
```

Method which transfers the elements contained in the transmit buffer from the master to the slave device while simultaneously receiving elements from the slave and stores it into the receive buffer. The transmit and the receive buffer should be of the same size. This is a blocking function, meaning that it should only return after the transfer is completely finished.

## Parameters

- `txBuffer`  
  The buffer containing the elements to be transferred.
- `rxBuffer`  
The buffer where the received elements can be stored.

## Return value

`true` if the transfer could be completed successfully, otherwise `false`.