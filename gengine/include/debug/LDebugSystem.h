
#pragma once

#include <LCommon.h>
#include <debug/LDebugDrawer.h>
#include <debug/LDebugViewer.h>

namespace engine { namespace DebugSystem {

    void init();

    // drawer calls

    void drawLine( const LVec3& start, const LVec3& end, const LVec3& color );
    void drawArrow( const LVec3& start, const LVec3& end, const LVec3& color );
    void drawClipFrustum( const glm::mat4& invClipMatrix, const LVec3& color );
    void drawClipBox( const glm::mat4& invClipMatrix, const LVec3& color );

    // viewer calls

    void renderView( const LVec2& pos, const LVec2& size, GLuint textureID );

    void render();

    void release();
}}