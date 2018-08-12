#pragma once
#include <vector>
#include <memory>

class Camera;
class Sprite;
class LevelOne	
{
public:
	LevelOne();
	~LevelOne();

	void InitializeObjects();
	void RenderObjects();

private:
	std::vector<std::shared_ptr<Sprite>> m_PlayerVec;
	std::shared_ptr<Sprite> m_Background;
	std::shared_ptr<Camera> m_Camera;
};

