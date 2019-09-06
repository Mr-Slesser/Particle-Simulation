#ifndef GLLOG_H
#define GLLOG_H

static void Log_GL_Parameters()
{
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
    const char *names[] = {
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

    auto str = glGetString(GL_VENDOR);
    GL_LOG_TRACE("Vendor: {}", str);

    str = glGetString(GL_VERSION);
    GL_LOG_TRACE("Version: {}", str);

    str = glGetString(GL_RENDERER);
    GL_LOG_TRACE("Renderer: {}", str);

    GL_LOG_TRACE("--------GL Context Params--------");

    char msg[256];
    for (int i = 0; i < 10; i++)
    {
        int v = 0;
        glGetIntegerv(params[i], &v);
        GL_LOG_INFO("{} {}", names[i], v);
    }

    int v[2];
    v[0] = v[1] = 0;
    glGetIntegerv(params[10], v);
    GL_LOG_INFO("{} {} {}", names[10], v[0], v[1]);
    unsigned char s = 0;
    glGetBooleanv(params[11], &s);
    GL_LOG_INFO("{} {}", names[11], (unsigned int)s);
    GL_LOG_TRACE("---------------------------------");
    std::cout << "\n\n";
}

static const char *GL_type_to_string(GLenum type)
{
    switch (type)
    {
    case GL_BOOL:
        return "bool";
    case GL_INT:
        return "int";
    case GL_FLOAT:
        return "float";
    case GL_FLOAT_VEC2:
        return "vec2";
    case GL_FLOAT_VEC3:
        return "vec3";
    case GL_FLOAT_VEC4:
        return "vec4";
    case GL_FLOAT_MAT2:
        return "mat2";
    case GL_FLOAT_MAT3:
        return "mat3";
    case GL_FLOAT_MAT4:
        return "mat4";
    case GL_SAMPLER_2D:
        return "sampler2D";
    case GL_SAMPLER_3D:
        return "sampler3D";
    case GL_SAMPLER_CUBE:
        return "samplerCube";
    case GL_SAMPLER_2D_SHADOW:
        return "sampler2DShadow";
    default:
        break;
    }
    return "other";
}

static void Print_program_info_log(GLuint program)
{
    int max_length = 2048;
    int actual_length = 0;
    char program_log[2048];
    glGetProgramInfoLog(program, max_length, &actual_length, program_log);
    GL_LOG_TRACE("Program info log for GL index {}:", program)
    GL_LOG_INFO("{}", program_log);
}

static void Print_All(GLuint program)
{
    GL_LOG_TRACE("--------------------Shader program {} info:", program);
    int params = -1;
    glGetProgramiv(program, GL_LINK_STATUS, &params);
    GL_LOG_INFO("GL_LINK_STATUS = {}", params);

    glGetProgramiv(program, GL_ATTACHED_SHADERS, &params);
    GL_LOG_INFO("GL_ATTACHED_SHADERS = {}", params);

    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &params);
    GL_LOG_INFO("GL_ACTIVE_ATTRIBUTES = {}", params);

    for (int i = 0; i < params; i++)
    {
        char name[64];
        int max_length = 64;
        int actual_length = 0;
        int size = 0;
        GLenum type;
        glGetActiveAttrib(program, i, max_length, &actual_length, &size, &type, name);

        if (size > 1)
        {
            for (int j = 0; j < size; j++)
            {
                char long_name[64];
                GL_LOG_INFO("{}[{}]", name, j);
                int location = glGetAttribLocation(program, long_name);
                GL_LOG_INFO("  {}) type:{} name:{} location:{}", i, GL_type_to_string(type), long_name, location);
            }
        }
        else
        {
            int location = glGetAttribLocation(program, name);
            GL_LOG_INFO("  {}) type:{} name:{} location:{}", i, GL_type_to_string(type), name, location);
        }
    }

    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &params);
    for (int i = 0; i < params; i++)
    {
        char name[64];
        int max_length = 64;
        int actual_length = 0;
        int size = 0;
        GLenum type;
        glGetActiveUniform(program, i, max_length, &actual_length, &size, &type, name);
        if (size > 1)
        {
            for (int j = 0; j < size; j++)
            {
                char long_name[64];
                GL_LOG_INFO("{}[{}]", name, j);
                int location = glGetUniformLocation(program, long_name);
                GL_LOG_INFO("  {}) type:{} name:{} location:{}", i, GL_type_to_string(type), long_name, location);
            }
        }
        else
        {
            int location = glGetUniformLocation(program, name);
            GL_LOG_INFO("  {}) type:{} name:{} location:{}", i, GL_type_to_string(type), name, location);
        }
    }

    Print_program_info_log(program);
    std::cout << "\n\n";
}

#endif /* GLLOG_H */
