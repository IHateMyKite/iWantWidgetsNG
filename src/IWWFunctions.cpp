#include <IWWFunctions.h>

int IWW::LoadMeter(PAPYRUSFUNCHANDLE, std::string a_root, int a_xpos, int a_ypos, bool a_visible)
{
    std::string     loc_argstr = std::string(std::to_string(a_xpos) + "|" + std::to_string(a_ypos) + "|" + std::to_string(static_cast<int>(a_visible)));

    SKSELOG("LoadMeter({},{}) called",a_root,loc_argstr)

    RE::UI* loc_ui = RE::UI::GetSingleton();

    //get hud view
    auto loc_hudmenu = loc_ui->menuMap.find("HUD Menu")->second.menu;
    if (loc_hudmenu == nullptr) return -1;

    //get hud movie
    auto loc_uimovie = loc_hudmenu->uiMovie;
    if (loc_uimovie == nullptr) return -1;

    //invoke function
    std::string     loc_pathloadmeter = (a_root + ".loadMeter");
    RE::GFxValue    loc_arg;
    RE::GFxValue    loc_res;
    loc_arg.SetString(loc_argstr);
    loc_uimovie->Invoke(loc_pathloadmeter.c_str(),&loc_res,&loc_arg,1);

    //reset output, as it is no longer needed
    RE::GFxValue loc_message;
    std::string loc_pathresetoutput = (a_root + "._getOutputMessage");
    loc_uimovie->Invoke(loc_pathresetoutput.c_str(),&loc_message,NULL,0);

    return ROUND(loc_res.GetNumber());
}

int IWW::LoadText(PAPYRUSFUNCHANDLE, std::string a_root, std::string a_text, std::string a_font, int a_size, int a_xpos, int a_ypos, bool a_visible)
{
    std::string     loc_argstr = std::string(
        a_text + "|" + 
        a_font + "|" + 
        std::to_string(a_size) + "|" +
        std::to_string(a_xpos) + "|" +
        std::to_string(a_ypos) + "|" +
        std::to_string(static_cast<int>(a_visible))
    );

    SKSELOG("LoadText({},{}) called",a_root,loc_argstr)

    RE::UI* loc_ui = RE::UI::GetSingleton();
    //get hud view
    auto loc_hudmenu = loc_ui->menuMap.find("HUD Menu")->second.menu;
    if (loc_hudmenu == nullptr) return -1;
    //get hud movie
    auto loc_uimovie = loc_hudmenu->uiMovie;
    if (loc_uimovie == nullptr) return -1;

    //invoke function
    std::string     loc_pathloadmeter = (a_root + ".loadText");
    RE::GFxValue    loc_arg;
    RE::GFxValue    loc_res;
    loc_arg.SetString(loc_argstr);
    loc_uimovie->Invoke(loc_pathloadmeter.c_str(),&loc_res,&loc_arg,1);

    //reset output, as it is no longer needed
    RE::GFxValue loc_message;
    std::string loc_pathresetoutput = (a_root + "._getOutputMessage");
    loc_uimovie->Invoke(loc_pathresetoutput.c_str(),&loc_message,NULL,0);

    return ROUND(loc_res.GetNumber());
}

int IWW::LoadWidget(PAPYRUSFUNCHANDLE, std::string a_root, std::string a_filename, int a_xpos, int a_ypos, bool a_visible)
{
    std::string     loc_argstr = std::string(
        a_filename + "|" + 
        std::to_string(a_xpos) + "|" +
        std::to_string(a_ypos) + "|" +
        std::to_string(static_cast<int>(a_visible))
    );

    SKSELOG("loadWidget({},{}) called",a_root,loc_argstr)

    RE::UI* loc_ui = RE::UI::GetSingleton();
    //get hud view
    auto loc_hudmenu = loc_ui->menuMap.find("HUD Menu")->second.menu;
    if (loc_hudmenu == nullptr) return -1;
    //get hud movie
    auto loc_uimovie = loc_hudmenu->uiMovie;
    if (loc_uimovie == nullptr) return -1;

    //invoke function
    std::string     loc_pathloadmeter = (a_root + ".loadWidget");
    RE::GFxValue    loc_arg;
    RE::GFxValue    loc_res;
    loc_arg.SetString(loc_argstr);
    loc_uimovie->Invoke(loc_pathloadmeter.c_str(),&loc_res,&loc_arg,1);

    //reset output, as it is no longer needed
    RE::GFxValue loc_message;
    std::string loc_pathresetoutput = (a_root + "._getOutputMessage");
    loc_uimovie->Invoke(loc_pathresetoutput.c_str(),&loc_message,NULL,0);

    return ROUND(loc_res.GetNumber());
}
