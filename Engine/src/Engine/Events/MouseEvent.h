#pragma once

#include "Event.h"

#include <sstream>

namespace Engine {

	class EG_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			:m_MouseX(x), m_MouseY(y) {}

		inline float GetX() { return m_MouseX; }
		inline float GetY() { return m_MouseY; }

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << "," << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX, m_MouseY;
	};

	class EG_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float x, float y)
			:m_XOffset(x), m_YOffset(y) {}

		inline float GetXOffset() { return m_XOffset; }
		inline float GetYOffset() { return m_YOffset; }

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << "," << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_XOffset, m_YOffset;
	};

	class EG_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int button)
			:m_Button(button) {}
		int m_Button;
	};

	class EG_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		//MouseButtonPressedEvent(int button, int repeatCount)
		//	:MouseButtonEvent(button), m_RepeatCount(repeatCount) {}
		MouseButtonPressedEvent(int button)
			:MouseButtonEvent(button) {}

		//inline int GetRepeatCount() { return m_RepeatCount; }

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
			//protected:
			//	int m_RepeatCount;
	};

	class EG_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			:MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}