

#pragma once

#include "LCommon.h"
#include "../Config.h"

using namespace std;

namespace engine
{

    class LICamera
    {
        protected :

        LVec3 m_pos;
        LVec3 m_targetDir;
        LVec3 m_worldUp;

        float m_fov;
        float m_aspectRatio;
        float m_zNear;
        float m_zFar;

        string m_cameraId;

        virtual void _updateCamera();

        public :

        LICamera( const LVec3& pos,
                  const LVec3& targetDir,
                  const LVec3& worldUp,
                  float fov = 45.0f,
                  float aspectRatio = ( (float)APP_WIDTH ) / APP_HEIGHT,
                  float zNear = 0.1f, float zFar = 100.0f );

        ~LICamera();

        LVec3 getPosition() const { return m_pos; }
        LVec3 getTargetDir() const { return m_targetDir; }

        void setPosition( const LVec3& pos );

        virtual glm::mat4 getViewMatrix() = 0;
        glm::mat4 getProjectionMatrix();

        virtual void update( float dt ) 
        {
            // Override this
        }

        virtual void dumpInfo()
        {
            cout << "Camera base information for camera < " << m_cameraId << " > *******" << endl;

            cout << "pos: " << m_pos.toString() << endl;
            cout << "targetDir: " << m_targetDir.toString() << endl;
            cout << "worldUp: " << m_worldUp.toString() << endl;
            cout << "fov: " << m_fov << endl;
            cout << "aspectRatio: " << m_aspectRatio << endl;
            cout << "zNear: " << m_zNear << endl;
            cout << "zFar: " << m_zFar << endl;

            cout << "******************************************" << endl;
        }

    };



}