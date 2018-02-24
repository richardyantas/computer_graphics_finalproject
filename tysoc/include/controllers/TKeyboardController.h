
#pragma once

#include <TPlayerEntity.h>
#include <LInputHandler.h>

using namespace std;

#define KEYBOARD_CONTROLLER_DEFAULT_TARGET_SPEED 4.0f
#define KEYBOARD_CONTROLLER_KP 8.0f
#define KEYBOARD_CONTROLLER_KI 1.0f
#define KEYBOARD_CONTROLLER_KD 5.0f

#define KEYBOARD_CONTROLLER_FREEMOVEMENT_SPEED 4.0f

namespace tysoc
{
    class TPlayerEntity;

    class TKeyboardController : public TComponent
    {

        private :

        TPlayerEntity* m_playerEntity;
        TBasicPhysicsComponent* m_playerPhysics;

        float m_targetSpeed;
        TVec3 m_targetDirection;

        float m_ep;
        float m_ei;
        float m_ed;

        float m_kp;
        float m_ki;
        float m_kd;

        float m_uControl;

        void _handleFreeMovement( float dt );
        void _handleSimMovement( float dt );

        TVec3 _updatePIDController( float dt, float error );
        void _resetPIDController();

        public :

        TKeyboardController( TPlayerEntity* parent );
        ~TKeyboardController();

        static string getStaticType() { return string( "controller"); }

        void update( float dt ) override;

        float getAppliedControl() { return m_uControl; }

        void setKp( float v ) { m_kp = v; }
        void setKi( float v ) { m_ki = v; }
        void setKd( float v ) { m_kd = v; }
    };



}