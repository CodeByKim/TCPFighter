#pragma once
#include "CommonLibrary.h"
#include "BaseComponent.h"
#include "Graphics.h"

class GameObject;
class Sprite;

class RenderComponent : public BaseComponent
{
public:
	RenderComponent(HWND hWnd, ScreenSize screenSize);
	~RenderComponent();

	void DrawSprite(Sprite* sprite, Position2D pos);

	void Update(std::vector<std::unique_ptr<GameObject>>& objects) override;
	eComponentType GetType() override;

private:
	//void CreateDibBuffer(int width, int height, int colorBit);
	//void ReleaseDibBuffer();

	Graphics mGraphics;
	//BITMAPINFO mDibInfo;
	//HWND mhWnd;
	//HDC mDC;

	//ScreenMemoryBuffer mScreenBuffer;
};

