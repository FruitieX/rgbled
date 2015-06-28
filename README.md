# rgbled

Arduino RGB led controller over serial port.

Format for setting colors is e.g. `R255.00G255.00B255.00\n`, which would be white

## Features

- Supports floats & doubles as well as integers
- Temporal dithering
- Manual calibration of channels
- Communication over serial port
- Fast updates (115200 baud)
