# MikroDuino Nano V2

MikroDuino Nano V2 is an Arduino Nano-based electronics learning platform. This repository brings together Arduino example sketches, supporting libraries, board images, kit information, Proteus design files, and project documentation.

## Repository contents

- `Examples/` — Arduino sketches organized by topic, including ADC, GPIO, PWM, I2C, OLED, DHT11, DS1307 RTC, IR remote, MAX7219, MPU6050, TM1637, TM1638, and UART.
- `Examples/libraries/` — libraries used by the example projects.
- `Examples.zip` — an archive of the examples.
- `Images/` — board, component, and project images.
- `Kit/` — kit parts list and related files.
- `Proteus/` — Proteus design files and project backups.
- `Publisher/` — available brochures and getting-started documentation.
- `Camtasia/` — source media and project files for the introduction.

## Getting started

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Open the `Examples/` folder and choose a sketch for the topic you want to try. For example, `Examples/GPIO/01-Blink/01-Blink.ino`.
3. Connect your MikroDuino Nano V2 and select the board and processor settings that match your board in the Arduino IDE.
4. Install any libraries required by the sketch if they are not already available in `Examples/libraries/`.
5. Select the correct port, then compile and upload the sketch.

Some examples require additional components or displays. Check each sketch and its accompanying files before wiring hardware.

## Large files

Three files larger than GitHub's 100 MB per-file limit were not uploaded:

- `Camtasia/MikroDuino nano Intro/MikroDuino nano Intro.mp4`
- `Images/20250302_143846.mp4`
- `Publisher/Arduino Getting Started with Mikroduino-V2.pub`

These paths are listed in `.gitignore`. Other files in those folders, including the available PDF getting-started guide, are included.

## License

See [LICENSE](LICENSE) for this repository's license. Bundled libraries may have their own licenses; see the license files in their respective folders.
