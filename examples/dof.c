///////////////////////////////////////////////////////////////////////////////////
// The MIT License (MIT)
//
// Copyright (c) 2017 Tarek Sherif
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
///////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// DOF algorithm from http://www.nutty.ca/?page_id=352&link=depth_of_field
/////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <math.h>
#include "../src/xogl.h"
#include "utils/utils.h"
#include "utils/math.h"

#define XK_LATIN1
#include <X11/keysymdef.h>

#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image.h"

#define WINDOW_WIDTH 2000
#define WINDOW_HEIGHT 2000


#define PI 3.14159

#define ABS(a) ((a) > 0 ? (a) : (-a))
#define NEAR 0.1
#define FAR 10.0
#define FOCAL_LENGTH 1.0
#define FOCUS_DISTANCE 2.0
#define MAGNIFICATION (FOCAL_LENGTH / ABS(FOCUS_DISTANCE - FOCAL_LENGTH))
#define FSTOP 2.8
#define BLUR_COEFFICIENT  (FOCAL_LENGTH * MAGNIFICATION / FSTOP)

#define NUM_ROWS 5
#define BOXES_PER_ROW 20
#define NUM_BOXES (BOXES_PER_ROW * NUM_ROWS)

typedef struct {
    vec3 scale;
    vec3 rotate;
    vec3 translate;
    float *modelMatrix;
} Box;

