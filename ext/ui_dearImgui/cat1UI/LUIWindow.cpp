
#include "LUIWindow.h"

using namespace std;

namespace cat1UI
{


    LUIWindow::LUIWindow( string name )
    {
        m_isActive = true;
        m_name = name;
    }

    LUIWindow::~LUIWindow()
    {
        for ( auto _it : m_textWidgets ) 
        { 
            delete _it.second; 
        }
        m_textWidgets.clear();

        for ( auto _it : m_buttonWidgets ) 
        { 
            delete _it.second; 
        }
        m_buttonWidgets.clear();

        for ( auto _it : m_sliderWidgets ) 
        { 
            delete _it.second; 
        }
        m_sliderWidgets.clear();

        for ( auto _it : m_checkboxWidgets ) 
        { 
            delete _it.second; 
        }
        m_checkboxWidgets.clear();

        for ( auto _it : m_comboboxWidgets )
        {
            delete _it.second;
        }
        m_comboboxWidgets.clear();

        for ( auto _it : m_colorPickerWidgets )
        {
            delete _it.second;
        }
        m_colorPickerWidgets.clear();

        m_widgetsRenderQueue.clear();
    }


    LUIText* LUIWindow::addTextWidget( int order, string id, string text )
    {
        if ( m_textWidgets.find( id ) != m_textWidgets.end() )
        {
            cout << "textWidget with id: " << id << " already exists. Not adding new widget" << endl;
            return NULL;
        }

        auto _textWidget = new LUIText( id, order, text );

        m_textWidgets[ id ] = _textWidget;

        return _textWidget;
    }

    LUIButton* LUIWindow::addButtonWidget( int order, string id, string buttonName )
    {
        if ( m_buttonWidgets.find( id ) != m_buttonWidgets.end() )
        {
            cout << "buttonWidget with id: " << id << " already exists. Not adding new widget" << endl;
            return NULL;
        }

        auto _buttonWidget = new LUIButton( id, order, buttonName );

        m_buttonWidgets[ id ] = _buttonWidget;

        return _buttonWidget;
    }

    LUISlider* LUIWindow::addSliderWidget( int order, string id, float minVal, float maxVal, float initialValue, string sliderName )
    {
        if ( m_sliderWidgets.find( id ) != m_sliderWidgets.end() )
        {
            cout << "sliderWidget with id: " << id << " already exists. Not adding new widget" << endl;
            return NULL;
        }

        auto _sliderWidget = new LUISlider( id, order, minVal, maxVal, initialValue, sliderName );

        m_sliderWidgets[ id ] = _sliderWidget;

        return _sliderWidget;
    }

    LUICheckbox* LUIWindow::addCheckboxWidget( int order, string id, bool initialState, string checkboxName )
    {
        if ( m_checkboxWidgets.find( id ) != m_checkboxWidgets.end() )
        {
            cout << "checkboxWidget with id: " << id << " already exists. Not adding new widget" << endl;
            return NULL;
        }

        auto _checkboxWidget = new LUICheckbox( id, order, checkboxName, initialState );

        m_checkboxWidgets[ id ] = _checkboxWidget;

        return _checkboxWidget;
    }

    LUIComboBox* LUIWindow::addComboBoxWidget( int order, string id, string comboBoxName, const vector< string >& options )
    {
        if ( m_comboboxWidgets.find( id ) != m_comboboxWidgets.end() )
        {
            cout << "comboboxWidget with id: " << id << " already exists. Not adding new widget" << endl;
            return NULL;
        }

        auto _comboBoxWidget = new LUIComboBox( id, order, comboBoxName, options );

        m_comboboxWidgets[id] = _comboBoxWidget;

        return _comboBoxWidget;
    }

    LUIColorPicker* LUIWindow::addColorPickerWidget( int order, string id, string colorPickerName, float* initialColor )
    {
        if ( m_colorPickerWidgets.find( id ) != m_colorPickerWidgets.end() )
        {
            cout << "checkboxWidget with id: " << id << " already exists. Not adding new widget" << endl;
            return NULL;
        }

        auto _colorPickerWidget = new LUIColorPicker( id, order, colorPickerName, initialColor );

        m_colorPickerWidgets[id] = _colorPickerWidget;

        return _colorPickerWidget;
    }

    LUIText* LUIWindow::getTextWidget( string id )
    {
        if ( m_textWidgets.find( id ) == m_textWidgets.end() )
        {
            cout << "textWidget with id: " << id << " not found" << endl;
            return NULL;
        }

        return m_textWidgets[ id ];
    }

    LUIButton* LUIWindow::getButtonWidget( string id )
    {
        if ( m_buttonWidgets.find( id ) == m_buttonWidgets.end() )
        {
            cout << "buttonWidget with id: " << id << " not found" << endl;
            return NULL;
        }

        return m_buttonWidgets[ id ];
    }

    LUISlider* LUIWindow::getSliderWidget( string id )
    {
        if ( m_sliderWidgets.find( id ) == m_sliderWidgets.end() )
        {
            cout << "sliderWidget with id: " << id << " not found" << endl;
            return NULL;
        }

        return m_sliderWidgets[ id ];
    }

    LUICheckbox* LUIWindow::getCheckboxWidget( string id )
    {
        if ( m_checkboxWidgets.find( id ) == m_checkboxWidgets.end() )
        {
            cout << "checkboxWidget with id: " << id << " not found" << endl;
            return NULL;
        }

        return m_checkboxWidgets[ id ];
    }

    LUIComboBox* LUIWindow::getComboBoxWidget( string id )
    {
        if ( m_comboboxWidgets.find( id ) == m_comboboxWidgets.end() )
        {
            cout << "comboboxWidget with id: " << id << " not found" << endl;
            return NULL;
        }

        return m_comboboxWidgets[id];
    }

    LUIColorPicker* LUIWindow::getColorPickerWidget( string id )
    {
        if ( m_colorPickerWidgets.find( id ) == m_colorPickerWidgets.end() )
        {
            cout << "colorPickerWidget with id: " << id << " not found" << endl;
            return NULL;
        }

        return m_colorPickerWidgets[id];
    }

    void LUIWindow::render()
    {
        // sort the widgets in their corresponding buffers
        m_widgetsRenderQueue.clear();

        for ( auto _it : m_textWidgets ) { m_widgetsRenderQueue.push_back( _it.second ); }
        for ( auto _it : m_buttonWidgets ) { m_widgetsRenderQueue.push_back( _it.second ); }
        for ( auto _it : m_sliderWidgets ) { m_widgetsRenderQueue.push_back( _it.second ); }
        for ( auto _it : m_checkboxWidgets ) { m_widgetsRenderQueue.push_back( _it.second ); }
        for ( auto _it : m_comboboxWidgets ) { m_widgetsRenderQueue.push_back( _it.second ); }
        for ( auto _it : m_colorPickerWidgets ) { m_widgetsRenderQueue.push_back( _it.second ); }

        std::sort( m_widgetsRenderQueue.begin(), m_widgetsRenderQueue.end(), comparatorWidgetsOrder );

        ImGui::Begin( m_name.c_str(), &m_isActive );

        for ( auto _widget : m_widgetsRenderQueue )
        {
            _widget->render();
        }

        ImGui::End();

        m_widgetsRenderQueue.clear();
    }

}