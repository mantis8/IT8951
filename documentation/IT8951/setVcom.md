# _mati::IT8951\<BufferSize\>::_**setVcom**

```cpp
Status setVcom(const float vcom);
```

Sets the VCOM value. This function should always be called after the instantiating or a [reset](reset.md) to ensure correct behavior. The VCOM value is dependent on the used display and can be found on the connector.

## Parameters

- `vcom`  
The VCOM value required by the connected display.

## Return value

- `Status::ok`  
 The operation has been completed successfully.
- `Status::busy`  
 The IT8951 is busy and cannot execute the operation.
- `Status::error`  
 The operation could not be completed successfully. Either the internal buffer is too small or the underlying hardware (SPI or GPIO) is in an error state.
