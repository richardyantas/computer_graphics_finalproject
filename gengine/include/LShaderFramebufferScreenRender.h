
#pragma once

#include "LShader.h"

namespace engine
{


    class LShaderFramebufferScreenRender : public LShader
    {
        protected :

        GLuint m_uTextureChannel;

        public :

        LShaderFramebufferScreenRender( GLuint id ) : LShader( id )
        {
            bind();

            // Load uniforms
            m_uTextureChannel = glGetUniformLocation( m_id, "u_texChannel" );

            unbind();
        }

        void LShaderFramebufferScreenRender::setTextureSamplingChannel( int channel )
        {
            _setInt( m_uTextureChannel, channel );
        }

    };



}