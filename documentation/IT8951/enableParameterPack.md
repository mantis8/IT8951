# _mati::IT8951\<BufferSize\>::_**enableParameterPack**

```cpp
Status enableParameterPack();
```

Enables the IT8951 to accept a continuation of parameters. To ensure correct behavior, this function should always be called immediately after the instantiation or a [reset](reset.md). Calls to other member functions before this might fail otherwise.

## Parameters

(none)

## Return value

 - `Status::ok`  
 The operation has been completed successfully.
 - `Status::busy`  
 The IT8951 is busy and cannot execute the operation.
 - `Status::error`  
 The operation could not be completed successfully. Either the internal buffer is too small or the underlying hardware (SPI or GPIO) is in an error state.