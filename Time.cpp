#include "Time.hpp"

Time::Time()
{
	m_Start = m_Clock.now();
	m_LastFrame = m_Clock.now();
	m_DeltaTime = 0;
}

void Time::OnLoop()
{
	m_DeltaTime = Seconds(m_Clock.now() - m_LastFrame);
	m_LastFrame = m_Clock.now();
}
