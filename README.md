XOGL
====

Minimal OpenGL loader for X11.

XOGL consists of three functions:
- `xogl_init()`: Initialize an OpenGL context and load OpenGL functions.
- `xogl_swapBuffers()`: Swap front and backbuffers. Use after finished drawing.
- `xogl_destroy()`: Destroy the OpenGL context.

Basic usage:
```C
    Display* disp = XOpenDisplay(NULL);
    Window win = XCreateSimpleWindow(disp, DefaultRootWindow(disp), 20, 20, 1024, 1024, 0, 0, 0);
    XMapWindow(disp, win);

    // Attempt to initialize an OpenGL 4.5 context
    if (xogl_init(disp, win, 4, 5)) {
        fprintf(stderr, "Unable initialize OpenGL!\n");
        return 1;
    }

    // OpenGL setup function calls

    while(1) {
        if (!running) {
            break;
        }

        // OpenGL frame function calls

        xogl_swapBuffers(disp, win);
    }

    xogl_destroy(disp);
```
