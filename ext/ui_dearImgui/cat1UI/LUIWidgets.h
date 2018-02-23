
#pragma once

#include "LUICommon.h"

using namespace std;

namespace cat1UI
{

    namespace widgetType
    {
        enum _widgetType
        {
            TEXT,
            BUTTON,
            CHECKBOX,
            SLIDER,
            COMBOBOX
        };
    }

    class LUIWidget
    {
        protected :

        widgetType::_widgetType m_type;
        string m_id;
        int m_order;

        public :

        LUIWidget( string id, int order );
        ~LUIWidget();

        virtual void render() = 0;

        int getOrder() { return m_order; }
        widgetType::_widgetType getType() { return m_type; }
    };


    class LUIText : public LUIWidget
    {

        private :

        string m_text;

        public :

        LUIText( string id, int order, string text );
        ~LUIText();

        void render() override;

        void setText( string text ) { m_text = text; }
        string getText() { return m_text; }
    };

    class LUIButton : public LUIWidget
    {

        private :

        string m_buttonName;
        bool m_buttonState;

        public :

        LUIButton( string id, int order, string buttonName );
        ~LUIButton();

        void render() override;

        void setButtonState( bool buttonState ) { m_buttonState = buttonState; }
        bool getButtonState() { return m_buttonState; }

        string getButtonName() { return m_buttonName; }

    };

    class LUICheckbox : public LUIWidget
    {

        private :

        string m_checkboxName;
        bool m_checkboxState;

        public :

        LUICheckbox( string id, int order, string checkboxName, bool initialState );
        ~LUICheckbox();

        void render() override;

        void setCheckboxState( bool checkboxState ) { m_checkboxState = checkboxState; }
        bool getCheckboxState() { return m_checkboxState; }

        string getCheckboxName() { return m_checkboxName; }
    };

    class LUISlider : public LUIWidget
    {

        private :

        float m_sliderCurrentValue;
        float m_sliderMinValue;
        float m_sliderMaxValue;
        string m_sliderName;

        public :

        LUISlider( string id, int order, float minValue, float maxValue, float currentValue, string sliderName );
        ~LUISlider();

        void render() override;

        float getSliderValue() { return m_sliderCurrentValue; }
        string getSliderName() { return m_sliderName; }

    };

    class LUIComboBox : public LUIWidget
    {
        private:

        vector< string > m_comboBoxOptions;
        string m_comboBoxName;
        int m_currentOptionIndx;
        string m_currentOptionStr;

        bool m_hasChangedValue;

        public:

        LUIComboBox( string id, int order, string comboBoxName, const vector< string >& options );
        ~LUIComboBox();

        void render() override;

        int getCurrentOptionIndx() { return m_currentOptionIndx; }
        string getCurrentOptionStr() { return m_currentOptionStr; }
        string getComboBoxName() { return m_comboBoxName; }

        bool hasChangedValue() { return m_hasChangedValue; }
    };

    bool comparatorWidgetsOrder( LUIWidget* w1, LUIWidget* w2 );

}