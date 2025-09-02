from dataclasses import dataclass
from contextlib import contextmanager
from typing import Any, Generator
import serial


@dataclass
class TransportSession:
    connection: serial.Serial


@contextmanager
def open(port: str, baudrate: int = 57600) -> Generator[TransportSession, Any, None]:
    ser: serial.Serial = None
    try:
        ser = serial.Serial(port, baudrate, timeout=1)
        if not ser.is_open:
            ser.open()
        assert ser.is_open, "Failed to open serial port"
        yield TransportSession(connection=ser)
    finally:
        if ser is not None and ser.is_open:
            ser.close()


def clear(session: TransportSession):
    _send(session, "CLEAR")


def set_pixel(session: TransportSession, x: int, y: int, value: bool):
    val = 1 if value else 0
    payload = f"SETPIXEL|{x}|{y}|{val}"
    _send(session, payload)


def render(session: TransportSession, frame: list[int]):
    payload = "RENDER|" + "|".join(str(c) for c in frame)
    _send(session, payload)


def ping(session: TransportSession) -> bool:
    response = _query(session, "PING")
    return response == "PONG"


def firmware_version(session: TransportSession) -> str:
    response = _query(session, "FWVERSION")
    return response


def _send(session: TransportSession, payload: str):
    data = payload + "\n"
    # print(f"  DEBUG: Sending: {data}")
    session.connection.write(data.encode("ascii"))
    session.connection.flush()


def _query(session: TransportSession, command: str) -> str:
    _send(session, command)
    resp = session.connection.readline().decode("ascii").strip()
    # print(f"  DEBUG: RAW Response: {resp}")
    return resp
