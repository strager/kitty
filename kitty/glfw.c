/*
 * Copyright (C) 2016 Kovid Goyal <kovid at kovidgoyal.net>
 *
 * Distributed under terms of the GPL3 license.
 */

#include "data-types.h"
#include <GLFW/glfw3.h>

#define MAX_WINDOWS 255
/* static PyObject* window_weakrefs[MAX_WINDOWS + 1] = {0}; */

#define CALLBACK(name, fmt, ...) \
    if ((name) != NULL) { \
        PyGILState_STATE _pystate = PyGILState_Ensure(); \
        PyObject *_pyret = PyObject_CallFunction((name), fmt, __VA_ARGS__); \
        PyGILState_Release(_pystate); \
        if (_pyret == NULL) { PyErr_Print(); PyErr_Clear(); return; } \
        Py_CLEAR(_pyret); \
    } 


// Library Setup {{{
static PyObject *error_callback = NULL;

static void 
cb_error_callback(int error, const char* description) {
    CALLBACK(error_callback, "is", error, description) else fprintf(stderr, "[glfw error]: %s\n", description);
}

PyObject*
glfw_set_error_callback(PyObject UNUSED *self, PyObject *callback) {
    Py_CLEAR(error_callback);
    error_callback = callback;
    Py_INCREF(callback);
    Py_RETURN_NONE;
}

PyObject*
glfw_init(PyObject UNUSED *self) {
    PyObject *ans = glfwInit() ? Py_True: Py_False;
    Py_INCREF(ans);
    return ans;
}

PyObject*
glfw_terminate(PyObject UNUSED *self) {
    glfwTerminate();
    Py_RETURN_NONE;
}

PyObject*
glfw_window_hint(PyObject UNUSED *self, PyObject *args) {
    int hint, value;
    if (!PyArg_ParseTuple(args, "ii", &hint, &value)) return NULL;
    glfwWindowHint(hint, value);
    Py_RETURN_NONE;
}

PyObject* 
glfw_swap_interval(PyObject UNUSED *self, PyObject *args) {
    int value;
    if (!PyArg_ParseTuple(args, "i", &value)) return NULL;
    glfwSwapInterval(value);
    Py_RETURN_NONE;
}

PyObject*
glfw_wait_events(PyObject UNUSED *self) {
    Py_BEGIN_ALLOW_THREADS;
    glfwWaitEvents();
    Py_END_ALLOW_THREADS;
    Py_RETURN_NONE;
}

// }}}

