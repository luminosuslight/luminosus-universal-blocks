# --- Source Files ---
set(PROJECT_HEADERS
    ${PROJECT_HEADERS}
    universal-blocks/content/ImageBlock.h
    universal-blocks/content/NotesBlock.h
    universal-blocks/controls/SliderBlock.h
    universal-blocks/inspection/ApplicationLogBlock.h
    universal-blocks/inspection/DataInspectionBlock.h
    universal-blocks/inspection/GuiEditorBlock.h
    universal-blocks/inspection/PerformanceMonitorBlock.h
    universal-blocks/inspection/SmokeTestBlock.h
    universal-blocks/time/ClockBlock.h
    universal-blocks/time/StopWatchBlock.h
    universal-blocks/time/TimerBlock.h
)

set(PROJECT_SOURCES
    ${PROJECT_SOURCES}
    universal-blocks/content/ImageBlock.cpp
    universal-blocks/content/NotesBlock.cpp
    universal-blocks/controls/SliderBlock.cpp
    universal-blocks/inspection/ApplicationLogBlock.cpp
    universal-blocks/inspection/DataInspectionBlock.cpp
    universal-blocks/inspection/GuiEditorBlock.cpp
    universal-blocks/inspection/PerformanceMonitorBlock.cpp
    universal-blocks/inspection/SmokeTestBlock.cpp
    universal-blocks/time/ClockBlock.cpp
    universal-blocks/time/StopWatchBlock.cpp
    universal-blocks/time/TimerBlock.cpp
)

# --- Resource Files ---
set(PROJECT_RESOURCES
    ${PROJECT_RESOURCES}
    universal-blocks/universal-blocks.qrc
)
