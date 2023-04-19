# _mati::IT8951\<BufferSize\>::_**IT8951**

```cpp
IT8951(hardware_abstraction::ISpi& spi, hardware_abstraction::IGpio& resetPin, hardware_abstraction::IGpio& busyPin);
```

Constructs the IT8951. Statically allocates two 16 bit buffers of size `BufferSize`. This size - 2 (preamble + dummy word) limits the amount of data which can be sent in one command to the IT8951.

## Parameters

- `spi`  
The SPI connected to the IT8951.
- `resetPin`  
The GPIO connected to the reset pin of the IT8951. This pin needs to be writable.
- `busyPin`  
The GPIO connected to the busy pin of the IT891. This pin needs to be readable.
