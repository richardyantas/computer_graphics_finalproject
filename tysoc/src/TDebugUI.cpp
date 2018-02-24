
#include <TDebugUI.h>

using namespace cat1UI;
using namespace std;

namespace tysoc
{


    TDebugUI::TDebugUI( GLFWwindow* pGlfwWindow )
    {
        engine::DebugSystem::init();

        m_scenario = NULL;
        m_uiHandler = LUIHandler::create( pGlfwWindow );

        m_wMaster = new LUIWindow( "Master panel" );

        m_wMaster->addCheckboxWidget( 0, "chbox_DebugDraw", false, "Show Debug draws" );
        m_wMaster->addCheckboxWidget( 1, "chbox_DebugLayers", false, "Show Debug layers" );
        m_wMaster->addCheckboxWidget( 2, "chbox_CamPanel", false, "Show cam info panel" );
        m_wMaster->addCheckboxWidget( 3, "chbox_PlayerPanel", true, "Show player info panel" );
        m_wMaster->addCheckboxWidget( 4, "chbox_LightingPanel", false, "Show lighting options" );
        m_wMaster->addCheckboxWidget( 5, "chbox_TestPanel", false, "Show test panel" );

        m_wCamInfo = new LUIWindow( "Camera info" );

        m_wCamInfo->addTextWidget( 0, "txt_cam_pos", "" );
        m_wCamInfo->addTextWidget( 1, "txt_cam_target", "" );
        m_wCamInfo->addTextWidget( 2, "txt_cam_fov", "" );
        m_wCamInfo->addTextWidget( 3, "txt_cam_znear", "" );
        m_wCamInfo->addTextWidget( 4, "txt_cam_zfar", "" );
        m_wCamInfo->addTextWidget( 5, "txt_cam_n0", "" );
        m_wCamInfo->addTextWidget( 6, "txt_cam_n1", "" );
        m_wCamInfo->addTextWidget( 7, "txt_cam_n2", "" );
        m_wCamInfo->addTextWidget( 8, "txt_cam_n3", "" );
        m_wCamInfo->addTextWidget( 9, "txt_cam_f0", "" );
        m_wCamInfo->addTextWidget( 10, "txt_cam_f1", "" );
        m_wCamInfo->addTextWidget( 11, "txt_cam_f2", "" );
        m_wCamInfo->addTextWidget( 12, "txt_cam_f3", "" );

        m_wLighting = new LUIWindow( "Lighting options" );
        m_wLighting->addSliderWidget( 0, "sl_globalAmbient", 0.0f, 1.0f, 0.1f, "Global ambient light" );
        m_wLighting->addSliderWidget( 1, "sl_ambient", 0.0f, 1.0f, 0.1f, "Light source ambient component" );
        m_wLighting->addSliderWidget( 2, "sl_diffuse", 0.0f, 1.0f, 0.8f, "Light source diffuse component" );
        m_wLighting->addSliderWidget( 3, "sl_specular", 0.0f, 1.0f, 0.05f, "Light source specular component" );

        m_wTestPanel = new LUIWindow( "Test panel" );

        m_wPlayerInfo = new LUIWindow( "Player info" );

        m_uiHandler->addWindow( m_wMaster );
        m_uiHandler->addWindow( m_wCamInfo );
        m_uiHandler->addWindow( m_wPlayerInfo );
        m_uiHandler->addWindow( m_wLighting );
        m_uiHandler->addWindow( m_wTestPanel );

    }

    TDebugUI::~TDebugUI()
    {
        m_uiHandler = NULL;
        m_scenario = NULL;
        m_wMaster = NULL;
        m_wLighting = NULL;
        m_wTestPanel = NULL;

        engine::DebugSystem::release();
        LUIHandler::release();
    }

    void TDebugUI::init( TBaseScenario* pScenario )
    {
        m_scenario = pScenario;

        unordered_map< string, engine::LICamera* > _cameras = m_scenario->getCameras();

        vector< string > _camerasIDs;

        for ( auto _it : _cameras )
        {
            _camerasIDs.push_back( _it.first );
        }

        m_wTestPanel->addComboBoxWidget( 0, "comb_cameras", "cameras", _camerasIDs );
        m_wTestPanel->addButtonWidget( 1, "btn_primitive", "primitives" );

        // player panel initialization

        m_playerRef = m_scenario->getPlayer();

        m_wPlayerInfo->addCheckboxWidget( 0, "txt_player_freemovement", false, "free movement" );
        m_wPlayerInfo->addTextWidget( 1, "txt_player_velocity", "" );
        m_wPlayerInfo->addTextWidget( 2, "txt_player_Control", "" );
        m_wPlayerInfo->addSliderWidget( 3, "sl_player_kp", 0.0f, 10.0f, 3.0f, "kp" );
        m_wPlayerInfo->addSliderWidget( 4, "sl_player_ki", 0.0f, 5.0f, 0.5f, "ki" );
        m_wPlayerInfo->addSliderWidget( 5, "sl_player_kd", 0.0f, 10.0f, 3.0f, "kd" );
    }

