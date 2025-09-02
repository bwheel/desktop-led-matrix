from dataclasses import dataclass

from .font import render_text_to_columns


@dataclass
class Rendering:
    columns: list[int]  # list of column data to scroll
    column_index: int = 0  # current position in content


__FRAME_WIDTH = 20  # width of the display in columns
__EMPTY_COLUMN = 0x00  # column of all zeros for spacing
__EMPTY_FRAME = [__EMPTY_COLUMN] * __FRAME_WIDTH  # empty frame for idle display


def create(text: str) -> Rendering:
    columns = render_text_to_columns(text)
    # only scroll if text is wider than the display
    if len(columns) > __FRAME_WIDTH:
        columns = __EMPTY_FRAME + columns + __EMPTY_FRAME
    return Rendering(columns=columns)


def get_current_frame(rendering: Rendering) -> list[int]:
    """Get the current frame to display."""
    start = rendering.column_index
    end = start + __FRAME_WIDTH
    frame = rendering.columns[start:end]
    # pad with empty columns if at the end
    if len(frame) < __FRAME_WIDTH:
        frame += [__EMPTY_COLUMN] * (__FRAME_WIDTH - len(frame))
    return frame


def frame_fits(rendering: Rendering) -> bool:
    """Check if the current render fits within the display width."""
    return len(rendering.columns) <= __FRAME_WIDTH


def advance_render(rendering: Rendering) -> Rendering:
    """Advance the render position by one column, wrapping if needed."""
    rendering.column_index += 1
    if rendering.column_index >= len(rendering.columns):
        rendering.column_index = 0
    return rendering
