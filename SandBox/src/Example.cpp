#include "Example.h"
#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

ExampleLayer::ExampleLayer()
// 初始化相机横纵比 aspect ratio.
	:Layer("Example"), m_CameraController(16.0f / 9.0f,false)
{
	m_VertexArray.reset(Hazel::VertexArray::Create());

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f , 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f , 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f , 1.0f
	};

	m_VertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));
	Hazel::BufferLayout layout = {
		{Hazel::ShaderDataType::Float3, "a_Position"},
		{Hazel::ShaderDataType::Float4, "a_Color"}
	};

	m_VertexBuffer->SetLayout(layout);

	m_VertexArray->AddVertexBuffer(m_VertexBuffer);

	unsigned int indices[3] = { 0, 1, 2 };
	m_IndexBuffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

	m_VertexArray->SetIndexBuffer(m_IndexBuffer);

	// Texture 

	m_TVArray.reset(Hazel::VertexArray::Create());
	float texturevertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};
	Hazel::Ref<Hazel::VertexBuffer> TVB;
	TVB.reset(Hazel::VertexBuffer::Create(texturevertices, sizeof(texturevertices)));
	TVB->SetLayout({
		{ Hazel::ShaderDataType::Float3, "a_Position"},
		{ Hazel::ShaderDataType::Float2, "a_TexCoord"}
		});
	m_TVArray->AddVertexBuffer(TVB);
	uint32_t TIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Hazel::Ref<Hazel::IndexBuffer> TIB;
	TIB.reset(Hazel::IndexBuffer::Create(TIndices, sizeof(TIndices) / sizeof(uint32_t)));
	m_TVArray->SetIndexBuffer(TIB);

	m_Shaders.Load("Assets/Shaders/Triangle.glsl");
	m_Shaders.Load("Assets/Shaders/Texture.glsl");
	auto& TextureShader = m_Shaders.Get("Texture");
	m_Texture = Hazel::Texture2D::Create("Assets/Textures/back.jpg");
	//m_LogoTexture = Hazel::Texture2D::Create("Assets/Textures/LogoA.png");

	std::dynamic_pointer_cast<Hazel::OpenGLShader>(TextureShader)->Bind();
	std::dynamic_pointer_cast<Hazel::OpenGLShader>(TextureShader)->UploadUniformInt("u_Texture", 0);

}

void ExampleLayer::OnUpdate(Hazel::Timestep ts) {
	HZ_TRACE("Delta time : {0}s ({1}ms)", ts.GetSeconds(), ts.GetMillseconds());

	m_CameraController.OnUpdate(ts);
	//红、绿、蓝和 alpha 值，指定值范围均为[ 0.0f,1.0f ]
	//指定屏幕底色.
	//glClearColor(0.2f, 0.1f, 0.3f, 1);
	Hazel::RenderCommand::SetClearColor({ 0.2f, 0.1f, 0.3f, 1 });
	//将之前颜色全部清除.恢复为屏幕底色
	//GL_COLOR_BUFFER_BIT 指定为当前被激活为写操作的颜色缓存
	//glClear(GL_COLOR_BUFFER_BIT);
	Hazel::RenderCommand::Clear();

	glm::mat4 transform = glm::mat4(1.0f);

	Hazel::Renderer::BeginScene(m_CameraController.GetCamera());

	m_Texture->Bind();
	
	//Hazel::Renderer::Submit(m_Shader, m_VertexArray, transform);
	auto& TextureShader = m_Shaders.Get("Texture");
	Hazel::Renderer::Submit(Hazel::RendererType::TRIANGLES, TextureShader, m_TVArray, transform);
	//m_LogoTexture->Bind();
	//Hazel::Renderer::Submit(Hazel::RendererType::TRIANGLES, TextureShader, m_TVArray, transform);
	//std::cout << m_VertexArray->GetIndexBuffer()->GetCount() << std::endl;
	Hazel::Renderer::EndScene();

}

void ExampleLayer::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Setting");
	static glm::vec3 tmpcolortable = { 0.2f,0.3f,0.8f };
	ImGui::ColorEdit3("Square Color", glm::value_ptr(tmpcolortable));
	ImGui::End();
}