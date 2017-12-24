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

typedef void (*glGenBuffersProc)(GLsizei, GLuint *);
typedef void (*glBindBufferProc)(GLenum target, GLuint); 
typedef void (*glGenVertexArraysProc)(GLsizei, GLuint *);
typedef void (*glBindVertexArrayProc)(GLuint); 
typedef void (*glBufferDataProc)(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage); 
typedef void (*glVertexAttribPointerProc)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer); 
typedef void (*glEnableVertexAttribArrayProc)(GLuint index); 
typedef GLuint (*glCreateShaderProc)(GLenum type); 
typedef void (*glShaderSourceProc)(GLuint shader, GLsizei count, const GLchar* const *string, const GLint *length); 
typedef void (*glCompileShaderProc)(GLuint shader); 
typedef void (*glAttachShaderProc)(GLuint program, GLuint shader); 
typedef void (*glLinkProgramProc)(GLuint program); 
typedef void (*glUseProgramProc)(GLuint program); 
typedef GLuint (*glCreateProgramProc)(); 
typedef void (*glGetShaderivProc)(GLuint, GLenum, GLint *);
typedef void (*glGetProgramivProc)(GLuint, GLenum, GLint *);


glGenBuffersProc glGenBuffers;
glBindBufferProc glBindBuffer;
glGenVertexArraysProc glGenVertexArrays;
glBindVertexArrayProc glBindVertexArray;
glBufferDataProc glBufferData;
glVertexAttribPointerProc glVertexAttribPointer;
glEnableVertexAttribArrayProc glEnableVertexAttribArray;
glCreateShaderProc glCreateShader;
glShaderSourceProc glShaderSource;
glCompileShaderProc glCompileShader;
glCreateProgramProc glCreateProgram;
glAttachShaderProc glAttachShader;
glLinkProgramProc glLinkProgram;
glUseProgramProc glUseProgram;
glGetShaderivProc glGetShaderiv;
glGetProgramivProc glGetProgramiv;


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


    void* libGL = dlopen("libGL.so", RTLD_LAZY);
    if (!libGL) {
        printf("GRAARGS NO LIBGL\n");
    }

    glGenVertexArrays = (glGenVertexArraysProc) dlsym(libGL, "glGenVertexArrays");

    if (!glGenVertexArrays) {
        printf("GRAARGS NO glGenVertexArrays\n");
    }

    glBindVertexArray = (glBindVertexArrayProc) dlsym(libGL, "glBindVertexArray");

    if (!glBindVertexArray) {
        printf("GRAARGS NO glBindVertexArray\n");
    }

    glGenBuffers = (glGenBuffersProc) dlsym(libGL, "glGenBuffers");

    if (!glGenBuffers) {
        printf("GRAARGS NO glGenBuffers\n");
    }

    glBindBuffer = (glBindBufferProc) dlsym(libGL, "glBindBuffer");

    if (!glBindBuffer) {
        printf("GRAARGS NO glBindBuffer\n");
    }

    glBufferData = (glBufferDataProc) dlsym(libGL, "glBufferData");

    if (!glBufferData) {
        printf("GRAARGS NO glBufferData\n");
    }

    glVertexAttribPointer = (glVertexAttribPointerProc) dlsym(libGL, "glVertexAttribPointer");

    if (!glVertexAttribPointer) {
        printf("GRAARGS NO glVertexAttribPointer\n");
    }

    glEnableVertexAttribArray = (glEnableVertexAttribArrayProc) dlsym(libGL, "glEnableVertexAttribArray");

    if (!glEnableVertexAttribArray) {
        printf("GRAARGS NO glEnableVertexAttribArray\n");
    }

    glCreateShader = (glCreateShaderProc) dlsym(libGL, "glCreateShader");

    if (!glCreateShader) {
        printf("GRAARGS NO glCreateShader\n");
    }

    glShaderSource = (glShaderSourceProc) dlsym(libGL, "glShaderSource");

    if (!glShaderSource) {
        printf("GRAARGS NO glShaderSource\n");
    }

    glCompileShader = (glCompileShaderProc) dlsym(libGL, "glCompileShader");

    if (!glCompileShader) {
        printf("GRAARGS NO glCompileShader\n");
    }

    glCreateProgram = (glCreateProgramProc) dlsym(libGL, "glCreateProgram");

    if (!glCreateProgram) {
        printf("GRAARGS NO glCreateProgram\n");
    }

    glAttachShader = (glAttachShaderProc) dlsym(libGL, "glAttachShader");

    if (!glAttachShader) {
        printf("GRAARGS NO glAttachShader\n");
    }

    glLinkProgram = (glLinkProgramProc) dlsym(libGL, "glLinkProgram");

    if (!glLinkProgram) {
        printf("GRAARGS NO glLinkProgram\n");
    }

    glUseProgram = (glUseProgramProc) dlsym(libGL, "glUseProgram");

    if (!glUseProgram) {
        printf("GRAARGS NO glUseProgram\n");
    }

    glGetShaderiv = (glGetShaderivProc) dlsym(libGL, "glGetShaderiv");

    if (!glGetShaderiv) {
        printf("GRAARGS NO glGetShaderiv\n");
    }

    glGetProgramiv = (glGetProgramivProc) dlsym(libGL, "glGetProgramiv");

    if (!glGetProgramiv) {
        printf("GRAARGS NO glGetProgramiv\n");
    }


    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddress((const GLubyte* )"glXCreateContextAttribsARB");

    if (!glXCreateContextAttribsARB) {
        printf("GRRRNO glXCreateContextAttribsARB!!!!\n");
        exit(1); 
    }

    static int contextAttribs[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 5,
        GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
        GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
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

    glClearColor(0.0, 0.0, 0.0, 1.0);

    GLuint vertexArray = 0;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    GLfloat positionData[] = {
        -0.5, -0.5,
        0.5, -0.5,
        0.0, 0.5
    };

    GLuint positions = 0;
    glGenBuffers(1, &positions);
    glBindBuffer(GL_ARRAY_BUFFER, positions);
    glBufferData(GL_ARRAY_BUFFER, 3 * 2 * sizeof(GLfloat), positionData, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    GLubyte colorData[] = {
        255, 0, 0,
        0, 255, 0,
        0, 0, 255
    };

    GLuint colors = 0;
    glGenBuffers(1, &colors);
    glBindBuffer(GL_ARRAY_BUFFER, colors);
    glBufferData(GL_ARRAY_BUFFER, 3 * 3 * sizeof(GLubyte), colorData, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, NULL);
    glEnableVertexAttribArray(1);

    const char* vsSource =
    "#version 450\n"
    "layout(location=0) in vec2 position;\n"
    "layout(location=1) in vec3 color;\n"
    "out vec3 vColor;\n"
    "void main() {\n"
    "    vColor = color;\n"
    "    gl_Position = vec4(position, 0.0, 1.0);\n"
    "}\n";

    const char* fsSource =
    "#version 450\n"
    "in vec3 vColor;\n"
    "out vec4 fragColor;\n"
    "void main() {\n"
    "    fragColor = vec4(vColor, 1.0);\n"
    "}\n";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsSource, NULL);
    glCompileShader(vs);

    int params = -1;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &params);
    if (params != GL_TRUE) {
        printf("Vertex shader did not compile!\n");
        exit(1);
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsSource, NULL);
    glCompileShader(fs);

    params = -1;
    glGetShaderiv(fs, GL_COMPILE_STATUS, &params);
    if (params != GL_TRUE) {
        printf("Fragment shader did not compile!\n");
        exit(1);
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    params = -1;
    glGetProgramiv(program, GL_LINK_STATUS, &params);

    if (params != GL_TRUE) {
        printf("Program did not link!\n");
        exit(1);
    }

    glUseProgram(program);

    while (1) {
        XNextEvent(disp, &event);

        if (event.type == Expose) {
            XGetWindowAttributes(disp, win, &xWinAtt);
            glViewport(0, 0, xWinAtt.width, xWinAtt.height);
            glClear(GL_COLOR_BUFFER_BIT);
            glDrawArrays(GL_TRIANGLES, 0, 3);
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
