#include "MiniginPCH.h"
#include "RenderComponent.h"

#include <memory>

#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

dae::RenderComponent::RenderComponent(GameObject* pOwner)
	:Component(pOwner),
	m_CustomWidthHeight(false),
	m_Width(),
	m_Height()
{
}
void dae::RenderComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		const auto pos = GetOwner()->GetTransform()->GetPosition() + m_Transform.GetPosition();
		//Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
		if (m_CustomWidthHeight)
		{
			//Renderer::GetInstance().RenderTexture(*m_pTexture, m_Transform.GetPosition().x, m_Transform.GetPosition().y, m_Width, m_Height);
			Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y, m_Width, m_Height);
		}
		else
		{
			//Renderer::GetInstance().RenderTexture(*m_pTexture, m_Transform.GetPosition().x, m_Transform.GetPosition().y);
			Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
		}
	}
}
std::shared_ptr<dae::Texture2D> dae::RenderComponent::GetTexture() const
{
	return m_pTexture;
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}
void dae::RenderComponent::SetTexture(const std::shared_ptr<Texture2D>& pTexture)
{
	m_pTexture = pTexture;
}

void dae::RenderComponent::Update()
{
}
dae::RenderComponent::~RenderComponent()
{
	m_pTexture.reset();
}
void dae::RenderComponent::SetPosition(const float x, const float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
const glm::vec3& dae::RenderComponent::GetPosition() const
{
	return m_Transform.GetPosition();
}