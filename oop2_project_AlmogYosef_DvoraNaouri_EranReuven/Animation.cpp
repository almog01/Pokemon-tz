#include "Animation.h"



Animation::Animation(Collider & collider, const Texture & texture, Vector2u imageCount, float speed)
	: m_collider(collider), m_imageCount(imageCount), m_speed(speed), m_totalTime(0.f),
	m_switchTime(50.f), m_currImage(Vector2u(0, 0)), m_forward(true)
{
	// calculate the width and height of the actual image
	uvRect.width = texture.getSize().x / imageCount.x;
	uvRect.height = texture.getSize().y / imageCount.y;
}

Animation::~Animation()
{
}

void Animation::addAnimation(const string & name, unsigned row)
{
	m_animations[name] = row;
}

void Animation::play(const string & name)
{
	m_currImage.y = m_animations[name];		// select the animation by its row
	m_totalTime += m_speed;		// add to the total time the animation is playing

	if (m_totalTime >= m_switchTime)	// switch image when total played time is larger than switch time
	{
		m_totalTime -= m_switchTime;
		if (m_currImage.x == m_imageCount.x - 1)
			m_forward = false;
		else if (m_currImage.x == 0)
			m_forward = true;

		m_currImage.x = m_forward ? m_currImage.x + 1 : m_currImage.x - 1;
	}
	// calculate the new texture rect to display
	uvRect.left = m_currImage.x * uvRect.width;	
	uvRect.top = m_currImage.y * uvRect.height;
	m_collider.setTextureRect(uvRect);
}
