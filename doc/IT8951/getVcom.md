# _mati::IT8951\<BufferSize\>::_**getVcom**

```cpp
std::tuple<Status, float> getVcom();
```
Reads and returns the VCOM value from the IT8951.

## Parameters

(none)

## Return value

If the first element of the tuple is equal to:
 - `Status::ok`  
 The operation has been completed successfully. The corresponding float containing the VCOM value is valid.
 - `Status::busy`  
 The IT8951 is busy and cannot execute the operation. The corresponding float containing the VCOM value is not valid.
 - `Status::error`  
 The operation could not be completed successfully. Either the internal buffer is too small or the underlying hardware (SPI or GPIO) is in an error state. The corresponding float containing the VCOM value is not valid.