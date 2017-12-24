#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<X11/Xlib.h>
#include<GL/glx.h>
#include<dlfcn.h>

Display* disp;
Window win;
XEvent event;
GLint visualAtt[] = {
    GLX_RENDER_TYPE, GLX_RGBA_BIT, 
    GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT, 
    GLX_DOUBLEBUFFER, True, 
    GLX_RED_SIZE, 1,
    GLX_GREEN_SIZE, 1,
    GLX_BLUE_SIZE, 1,
    None
};
XVisualInfo *vi;
Colormap cmap;
XSetWindowAttributes xSetAtt;
XWindowAttributes xWinAtt;
GLXContext ctx_old;
GLXContext ctx;

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

int main(int argc, char** argv) {
    disp = XOpenDisplay(NULL);

    if (disp == NULL) {
        printf("ARGHHHH!!\n");
        exit(1);
    }

    win = XCreateSimpleWindow(disp, DefaultRootWindow(disp), 20, 20, 1000, 1000, 0, 0, 0);

    int numFBC = 0;
    GLXFBConfig *fbc = glXChooseFBConfig(disp, DefaultScreen(disp), visualAtt, &numFBC);

    if (!fbc) {
        printf("GRRRNO FRAMBUFFAR!!!!\n");
        exit(1);        
    }

    vi = glXGetVisualFromFBConfig(disp, *fbc);

    if (vi == NULL) {
        printf("GRRRNO VISUAL!!!!\n");
        exit(1);        
    }

    printf("Visual %p selected\n", (void *) vi->visualid);
    
    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddress((const GLubyte* )"glXCreateContextAttribsARB");

    if (!glXCreateContextAttribsARB) {
        printf("GRRRNO glXCreateContextAttribsARB!!!!\n");
        exit(1); 
    }

    static int contextAttribs[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 5,
        None
    };

    ctx = glXCreateContextAttribsARB(disp, *fbc, NULL, True, contextAttribs);

    if (!ctx) {
        printf("GRRR WHY NO CONTEXT!?!?!\n");
        exit(1);
    }
    
    XSelectInput(disp, win, ExposureMask | KeyPressMask);
    XMapWindow(disp, win);
    XStoreName(disp, win, "Tarek's Bare-bones OpenGL App!");
    glXMakeCurrent(disp, win, ctx);

    int major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    printf("OPENGL: \nVersion: %d.%d\nVendor: %s\nRenderer: %s\n", major, minor, glGetString(GL_VENDOR), glGetString(GL_RENDERER));

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
