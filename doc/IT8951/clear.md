# _mati::IT8951\<BufferSize\>::_**clear**

```cpp
Status clear(const uint16_t xCoordinate, const uint16_t yCoordinate, const uint16_t width, const uint16_t height);
```

Clears the selected part of the display.

## Parameters

- `xCoordinate`  
The X coordinate of the lower left corner of the display part to be cleared.
- `yCoordinate`  
The Y coordinate of the lower left corner point of the display part to be cleared.
- `width`  
The width of the of the display part to be cleared.
- `height`  
The height of the of the display part to be cleared.

## Return value

 - `Status::ok`  
 The operation has been completed successfully.
 - `Status::busy`  
 The IT8951 is busy and cannot execute the operation.
 - `Status::error`  
 The operation could not be completed successfully. Either the internal buffer is too small, the underlying hardware (SPI or GPIO) is in an error state.