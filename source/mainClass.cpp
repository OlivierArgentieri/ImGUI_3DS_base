
#include "mainClass.h"
#include "platform.h"
#include "imgui.h"

#include "licenses.h"
#include "log.h"
#include "fs.h"

MainClass::MainClass() : m_quit(false)
{}

void MainClass::draw()
{
	auto const &io    = ImGui::GetIO ();
	auto const width  = io.DisplaySize.x;
	auto const height = io.DisplaySize.y;

	ImGui::SetNextWindowPos(ImVec2 (0, 0), ImGuiCond_FirstUseEver);
    // top screen
	ImGui::SetNextWindowSize(ImVec2 (width, height * 0.5f));

    ImGui::Begin("Test debug imgui",
		    nullptr,
		    ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar
    );

    // showMenu();
    
    ImGui::BeginChild(
	    "Logs", ImVec2 (0, 0.5f * height), false, ImGuiWindowFlags_HorizontalScrollbar);
    drawLog();

    ImGui::EndChild();
    ImGui::End ();

    // bottom screen
	ImGui::SetNextWindowSize(ImVec2 (width * 0.8f, height * 0.5f));
	ImGui::SetNextWindowPos(ImVec2 (width * 0.1f, height * 0.5f), ImGuiCond_FirstUseEver);
	ImGui::Begin("Bottom Window",
	    nullptr,
	    ImGuiWindowFlags_NoCollapse);

	// showMenu();
    ImGui::End();
}

UniqueMainClass MainClass::create()
{
    return UniqueMainClass (new MainClass ());
}

void MainClass::showMenu()
{
	auto const prevShowAbout    = m_showAbout;

    if (ImGui::BeginMenuBar ())
	{
        if (ImGui::BeginMenu (u8"Menu \xee\x80\x83"))
        {
            if (ImGui::MenuItem ("About"))
				m_showAbout = true;
            ImGui::EndMenu ();
        }
        ImGui::EndMenuBar ();
    }

    if (m_showAbout)
	{
		if (!prevShowAbout)
			ImGui::OpenPopup("About");
		showAbout();
	}
}

void MainClass::showAbout()
{
    auto const &io    = ImGui::GetIO ();
	auto const width  = io.DisplaySize.x;
	auto const height = io.DisplaySize.y;

    ImGui::SetNextWindowSize (ImVec2 (width * 0.8f, height * 0.5f));
	ImGui::SetNextWindowPos (ImVec2 (width * 0.1f, height * 0.5f));

    if (ImGui::BeginPopupModal ("About",
	        nullptr,
	        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
	{
        ImGui::TextUnformatted (STATUS_STRING);
        ImGui::TextWrapped ("Copyright © 2021 Michael Theall, Dave Murphy, TuxSH");
		
        if (ImGui::TreeNode (g_libctruVersion))
		{
			ImGui::TextWrapped (g_zlibLicense);
			ImGui::Separator ();
			ImGui::TextWrapped (g_zlibLicense);
			ImGui::TreePop ();
		}

		if (ImGui::TreeNode (g_citro3dVersion))
		{
			ImGui::TextWrapped (g_citro3dCopyright);
			ImGui::Separator ();
			ImGui::TextWrapped (g_zlibLicense);
			ImGui::TreePop ();
		}
        ImGui::EndPopup ();
    }
}