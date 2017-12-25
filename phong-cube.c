#include <stdio.h>
#include <stdlib.h>
#include "opengl.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static GLuint modelLocation;
static GLuint viewProjLocation;
static GLuint eyePositionLocation;
static GLuint lightPositionLocation;
static GLuint texLocation;
static int numVertices;

void RendererInit() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    float positionData[] = {
        //front
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,

        //right
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,

        //back
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,

        //left
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,

        //top
        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,

        //bottom
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f
    };

    float uvData[] = {
        //front
        0, 0,
        1, 0,
        0, 1,
        0, 1,
        1, 0,
        1, 1,

        //right
        0, 0,
        1, 0,
        0, 1,
        0, 1,
        1, 0,
        1, 1,

        //back
        0, 0,
        1, 0,
        0, 1,
        0, 1,
        1, 0,
        1, 1,

        //left
        0, 0,
        1, 0,
        0, 1,
        0, 1,
        1, 0,
        1, 1,

        //top
        0, 0,
        1, 0,
        0, 1,
        0, 1,
        1, 0,
        1, 1,

        //bottom
        0, 0,
        1, 0,
        0, 1,
        0, 1,
        1, 0,
        1, 1
    };

    float normalData[] = {
        // front
        0, 0, 1, 
        0, 0, 1, 
        0, 0, 1, 
        0, 0, 1, 
        0, 0, 1, 
        0, 0, 1,

        // right
        1, 0, 0, 
        1, 0, 0, 
        1, 0, 0, 
        1, 0, 0, 
        1, 0, 0, 
        1, 0, 0,

        // back 
        0, 0, -1, 
        0, 0, -1, 
        0, 0, -1, 
        0, 0, -1, 
        0, 0, -1, 
        0, 0, -1, 

        // left
        -1, 0, 0, 
        -1, 0, 0, 
        -1, 0, 0, 
        -1, 0, 0, 
        -1, 0, 0, 
        -1, 0, 0,

        // top 
        0, 1, 0, 
        0, 1, 0, 
        0, 1, 0, 
        0, 1, 0, 
        0, 1, 0, 
        0, 1, 0,

        // bottom
        0, -1, 0, 
        0, -1, 0, 
        0, -1, 0, 
        0, -1, 0, 
        0, -1, 0, 
        0, -1, 0
    };

    numVertices = (sizeof(positionData) / sizeof(float)) / 3;

    GLuint vertexArray = 0;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    GLuint positions = 0;
    glGenBuffers(1, &positions);
    glBindBuffer(GL_ARRAY_BUFFER, positions);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    GLuint uvs = 0;
    glGenBuffers(1, &uvs);
    glBindBuffer(GL_ARRAY_BUFFER, uvs);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvData), uvData, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 0, NULL);
    glEnableVertexAttribArray(1);

    GLuint normals = 0;
    glGenBuffers(1, &normals);
    glBindBuffer(GL_ARRAY_BUFFER, normals);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normalData), normalData, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, 0, NULL);
    glEnableVertexAttribArray(2);

    const char* vsSource =
    "#version 450\n"
    "layout(location=0) in vec4 position;\n"
    "layout(location=1) in vec2 uv;\n"
    "layout(location=2) in vec4 normal;\n"
    
    "uniform mat4 uViewProj;\n"
    "uniform mat4 uModel;\n"
    
    "out vec3 vPosition;\n"
    "out vec2 vUV;\n"
    "out vec3 vNormal;\n"

    "void main() {\n"
        "vec4 worldPosition = uModel * position;\n"
        "vPosition = worldPosition.xyz;\n"
        "vUV = vec2(uv.x, 1.0 - uv.y);\n"
        "vNormal = (uModel * normal).xyz;\n"
        "gl_Position = uViewProj * worldPosition;\n"
    "};\n";

    const char* fsSource =
    "#version 450\n"

    "uniform vec4 uEyePosition;\n"
    "uniform vec4 uLightPosition;\n"
    "uniform sampler2D tex;\n"
    
    "in vec3 vPosition;\n"
    "in vec2 vUV;\n"
    "in vec3 vNormal;\n"

    "out vec4 fragColor;\n"
    "void main() {\n"
        "vec3 color = texture(tex, vUV).rgb;\n"

        "vec3 normal = normalize(vNormal);\n"
        "vec3 eyeVec = normalize(uEyePosition.xyz - vPosition);\n"
        "vec3 incidentVec = normalize(vPosition - uLightPosition.xyz);\n"
        "vec3 lightVec = -incidentVec;\n"
        "float diffuse = max(dot(lightVec, normal), 0.0);\n"
        "float highlight = pow(max(dot(eyeVec, reflect(incidentVec, normal)), 0.0), 100.0);\n"
        "float ambient = 0.1;\n"
        "fragColor = vec4(color * (diffuse + highlight + ambient), 1.0);\n"
        "fragColor.rgb = color;\n"
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

    modelLocation = glGetUniformLocation(program, "uModel");
    viewProjLocation = glGetUniformLocation(program, "uViewProj");
    eyePositionLocation = glGetUniformLocation(program, "uEyePosition");
    lightPositionLocation = glGetUniformLocation(program, "uLightPosition");
    texLocation = glGetUniformLocation(program, "tex");

    int img_width, img_height, bytes_per_pixel;
    unsigned char* image = stbi_load("opengl-logo.png", &img_width, &img_height, &bytes_per_pixel, 4);

    if (!image) {
        printf("No image!\n");
        exit(1);
    }

    GLuint tex = 0;
    glGenTextures(1, &tex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glUniform1i(texLocation, 0);

    float eyePosition[] = { 1.0f, 1.0f, 1.0f };
    float lookPosition[] = { 0.0f, 0.0f, 0.0f };
    float upVector[] = { 0.0f, 1.0f, 0.0f };

    float lightPosition[] = {1.0f, 1.0f, 0.5f};

    float viewProjMatrix[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    float modelMatrix[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    glUniform3fv(eyePositionLocation, 1, eyePosition);
    glUniform3fv(lightPositionLocation, 1, lightPosition);
    glUniformMatrix4fv(viewProjLocation, 1, GL_FALSE, viewProjMatrix);
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, modelMatrix);
}

void RendererMain(double time) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

void RendererInput(RendererEvent event) {
    if (event.type == RENDERER_KEY_PRESS) {
        if (event.key == 'q') {
            StopRenderLoop();
        }
    }
}
