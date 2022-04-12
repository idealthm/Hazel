#include "Planet.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.h"

PlanetLayer::CameraControl PlanetLayer::m_Control = PlanetLayer::CameraControl::None;
PlanetLayer::CameraControl PlanetLayer::m_ViewControl = PlanetLayer::CameraControl::None;

PlanetLayer::PlanetLayer()
	: Layer("Planet"), m_CameraController(16.0f / 9.0f), m_EarthPosition(1.0f, 0.0f, 0.0f), m_MoonPosition(0.3f, 0.0f, 0.0f), m_SunPosition(0.0f, 0.0f, 0.0f), m_SpacecraftPosition(0.0f, 0.0f, 0.0f)
{
	//≥ı ºªØ∂•µ„

	std::vector<float> verticesEarth = GetSphereVertex(0.3f, 30, 30);
	std::vector<float> verticesBox = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	std::vector<float> verticesCircle = GetCircleVertex(0.3f, 30);
	m_VertexBuffer = Hazel::VertexBuffer::Create(verticesEarth.data(), sizeof(float)*verticesEarth.size());
	Hazel::BufferLayout layout = {
		{Hazel::ShaderDataType::Float3, "a_Position"}
	};
	m_VertexBuffer->SetLayout(layout);
	m_VertexArray = Hazel::VertexArray::Create();
	m_VertexArray->AddVertexBuffer(m_VertexBuffer);

	std::vector<uint32_t> indicesEarth = GetSphereIndex(30, 30);
	m_IndexBuffer=Hazel::IndexBuffer::Create(indicesEarth.data(), (uint32_t)indicesEarth.size());
	m_VertexArray->SetIndexBuffer(m_IndexBuffer);
	
	Hazel::Ref<Hazel::VertexBuffer> BVB;
	BVB=Hazel::VertexBuffer::Create(verticesBox.data(), sizeof(float) * verticesBox.size());
	Hazel::BufferLayout Boxlayout = {
		{Hazel::ShaderDataType::Float3, "a_Position"},
		{Hazel::ShaderDataType::Float2, "a_TexCoood"}
	};
	BVB->SetLayout(Boxlayout);

	m_BoxArray = Hazel::VertexArray::Create();
	m_BoxArray->AddVertexBuffer(BVB);
	
	std::vector<uint32_t> BoxIndices;
	for (int i = 0; i < verticesBox.size() / 5; i++)
		BoxIndices.push_back(i);
	Hazel::Ref<Hazel::IndexBuffer> BIB;
	BIB=Hazel::IndexBuffer::Create(BoxIndices.data(), (uint32_t)BoxIndices.size());
	m_BoxArray->SetIndexBuffer(BIB);

	// -------------------Circle------------------------------------------
	Hazel::Ref<Hazel::VertexBuffer> CVB;
	CVB=Hazel::VertexBuffer::Create(verticesCircle.data(), sizeof(float) * verticesCircle.size());
	CVB->SetLayout(layout);

	m_CAO=Hazel::VertexArray::Create();
	m_CAO->AddVertexBuffer(CVB);

	std::vector<uint32_t> CircleIndices;
	for (int i = 0; i < verticesCircle.size() / 3; i++)
		CircleIndices.push_back(i);
	CircleIndices.push_back(0);
	Hazel::Ref<Hazel::IndexBuffer> CIB;
	CIB = Hazel::IndexBuffer::Create(CircleIndices.data(), (uint32_t)CircleIndices.size());
	m_CAO->SetIndexBuffer(CIB);
	// -------------------Circle---------------------------------------------

	m_Shaders.Load("Assets/Shaders/Planet.glsl");
	m_Shaders.Load("Assets/Shaders/SpaceBox.glsl");

	m_Texture = Hazel::Texture2D::Create("Assets/Textures/Space.jpg");
	auto& shader = m_Shaders.Get("SpaceBox");
	std::dynamic_pointer_cast<Hazel::OpenGLShader>(shader)->Bind();
	std::dynamic_pointer_cast<Hazel::OpenGLShader>(shader)->UploadUniformInt("u_Texture", 0);
}

