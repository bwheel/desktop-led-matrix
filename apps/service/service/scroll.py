import time
from dataclasses import dataclass


@dataclass
class Scroll:
    start: time.time  # when the scroll started


__SCROLL_SPEED = 0.1  # seconds per column scroll


def create() -> Scroll:
    return Scroll(start=time.time())


def should_advance(scroll: Scroll) -> bool:
    """Check if enough time has passed to advance the scroll."""
    elapsed = time.time() - scroll.start
    return elapsed >= __SCROLL_SPEED
