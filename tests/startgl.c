#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<X11/Xlib.h>
#include<GL/glx.h>
#include<dlfcn.h>

Display* disp;
Window root;
Window win;
XEvent event;
int s;
GLint att[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
XVisualInfo *vi;
Colormap cmap;
XSetWindowAttributes xSetAtt;
XWindowAttributes xWinAtt;
GLXContext ctx;

int main(int argc, char** argv) {
    char* message = "Hi, there!";
    disp = XOpenDisplay(NULL);

    if (disp == NULL) {
        printf("ARGHHHH!!\n");
        exit(1);
    }

    root = DefaultRootWindow(disp);
    vi = glXChooseVisual(disp, 0, att);

    if (vi == NULL) {
        printf("GRRRNO VISUAL!!!!\n");
        exit(1);        
    }

    printf("Visual %p selected\n", (void *) vi->visualid);

    cmap = XCreateColormap(disp, root, vi->visual, AllocNone);

    xSetAtt.colormap = cmap;
    xSetAtt.event_mask = ExposureMask | KeyPressMask;

    win = XCreateWindow(disp, root, 100, 100, 1200, 1200, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &xSetAtt);

    XMapWindow(disp, win);
    XStoreName(disp, win, "Tarek's Bare-bones OpenGL App!");

    ctx = glXCreateContext(disp, vi, NULL, GL_TRUE);
    glXMakeCurrent(disp, win, ctx);

    glClearColor(0.0, 1.0, 0.0, 1.0);

    while (1) {
        XNextEvent(disp, &event);

        if (event.type == Expose) {
            XGetWindowAttributes(disp, win, &xWinAtt);
            glViewport(0, 0, xWinAtt.width, xWinAtt.height);
            glClear(GL_COLOR_BUFFER_BIT);
            glXSwapBuffers(disp, win);
        }

        if (event.type == KeyPress) {
            break;
        }
    };

    glXMakeCurrent(disp, None, NULL);
    glXDestroyContext(disp, ctx);
    XDestroyWindow(disp, win);
    XCloseDisplay(disp);
    printf("Done!\n");
}
