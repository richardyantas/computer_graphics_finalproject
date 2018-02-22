
#pragma once

#include <LUIWidgets.h>

using namespace std;

namespace cat1UI
{
    
    class LUIWindow
    {

        protected :

        unordered_map< string, cat1UI::LUIText* > m_textWidgets;
        unordered_map< string, cat1UI::LUIButton* > m_buttonWidgets;
        unordered_map< string, cat1UI::LUISlider* > m_sliderWidgets;
        unordered_map< string, cat1UI::LUICheckbox* > m_checkboxWidgets;

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

        LUIText* getTextWidget( string id );
        LUIButton* getButtonWidget( string id );
        LUISlider* getSliderWidget( string id );
        LUICheckbox* getCheckboxWidget( string id );

        void render();

        void enable() { m_isActive = true; }
        void disable() { m_isActive = false; }
        bool isActive() { return m_isActive; }

        string getName() { return m_name; }
    };



}