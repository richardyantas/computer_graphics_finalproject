
#pragma once

#include <LUIWidgets.h>

using namespace std;

namespace cat1UI
{
    
    class LUIWindow
    {

        protected :

        unordered_map< string, LUIText* > m_textWidgets;
        unordered_map< string, LUIButton* > m_buttonWidgets;
        unordered_map< string, LUISlider* > m_sliderWidgets;
        unordered_map< string, LUICheckbox* > m_checkboxWidgets;
        unordered_map< string, LUIComboBox* > m_comboboxWidgets;
        unordered_map< string, LUIColorPicker* > m_colorPickerWidgets;

        bool m_isActive;
        string m_name;

        vector< LUIWidget* > m_widgetsRenderQueue;

        public :

        LUIWindow( string name );
        ~LUIWindow();

        LUIText* addTextWidget( int order, string id, string text );
        LUIButton* addButtonWidget( int order, string id, string buttonName );
        LUISlider* addSliderWidget( int order, string id, float minVal, float maxVal, float initialValue, string sliderName );
        LUICheckbox* addCheckboxWidget( int order, string id, bool initialState, string checkboxName );
        LUIComboBox* addComboBoxWidget( int order, string id, string comboBoxName, const vector< string >& options );
        LUIColorPicker* addColorPickerWidget( int order, string id, string colorPickerName, float* initialColor );

        LUIText* getTextWidget( string id );
        LUIButton* getButtonWidget( string id );
        LUISlider* getSliderWidget( string id );
        LUICheckbox* getCheckboxWidget( string id );
        LUIComboBox* getComboBoxWidget( string id );
        LUIColorPicker* getColorPickerWidget( string id );

        void render();

        void enable() { m_isActive = true; }
        void disable() { m_isActive = false; }
        void setMode( bool active ) { m_isActive = active; }
        bool isActive() { return m_isActive; }

        string getName() { return m_name; }
    };



}