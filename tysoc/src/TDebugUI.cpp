
#include <TDebugUI.h>

using namespace cat1UI;

namespace tysoc
{


    TDebugUI::TDebugUI( GLFWwindow* pGlfwWindow )
    {
        m_world = NULL;
        m_uiHandler = LUIHandler::create( pGlfwWindow );

        m_windowMaster = new LUIWindow( "Master panel" );

        m_windowMaster->addCheckboxWidget( 0, "chbox_DebugDraw", false, "Show Debug draws" );
        m_windowMaster->addCheckboxWidget( 1, "chbox_DebugLayers", false, "Show Debug layers" );
        m_windowMaster->addCheckboxWidget( 2, "chbox_Lighting", false, "Show lighting options" );
        m_windowMaster->addCheckboxWidget( 3, "chbox_TestPanel", false, "Show test panel" );

        m_windowLighting = new LUIWindow( "Lighting options" );
        m_windowLighting->addSliderWidget( 0, "sl_globalAmbient", 0.0f, 1.0f, 0.1f, "Global ambient light" );
        m_windowLighting->addSliderWidget( 1, "sl_ambient", 0.0f, 1.0f, 0.1f, "Light source ambient component" );
        m_windowLighting->addSliderWidget( 2, "sl_diffuse", 0.0f, 1.0f, 0.8f, "Light source diffuse component" );
        m_windowLighting->addSliderWidget( 3, "sl_specular", 0.0f, 1.0f, 0.05f, "Light source specular component" );

        m_windowTestPanel = new LUIWindow( "Test panel" );

        m_uiHandler->addWindow( m_windowMaster );
        m_uiHandler->addWindow( m_windowLighting );
        m_uiHandler->addWindow( m_windowTestPanel );

    }

    TDebugUI::~TDebugUI()
    {
        m_uiHandler = NULL;
        m_world = NULL;
        m_windowMaster = NULL;
        m_windowLighting = NULL;
        m_windowTestPanel = NULL;

        LUIHandler::release();
    }

    void TDebugUI::init( TWorld* pWorld )
    {
        m_world = pWorld;

        unordered_map< string, engine::LICamera* > _cameras = m_world->getCameras();

        vector< string > _camerasIDs;

        for ( auto _it : _cameras )
        {
            _camerasIDs.push_back( _it.first );
        }

        m_windowTestPanel->addComboBoxWidget( 0, "comb_cameras", "cameras", _camerasIDs );
        m_windowTestPanel->addButtonWidget( 1, "btn_primitive", "primitives" );
    }

    void TDebugUI::render()
    {
        m_uiHandler->render();

        {
            auto _combCameras = m_windowTestPanel->getComboBoxWidget( "comb_cameras" );
            if ( _combCameras->hasChangedValue() )
            {
                // Change camera
                auto _newCameraID = _combCameras->getCurrentOptionStr();
                m_world->changeToCamera( _newCameraID );
            }
        }

        {
            auto _vGlobalAmbient = m_windowLighting->getSliderWidget( "sl_globalAmbient" )->getSliderValue();
            auto _vAmbient = m_windowLighting->getSliderWidget( "sl_ambient" )->getSliderValue();
            auto _vDiffuse= m_windowLighting->getSliderWidget( "sl_diffuse" )->getSliderValue();
            auto _vSpecular = m_windowLighting->getSliderWidget( "sl_specular" )->getSliderValue();
            // Set light values
            m_world->setGlobalAmbientLight( engine::LVec3( _vGlobalAmbient, _vGlobalAmbient, _vGlobalAmbient ) );

            auto _lights = m_world->getLights< engine::LLightDirectional >();
            if ( _lights.size() > 0 )
            {
                auto _mainLight = _lights[0];
                _mainLight->ambient  = engine::LVec3( _vAmbient, _vAmbient, _vAmbient );
                _mainLight->diffuse  = engine::LVec3( _vDiffuse, _vDiffuse, _vDiffuse );
                _mainLight->specular = engine::LVec3( _vSpecular, _vSpecular, _vSpecular );
            }
        }
    }
}