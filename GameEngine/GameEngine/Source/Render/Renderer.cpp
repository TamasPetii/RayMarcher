#include "Renderer.h"

Renderer::Renderer()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glClearColor(0.2f, 0.2f, 0.2f, 1.f);

	mCamera = new Camera(1200, 800);
	mSceneFrameBuffer = new FrameBufferObject<FBO_ColorTexture>();
	mSceneProgram = new Program(
		{
			Shader(GL_VERTEX_SHADER, "Source/Shader/RayMarch.vert"),
			Shader(GL_FRAGMENT_SHADER, "Source/Shader/RayMarch.frag")
		},
		{
			ShaderLayout(0, "vert_position"),
		}
	);
}

Renderer::~Renderer()
{
	//Delete Entities

	delete mCamera;
	delete mSceneFrameBuffer;
	delete mSceneProgram;
	Texture2D::ClearTextures();
}


void Renderer::Render()
{
	Renderer::PreRender();
	Renderer::RenderScene(mSceneFrameBuffer, mSceneProgram);
	Renderer::PostRender();
}

void Renderer::Update()
{
	static int nbFrames = 0;
	static double lastTime = glfwGetTime();

	double currentTime = glfwGetTime();

	lastTime = currentTime;
}

void Renderer::PreRender()
{
	mSceneFrameBuffer->ClearBuffers();
}

void Renderer::PostRender()
{

}

void Renderer::RenderScene(IFrameBufferObject* frameBuffer, Program* shaderProgram)
{

}
