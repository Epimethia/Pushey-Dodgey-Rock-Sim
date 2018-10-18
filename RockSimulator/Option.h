#pragma once
#include "Utilities.h"
#include "TextLabel.h"
#include <memory>

struct Option
{
	std::shared_ptr<TextLabel> OptionText;
	glm::vec2 m_vUnselectedPos;
	glm::vec2 m_vSelectedPos;
	bool m_bSelected;

	Option(std::string _Text, glm::vec2 _UnselectedPos, glm::vec2 _SelectedPos)
	{
		m_vUnselectedPos = _UnselectedPos;
		m_vSelectedPos = _SelectedPos;
		OptionText = std::make_shared<TextLabel>(_Text, "Resources/Fonts/Thirteen-Pixel-Fonts.ttf", m_vUnselectedPos);
		OptionText->SetScale(1.2f);
		m_bSelected = false;
	}

	void Render()
	{
		OptionText->Render();
	}

	void ToggleActive()
	{
		m_bSelected = !m_bSelected;

		if (m_bSelected)
		{
			OptionText->SetPosition(m_vSelectedPos);
			OptionText->SetScale(1.6f);
		}
		else
		{
			OptionText->SetPosition(m_vUnselectedPos);
			OptionText->SetScale(1.2f);
		}
	}
};