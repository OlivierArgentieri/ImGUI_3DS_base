#pragma once
#include "platform.h"

#include <atomic>
#include <chrono>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

class MainClass;
using UniqueMainClass = std::unique_ptr<MainClass>;
/// \brief Main Class Example
class MainClass
{
public:
    /// \brief draw call for imgui
    void draw();

    /// \brief Create instance
    static UniqueMainClass create();

private:
    /// \brief private constructor
    MainClass();
    /// \brief Show menu menu in the current window
	void showMenu();

    /// \brief Show about window
	void showAbout();

    /// \brief Whether thread should quit
	std::atomic<bool> m_quit;

    /// \brief ImGui window name
	std::string m_name;

    /// \brief Whether to show about window
	bool m_showAbout = false;
};