void PlanetLayer::OnUpdate(Hazel::Timestep ts)
{
	if (m_ViewControl == CameraControl::None)
	{
		m_CameraController.OnUpdate(ts);
	}
	m_EarthRotation += ts * m_RotateSpeed;
	m_MoonRotation += ts * m_RotateSpeed * 12.0f;
	m_SpacecraftRotation += ts * m_RotateSpeed * 18.0f;
	m_EarthPosition.x = m_SunToEarthLength * cos(glm::radians(m_EarthRotation));
	m_EarthPosition.y = m_SunToEarthLength * sin(glm::radians(m_EarthRotation));
	m_MoonPosition.x = m_EarthToMoonLength * cos(glm::radians(m_MoonRotation));
	m_MoonPosition.y = m_EarthToMoonLength * sin(glm::radians(m_MoonRotation));
	m_SpacecraftPosition.x = 1.5f*m_EarthToMoonLength * cos(glm::radians(m_SpacecraftRotation));
	m_SpacecraftPosition.y = 1.5f*m_EarthToMoonLength * sin(glm::radians(m_SpacecraftRotation));

	
	Hazel::RenderCommand::SetClearColor({ 0.2f, 0.1f, 0.3f, 1.0f });

	Hazel::RenderCommand::Clear();

	glm::mat4 Stransform = glm::translate(glm::mat4(1.0f), m_SunPosition);
	glm::mat4 Etransform = glm::translate(Stransform, m_EarthPosition);
	glm::mat4 Mtransform = glm::translate(Etransform, m_MoonPosition);

	static glm::mat4 Ptransform = glm::mat4(1.0f);
	switch (m_Control)
	{
		case PlanetLayer::CameraControl::Sun:	Ptransform = Stransform; break;
		case PlanetLayer::CameraControl::Earth:	Ptransform = Etransform; break;
		case PlanetLayer::CameraControl::Moon:	Ptransform = Mtransform; break;
	}
	if (m_ViewControl != CameraControl::None)m_CameraController.SetPosition(glm::translate(glm::mat4(1.0f), {0.0f,0.0f,0.1f}) * Ptransform * glm::vec4(m_SpacecraftPosition, 1.0f));

	
	Hazel::Renderer::BeginScene(m_CameraController.GetCamera());
	auto& BoxShader = m_Shaders.Get("SpaceBox");
	auto& PlanetShader = m_Shaders.Get("Planet");
	m_Texture->Bind();
	Hazel::Renderer::Submit(Hazel::RendererType::TRIANGLES, BoxShader, m_BoxArray, glm::scale(glm::mat4(1.0f),glm::vec3(20.f)));

	PlanetShader->Bind();
	std::dynamic_pointer_cast<Hazel::OpenGLShader>(PlanetShader)->UploadUniformFloat4("u_color", {0.8f,0.2f,0.3f,1.0f});
	Hazel::Renderer::Submit(Hazel::RendererType::TRIANGLES, PlanetShader, m_VertexArray, Stransform);

	std::dynamic_pointer_cast<Hazel::OpenGLShader>(PlanetShader)->UploadUniformFloat4("u_color", { 0.1f,0.2f,0.6f,1.0f });
	Hazel::Renderer::Submit(Hazel::RendererType::TRIANGLES, PlanetShader, m_VertexArray, glm::scale(Etransform, glm::vec3(0.35f)));

	Hazel::Renderer::Submit(Hazel::RendererType::LINE_STRIP, PlanetShader, m_CAO, Stransform * glm::scale(Stransform, glm::vec3(1.5f)));
	
	std::dynamic_pointer_cast<Hazel::OpenGLShader>(PlanetShader)->UploadUniformFloat4("u_color", { 0.8f,0.7f,0.9f,1.0f });
	Hazel::Renderer::Submit(Hazel::RendererType::TRIANGLES, PlanetShader, m_VertexArray, glm::scale(Mtransform, glm::vec3(0.15f)));
	
	std::dynamic_pointer_cast<Hazel::OpenGLShader>(PlanetShader)->UploadUniformFloat4("u_color", { 0.4f,0.9f,0.3f,1.0f });
	Hazel::Renderer::Submit(Hazel::RendererType::TRIANGLES, PlanetShader, m_VertexArray, glm::scale(glm::translate(Ptransform , m_SpacecraftPosition), glm::vec3(0.05f)) );

	//std::cout << m_BoxArray->GetIndexBuffer()->GetCount() << std::endl;
	Hazel::Renderer::EndScene();
}

