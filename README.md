# IT8951

- [IT8951](#it8951)
  - [Introduction](#introduction)
  - [Documentation](#documentation)
  - [Usage](#usage)
  - [Dependencies](#dependencies)
  - [License](#license)

## Introduction

This module provides a generic driver for the IT8951 e-paper controller by Waveshare. It has the following properties:

- Written in C++20.
- No hardware dependencies. Any host with the required SPI and GPIOs can use this module.
- No dynamic memory allocation.
- Thread safe, meaning that simultaneous calls from different threads do not lead to undefined behavior.

Refer to the [Waveshare wiki] or the [IT8951 Specifications] for more information about the IT8951 and the corresponding e-paper displays.

## Documentation

The documentation can be found in the folder [documentation](documentation).

## Usage

Add the [module](module) to your repository and implement the SPI and GPIO interfaces. An example can be found in the folder [example](example). The example uses the following hardware:

- IT8951 Driver HAT
- RaspberryPi 4
- 10.3 inch e-paper display

Do not use the example in your production code. It is only there to help you with your own integration and is not meant for real apllications. Also, because of its dependencies, it cannot be released under the MIT license.

## Dependencies

The IT8951 module depends on the following headers of the C++ standard library:

- `<algorithm>`
- `<array>`
- `<atomic>`
- `<cstdint>`
- `<functional>`
- `<limits>`
- `<semaphore>`
- `<span>`
- `<string>`
- `<thread>`
- `<tuple>`

## License

This module is distributed under the MIT license (see accompanying file LICENSE). The [example](example) however is distributed under the GNU GENERAL PUBLIC LICENSE Version 3 (see accompanying file LICENSE-example).

[Waveshare Wiki]: https://www.waveshare.com/wiki/Main_Page#Display-e-Paper
[IT8951 Specifications]: https://www.waveshare.com/w/upload/1/18/IT8951_D_V0.2.4.3_20170728.pdf
