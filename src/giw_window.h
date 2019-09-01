/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015-2017 GDB ImageWatch (github.com/csantosbh/gdb-imagewatch/)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef GIW_WINDOW_H_
#define GIW_WINDOW_H_

#include <Python.h>

#ifndef GIW_API
#  if __GNUC__ >= 4
#    define GIW_API __attribute__((visibility("default")))
#  else
#    define GIW_API
#  endif
#endif

#ifdef __cplusplus
extern "C" {
#endif


typedef void* AppHandler;
typedef void* WindowHandler;


/**
 * Initialize GIW application
 *
 * The thread in which this function will be called will become the GUI thread;
 * all later functions (with exception of giw_terminate()) must be called
 * in the same thread.
 *
 * @return  Application context
 */
GIW_API
AppHandler giw_initialize();

/**
 * Cleanup GIW application
 *
 * This function should be called prior to the application shutdown, in order to
 * release some of the resources acquired by the underlying GUI library.
 *
 * @param handler  Application context generated by giw_initialize()
 */
GIW_API
void giw_cleanup(AppHandler handler);

/**
 * Request GIW application to be terminated
 *
 * This function will close all windows, making the method giw_exec() to finish
 * executing. This function can be called from any thread.
 */
GIW_API
void giw_terminate();

/**
 * Execute GUI loop
 *
 * This methods blocks the caller until the GIW window is closed. If
 * non-blocking behavior is desired, it must be called from a dedicated thread.
 * Notice that it must also be called in the same thread as giw_initialize().
 *
 * @param handler  Application context
 */
GIW_API
void giw_exec(AppHandler handler);

/**
 * Create and open new window
 *
 * Must be called after giw_initialize(), in the same thread as it was called.
 *
 * @param plot_callback  Callback function to be called when the user requests
 *     a symbol name from the giw window
 *
 * @return  Window context
 */
GIW_API
WindowHandler giw_create_window(int (*plot_callback)(const char*));

/**
 * Check if the given window is open
 *
 * @param handler  Window handler, generated by giw_create_window()
 * @return  Returns 1 if the window has been fully initialized, 0 otherwise.
 */
GIW_API
int giw_is_window_ready(WindowHandler handler);

/**
 * Clean up GIW window
 *
 * This function should be called prior to the application shutdown, in order to
 * release some of the resources acquired by the underlying GUI library.
 *
 * @param handler  Window handler, generated by giw_create_window()
 */
GIW_API
void giw_destroy_window(WindowHandler handler);

/**
 * Get a list of the names of all buffers being visualized
 *
 * Returns a python list object with the names of all buffers present in the
 * visualization list.
 *
 * @param handler  Window handler, generated by giw_create_window()
 * @return  Python list object containing python str objects with the names of
 *     all buffers being visualized.
 */
GIW_API
PyObject* giw_get_observed_buffers(WindowHandler handler);

/**
 * Set list of symbols available in the current context
 *
 * Sets a list of names of variables available for plotting in the current
 * context. This list will serve as base for the autocomplete mechanism in the
 * symbol searcher input.
 *
 * @param handler  Window handler, generated by giw_create_window()
 * @param available_set  Python list of python str objects containing the names
 *     of all available symbols in the current context.
 */
GIW_API
void giw_set_available_symbols(WindowHandler handler,
                               PyObject* available_vars);

/**
 * Add a buffer to the plot list
 *
 * @param handler  Handler of the window where the buffer should be plotted
 * @param buffer_metadata  Python dictionary with the following elements:
 *     - [pointer     ] PyMemoryView object wrapping the target buffer
 *     - [display_name] Variable name as it shall be displayed
 *     - [width       ] Buffer width, in pixels
 *     - [height      ] Buffer height, in pixels
 *     - [channels    ] Number of channels (1 to 4)
 *     - [type        ] Buffer type (see symbols.py for details)
 *     - [row_stride  ] Row stride, in pixels
 *     - [pixel_layout] String defining pixel channel layout (e.g. 'rgba')
 * */
GIW_API
void giw_plot_buffer(WindowHandler handler, PyObject* bufffer_metadata);

#ifdef __cplusplus
}
#endif

#endif