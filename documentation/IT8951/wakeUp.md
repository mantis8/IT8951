# _mati::IT8951\<BufferSize\>::_**wakeUp**

```cpp
Status wakeUp();
```

Wakes the IT8951 up from standby or sleep. See the [IT8951 Specifications] for more information about the power management.

## Parameters

(none)

## Return value

- `Status::ok`  
 The operation has been completed successfully.
- `Status::busy`  
 The IT8951 is busy and cannot execute the operation.
- `Status::error`  
 The operation could not be completed successfully. The underlying hardware (SPI or GPIO) might be in an error state.

[IT8951 Specifications]: https://www.waveshare.com/w/upload/1/18/IT8951_D_V0.2.4.3_20170728.pdf
