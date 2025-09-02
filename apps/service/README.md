# Desktop LED Matrix Service

This project provides a service for controlling a desktop LED matrix device. It fetches financial data from the Finnhub API and communicates with the LED matrix via a serial port connection.

## Features

- Retrieves real-time financial data using the Finnhub API.
- Sends data to the LED matrix device over a serial port.
- Easy to run locally for development and testing.

## Dependencies

- **Finnhub API**: You must have a Finnhub API key to fetch financial data. [Get your API key here](https://finnhub.io/).
- **Serial Port**: The service requires access to the serial port connected to your LED matrix device.

## Running Locally

1. **Clone the repository**
  ```bash
  git clone https://github.com/yourusername/desktop-led-matrix.git
  cd desktop-led-matrix/apps/service
  ```

2. **Set up environment variables**

  Create a `.env` file in the project root with the following:
  ```
  FINNHUB_API_KEY=your_finnhub_api_key
  SERIAL_PORT=/dev/ttyUSB0  # Update with your device's serial port
  ```

3. **Start the service**

  Run the following command to start the service:
  ```bash
  python -m service.main
  ```

## Notes

- Ensure your user has permission to access the serial port.
- The LED matrix device must be connected and powered on.
