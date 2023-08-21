#pragma once
#include "../Engine/Engine.h"
#include "Entity/Entity.h"
#include "Canvas.h"
#include "Sphere.h"
#include "Torus.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Render();
	void Update();

	inline IFrameBufferObject* GetSceneFrameBuffer() const { return mSceneFrameBuffer; }
	inline Camera* GetCamera() const { return mCamera; }
private:
	void PreRender();
	void PostRender();
	void RenderScene(IFrameBufferObject* frameBuffer, Program* shaderProgram);

	Canvas* mCanvas;
	Camera* mCamera;
	Program* mSceneProgram;
	IFrameBufferObject* mSceneFrameBuffer;

	std::vector<Sphere> mSpheres;
	std::vector<Torus> mToruses;
	glm::vec3 mLightPos;
};