    void TDebugUI::render()
    {
        m_uiHandler->render();

        {
            // Check checkboxes to show/hide panels
            m_wCamInfo->setMode( m_wMaster->getCheckboxWidget( "chbox_CamPanel" )->getCheckboxState() );
            m_wPlayerInfo->setMode( m_wMaster->getCheckboxWidget( "chbox_PlayerPanel" )->getCheckboxState() );
            m_wLighting->setMode( m_wMaster->getCheckboxWidget( "chbox_LightingPanel")->getCheckboxState() );
            m_wTestPanel->setMode( m_wMaster->getCheckboxWidget( "chbox_TestPanel")->getCheckboxState() );
        }

        if ( m_wTestPanel->isActive() )
        {
            auto _combCameras = m_wTestPanel->getComboBoxWidget( "comb_cameras" );
            if ( _combCameras->hasChangedValue() )
            {
                // Change camera
                auto _newCameraID = _combCameras->getCurrentOptionStr();
                m_scenario->changeToCamera( _newCameraID );
            }
        }

        if ( m_wLighting->isActive() )
        {
            auto _vGlobalAmbient = m_wLighting->getSliderWidget( "sl_globalAmbient" )->getSliderValue();
            auto _vAmbient = m_wLighting->getSliderWidget( "sl_ambient" )->getSliderValue();
            auto _vDiffuse= m_wLighting->getSliderWidget( "sl_diffuse" )->getSliderValue();
            auto _vSpecular = m_wLighting->getSliderWidget( "sl_specular" )->getSliderValue();
            // Set light values
            m_scenario->setGlobalAmbientLight( engine::LVec3( _vGlobalAmbient, _vGlobalAmbient, _vGlobalAmbient ) );

            auto _lights = m_scenario->getLights< engine::LLightDirectional >();
            if ( _lights.size() > 0 )
            {
                auto _mainLight = _lights[0];
                _mainLight->ambient  = engine::LVec3( _vAmbient, _vAmbient, _vAmbient );
                _mainLight->diffuse  = engine::LVec3( _vDiffuse, _vDiffuse, _vDiffuse );
                _mainLight->specular = engine::LVec3( _vSpecular, _vSpecular, _vSpecular );
            }
        }

        if ( m_wCamInfo->isActive() )
        {
            // Camera frustum info

            auto _currentCamera = m_scenario->getCurrentCamera();

            auto _cameraPosition = _currentCamera->getPosition();
            auto _cameraTarget = _currentCamera->getTargetDir();
            auto _cameraFov = _currentCamera->getFov();
            auto _cameraZNear = _currentCamera->getZNear();
            auto _cameraZFar = _currentCamera->getZFar();

            m_wCamInfo->getTextWidget( "txt_cam_pos" )->setText( _makeText( "pos", _cameraPosition.toString() ) );
            m_wCamInfo->getTextWidget( "txt_cam_target" )->setText( _makeText( "target", _cameraTarget.toString() ) );
            m_wCamInfo->getTextWidget( "txt_cam_fov" )->setText( _makeText( "fov", to_string( _cameraFov ) ) );
            m_wCamInfo->getTextWidget( "txt_cam_znear" )->setText( _makeText( "zNear", to_string( _cameraZNear ) ) );
            m_wCamInfo->getTextWidget( "txt_cam_zfar" )->setText( _makeText( "zFar", to_string( _cameraZFar ) ) );

            glm::vec3 _frustumPointsClipSpace[8] = {
                // near plane
                { -1.0f, -1.0f, -1.0f },{ 1.0f, -1.0f, -1.0f },
                { 1.0f,  1.0f, -1.0f },{ -1.0f,  1.0f, -1.0f },
                // far plane
                { -1.0f, -1.0f,  1.0f },{ 1.0f, -1.0f,  1.0f },
                { 1.0f,  1.0f,  1.0f },{ -1.0f,  1.0f,  1.0f }
            };

            glm::mat4 _viewMatrix = _currentCamera->getViewMatrix();
            glm::mat4 _projMatrix = _currentCamera->getProjectionMatrix();

            glm::mat4 _clipMatrix = _projMatrix * _viewMatrix;
            glm::mat4 _invClipMatrix = glm::inverse( _clipMatrix );

            vector< engine::LVec3 > _planes;

            for ( int q = 0; q < 8; q++ )
            {
                glm::vec4 _pointFrustum = _invClipMatrix * glm::vec4( _frustumPointsClipSpace[q], 1.0f );
                glm::vec3 _pointFrustumNormalized = glm::vec3( _pointFrustum.x / _pointFrustum.w,
                                                               _pointFrustum.y / _pointFrustum.w,
                                                               _pointFrustum.z / _pointFrustum.w );

                _planes.push_back( engine::LVec3( _pointFrustumNormalized.x, 
                                                  _pointFrustumNormalized.y, 
                                                  _pointFrustumNormalized.z ) );
            }

            m_wCamInfo->getTextWidget( "txt_cam_n0" )->setText( _makeText( "n0", _planes[0].toString() ) );
            m_wCamInfo->getTextWidget( "txt_cam_n1" )->setText( _makeText( "n1", _planes[1].toString() ) );
            m_wCamInfo->getTextWidget( "txt_cam_n2" )->setText( _makeText( "n2", _planes[2].toString() ) );
            m_wCamInfo->getTextWidget( "txt_cam_n3" )->setText( _makeText( "n3", _planes[3].toString() ) );

            m_wCamInfo->getTextWidget( "txt_cam_f0" )->setText( _makeText( "f0", _planes[4].toString() ) );
            m_wCamInfo->getTextWidget( "txt_cam_f1" )->setText( _makeText( "f1", _planes[5].toString() ) );
            m_wCamInfo->getTextWidget( "txt_cam_f2" )->setText( _makeText( "f2", _planes[6].toString() ) );
            m_wCamInfo->getTextWidget( "txt_cam_f3" )->setText( _makeText( "f3", _planes[7].toString() ) );
        }


        if ( m_wPlayerInfo->isActive() )
        {
            // player info
            auto _playerPhysics = m_playerRef->getComponent< TBasicPhysicsComponent >();
            auto _playerController = m_playerRef->getComponent< TKeyboardController >();

            TVec3 _playerVelocity = _playerPhysics->getVelocity();
            float _playerControl  = _playerController->getAppliedControl();

            bool _inFreeMovement = m_wPlayerInfo->getCheckboxWidget( "txt_player_freemovement" )->getCheckboxState();
            m_playerRef->setFreeMovementMode( _inFreeMovement );

            m_wPlayerInfo->getTextWidget( "txt_player_velocity" )->setText( _makeText( "vel: ", _playerVelocity.toString() ) );
            m_wPlayerInfo->getTextWidget( "txt_player_Control" )->setText( _makeText( "u: ", to_string( _playerControl ) ) );

            _playerController->setKp( m_wPlayerInfo->getSliderWidget( "sl_player_kp" )->getSliderValue() );
            _playerController->setKi( m_wPlayerInfo->getSliderWidget( "sl_player_ki" )->getSliderValue() );
            _playerController->setKd( m_wPlayerInfo->getSliderWidget( "sl_player_kd" )->getSliderValue() );
        }


        {
            // draw some stuff
            auto _cameras = m_scenario->getCameras();
            auto _currentCamera = m_scenario->getCurrentCamera();

            for ( auto _it : _cameras )
            {
                auto _viewMat = _it.second->getViewMatrix();
                auto _projMat = _it.second->getProjectionMatrix();

                engine::DebugSystem::drawClipVolume( _projMat * _viewMat );
            }

            engine::DebugSystem::drawLine( engine::LVec3( 0, 0, 0 ), engine::LVec3( 10, 0, 0 ), engine::LVec3( 1, 0, 0 ) );
            engine::DebugSystem::drawLine( engine::LVec3( 0, 0, 0 ), engine::LVec3( 0, 10, 0 ), engine::LVec3( 0, 1, 0 ) );
            engine::DebugSystem::drawLine( engine::LVec3( 0, 0, 0 ), engine::LVec3( 0, 0, 10 ), engine::LVec3( 0, 0, 1 ) );

            auto _trail = m_playerRef->trail().getTrailPoints();

            engine::DebugSystem::drawTrailPoints( _trail, engine::LVec3( 0, 1, 1 ) );

            engine::DebugSystem::setupMatrices( _currentCamera->getViewMatrix(), _currentCamera->getProjectionMatrix() );
            engine::DebugSystem::render();
        }
    }

    string TDebugUI::_makeText( string title, string msg )
    {
        string _res( title );
        _res += ": ";
        _res += msg;

        return _res;
    }

}