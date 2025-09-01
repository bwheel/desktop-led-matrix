# Firmware for Desktop LED Matrix

This folder contains the firmware source code for the Spikenzie LED Clock and related hardware. The firmware is designed to run on microcontrollers compatible with PlatformIO, enabling control and customization of the LED matrix display.

## Features

- Control of LED matrix display
- Custom animations and clock functionality
- Easy integration with desktop applications

## Getting Started

### Prerequisites

- [PlatformIO](https://platformio.org/) installed (recommended via VS Code extension or command line)

### Compiling the Firmware

1. Open this folder in [Visual Studio Code](https://code.visualstudio.com/) with the PlatformIO extension installed, or navigate to this folder in your terminal.
2. Run the following command to build the firmware:
   ```
   platformio run
   ```

### Uploading to the Device

1. Connect your microcontroller to your computer via USB.
2. Run the following command to upload the firmware:
   ```
   platformio run --target upload
   ```

### Monitoring Serial Output

To view debug output or logs from the device, use:
```
platformio device monitor
```

## More Information

- [PlatformIO Documentation](https://docs.platformio.org/)
- [PlatformIO IDE for VS Code](https://platformio.org/install/ide?install=vscode)

---
For hardware setup and wiring, refer to the main project documentation