void PlanetLayer::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
	Hazel::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Hazel::KeyPressedEvent>(HZ_BIND_EVENT_FN(PlanetLayer::OnKeyPressedEvent));
}

bool PlanetLayer::OnKeyPressedEvent(Hazel::KeyPressedEvent& e)
{
	if (Hazel::Input::IsKeyPressed(HZ_KEY_U))
		m_ViewControl = CameraControl::None;
	if (Hazel::Input::IsKeyPressed(HZ_KEY_I))
		m_ViewControl = CameraControl::Sun , m_Control = CameraControl::Sun;
	if (Hazel::Input::IsKeyPressed(HZ_KEY_O))
		m_ViewControl = CameraControl::Earth, m_Control = CameraControl::Earth;
	if (Hazel::Input::IsKeyPressed(HZ_KEY_P))
		m_ViewControl = CameraControl::Moon, m_Control = CameraControl::Moon;
	return true;
}

void PlanetLayer::OnImGuiRender()
{
}

std::vector<float> PlanetLayer::GetCircleVertex(float radius, uint32_t slices)
{
	HZ_CORE_ASSERT(slices >= 3, "Too less Vertex");
	std::vector<float> result;

	for (uint32_t i = 0; i < slices; i++)
	{
		result.push_back(radius * cos(glm::radians(360.0f * i / slices)));
		result.push_back(radius * sin(glm::radians(360.0f * i / slices)));
		result.push_back(0.0f);
	}
	return result;
}

std::vector<uint32_t> PlanetLayer::GetCircleIndex(uint32_t slices)
{
	HZ_CORE_ASSERT(slices >= 3, "Too less Vertex");
	std::vector<uint32_t> result;
	//result.resize(slices*3);
	for (uint32_t i = 0; i < slices ; i++)
	{
		result.push_back(0);
		result.push_back(i+1);
		result.push_back(i+2);
	}
	result.push_back(0);
	result.push_back(slices);
	result.push_back(1);
	return result;
}


std::vector<float> PlanetLayer::GetSphereVertex(float radius, uint32_t slices, uint32_t stacks)
{
	HZ_CORE_ASSERT(slices >= 3, "Too less Vertex");
	HZ_CORE_ASSERT(stacks >= 3, "Too less Vertex");
	std::vector<float> result;
	for (uint32_t i = 0; i <= stacks; i++) {
		for (uint32_t j = 0; j < slices; j++) {
			float zPos = radius - (radius * 2 * i / stacks);
			float curRadius = sqrt(radius * radius - zPos * zPos);
			result.push_back(curRadius * cos(glm::radians(360.0f * j / slices)));		// x
			result.push_back(curRadius * sin(glm::radians(360.0f * j / slices)));		// y
			result.push_back(zPos);														// z
			if (i == 0u || i == stacks)break;
		}
	}
	return result;
}

std::vector<uint32_t> PlanetLayer::GetSphereIndex(uint32_t slices, uint32_t stacks)
{
	HZ_CORE_ASSERT(slices >= 3, "Too less Vertex");
	HZ_CORE_ASSERT(stacks >= 3, "Too less Vertex");
	std::vector<uint32_t> result;
	uint32_t nowPos = 1;
	for (uint32_t i = 1; i < stacks; i++) {
		for (uint32_t j = 1; j <= slices; j++) {
			if (i == 1) {
				//nowPos++;
				 //up Triangle
				result.push_back(0u);
				result.push_back(nowPos++);
				result.push_back(j != slices ? nowPos : nowPos - slices);
				// down Triangle
				result.push_back(1 + (slices) * (stacks - 1));
				result.push_back(j + (slices) * (stacks - 2));
				result.push_back((j != slices ? j + 1 : 1) + (slices) * (stacks - 2));
			}
			else {
				// left up
				result.push_back(nowPos - (j != 1 ? slices + 1: 1));			
				result.push_back(nowPos - slices);
				result.push_back(nowPos );
				// right down
				result.push_back(nowPos - slices);
				result.push_back(nowPos ++);	
				result.push_back(j != slices ? nowPos : nowPos - slices );
			}
		}
	}
	return result;
}