// constants {{{
bool
init_glfw(PyObject *m) {
    PyEval_InitThreads();
    glfwSetErrorCallback(cb_error_callback);
#define ADDC(n) if(PyModule_AddIntConstant(m, #n, n) != 0) return false;
    ADDC(GLFW_RELEASE);
    ADDC(GLFW_PRESS);
    ADDC(GLFW_REPEAT);

// --- Keys --------------------------------------------------------------------

// --- The unknown key ---------------------------------------------------------
    ADDC(GLFW_KEY_UNKNOWN);

// --- Printable keys ----------------------------------------------------------
    ADDC(GLFW_KEY_SPACE);
    ADDC(GLFW_KEY_APOSTROPHE);
    ADDC(GLFW_KEY_COMMA);
    ADDC(GLFW_KEY_MINUS);
    ADDC(GLFW_KEY_PERIOD);
    ADDC(GLFW_KEY_SLASH);
    ADDC(GLFW_KEY_0);
    ADDC(GLFW_KEY_1);
    ADDC(GLFW_KEY_2);
    ADDC(GLFW_KEY_3);
    ADDC(GLFW_KEY_4);
    ADDC(GLFW_KEY_5);
    ADDC(GLFW_KEY_6);
    ADDC(GLFW_KEY_7);
    ADDC(GLFW_KEY_8);
    ADDC(GLFW_KEY_9);
    ADDC(GLFW_KEY_SEMICOLON);
    ADDC(GLFW_KEY_EQUAL);
    ADDC(GLFW_KEY_A);
    ADDC(GLFW_KEY_B);
    ADDC(GLFW_KEY_C);
    ADDC(GLFW_KEY_D);
    ADDC(GLFW_KEY_E);
    ADDC(GLFW_KEY_F);
    ADDC(GLFW_KEY_G);
    ADDC(GLFW_KEY_H);
    ADDC(GLFW_KEY_I);
    ADDC(GLFW_KEY_J);
    ADDC(GLFW_KEY_K);
    ADDC(GLFW_KEY_L);
    ADDC(GLFW_KEY_M);
    ADDC(GLFW_KEY_N);
    ADDC(GLFW_KEY_O);
    ADDC(GLFW_KEY_P);
    ADDC(GLFW_KEY_Q);
    ADDC(GLFW_KEY_R);
    ADDC(GLFW_KEY_S);
    ADDC(GLFW_KEY_T);
    ADDC(GLFW_KEY_U);
    ADDC(GLFW_KEY_V);
    ADDC(GLFW_KEY_W);
    ADDC(GLFW_KEY_X);
    ADDC(GLFW_KEY_Y);
    ADDC(GLFW_KEY_Z);
    ADDC(GLFW_KEY_LEFT_BRACKET);
    ADDC(GLFW_KEY_BACKSLASH);
    ADDC(GLFW_KEY_RIGHT_BRACKET);
    ADDC(GLFW_KEY_GRAVE_ACCENT);
    ADDC(GLFW_KEY_WORLD_1);
    ADDC(GLFW_KEY_WORLD_2);

// --- Function keys -----------------------------------------------------------
    ADDC(GLFW_KEY_ESCAPE);
    ADDC(GLFW_KEY_ENTER);
    ADDC(GLFW_KEY_TAB);
    ADDC(GLFW_KEY_BACKSPACE);
    ADDC(GLFW_KEY_INSERT);
    ADDC(GLFW_KEY_DELETE);
    ADDC(GLFW_KEY_RIGHT);
    ADDC(GLFW_KEY_LEFT);
    ADDC(GLFW_KEY_DOWN);
    ADDC(GLFW_KEY_UP);
    ADDC(GLFW_KEY_PAGE_UP);
    ADDC(GLFW_KEY_PAGE_DOWN);
    ADDC(GLFW_KEY_HOME);
    ADDC(GLFW_KEY_END);
    ADDC(GLFW_KEY_CAPS_LOCK);
    ADDC(GLFW_KEY_SCROLL_LOCK);
    ADDC(GLFW_KEY_NUM_LOCK);
    ADDC(GLFW_KEY_PRINT_SCREEN);
    ADDC(GLFW_KEY_PAUSE);
    ADDC(GLFW_KEY_F1);
    ADDC(GLFW_KEY_F2);
    ADDC(GLFW_KEY_F3);
    ADDC(GLFW_KEY_F4);
    ADDC(GLFW_KEY_F5);
    ADDC(GLFW_KEY_F6);
    ADDC(GLFW_KEY_F7);
    ADDC(GLFW_KEY_F8);
    ADDC(GLFW_KEY_F9);
    ADDC(GLFW_KEY_F10);
    ADDC(GLFW_KEY_F11);
    ADDC(GLFW_KEY_F12);
    ADDC(GLFW_KEY_F13);
    ADDC(GLFW_KEY_F14);
    ADDC(GLFW_KEY_F15);
    ADDC(GLFW_KEY_F16);
    ADDC(GLFW_KEY_F17);
    ADDC(GLFW_KEY_F18);
    ADDC(GLFW_KEY_F19);
    ADDC(GLFW_KEY_F20);
    ADDC(GLFW_KEY_F21);
    ADDC(GLFW_KEY_F22);
    ADDC(GLFW_KEY_F23);
    ADDC(GLFW_KEY_F24);
    ADDC(GLFW_KEY_F25);
    ADDC(GLFW_KEY_KP_0);
    ADDC(GLFW_KEY_KP_1);
    ADDC(GLFW_KEY_KP_2);
    ADDC(GLFW_KEY_KP_3);
    ADDC(GLFW_KEY_KP_4);
    ADDC(GLFW_KEY_KP_5);
    ADDC(GLFW_KEY_KP_6);
    ADDC(GLFW_KEY_KP_7);
    ADDC(GLFW_KEY_KP_8);
    ADDC(GLFW_KEY_KP_9);
    ADDC(GLFW_KEY_KP_DECIMAL);
    ADDC(GLFW_KEY_KP_DIVIDE);
    ADDC(GLFW_KEY_KP_MULTIPLY);
    ADDC(GLFW_KEY_KP_SUBTRACT);
    ADDC(GLFW_KEY_KP_ADD);
    ADDC(GLFW_KEY_KP_ENTER);
    ADDC(GLFW_KEY_KP_EQUAL);
    ADDC(GLFW_KEY_LEFT_SHIFT);
    ADDC(GLFW_KEY_LEFT_CONTROL);
    ADDC(GLFW_KEY_LEFT_ALT);
    ADDC(GLFW_KEY_LEFT_SUPER);
    ADDC(GLFW_KEY_RIGHT_SHIFT);
    ADDC(GLFW_KEY_RIGHT_CONTROL);
    ADDC(GLFW_KEY_RIGHT_ALT);
    ADDC(GLFW_KEY_RIGHT_SUPER);
    ADDC(GLFW_KEY_MENU);
    ADDC(GLFW_KEY_LAST);

// --- Modifiers ---------------------------------------------------------------
    ADDC(GLFW_MOD_SHIFT);
    ADDC(GLFW_MOD_CONTROL);
    ADDC(GLFW_MOD_ALT);
    ADDC(GLFW_MOD_SUPER);

// --- Mouse -------------------------------------------------------------------
    ADDC(GLFW_MOUSE_BUTTON_1);
    ADDC(GLFW_MOUSE_BUTTON_2);
    ADDC(GLFW_MOUSE_BUTTON_3);
    ADDC(GLFW_MOUSE_BUTTON_4);
    ADDC(GLFW_MOUSE_BUTTON_5);
    ADDC(GLFW_MOUSE_BUTTON_6);
    ADDC(GLFW_MOUSE_BUTTON_7);
    ADDC(GLFW_MOUSE_BUTTON_8);
    ADDC(GLFW_MOUSE_BUTTON_LAST);
    ADDC(GLFW_MOUSE_BUTTON_LEFT);
    ADDC(GLFW_MOUSE_BUTTON_RIGHT);
    ADDC(GLFW_MOUSE_BUTTON_MIDDLE);


// --- Joystick ----------------------------------------------------------------
    ADDC(GLFW_JOYSTICK_1);
    ADDC(GLFW_JOYSTICK_2);
    ADDC(GLFW_JOYSTICK_3);
    ADDC(GLFW_JOYSTICK_4);
    ADDC(GLFW_JOYSTICK_5);
    ADDC(GLFW_JOYSTICK_6);
    ADDC(GLFW_JOYSTICK_7);
    ADDC(GLFW_JOYSTICK_8);
    ADDC(GLFW_JOYSTICK_9);
    ADDC(GLFW_JOYSTICK_10);
    ADDC(GLFW_JOYSTICK_11);
    ADDC(GLFW_JOYSTICK_12);
    ADDC(GLFW_JOYSTICK_13);
    ADDC(GLFW_JOYSTICK_14);
    ADDC(GLFW_JOYSTICK_15);
    ADDC(GLFW_JOYSTICK_16);
    ADDC(GLFW_JOYSTICK_LAST);


// --- Error codes -------------------------------------------------------------
    ADDC(GLFW_NOT_INITIALIZED);
    ADDC(GLFW_NO_CURRENT_CONTEXT);
    ADDC(GLFW_INVALID_ENUM);
    ADDC(GLFW_INVALID_VALUE);
    ADDC(GLFW_OUT_OF_MEMORY);
    ADDC(GLFW_API_UNAVAILABLE);
    ADDC(GLFW_VERSION_UNAVAILABLE);
    ADDC(GLFW_PLATFORM_ERROR);
    ADDC(GLFW_FORMAT_UNAVAILABLE);

// ---
    ADDC(GLFW_FOCUSED);
    ADDC(GLFW_ICONIFIED);
    ADDC(GLFW_RESIZABLE);
    ADDC(GLFW_VISIBLE);
    ADDC(GLFW_DECORATED);
    ADDC(GLFW_AUTO_ICONIFY);
    ADDC(GLFW_FLOATING);

// ---
    ADDC(GLFW_RED_BITS);
    ADDC(GLFW_GREEN_BITS);
    ADDC(GLFW_BLUE_BITS);
    ADDC(GLFW_ALPHA_BITS);
    ADDC(GLFW_DEPTH_BITS);
    ADDC(GLFW_STENCIL_BITS);
    ADDC(GLFW_ACCUM_RED_BITS);
    ADDC(GLFW_ACCUM_GREEN_BITS);
    ADDC(GLFW_ACCUM_BLUE_BITS);
    ADDC(GLFW_ACCUM_ALPHA_BITS);
    ADDC(GLFW_AUX_BUFFERS);
    ADDC(GLFW_STEREO);
    ADDC(GLFW_SAMPLES);
    ADDC(GLFW_SRGB_CAPABLE);
    ADDC(GLFW_REFRESH_RATE);
    ADDC(GLFW_DOUBLEBUFFER);

// ---
    ADDC(GLFW_CLIENT_API);
    ADDC(GLFW_CONTEXT_VERSION_MAJOR);
    ADDC(GLFW_CONTEXT_VERSION_MINOR);
    ADDC(GLFW_CONTEXT_REVISION);
    ADDC(GLFW_CONTEXT_ROBUSTNESS);
    ADDC(GLFW_OPENGL_FORWARD_COMPAT);
    ADDC(GLFW_OPENGL_DEBUG_CONTEXT);
    ADDC(GLFW_OPENGL_PROFILE);

// ---
    ADDC(GLFW_OPENGL_API);
    ADDC(GLFW_OPENGL_ES_API);

// ---
    ADDC(GLFW_NO_ROBUSTNESS);
    ADDC(GLFW_NO_RESET_NOTIFICATION);
    ADDC(GLFW_LOSE_CONTEXT_ON_RESET);

// ---
    ADDC(GLFW_OPENGL_ANY_PROFILE);
    ADDC(GLFW_OPENGL_CORE_PROFILE);
    ADDC(GLFW_OPENGL_COMPAT_PROFILE);

// ---
    ADDC(GLFW_CURSOR);
    ADDC(GLFW_STICKY_KEYS);
    ADDC(GLFW_STICKY_MOUSE_BUTTONS);

// ---
    ADDC(GLFW_CURSOR_NORMAL);
    ADDC(GLFW_CURSOR_HIDDEN);
    ADDC(GLFW_CURSOR_DISABLED);

// ---
    ADDC(GLFW_CONNECTED);
    ADDC(GLFW_DISCONNECTED);

return true;
#undef ADDC
}
// }}}
