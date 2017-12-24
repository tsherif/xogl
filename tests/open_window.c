#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<X11/Xlib.h>
#include<GL/glx.h>

Display* d;
Window w;
XEvent e;
int s;

int main(int argc, char** argv) {
    char* message = "Hi, there!";
    d = XOpenDisplay(NULL);

    if (d == NULL) {
        printf("ARGHHHH!!\n");
        exit(1);
    }

    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 20, 20, 1000, 1000, 1, BlackPixel(d, s), WhitePixel(d, s));

    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapWindow(d, w);

    while (1) {
        XNextEvent(d, &e);

        if (e.type == Expose) {
            XFillRectangle(d, w, DefaultGC(d, s), 40, 40, 20, 20);
            XDrawString(d, w, DefaultGC(d, s), 20, 100, message, strlen(message));
        }

        if (e.type == KeyPress) {
            break;
        }
    };

    XCloseDisplay(d);
    printf("Done!\n");
}
