#pragma once
#include "UIScreen.h"

class HUD : public UIScreen
{
public:
	HUD();
	~HUD();

	void update(float dt) override;
	void draw(class Shader& shader) override;

	void addTargetComponent(class TargetComponent* tc);
	void removeTargetComponent(class TargetComponent* tc);


protected:
	void updateCrosshair(float deltaTime);
	void updateRadar(float deltaTime);

	class Texture* crosshair;
	class Texture* crosshairEnemy;
	class Texture* radar;
	class Texture* blipTex;
	class Texture* radarArrow;

	std::vector<class TargetComponent*> targetComponents;
	bool isTargetingEnemy;
	vector<Vector2> blips;
	float radarRange;
	float radarRadius;
};

