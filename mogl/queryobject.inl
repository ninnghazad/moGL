////////////////////////////////////////////////////////////////////////////////
/// Modern OpenGL Wrapper
///
/// Copyright (c) 2015 Thibault Schueller
/// This file is distributed under the MIT License
///
/// @file queryobject.inl
/// @author Thibault Schueller <ryp.sqrt@gmail.com>
////////////////////////////////////////////////////////////////////////////////

namespace mogl
{
    inline QueryObject::QueryObject(GLenum type)
    :   _type(type)
    {
        glCreateQueries(_type, 1, &_handle);
    }

    inline QueryObject::~QueryObject()
    {
        if (_handle)
            glDeleteQueries(1, &_handle);
    }

    inline void QueryObject::begin()
    {
        glBeginQuery(_type, _handle);
    }

    inline void QueryObject::end()
    {
        glEndQuery(_type);
    }

    template <>
    inline GLint QueryObject::getResult(GLenum param)
    {
        GLint   rslt;
        glGetQueryObjectiv(_handle, param, &rslt);
        return rslt;
    }

    template <>
    inline GLuint QueryObject::getResult(GLenum param)
    {
        GLuint  rslt;
        glGetQueryObjectuiv(_handle, param, &rslt);
        return rslt;
    }

    template <>
    inline GLint64 QueryObject::getResult(GLenum param)
    {
        GLint64 rslt;
        glGetQueryObjecti64v(_handle, param, &rslt);
        return rslt;
    }

    template <>
    inline GLuint64 QueryObject::getResult(GLenum param)
    {
        GLuint64    rslt;
        glGetQueryObjectui64v(_handle, param, &rslt);
        return rslt;
    }

    inline GLenum QueryObject::getType() const
    {
        return _type;
    }

    inline bool QueryObject::isValid() const
    {
        return glIsQuery(_handle) == GL_TRUE;
    }

}
