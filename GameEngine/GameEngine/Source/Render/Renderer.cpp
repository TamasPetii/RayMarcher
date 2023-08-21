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

	mSpheres.push_back(Sphere(glm::vec3(1, 0, 0), glm::vec3(0, 2, 0), 1));
	mSpheres.push_back(Sphere(glm::vec3(0, 1, 0), glm::vec3(3, 3.5, -5), 2.5));
	mSpheres.push_back(Sphere(glm::vec3(0, 0, 1), glm::vec3(-10, 6, 3), 5));
	mToruses.push_back(Torus(glm::vec3(1, 0, 1), glm::vec3(0, 10, 0), 1, 0.2));
}

Renderer::~Renderer()
{
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
}

void Renderer::PostRender()
{

}

void Renderer::RenderScene(IFrameBufferObject* frameBuffer, Program* shaderProgram)
{
	mSceneFrameBuffer->Bind();
	mSceneProgram->Bind();

	for (int i = 0; i < mSpheres.size(); ++i)
	{
		mSceneProgram->SetUniform("uSpheres[" + std::to_string(i) + "].color", mSpheres[i].GetColor());
		mSceneProgram->SetUniform("uSpheres[" + std::to_string(i) + "].origin", mSpheres[i].GetOrigin());
		mSceneProgram->SetUniform("uSpheres[" + std::to_string(i) + "].radius", mSpheres[i].GetRadius());
	}
	mSceneProgram->SetUniform("uSphereNumber", (int)mSpheres.size());

	for (int i = 0; i < mToruses.size(); ++i)
	{
		mSceneProgram->SetUniform("uToruses[" + std::to_string(i) + "].color", mToruses[i].GetColor());
		mSceneProgram->SetUniform("uToruses[" + std::to_string(i) + "].origin", mToruses[i].GetOrigin());
		mSceneProgram->SetUniform("uToruses[" + std::to_string(i) + "].radiusPrimary", mToruses[i].GetRadiusPrimary());
		mSceneProgram->SetUniform("uToruses[" + std::to_string(i) + "].radiusSecondary", mToruses[i].GetRadiusSecondary());
	}
	mSceneProgram->SetUniform("uTorusNumber", (int)mToruses.size());

	mSceneProgram->SetUniform("uLightPos", mLightPos);
	mSceneProgram->SetUniform("uViewProjMatrix", mCamera->GetViewProjMatrix());
	mCanvas->Draw();

	mSceneProgram->UnBind();
	mSceneFrameBuffer->UnBind();
}
