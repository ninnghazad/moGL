////////////////////////////////////////////////////////////////////////////////
/// Modern OpenGL Wrapper
///
/// Copyright (c) 2014 Thibault Schueller
/// This file is distributed under the MIT License
///
/// @file textureobject.hpp
/// @author Thibault Schueller <ryp.sqrt@gmail.com>
////////////////////////////////////////////////////////////////////////////////

#ifndef MOGL_TEXTUREOBJECT_INCLUDED
#define MOGL_TEXTUREOBJECT_INCLUDED

namespace mogl
{
    class TextureObject
    {
    public:
        TextureObject(GLenum target);
        ~TextureObject();

        TextureObject(const TextureObject& other) = delete;
        TextureObject& operator=(const TextureObject& other) = delete;

    public:
        void    bind();
        void    setImage2D(GLint level, GLint internalFormat, GLsizei width,
                           GLsizei height, GLint border, GLenum format,
                           GLenum type, const GLvoid* data);
        void    generateMipmap();
        GLuint  getHandle() const;
        GLenum  getTarget() const;
        template <class T>
        void    setParameter(GLenum property, T value);

    private:
        GLuint  _handle;
        GLenum  _target;
    };
}

#endif // MOGL_TEXTUREOBJECT_INCLUDED
