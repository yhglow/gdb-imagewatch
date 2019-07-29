include($$PWD/../common.pri)

CONFIG += $$BUILD_MODE
message(GDB-ImageWatch UI build mode: $$BUILD_MODE)

# Prevent strip from producing spurious error messages
QMAKE_STRIP = echo "strip disabled: "

QT += \
  core \
  gui \
  opengl \
  widgets \
  gui

QMAKE_LFLAGS += \
  # If you have an error "cannot find -lGL", uncomment the following line and
  # replace the folder by the location of your libGL.so
  #-L/path/to/your/opengl/folder

linux-g++ {
    QMAKE_LFLAGS += -Wl,--exclude-libs,ALL
}

SOURCES += \
  giw_window.cpp \
  io/buffer_exporter.cpp \
  math/assorted.cpp \
  math/linear_algebra.cpp \
  ui/gl_canvas.cpp \
  ui/symbol_completer.cpp \
  ui/symbol_search_input.cpp \
  ui/main_window/main_window.cpp \
  ui/main_window/initialization.cpp \
  ui/main_window/auto_contrast.cpp \
  ui/main_window/ui_events.cpp \
  visualization/events.cpp \
  visualization/game_object.cpp \
  visualization/shader.cpp \
  visualization/stage.cpp \
  visualization/components/background.cpp \
  visualization/components/buffer.cpp \
  visualization/components/buffer_values.cpp \
  visualization/components/camera.cpp\
  visualization/components/component.cpp\
  visualization/shaders/background_fs.cpp \
  visualization/shaders/background_vs.cpp \
  visualization/shaders/buffer_fs.cpp \
  visualization/shaders/buffer_vs.cpp \
  visualization/shaders/text_fs.cpp \
  visualization/shaders/text_vs.cpp \
  ui/gl_text_renderer.cpp \
  ui/go_to_widget.cpp \
  ui/decorated_line_edit.cpp

# Qt related headers
HEADERS += \
  debuggerinterface/preprocessor_directives.h \
  ui/gl_canvas.h \
  ui/main_window/main_window.h \
  ui/symbol_completer.h \
  ui/symbol_search_input.h \
  ui/gl_text_renderer.h \
  ui/go_to_widget.h \
  ui/decorated_line_edit.h

TARGET = giwwindow
TEMPLATE = app
target.path = $$PREFIX/bin/gdb-imagewatch/

INSTALLS += \
  target

# Assorted configuration
INCLUDEPATH += \
  $$PWD \
  $$PWD/thirdparty/Khronos/

FORMS += ui/main_window.ui

RESOURCES += resources/resources.qrc

