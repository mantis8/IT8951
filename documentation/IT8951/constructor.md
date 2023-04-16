# _mati::IT8951\<BufferSize\>::_**IT8951**

```cpp
IT8951(hardware_abstraction::ISpi& spi, hardware_abstraction::IGpio& resetGpo, hardware_abstraction::IGpio& busyGpi);
```

Constructs the IT8951.

## Parameters

- `spi`  
The SPI connected to the IT8951.
- `resetGpo`  
The GPIO connected to the reset pin of the IT8951. This pin needs to be writable.
- `busyGpi`  
The GPIO connected to the busy pin of the IT891. This pin needs to be readable.

## Note

TODO: memory allocation