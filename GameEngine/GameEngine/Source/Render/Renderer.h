#pragma once
#include "../Engine/Engine.h"
#include "Entity/Entity.h"
#include "Canvas.h"
#include "Shape/Sphere.h"
#include "Shape/Torus.h"
#include "Shape/Cube.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Render();
	void Update();

	inline IFrameBufferObject* GetSceneFrameBuffer() const { return mSceneFrameBuffer; }
	inline IFrameBufferObject* GetAntiAliasingFrameBuffer() const { return mAntiAliasingFrameBuffer; }
	inline Camera* GetCamera() const { return mCamera; }
private:
	void PreRender();
	void PostRender();
	void RenderScene(IFrameBufferObject* frameBuffer, Program* shaderProgram);

	Canvas* mCanvas;
	Camera* mCamera;
	Program* mSceneProgram;
	IFrameBufferObject* mAntiAliasingFrameBuffer;
	IFrameBufferObject* mSceneFrameBuffer;

	std::vector<Shape*> mShapes;
	glm::vec3 mLightPos;
};