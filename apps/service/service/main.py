import time
import os

from dotenv import load_dotenv
import finnhub


from service import transport
from service import render
from service import scroll


def get_stock_price(symbol: str) -> str:
    api_key = os.getenv("ALPHA_VANTAGE_API_KEY")
    finnhub_client = finnhub.Client(api_key=api_key)
    quote = finnhub_client.quote(symbol)
    return f"${quote['c']}"


def main():
    load_dotenv()  # Load environment variables from .env file
    dave_price = get_stock_price("DAVE")
    serial_port = os.getenv("SERIAL_PORT")
    baudrate = int(os.getenv("BAUDRATE", "57600"))
    print(f"Current price of DAVE:{dave_price}")
    with transport.open(port=serial_port, baudrate=baudrate) as session:
        rendering = render.create(dave_price)
        scroll_state = scroll.create()
        frame = render.get_current_frame(rendering)

        transport.clear(session)
        response = transport.ping(session)
        print(f"Ping response: {response}")
        version = transport.firmware_version(session)
        print(f"Firmware version: {version}")

        stock_start_time = time.time()
        stock_update_interval = 60 * 0.5  # Update stock price every 30 seconds

        while True:
            if time.time() - stock_start_time > stock_update_interval:
                dave_price = get_stock_price("DAVE")
                rendering = render.create(dave_price)
                scroll_state = scroll.create()
                stock_start_time = time.time()

            if not render.frame_fits(rendering):
                if scroll.should_advance(scroll_state):
                    frame = render.get_current_frame(rendering)
                    rendering = render.advance_render(rendering)
                transport.render(session, frame)
                time.sleep(0.12)
            else:
                transport.render(session, frame)
                time.sleep(1)


if __name__ == "__main__":
    main()
