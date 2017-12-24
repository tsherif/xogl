#define XK_LATIN1
#define XK_MISCELLANY
#include<X11/Xlib.h>
#include<X11/keysymdef.h>
#include<stdio.h>
#include<string.h>

#define PI 3.14159

int main(int argc, char const *argv[]) {
    Display* disp;
    int screen;
    Window win;
    GC ctx;
    unsigned long black, white, seagreen;

    disp = XOpenDisplay(0);
    screen = DefaultScreen(disp);
    black = BlackPixel(disp, screen);
    white = WhitePixel(disp, screen);

    XColor screenColor;
    XColor exactColor;    
    // XParseColor(disp, DefaultColormap(disp, screen), "rgb:00/ff/00", &tmp);
    XAllocNamedColor(disp, DefaultColormap(disp, screen), "rgb:00/ff/ff", &screenColor, &exactColor);
    seagreen = screenColor.pixel;

    win = XCreateSimpleWindow(disp, DefaultRootWindow(disp), 0, 0, 600, 600, 5, white, black);
    XStoreName(disp, win, "Tarek's X11!!!");

    XSelectInput(disp, win, ExposureMask | ButtonPressMask | KeyPressMask);

    ctx = XCreateGC(disp, win, 0, 0);

    XSetBackground(disp, ctx, black);
    XSetForeground(disp, ctx, white);

    XMapWindow(disp, win);

    XEvent event;
    KeySym key;
    char text[255];

    typedef struct {
        int x;
        int y;
        int radius;
    } circle;

    circle player = { 300, 300, 20 };

    while(1) {
        XNextEvent(disp, &event);
   
        XSetForeground(disp, ctx, black);
        XFillRectangle(disp, win, ctx, 0, 0, 600, 600);

        if (event.type == KeyPress) {

            KeySym key = XLookupKeysym(&event.xkey, 0);
                
            if (key == XK_space) {
                printf("You  hit SPACE\n");
            } else if (key > '0' && key < 'z') {
                printf("%c\n", (char) key);
            }

            if (key == XK_Left) {
                player.x -= 5;
            }

            if (key == XK_Right) {
                player.x += 5;
            }

            if (key == XK_Up) {
                player.y -= 5;
            }

            if (key == XK_Down) {
                player.y += 5;
            }

            if (key == XK_q) {
                break;
            }
    
        }

        if (event.type == ButtonPress) {
            XSetForeground(disp, ctx, white);
            XFillArc(disp, win, ctx, event.xbutton.x - 5, event.xbutton.y - 5, 10, 10, 0, 360 * 64);
        }


        XSetForeground(disp, ctx, seagreen);
        XFillArc(disp, win, ctx, player.x - player.radius, player.y - player.radius, 2 * player.radius, 2 * player.radius, 0, 360 * 64);

        const char* message = "Tarek's programming X11!!!";
        XDrawString(disp, win, ctx, 10, 30, message, strlen(message));

    }

    XFreeGC(disp, ctx);
    XDestroyWindow(disp, win);
    XCloseDisplay(disp);

    return 0;
}
