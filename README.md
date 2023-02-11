# IT8951

- [IT8951](#it8951)
  - [Introduction](#introduction)
  - [Example](#example)
  - [Detailed documentation](#detailed-documentation)
  - [Integration](#integration)
  - [Notes](#notes)
  - [Dependencies](#dependencies)
  - [References](#references)

## Introduction

This module provides a generic driver for the IT8951 e-paper controller by Waveshare. 

The module is written in C++20 with the following design goals:
1. Generic:
   - Works with display using the IT8951
   - No hardware dependencies, any host controller with the required SPI and GPIO can use this module.
2. Usable in memory and performance restricted software
   - No dynamic memory allocation

## Example

## Detailed documentation

You can find a detailed documentation in the folder "doc"

## Integration

Build your code with C++20 or later.

## Notes

## Dependencies

The IT8951 module depends on the following headers of the C++ standard library:

- `<span>`
- `<array>`
- `<stdint>`
- `<functional>`
- `<atomic>`

[_Waveshare Wiki_]

## References

1. Waveshare wiki. [waveshare-wiki], 29 January 2023, https://www.waveshare.com/wiki/Main_Page#Display-e-Paper
2. IT8951 specifications. [IT8951 Specifications], https://www.waveshare.com/w/upload/1/18/IT8951_D_V0.2.4.3_20170728.pdf
3. Kirilov, Viktor. [_doctest_][doctest], 05.02.2020, https://github.com/onqtam/doctest, MIT

[waveshare-wiki]: https://www.waveshare.com/wiki/Main_Page#Display-e-Paper
[IT8951 Specifications]: https://www.waveshare.com/w/upload/1/18/IT8951_D_V0.2.4.3_20170728.pdf
[doctest]:  https://github.com/onqtam/doctest