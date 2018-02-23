
#pragma once

#include <LCommon.h>
#include <LVertexBuffer.h>
#include <LVertexArray.h>

using namespace std;

namespace engine
{
    struct LDLinePositions
    {
        LVec3 vStart;
        LVec3 vEnd;
    };

    struct LDLineColors
    {
        LVec3 cStart;
        LVec3 cEnd;
    };

    class LDebugDrawer
    {

        private :

        vector< LDLinePositions > m_linesPositions;
        vector< LDLineColors > m_linesColors;

        LVertexBuffer* m_linesPositionsVBO;
        LVertexBuffer* m_linesColorsVBO;
        LVertexBuffer* m_linesVAO;

        void _renderLines();

        public :


        void drawLine( const LVec3& start, const LVec3& end, const LVec3& color );
        void drawArrow( const LVec3& start, const LVec3& end, const LVec3& color );
        void drawClipFrustum( const glm::mat4& invClipMatrix, const LVec3& color );
        void drawClipBox( const glm::mat4& invClipMatrix, const LVec3& color );

        void render();
    };



}

