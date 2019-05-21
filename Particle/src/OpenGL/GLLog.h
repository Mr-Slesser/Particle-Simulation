#ifndef GLLOG_H
#define GLLOG_H

#include <time.h>
#include <stdarg.h>
#include <cstdio>

#define GL_LOG_FILE "gl.log"

// TODO: Make an incrementing log file.

// Open an print data and time at the top. 
static bool restart_gl_log() {
    FILE* file = fopen(GL_LOG_FILE, "w");
    if(!file) {
        fprintf(stderr,
        "ERROR: could not open GL_LOG_FILE log file %s for writing\n",
        GL_LOG_FILE);
        return false;
    }
    time_t now = time(NULL);
    char* date = ctime(&now);
    fprintf(file, "GL_LOG_FILE log. local time %s\n", date);
    fclose(file);
    return true;
}

// Main printer...
static bool gl_log(const char* message, ...) {
    va_list argptr;
    FILE* file = fopen(GL_LOG_FILE, "a");
    if(!file) {
        fprintf(
        stderr,
        "ERROR: could not open GL_LOG_FILE %s file for appending\n",
        GL_LOG_FILE
        );
        return false;
    }
    va_start(argptr, message);
    vfprintf(file, message, argptr);
    va_end(argptr);
    fclose(file);
    return true;
}

// For errors...
static bool gl_log_err(const char* message, ...) {
    va_list argptr;
    FILE* file = fopen(GL_LOG_FILE, "a");
    if(!file) {
        fprintf(stderr,
        "ERROR: could not open GL_LOG_FILE %s file for appending\n",
        GL_LOG_FILE);
        return false;
    }
    va_start(argptr, message);
    vfprintf(file, message, argptr);
    va_end(argptr);
    va_start(argptr, message);
    vfprintf(stderr, message, argptr);
    va_end(argptr);
    fclose(file);
    return true;
}

// TODO: More of these..?
static void log_gl_params() {
    GLenum params[] = {
        GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
        GL_MAX_CUBE_MAP_TEXTURE_SIZE,
        GL_MAX_DRAW_BUFFERS,
        GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
        GL_MAX_TEXTURE_IMAGE_UNITS,
        GL_MAX_TEXTURE_SIZE,
        GL_MAX_VARYING_FLOATS,
        GL_MAX_VERTEX_ATTRIBS,
        GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
        GL_MAX_VERTEX_UNIFORM_COMPONENTS,
        GL_MAX_VIEWPORT_DIMS,
        GL_STEREO,
    };
    const char* names[] = {
        "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
        "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
        "GL_MAX_DRAW_BUFFERS",
        "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
        "GL_MAX_TEXTURE_IMAGE_UNITS",
        "GL_MAX_TEXTURE_SIZE",
        "GL_MAX_VARYING_FLOATS",
        "GL_MAX_VERTEX_ATTRIBS",
        "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
        "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
        "GL_MAX_VIEWPORT_DIMS",
        "GL_STEREO",
    };
    gl_log("\nGL Context Params:\n");
    char msg[256];
    // integers - only works if the order is 0-10 integer return types
    for (int i = 0; i < 10; i++) {
        int v = 0;
        glGetIntegerv(params[i], &v);
        gl_log("%s %i\n", names[i], v);
    }
    // others
    int v[2];
    v[0] = v[1] = 0;
    glGetIntegerv(params[10], v);
    gl_log("%s %i %i\n", names[10], v[0], v[1]);
    unsigned char s = 0;
    glGetBooleanv(params[11], &s);
    gl_log("%s %u\n", names[11], (unsigned int)s);
    gl_log("-----------------------------\n");
}

static const char* GL_type_to_string(GLenum type) {
    switch(type) {
        case GL_BOOL: return "bool";
        case GL_INT: return "int";
        case GL_FLOAT: return "float";
        case GL_FLOAT_VEC2: return "vec2";
        case GL_FLOAT_VEC3: return "vec3";
        case GL_FLOAT_VEC4: return "vec4";
        case GL_FLOAT_MAT2: return "mat2";
        case GL_FLOAT_MAT3: return "mat3";
        case GL_FLOAT_MAT4: return "mat4";
        case GL_SAMPLER_2D: return "sampler2D";
        case GL_SAMPLER_3D: return "sampler3D";
        case GL_SAMPLER_CUBE: return "samplerCube";
        case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
        default: break;
    }
    return "other";
}

static void _print_program_info_log(GLuint program, FILE* file) {
    int max_length = 2048;
    int actual_length = 0;
    char program_log[2048];
    glGetProgramInfoLog(program, max_length, &actual_length, program_log);
    fprintf(file, "program info log for GL index %u:\n%s", program, program_log);
    fclose(file);
}

static void print_all(GLuint program) {
    FILE* file = fopen(GL_LOG_FILE, "a");
    if(!file) {
        fprintf(stderr,
        "ERROR: could not open GL_LOG_FILE log file %s for appending\n",
        GL_LOG_FILE);
    }
    fprintf(file, "\n--------------------\nShader program %i info:\n", program);
    int params = -1;
    glGetProgramiv(program, GL_LINK_STATUS, &params);
    fprintf(file, "GL_LINK_STATUS = %i\n", params);
    
    glGetProgramiv(program, GL_ATTACHED_SHADERS, &params);
    fprintf(file, "GL_ATTACHED_SHADERS = %i\n", params);
    
    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &params);
    fprintf(file, "GL_ACTIVE_ATTRIBUTES = %i\n", params);
    for (int i = 0; i < params; i++)
    {
        char name[64];
        int max_length = 64;
        int actual_length = 0;
        int size = 0;
        GLenum type;
        glGetActiveAttrib (program, i, max_length, &actual_length, &size, &type, name);

        if (size > 1)
        {
            for(int j = 0; j < size; j++)
            {
                char long_name[64];
                fprintf(file, long_name, "%s[%i]", name, j);
                int location = glGetAttribLocation(program, long_name);
                fprintf(file, "  %i) type:%s name:%s location:%i\n", i, GL_type_to_string(type), long_name, location);
            }
        }
        else
        {
            int location = glGetAttribLocation(program, name);
            fprintf(file, "  %i) type:%s name:%s location:%i\n", i, GL_type_to_string(type), name, location);
        }
    }
    
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &params);
    fprintf(file, "GL_ACTIVE_UNIFORMS = %i\n", params);
    for(int i = 0; i < params; i++) {
        char name[64];
        int max_length = 64;
        int actual_length = 0;
        int size = 0;
        GLenum type;
        glGetActiveUniform(program, i, max_length, &actual_length, &size, &type, name);
        if(size > 1) {
        for(int j = 0; j < size; j++) {
            char long_name[64];
            fprintf(file, long_name, "%s[%i]", name, j);
            int location = glGetUniformLocation(program, long_name);
            fprintf(file, "  %i) type:%s name:%s location:%i\n", i, GL_type_to_string(type), long_name, location);
        }
        } else {
            int location = glGetUniformLocation(program, name);
            fprintf(file, "  %i) type:%s name:%s location:%i\n", i, GL_type_to_string(type), name, location);
        }
    }
    
    _print_program_info_log(program, file);
    fclose(file);
}

#endif /* GLLOG_H */
