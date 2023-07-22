#pragma once

namespace IWW
{
    int LoadMeter(PAPYRUSFUNCHANDLE, std::string a_root, int a_xpos, int a_ypos, bool a_visible);
    int LoadText(PAPYRUSFUNCHANDLE, std::string a_root, std::string a_text, std::string a_font, int a_size, int a_xpos, int a_ypos, bool a_visible);
    int LoadWidget(PAPYRUSFUNCHANDLE, std::string a_root, std::string a_filename, int a_xpos, int a_ypos, bool a_visible);
}