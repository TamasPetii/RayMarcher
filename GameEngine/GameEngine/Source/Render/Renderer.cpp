#include "Renderer.h"

Renderer::Renderer()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glClearColor(0.2f, 0.2f, 0.2f, 1.f);

	mCanvas = new Canvas();
	mCamera = new Camera(1200, 800);
	mAntiAliasingFrameBuffer = new FrameBufferObject<FBO_AntiAliasingColorTexture>();
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

	mShapes.push_back(new Sphere(glm::vec3(1, 0, 0), glm::vec3(0, 2, 0), 1));
	mShapes.push_back(new Sphere(glm::vec3(0, 1, 0), glm::vec3(3, 3.5, -5), 2.5));
	mShapes.push_back(new Sphere(glm::vec3(0, 0, 1), glm::vec3(-10, 6, 3), 5));
	mShapes.push_back(new Torus(glm::vec3(1, 0, 1), glm::vec3(0, 10, 0), 1, 0.2));
	mShapes.push_back(new Cube(glm::vec3(0.1, 0.4, 0.5), glm::vec3(0, 5, 10), glm::vec3(5,5,1)));
	mShapes.push_back(new Capsule(glm::vec3(0.4, 0.2, 0.5), glm::vec3(0, 5, -10), glm::vec3(0, 10, -10), 1));
}

Renderer::~Renderer()
{
	for (auto shape : mShapes)
	{
		delete shape;
	}

	delete mCanvas;
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
	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();

	mLightPos = glm::vec3(5 * cos(lastTime / 10 * 2 * 3.1415), 20, 5 * sin(lastTime / 10 * 2 * 3.1415));

	lastTime = currentTime;
}

void Renderer::PreRender()
{
	mSceneFrameBuffer->ClearBuffers();

	for (auto shape : mShapes)
	{
		shape->AttachToShader(mSceneProgram);
	}
}

void Renderer::PostRender()
{
	Cube::Index = 0;
	Sphere::Index = 0;
	Torus::Index = 0;
	Capsule::Index = 0;

	/*
	unsigned int width = mAntiAliasingFrameBuffer->GetWidth();
	unsigned int height = mAntiAliasingFrameBuffer->GetHeight();
	glBindFramebuffer(GL_READ_FRAMEBUFFER, mAntiAliasingFrameBuffer->GetFrameBufferId());
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mSceneFrameBuffer->GetFrameBufferId());
	glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	*/
}

void Renderer::RenderScene(IFrameBufferObject* frameBuffer, Program* shaderProgram)
{
	frameBuffer->Bind();
	shaderProgram->Bind();
	shaderProgram->SetUniform("uLightPos", mLightPos);
	shaderProgram->SetUniform("uViewProjMatrix", mCamera->GetViewProjMatrix());

	mCanvas->Draw();

	shaderProgram->UnBind();
	frameBuffer->UnBind();
}
