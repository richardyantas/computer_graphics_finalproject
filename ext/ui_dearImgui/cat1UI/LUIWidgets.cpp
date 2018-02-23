
#include "LUIWidgets.h"


namespace cat1UI
{


    LUIWidget::LUIWidget( string id, int order )
    {
        m_id = id;
        m_order = order;
    }

    LUIWidget::~LUIWidget()
    {

    }

    LUIText::LUIText( string id, int order, string text )
        : LUIWidget( id, order )
    {
        m_text = text;
        m_type = widgetType::TEXT;
    }

    LUIText::~LUIText()
    {

    }

    void LUIText::render()
    {
        ImGui::Text( m_text.c_str() );
    }

    LUIButton::LUIButton( string id, int order, string buttonName )
        : LUIWidget( id, order )
    {
        m_buttonName = buttonName;
        m_buttonState = false;
        m_type = widgetType::BUTTON;
    }

    LUIButton::~LUIButton()
    {

    }

    void LUIButton::render()
    {
        m_buttonState = ImGui::Button( m_buttonName.c_str() );
    }

    LUICheckbox::LUICheckbox( string id, int order, string checkboxName, bool initialState )
        : LUIWidget( id, order )
    {
        m_checkboxName = checkboxName;
        m_checkboxState = initialState;
        m_type = widgetType::CHECKBOX;
    }

    LUICheckbox::~LUICheckbox()
    {

    }

    void LUICheckbox::render()
    {
        ImGui::Checkbox( m_checkboxName.c_str(), &m_checkboxState );
    }

    LUISlider::LUISlider( string id, int order, float minValue, float maxValue, float currentValue, string sliderName )
        : LUIWidget( id, order )
    {
        m_sliderMinValue = minValue;
        m_sliderMaxValue = maxValue;
        m_sliderCurrentValue = currentValue;

        m_sliderName = sliderName;
        m_type = widgetType::SLIDER;
    }

    LUISlider::~LUISlider()
    {

    }

    void LUISlider::render()
    {
        ImGui::SliderFloat( m_sliderName.c_str(), 
                            &m_sliderCurrentValue, 
                            m_sliderMinValue, 
                            m_sliderMaxValue );    
    }

    LUIComboBox::LUIComboBox( string id, int order, string comboBoxName, const vector< string >& options )
        : LUIWidget( id, order )
    {
        m_comboBoxName = comboBoxName;
        m_comboBoxOptions = options;
        m_currentOptionIndx = 0;
        m_currentOptionStr = m_comboBoxOptions[0];
        m_hasChangedValue = false;

        m_type = widgetType::COMBOBOX;
    }

    LUIComboBox::~LUIComboBox()
    {

    }

    void LUIComboBox::render()
    {
        if ( ImGui::BeginCombo( m_comboBoxName.c_str(), m_currentOptionStr.c_str() ) )
        {
            m_hasChangedValue = false;
            for ( int q = 0; q < m_comboBoxOptions.size(); q++ )
            {
                if ( ImGui::Selectable( m_comboBoxOptions[q].c_str(), q == m_currentOptionIndx ) )
                {
                    m_currentOptionIndx = q;
                    m_currentOptionStr = m_comboBoxOptions[q];
                    m_hasChangedValue = true;
                }
            }
            ImGui::EndCombo();
        }
    }

    bool comparatorWidgetsOrder( LUIWidget* w1, LUIWidget* w2 )
    {
        return w1->getOrder() < w2->getOrder();
    }
}