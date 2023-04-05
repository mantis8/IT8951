# _mati::IT8951\<BufferSize\>::_**getDeviceInfo**

```cpp
std::tuple<Status, DeviceInfo> getDeviceInfo();
```

Gets the device information stored in the IT8951.

## Parameters

(none)

## Return value

If the first element of the tuple is equal to:
 - `Status::ok`  
 The operation has been completed successfully. The corresponding device information is valid.
 - `Status::busy`  
 The IT8951 is busy and cannot execute the operation. The corresponding device information is not valid.
 - `Status::error`  
 The operation could not be completed successfully. Either the internal buffer is too small or the underlying hardware (SPI or GPIO) is in an error state. The corresponding device information is not valid.