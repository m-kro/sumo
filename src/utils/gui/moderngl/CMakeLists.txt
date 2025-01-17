set(utils_gui_moderngl_STAT_SRCS
    GLShader.h
    GLShader.cpp
)

add_library(utils_gui_moderngl STATIC ${utils_gui_moderngl_STAT_SRCS})
set_property(TARGET utils_gui_moderngl PROPERTY PROJECT_LABEL "z_utils_gui_moderngl")
