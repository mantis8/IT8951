# _mati::IT8951\<BufferSize\>::_**isDisplayReady**

```cpp
std::tuple<Status, bool> isDisplayReady();
```

Queries if the display is ready. If not, calling [display](display.md) or [clear](clear.md) could lead to undefined behavior.

## Parameters

(none)

## Return value

If the first element of the tuple is equal to:

- `Status::ok`  
 The operation has been completed successfully. The corresponding bool containing the state (true = ready, false = not ready) of the display is valid.
- `Status::busy`  
 The IT8951 is busy and cannot execute the operation. The corresponding bool containing the state of the display is valid.
- `Status::error`  
 The operation could not be completed successfully. Either the internal buffer is too small or the underlying hardware (SPI or GPIO) is in an error state. The corresponding bool containing the state of the display is valid.
