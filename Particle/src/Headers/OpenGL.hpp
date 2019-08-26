#ifndef OPENGL_HPP
#define OPENGL_HPP

#define GLCheck(x)    \
    glClearErrors_(); \
    x;                \
    glCheckError_(__FILE__, __LINE__);

#ifdef NDEBUG
#define GLCheck(x) x;
#endif

static void glClearErrors_()
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
    }
}

static GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
        case GL_INVALID_ENUM:
            error = "INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            error = "INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            error = "INVALID_OPERATION";
            break;
        case GL_OUT_OF_MEMORY:
            error = "OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            error = "INVALID_FRAMEBUFFER_OPERATION";
            break;
        }
        GL_LOG_ERROR("{} | {} ({})", error, file, line);
    }
    return errorCode;
}

#endif /* OPENGL_HPP */
