

#include "LFixedCamera3d.h"


namespace engine
{

    LFixedCamera3d::LFixedCamera3d( const LVec3& pos,
                                    const LVec3& targetDir,
                                    const LVec3& worldUp,
                                    float fov,
                                    float aspectRatio,
                                    float zNear, float zFar ) 
        : LICamera( pos, targetDir, worldUp, fov, aspectRatio, zNear, zFar )
    {
        m_movSpeed = 0.0f;
        m_movDirection = LVec3( 0, 0, 0 );
    }

    glm::mat4 LFixedCamera3d::getViewMatrix()
    {
        glm::vec3 _cameraPos( m_pos.x, m_pos.y, m_pos.z );
        glm::vec3 _cameraDir( m_targetDir.x, m_targetDir.y, m_targetDir.z );
        glm::vec3 _cameraTarget = _cameraPos + _cameraDir;
        glm::vec3 _worldUp( m_worldUp.x, m_worldUp.y, m_worldUp.z );

        return glm::lookAt( _cameraPos, _cameraTarget, _worldUp );
    }

    void LFixedCamera3d::update( float dt )
    {
        m_pos.x += m_movDirection.x * m_movSpeed * dt;
        m_pos.y += m_movDirection.y * m_movSpeed * dt;
        m_pos.z += m_movDirection.z * m_movSpeed * dt;
    }
}