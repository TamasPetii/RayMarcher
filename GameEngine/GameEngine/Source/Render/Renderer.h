#pragma once
#include "../Engine/Engine.h"
#include "Entity/Entity.h"
#include <unordered_set>
#include <set>
#include <map>

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

	Camera* mCamera;
	Program* mSceneProgram;
	IFrameBufferObject* mSceneFrameBuffer;
};