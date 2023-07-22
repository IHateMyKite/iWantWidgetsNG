#pragma once

namespace IWW
{
    //return HUD as retval variable
    #define GETHUD(hudname,retval)                                          \
    RE::UI* GETHUD_ui = RE::UI::GetSingleton();                             \
    auto GETHUD_hudmenu = GETHUD_ui->menuMap.find("HUD Menu")->second.menu; \
    if (GETHUD_hudmenu == nullptr) return retval;                           \
    auto hudname = GETHUD_hudmenu->uiMovie;                                 \
    if (hudname == nullptr) return retval;

    //invoke function with single argument argname and save result to variable resname
    #define INVOKEARG(root,hudname,argname,resname,funname)             \
    std::string     INVOKEARG_pathloadmeter = (root + funname);         \
    RE::GFxValue    INVOKEARG_arg;                                      \
    RE::GFxValue    resname;                                            \
    INVOKEARG_arg.SetString(argname);                                   \
    hudname->Invoke(INVOKEARG_pathloadmeter.c_str(),&resname,&INVOKEARG_arg,1); 

    //invoke function with single argument argname and save result to variable resname
    #define INVOKEARGNORES(root,hudname,argname,funname)                     \
    std::string     INVOKEARGNORES_pathloadmeter = (root + funname);         \
    RE::GFxValue    INVOKEARGNORES_arg;                                      \
    INVOKEARGNORES_arg.SetString(argname);                                   \
    hudname->Invoke(INVOKEARGNORES_pathloadmeter.c_str(),NULL,&INVOKEARGNORES_arg,1);

    #define INVOKEARGNORES2(root,hudname,argname1,argname2,funname1,funname2) \
    std::string     INVOKEARGNORES_pathloadmeter1 = (root + funname1);       \
    std::string     INVOKEARGNORES_pathloadmeter2 = (root + funname2);       \
    RE::GFxValue    INVOKEARGNORES_arg1;                                     \
    INVOKEARGNORES_arg1.SetString(argname1);                                 \
    RE::GFxValue    INVOKEARGNORES_arg2;                                     \
    INVOKEARGNORES_arg2.SetString(argname2);                                 \
    hudname->Invoke(INVOKEARGNORES_pathloadmeter1.c_str(),NULL,&INVOKEARGNORES_arg1,1); \
    hudname->Invoke(INVOKEARGNORES_pathloadmeter2.c_str(),NULL,&INVOKEARGNORES_arg2,1);

    //reset output, as it is no longer needed
    #define RESETOUTPUT(root)                                               \
    RE::GFxValue RESETOUTPUT_message;                                       \
    std::string loc_pathresetoutput = (a_root + "._getOutputMessage");      \
    loc_uimovie->Invoke(loc_pathresetoutput.c_str(),&RESETOUTPUT_message,NULL,0);

    //load functions
    int LoadMeter(PAPYRUSFUNCHANDLE, std::string a_root, int a_xpos, int a_ypos, bool a_visible);
    int LoadText(PAPYRUSFUNCHANDLE, std::string a_root, std::string a_text, std::string a_font, int a_size, int a_xpos, int a_ypos, bool a_visible);
    int LoadWidget(PAPYRUSFUNCHANDLE, std::string a_root, std::string a_filename, int a_xpos, int a_ypos, bool a_visible);

    //all
    void SetPos(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_xpos, int a_ypos);
    void SetSize(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_height, int a_width);
    int  GetSize(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_type);
    void SetZoom(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_xscale, int a_yscale);
    void SetVisible(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_visible);
    void SetRotation(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_rotation);
    void SetTransparency(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_alpha);
    void SetRGB(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_r, int a_g, int a_b);
    void Destroy(PAPYRUSFUNCHANDLE, std::string a_root, int a_id);
    

    //meters
    void SetMeterPercent(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_perc);
    void SetMeterFillDirection(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, std::string a_direction);
    void SendToBack(PAPYRUSFUNCHANDLE, std::string a_root, int a_id);
    void SendToFront(PAPYRUSFUNCHANDLE, std::string a_root, int a_id);
    void DoMeterFlash(PAPYRUSFUNCHANDLE, std::string a_root, int a_id);
    void SetMeterRGB(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_lightR = 255, int a_lightG = 255, int a_lightB = 255, int a_darkR = 0, int a_darkG = 0, int a_darkB = 0, int a_flashR = 127, int a_flashG = 127, int a_flashB = 127);

    //text
    void SetText(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, std::string a_text);
    void AppendText(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, std::string a_text);

    void SwapDepths(PAPYRUSFUNCHANDLE, std::string a_root, int a_id1, int a_id2);
}