int main(int argc, char const *argv[]) {
    Display* disp;
    Window win;
    XEvent event;
    XWindowAttributes xWinAtt;

    int numVertices;

    // X Windows stuff
    disp = XOpenDisplay(NULL);

    if (disp == NULL) {
        printf("Unable to connect to X Server\n");
        return 1;
    }

    win = XCreateSimpleWindow(disp, DefaultRootWindow(disp), 20, 20, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 0);
    
    XSelectInput(disp, win, ExposureMask | KeyPressMask | ButtonPressMask);
    XStoreName(disp, win, "XOGL Depth of Field Example");
    XMapWindow(disp, win);

    if (xogl_init(disp, win, 4, 5)) {
        fprintf(stderr, "Unable initialize OpenGL!\n");
        return 1;
    }

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_CULL_FACE);

    Box boxes[NUM_BOXES];
    float modelMatrixData[NUM_BOXES * 16];

    int boxI = 0;
    for (int j = 0; j < NUM_ROWS; ++j) {
        int rowOffset = (j - NUM_ROWS / 2);
        for (int i = 0; i < BOXES_PER_ROW; ++i) {
            math_setVec3(boxes[boxI].scale, 0.9, 0.9, 0.9);
            math_setVec3(boxes[boxI].rotate, -boxI / PI, 0, boxI / PI);
            math_setVec3(boxes[boxI].translate, -i + 2 - rowOffset, 0, -i + 2 + rowOffset);

            // Points directly into modelMatrixData array
            boxes[boxI].modelMatrix = modelMatrixData + (boxI * 16);
            ++boxI;
        }
    }



    numVertices = (sizeof(UNIT_CUBE.positions) / sizeof(float)) / 3;

    GLuint boxArray = 0;
    glGenVertexArrays(1, &boxArray);
    glBindVertexArray(boxArray);

    GLuint positions = 0;
    glGenBuffers(1, &positions);
    glBindBuffer(GL_ARRAY_BUFFER, positions);
    glBufferData(GL_ARRAY_BUFFER, sizeof(UNIT_CUBE.positions), UNIT_CUBE.positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    GLuint uvs = 0;
    glGenBuffers(1, &uvs);
    glBindBuffer(GL_ARRAY_BUFFER, uvs);
    glBufferData(GL_ARRAY_BUFFER, sizeof(UNIT_CUBE.uvs), UNIT_CUBE.uvs, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    GLuint normals = 0;
    glGenBuffers(1, &normals);
    glBindBuffer(GL_ARRAY_BUFFER, normals);
    glBufferData(GL_ARRAY_BUFFER, sizeof(UNIT_CUBE.normals), UNIT_CUBE.normals, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(2);

    GLuint matrices = 0;
    glGenBuffers(1, &matrices);
    glBindBuffer(GL_ARRAY_BUFFER, matrices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(modelMatrixData), modelMatrixData, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 64, (const GLvoid *) 0);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 64, (const GLvoid *) 16);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 64, (const GLvoid *) 32);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 64, (const GLvoid *) 48);

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);
    glEnableVertexAttribArray(6);

    GLuint quadVertexArray = 0;
    glGenVertexArrays(1, &quadVertexArray);
    glBindVertexArray(quadVertexArray);

    GLuint quadPositions = 0;
    glGenBuffers(1, &quadPositions);
    glBindBuffer(GL_ARRAY_BUFFER, quadPositions);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QUAD_POSITIONS), QUAD_POSITIONS, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    ////////////////////////////////
    //  SET UP FRAMEBUFFERS
    ////////////////////////////////

    GLuint boxBuffer = 0;
    glGenFramebuffers(1, &boxBuffer);

    GLuint hblurBuffer = 0;
    glGenFramebuffers(1, &hblurBuffer);

    glBindFramebuffer(GL_FRAMEBUFFER, boxBuffer);
    glActiveTexture(GL_TEXTURE0);

    GLuint colorTarget = 0;
    glGenTextures(1, &colorTarget);
    glBindTexture(GL_TEXTURE_2D, colorTarget);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, WINDOW_WIDTH, WINDOW_HEIGHT);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTarget, 0);

    GLuint depthTarget = 0;
    glGenTextures(1, &depthTarget);
    glBindTexture(GL_TEXTURE_2D, depthTarget);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT16, WINDOW_WIDTH, WINDOW_HEIGHT);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTarget, 0);


    glBindFramebuffer(GL_FRAMEBUFFER, hblurBuffer);

    GLuint hblurTarget = 0;
    glGenTextures(1, &hblurTarget);
    glBindTexture(GL_TEXTURE_2D, hblurTarget);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, WINDOW_WIDTH, WINDOW_HEIGHT);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, hblurTarget, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    const char* boxVsSource =
    "#version 450\n"

    "layout(std140, column_major) uniform;\n"
    
    "layout(location=0) in vec4 position;\n"
    "layout(location=1) in vec2 uv;\n"
    "layout(location=2) in vec3 normal;\n"
    "layout(location=3) in mat4 modelMatrix;\n"
    
    "uniform SceneUniforms {\n"
        "mat4 uViewProj;\n"
        "vec4 uEyePosition;\n"
        "vec4 uLightPosition;\n"
    "};\n"       
    
    "out vec3 vPosition;\n"
    "out vec2 vUV;\n"
    "out vec3 vNormal;\n"
    "void main() {\n"
        "vec4 worldPosition = modelMatrix * position;\n"
        "vPosition = worldPosition.xyz;\n"
        "vUV = uv;\n"
        "vNormal = (modelMatrix * vec4(normal, 0.0)).xyz;\n"
        "gl_Position = uViewProj * worldPosition;\n"
    "}\n";

    const char* boxFsSource =
    "#version 450\n"
    "precision highp float;\n"

    "layout(std140, column_major) uniform;\n"

    "uniform SceneUniforms {\n"
        "mat4 uViewProj;\n"
        "vec4 uEyePosition;\n"
        "vec4 uLightPosition;\n"
    "};\n"

    "uniform sampler2D uTexture;\n"
    
    "in vec3 vPosition;\n"
    "in vec2 vUV;\n"
    "in vec3 vNormal;\n"

    "out vec4 fragColor;\n"
    "void main() {\n"
        "vec3 color = texture(uTexture, vUV).rgb;\n"

        "vec3 normal = normalize(vNormal);\n"
        "vec3 eyeVec = normalize(uEyePosition.xyz - vPosition);\n"
        "vec3 incidentVec = normalize(vPosition - uLightPosition.xyz);\n"
        "vec3 lightVec = -incidentVec;\n"
        "float diffuse = max(dot(lightVec, normal), 0.0);\n"
        "float highlight = pow(max(dot(eyeVec, reflect(incidentVec, normal)), 0.0), 100.0);\n"
        "float ambient = 0.1;\n"
        "fragColor = vec4(color * (diffuse + highlight + ambient), 1.0);\n"
    "}\n";

    const char* quadVsSource = 
    "#version 450\n"
    "layout(location=0) in vec4 aPosition;\n"
    "void main() {\n"
        "gl_Position = aPosition;\n"
    "}";

    const char* blurFsSource = 
    "#version 450\n"
    "precision highp float;\n"
    "layout(std140, column_major) uniform;\n"
    "#define MAX_BLUR 20.\n"
    "uniform DOFUniforms {\n"
        "vec2  uDepthRange;\n" 
        "vec2 uResolution;\n"
        "float uFocusDistance;\n"
        "float uBlurCoefficient;\n"
        "float uPPM;\n"
   "};\n"
    
    "uniform vec2 uTexelOffset;\n"
    "uniform sampler2D uColor;\n"
    "uniform sampler2D uDepth;\n"
    
    "out vec4 fragColor;\n"
    "void main() {\n"
        "ivec2 fragCoord = ivec2(gl_FragCoord.xy);\n"
        "ivec2 resolution = ivec2(uResolution) - 1;\n"
        // Convert to linear depth
        "float ndc = 2.0 * texelFetch(uDepth, fragCoord, 0).r - 1.0;\n"
        "float depth = -(2.0 * uDepthRange.y * uDepthRange.x) / (ndc * (uDepthRange.y - uDepthRange.x) - uDepthRange.y - uDepthRange.x);\n"
        "float deltaDepth = abs(uFocusDistance - depth);\n"
        
        // Blur more quickly in the foreground.
        "float xdd = depth < uFocusDistance ? abs(uFocusDistance - deltaDepth) : abs(uFocusDistance + deltaDepth);\n"
        "float blurRadius = min(floor(uBlurCoefficient * (deltaDepth / xdd) * uPPM), MAX_BLUR);\n"
        
        "vec4 color = vec4(0.0);\n"
        "if (blurRadius > 1.0) {\n"
            "float halfBlur = blurRadius * 0.5;\n"
            "float count = 0.0;\n"
            "for (float i = 0.0; i <= MAX_BLUR; ++i) {\n"
                "if (i > blurRadius) {\n"
                    "break;\n"
                "}\n"
                // texelFetch outside texture gives vec4(0.0) (undefined in ES 3)
                "ivec2 sampleCoord = clamp(fragCoord + ivec2(((i - halfBlur) * uTexelOffset)), ivec2(0), resolution);\n"
                "color += texelFetch(uColor, sampleCoord, 0);\n"
                "++count;\n"
            "}\n"
            "color /= count;\n"
        "} else {\n"
            "color = texelFetch(uColor, fragCoord, 0);\n"
        "}\n"
        "fragColor = color;\n"
    "}\n";

    GLuint boxVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(boxVertexShader, 1, &boxVsSource, NULL);
    glCompileShader(boxVertexShader);

    GLint params = -1;
    glGetShaderiv(boxVertexShader, GL_COMPILE_STATUS, &params);
    if (params != GL_TRUE) {
        char buffer[1024];
        glGetShaderInfoLog(boxVertexShader, 1024, NULL, buffer);
        fprintf(stderr, "Box VS: %s\n", buffer);
        return 1;
    }

    GLuint boxFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(boxFragmentShader, 1, &boxFsSource, NULL);
    glCompileShader(boxFragmentShader);

    params = -1;
    glGetShaderiv(boxFragmentShader, GL_COMPILE_STATUS, &params);
    if (params != GL_TRUE) {
        char buffer[1024];
        glGetShaderInfoLog(boxFragmentShader, 1024, NULL, buffer);
        fprintf(stderr, "Box FS: %s\n", buffer);
        return 1;
    }

    GLuint boxProgram = glCreateProgram();
    glAttachShader(boxProgram, boxVertexShader);
    glAttachShader(boxProgram, boxFragmentShader);
    glLinkProgram(boxProgram);

    params = -1;
    glGetProgramiv(boxProgram, GL_LINK_STATUS, &params);
    if (params != GL_TRUE) {
        char buffer[1024];
        glGetProgramInfoLog(boxProgram, 1024, NULL, buffer);
        fprintf(stderr, "Box program: %s\n", buffer);
        return 1;
    }

    GLuint blurVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(blurVertexShader, 1, &quadVsSource, NULL);
    glCompileShader(blurVertexShader);

    params = -1;
    glGetShaderiv(blurVertexShader, GL_COMPILE_STATUS, &params);
    if (params != GL_TRUE) {
        char buffer[1024];
        glGetShaderInfoLog(blurVertexShader, 1024, NULL, buffer);
        fprintf(stderr, "Blus VS: %s\n", buffer);
        return 1;
    }

    GLuint blurFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(blurFragmentShader, 1, &blurFsSource, NULL);
    glCompileShader(blurFragmentShader);

    params = -1;
    glGetShaderiv(blurFragmentShader, GL_COMPILE_STATUS, &params);
    if (params != GL_TRUE) {
        char buffer[1024];
        glGetShaderInfoLog(blurFragmentShader, 1024, NULL, buffer);
        fprintf(stderr, "Blur FS: %s\n", buffer);
        return 1;
    }

    GLuint blurProgram = glCreateProgram();
    glAttachShader(blurProgram, blurVertexShader);
    glAttachShader(blurProgram, blurFragmentShader);
    glLinkProgram(blurProgram);

    params = -1;
    glGetProgramiv(blurProgram, GL_LINK_STATUS, &params);
    if (params != GL_TRUE) {
        char buffer[1024];
        glGetProgramInfoLog(blurProgram, 1024, NULL, buffer);
        fprintf(stderr, "Blur program: s%s\n", buffer);
        return 1;
    }

    //////////////////////
    // UNIFORMS
    //////////////////////

    GLuint sceneUniformsLocation = glGetUniformBlockIndex(boxProgram, "SceneUniforms");
    glUniformBlockBinding(boxProgram, sceneUniformsLocation, 0);

    GLuint texLocation = glGetUniformLocation(boxProgram, "uTexture");

    GLuint dofUniformsLocation = glGetUniformBlockIndex(blurProgram, "DOFUniforms");
    glUniformBlockBinding(blurProgram, dofUniformsLocation, 1);

    GLuint texelOffsetLocation = glGetUniformLocation(blurProgram, "uTexelOffset");

    GLuint textureLocation = glGetUniformLocation(blurProgram, "uColor");
    GLuint depthLocation = glGetUniformLocation(blurProgram, "uDepth");

    struct {
        mat4 viewProjMatrix;
        float eyePosition[4];
        float lightPosition[4];
    } sceneUniformData = {{}, { 1.0f, 1.5f, 1.0f }, { 1.0f, 1.0f, 0.5f }};
    
    vec3 lookPosition = { 0.0f, 0.0f, 0.0f };
    vec3 upVector = { 0.0f, 1.0f, 0.0f };

    mat4 projMatrix;
    mat4 viewMatrix;
    
    math_perspectiveMat4(projMatrix, PI / 2.0f, WINDOW_WIDTH / WINDOW_HEIGHT, NEAR, FAR);
    math_lookAtMat4(viewMatrix, sceneUniformData.eyePosition, lookPosition, upVector);
    math_multiplyMat4(sceneUniformData.viewProjMatrix, projMatrix, viewMatrix);

    float hTexelOffset[2] = { 1.0, 0.0 };
    float vTexelOffset[2] = { 0.0, 1.0 };

    GLuint sceneUniformBuffer = 0;
    glGenBuffers(1, &sceneUniformBuffer);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, sceneUniformBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(sceneUniformData), &sceneUniformData, GL_STATIC_DRAW);

    struct {
        float depthRange[2]; 
        float resolution[2]; 
        float focusDistance;  
        float blurCoefficient;  
        float ppm;
    } dofUniformData = {{ NEAR, FAR }, { WINDOW_WIDTH, WINDOW_HEIGHT }, FOCUS_DISTANCE, BLUR_COEFFICIENT };

    dofUniformData.ppm = sqrt(WINDOW_WIDTH * WINDOW_WIDTH + WINDOW_HEIGHT * WINDOW_HEIGHT) / 35;

    GLuint dofUniformBuffer = 0;
    glGenBuffers(1, &dofUniformBuffer);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, dofUniformBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(dofUniformData), &dofUniformData, GL_STATIC_DRAW);

    int img_width, img_height, bytes_per_pixel;
    unsigned char* image = stbi_load("examples/img/opengl-logo.png", &img_width, &img_height, &bytes_per_pixel, 4);

    if (!image) {
        stbi_load("img/opengl-logo.png", &img_width, &img_height, &bytes_per_pixel, 4);
    }

    if (!image) {
        printf("No image!\n");
        exit(1);
    }

    GLuint tex = 0;
    glGenTextures(1, &tex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    int levels = floor(log2(fmax(img_width, img_height))) + 1;
    glTexStorage2D(GL_TEXTURE_2D, levels, GL_RGBA8, img_width, img_height);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, img_width, img_height, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, colorTarget);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, depthTarget);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, hblurTarget);

    glUseProgram(boxProgram);
    glUniform1i(texLocation, 0);

    glUseProgram(blurProgram);
    glUniform1i(depthLocation, 2);

    free(image);

    float frameTime = 1000.0 / 60.0; 
    double startTime, endTime;

    mat4 translation;
    mat4 rotationX;
    mat4 rotationY;
    mat4 rotationZ;
    mat4 scale;

    // Animation loop
    while (1) {
        startTime = utils_getTime();    

        if (XCheckWindowEvent(disp, win, ExposureMask | KeyPressMask, &event) == True) {

            if (event.type == Expose) {
                XGetWindowAttributes(disp, win, &xWinAtt);
                glViewport(0, 0, xWinAtt.width, xWinAtt.height);
            }

            if (event.type == KeyPress) {
                KeySym key = XLookupKeysym(&event.xkey, 0);
                
                if (key == XK_q) {
                    break;
                }
            }
        }

        ////////////////////
        // DRAW BOXES
        ////////////////////

        glEnable(GL_DEPTH_TEST);
        glBindFramebuffer(GL_FRAMEBUFFER, boxBuffer);
        glUseProgram(boxProgram);
        glBindVertexArray(boxArray);

        for (int i = 0; i < NUM_BOXES; ++i) {
            boxes[i].rotate[0] += 0.01;
            boxes[i].rotate[1] += 0.02;

            math_translationMat4(translation, boxes[i].translate[0], boxes[i].translate[1], boxes[i].translate[2]);
            math_rotationXMat4(rotationX, boxes[i].rotate[0]);
            math_rotationYMat4(rotationY, boxes[i].rotate[1]);
            math_rotationZMat4(rotationZ, boxes[i].rotate[2]);
            math_scalingMat4(scale, boxes[i].scale[0], boxes[i].scale[1], boxes[i].scale[2]);

            float* xform = boxes[i].modelMatrix;

            math_multiplyMat4(xform, rotationX, scale);
            math_multiplyMat4(xform, rotationY, xform);
            math_multiplyMat4(xform, rotationZ, xform);
            math_multiplyMat4(xform, translation, xform);
        }

        glBindBuffer(GL_ARRAY_BUFFER, matrices);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(modelMatrixData), modelMatrixData);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArraysInstanced(GL_TRIANGLES, 0, numVertices, NUM_BOXES);

        ////////////////////
        // HORIZONTAL BLUR
        ////////////////////

        glDisable(GL_DEPTH_TEST);
        glBindFramebuffer(GL_FRAMEBUFFER, hblurBuffer);
        // glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glUseProgram(blurProgram);
        glBindVertexArray(quadVertexArray);

        glUniform1i(textureLocation, 1);
        glUniform2fv(texelOffsetLocation, 1, hTexelOffset);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        ////////////////////
        // VERTICAL BLUR
        ////////////////////

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glUseProgram(blurProgram);
        glBindVertexArray(quadVertexArray);

        glUniform1i(textureLocation, 3);
        glUniform2fv(texelOffsetLocation, 1, vTexelOffset);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        xogl_swapBuffers();

        endTime = utils_getTime();
        double elapsed = endTime - startTime;
        if (elapsed < frameTime) {
            utils_milisleep(frameTime - elapsed);
            endTime = utils_getTime();
        }
    };

    // Teardown
    xogl_destroy();
    XDestroyWindow(disp, win);
    XCloseDisplay(disp);
    printf("Done!\n");
}
