#ifndef RANDOM_TEXTURE_HPP
#define	RANDOM_TEXTURE_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <stdlib.h>
#include <cstring>

class RandomTexture
{
public:
    RandomTexture()
    {
        m_textureObj = 0;    
    }

    ~RandomTexture()
    {
        if (m_textureObj != 0) {
            glDeleteTextures(1, &m_textureObj);
        }
    }
    
    bool InitRandomTexture(unsigned int Size)
    {
        float pRandomData[Size][3];
        memset(pRandomData, 0, sizeof(pRandomData));
        
        for (unsigned int i = 0 ; i < Size ; i++) {
            pRandomData[i][0] = (rand() % 100) / 100;
            pRandomData[i][1] = (rand() % 100) / 100;
            pRandomData[i][2] = (rand() % 100) / 100;
        }
            
        glGenTextures(1, &m_textureObj);
        glBindTexture(GL_TEXTURE_1D, m_textureObj);
        glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, Size, 0, GL_RGB, GL_FLOAT, pRandomData);
        glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);    
        
        //delete [] pRandomData;
        
        return true;
    }

    void Bind(GLenum TextureUnit)
    {
        glActiveTexture(TextureUnit);
        glBindTexture(GL_TEXTURE_1D, m_textureObj);
    }

private:
    GLuint m_textureObj;
};

#endif	/* RANDOM_TEXTURE_HPP */