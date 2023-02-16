# _mati::IT8951\<BufferSize\>::_**display**

```cpp
Status display(const uint16_t xCoordinate, const uint16_t yCoordinate, const uint16_t width, const uint16_t height);
```

Displays the selected part of the display. To write to the buffer, use the member function [writeImage](writeImage.md). 

## Parameters

- `xCoordinate`  
The X coordinate of the lower left corner point of the image.
- `yCoordinate`  
The Y coordinate of the lower left corner point of the image.
- `width`  
The width of the image.
- `height`  
The height of the image.

## Return value

 - `Status::ok`  
 The operation has been completed successfully.
 - `Status::busy`  
 The IT8951 is busy and cannot execute the operation.
 - `Status::error`  
 The operation could not be completed successfully. Either the internal buffer is too small, the underlying hardware (SPI or GPIO) is in an error state.