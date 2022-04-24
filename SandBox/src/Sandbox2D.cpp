#include "Sandbox2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.h"
#include "ImGui/imgui.h"

Sanbox2D::Sanbox2D()
	: Layer("Sanbox2D"), m_CameraController(1200.0f / 720.0f)
{
}

void Sanbox2D::OnAttach()
{
	m_Texture = Hazel::Texture2D::Create("Assets/Textures/back.jpg");

    Hazel::FrameBufferSpecification spec;
    spec.Width = 1280;
    spec.Height = 720;
    m_FrameBuffer = Hazel::FrameBuffer::Create(spec);

}

void Sanbox2D::OnDetach()
{
}

void Sanbox2D::OnUpdate(Hazel::Timestep ts)
{
	HZ_PROFILE_FUNCTION();

	// Update
	{
		HZ_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts); 
	}

	Hazel::Renderer2D::ResetStats();
	{
		HZ_PROFILE_SCOPE("RenderCommand::OnUpdate");
        m_FrameBuffer->Bind();
		Hazel::RenderCommand::SetClearColor({ 0.2f, 0.1f, 0.3f, 1.0f });
		Hazel::RenderCommand::Clear();
	}
	{
		HZ_PROFILE_SCOPE("Renderer2D::BeginScene");
		Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Hazel::Renderer2D::DrawQuad({ -0.5f, -0.4f }, { 0.8f, 0.3f }, { 0.2f, 0.1f, 0.8f, 1.0f });
		Hazel::Renderer2D::DrawQuad({ 0.3f, 0.3f }, { 0.4f, 0.6f }, { 0.5f, 0.3f, 0.4f, 1.0f });
		Hazel::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture);
		Hazel::Renderer2D::EndScene();
        m_FrameBuffer->UnBind();
	}
}

void Sanbox2D::OnEvent(Hazel::Event& event)
{
	m_CameraController.OnEvent(event);

}

void Sanbox2D::OnImGuiRender()
{
    static bool dockspaceOpen = true;

    if (dockspaceOpen)
    {
        ImGui::Begin("Setting");
        auto stats = Hazel::Renderer2D::GetStats();
        ImGui::Text("Renderer2D Stats:");
        ImGui::Text("Draw Calls: %d", stats.DrawCalls);
        ImGui::Text("Quads: %d", stats.QuadCount);
        ImGui::Text("Vertics: %d", stats.GettotalVertexCount());
        ImGui::Text("Indices: %d", stats.GettotalIndexCount());

        uint32_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
        ImGui::Image((void*)textureID, ImVec2{ 1280, 720 });
        ImGui::End();
    }
    else {
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
                ImGui::MenuItem("Padding", NULL, &opt_padding);
                ImGui::Separator();

                if (ImGui::MenuItem("Exit")) Hazel::Application::Get().Close();
                ImGui::Separator();

                if (ImGui::MenuItem("Close", NULL, false)) dockspaceOpen = false;
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::End();
    }
}
