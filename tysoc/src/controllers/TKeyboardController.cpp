
#include <controllers/TKeyboardController.h>



namespace tysoc
{


    TKeyboardController::TKeyboardController( TPlayerEntity* parent )
        : TComponent( parent )
    {
        this->type = TKeyboardController::getStaticType();

        m_playerEntity = parent;
        m_playerPhysics = m_playerEntity->getComponent< TBasicPhysicsComponent >();

        m_targetSpeed = KEYBOARD_CONTROLLER_DEFAULT_TARGET_SPEED;
        m_targetDirection = TVec3::normalize( m_playerEntity->movDirection() );

        m_uControl = 0;
        m_ep = m_ei = m_ed = 0;
        m_kp = KEYBOARD_CONTROLLER_KP;
        m_ki = KEYBOARD_CONTROLLER_KI;
        m_kd = KEYBOARD_CONTROLLER_KD;
    }

    TKeyboardController::~TKeyboardController()
    {
        m_playerEntity = NULL;
        m_playerPhysics = NULL;
    }

    void TKeyboardController::update( float dt )
    {
        if ( m_playerEntity->inFreeMovement() )
        {
            _handleFreeMovement( dt );
        }
        else
        {
            _handleSimMovement( dt );
        }
    }

    void TKeyboardController::_handleFreeMovement( float dt )
    {
        auto _playerPos = m_playerEntity->pos;
        auto _rBody = m_playerPhysics->getRigidBody();
        _rBody->setLinearVelocity( btVector3( 0, 0, 0 ) );
        _rBody->setAngularVelocity( btVector3( 0, 0, 0 ) );

        if ( engine::LInputHandler::INSTANCE->isKeyPressed( GLFW_KEY_RIGHT ) ||
             engine::LInputHandler::INSTANCE->isKeyPressed( GLFW_KEY_LEFT ) )
        {
            float _dir = engine::LInputHandler::INSTANCE->isKeyPressed( GLFW_KEY_RIGHT ) ? 1 : -1;

            _playerPos.x += KEYBOARD_CONTROLLER_FREEMOVEMENT_SPEED * dt * m_targetDirection.x * _dir;
            _playerPos.y += KEYBOARD_CONTROLLER_FREEMOVEMENT_SPEED * dt * m_targetDirection.y * _dir;
            _playerPos.z += KEYBOARD_CONTROLLER_FREEMOVEMENT_SPEED * dt * m_targetDirection.z * _dir;
        }
        else if ( engine::LInputHandler::INSTANCE->isKeyPressed( GLFW_KEY_UP ) ||
                  engine::LInputHandler::INSTANCE->isKeyPressed( GLFW_KEY_DOWN ) )
        {
            float _dir = engine::LInputHandler::INSTANCE->isKeyPressed( GLFW_KEY_UP ) ? 1 : -1;

            _playerPos.y += KEYBOARD_CONTROLLER_FREEMOVEMENT_SPEED * dt * _dir;
        }

        m_playerEntity->setForcedPosition( _playerPos );
    }

    void TKeyboardController::_handleSimMovement( float dt )
    {
        auto _rBody = m_playerPhysics->getRigidBody();

        if ( engine::LInputHandler::INSTANCE->isKeyPressed( GLFW_KEY_RIGHT ) )
        {
            TVec3 _currentVelocity = m_playerPhysics->getVelocity();
            float _currentSpeedInDirection = TVec3::dot( _currentVelocity, m_targetDirection );

            TVec3 _u = _updatePIDController( dt, m_targetSpeed - _currentSpeedInDirection );

            m_playerPhysics->applyForce( _u );
        }
        else
        {
            _resetPIDController();
        }

        if ( engine::LInputHandler::INSTANCE->isKeyPressed( GLFW_KEY_SPACE ) )
        {
            m_playerEntity->jump( 5 );
        }
    }

    TVec3 TKeyboardController::_updatePIDController( float dt, float error )
    {
        m_ed = error - m_ep;
        m_ei += error * dt;
        m_ep = error;

        m_uControl = m_kp * m_ep + m_ki * m_ei + m_kd * m_ed;

        return TVec3( m_targetDirection.x * m_uControl,
                      m_targetDirection.y * m_uControl,
                      m_targetDirection.z * m_uControl );
    }

    void TKeyboardController::_resetPIDController()
    {
        m_ep = 0;
        m_ei = 0;
        m_ep = 0;
        m_uControl = 0;
    }
}