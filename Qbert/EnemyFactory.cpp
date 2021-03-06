#include "MiniginPCH.h"
#include "EnemyFactory.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "SlickOrSamComponent.h"
#include "UggOrWrongWayComponent.h"
#include "CoilyComponent.h"

dae::GameObject* qbert::EnemyFactory::CreateEnemy(EnemyComponent::EnemyType type, QbertGame* qbertGame, bool isControlledByPlayer)
{
	dae::GameObject* enemy = new dae::GameObject();
	MovementComponent* movementComponent;
	dae::RenderComponent* renderComponent;

	CoilyComponent* CoilyComponent;
	UggOrWrongWayComponent* uggComponent;
	UggOrWrongWayComponent* wrongwayComponent;
	SlickOrSamComponent* slickComponent;
	SlickOrSamComponent* samComponent;
	switch (type)
	{
	case EnemyComponent::EnemyType::COILY:
		movementComponent = new MovementComponent(enemy, qbertGame, { 0,3 });
		enemy->AddComponent(movementComponent);

		CoilyComponent = new qbert::CoilyComponent(enemy, type, movementComponent, qbertGame->GetQbert(), qbertGame, isControlledByPlayer);
		enemy->AddComponent(CoilyComponent);

		renderComponent = new dae::RenderComponent(enemy);
		enemy->AddComponent(renderComponent);
		renderComponent->SetTexture("../Data/CoilyEgg.png");
		renderComponent->SetWidth(32);
		renderComponent->SetHeight(26);
		renderComponent->SetPosition(20, -15);
		break;
	case EnemyComponent::EnemyType::UGG:
		movementComponent = new MovementComponent(enemy, qbertGame, { 6,6 });
		enemy->AddComponent(movementComponent);

		uggComponent = new UggOrWrongWayComponent(enemy, EnemyComponent::EnemyType::UGG, movementComponent);
		enemy->AddComponent(uggComponent);

		renderComponent = new dae::RenderComponent(enemy);
		enemy->AddComponent(renderComponent);
		renderComponent->SetTexture("../Data/Ugg.png");
		renderComponent->SetWidth(34);
		renderComponent->SetHeight(32);
		renderComponent->SetPosition(45, 35);
		break;
	case EnemyComponent::EnemyType::WRONGWAY:
		movementComponent = new MovementComponent(enemy, qbertGame, { 6,0 });
		enemy->AddComponent(movementComponent);

		wrongwayComponent = new UggOrWrongWayComponent(enemy, EnemyComponent::EnemyType::WRONGWAY, movementComponent);
		enemy->AddComponent(wrongwayComponent);

		renderComponent = new dae::RenderComponent(enemy);
		enemy->AddComponent(renderComponent);
		renderComponent->SetTexture("../Data/Wrong-Way.png");
		renderComponent->SetWidth(34);
		renderComponent->SetHeight(32);
		renderComponent->SetPosition(-10, 35);
		break;

	case EnemyComponent::EnemyType::SLICK:
		movementComponent = new MovementComponent(enemy, qbertGame, { 0,3 });
		enemy->AddComponent(movementComponent);

		slickComponent = new SlickOrSamComponent(enemy, EnemyComponent::EnemyType::SLICK, movementComponent);
		enemy->AddComponent(slickComponent);

		renderComponent = new dae::RenderComponent(enemy);
		enemy->AddComponent(renderComponent);
		renderComponent->SetTexture("../Data/Slick.png");
		renderComponent->SetWidth(24);
		renderComponent->SetHeight(32);
		renderComponent->SetPosition(20, -15);
		break;
	case EnemyComponent::EnemyType::SAM:
		movementComponent = new MovementComponent(enemy, qbertGame, { 0,3 });
		enemy->AddComponent(movementComponent);

		samComponent = new SlickOrSamComponent(enemy, EnemyComponent::EnemyType::SAM, movementComponent);
		enemy->AddComponent(samComponent);

		renderComponent = new dae::RenderComponent(enemy);
		enemy->AddComponent(renderComponent);
		renderComponent->SetTexture("../Data/Sam.png");
		renderComponent->SetWidth(22);
		renderComponent->SetHeight(32);
		renderComponent->SetPosition(20, -15);
		break;
	}
	return enemy;
}