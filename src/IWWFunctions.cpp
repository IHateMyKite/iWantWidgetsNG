#include <IWWFunctions.h>

std::mutex          IWW::g_mutex;
RE::GPtr<RE::GFxMovieView>   IWW::g_hudmenu = nullptr;
RE::UI*             IWW::g_ui           = nullptr;
IWW::Spinlock       IWW::g_spinlock;

std::atomic_bool    IWW::g_reseting     = true;

void IWW::OnMessageReceived(SKSE::MessagingInterface::Message* a_msg)
{
    if (a_msg != nullptr)
    {
        switch(a_msg->type)
        {
        case SKSE::MessagingInterface::kDataLoaded:
            break;
        case SKSE::MessagingInterface::kPostLoad:
            IWW::Config::GetSingleton()->Setup();
            break;
        case SKSE::MessagingInterface::kPreLoadGame:    //set reload flag, so we can prevent in papyrus calls of native function untill view get reset by invoking _reset
            g_reseting = true;
        case SKSE::MessagingInterface::kPostLoadGame:   //for loading existing game
        case SKSE::MessagingInterface::kSaveGame:       //for new game
            _UpdateHud();
            LOG("kPostLoadGame | kSaveGame")
            break;
        }
    }
}

bool IWW::IsHudReady(PAPYRUSFUNCHANDLE)
{
    return _UpdateHud();
}

void IWW::Reset(PAPYRUSFUNCHANDLE, std::string a_root)
{
    LOG("Reset({}) called",a_root) //logging

    if (g_hudmenu == nullptr) 
    {
        ERROR("Reset({}) - ERROR - CAN'T LOAD UI!!",a_root) //logging
        return;
    }

    INVOKENOARGNORES(a_root,"._reset")

    LOG("Reset({}) done",a_root) //logging

    g_reseting = false; //reset done
}

bool IWW::IsResetting(PAPYRUSFUNCHANDLE)
{
    return g_reseting;
}

int IWW::LoadMeter(PAPYRUSFUNCHANDLE, std::string a_root, int a_xpos, int a_ypos, bool a_visible)
{
    std::string     loc_argstr = std::string(std::to_string(a_xpos) + "|" + std::to_string(a_ypos) + "|" + std::to_string(static_cast<int>(a_visible)));

    LOG("LoadMeter({},{}) called",a_root,loc_argstr) //logging

    if (g_hudmenu == nullptr) 
    {
        ERROR("LoadMeter({},{}) - ERROR - CAN'T LOAD UI!!",a_root,loc_argstr) //logging
        return -1; 
    }

    auto loc_res = INVOKEARGRESET(a_root,loc_argstr,".loadMeter")

    LOG("LoadMeter({},{}) - New ID = {}",a_root,loc_argstr,ROUND(loc_res.GetNumber())) //logging

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

    LOG("LoadText({},{}) called",a_root,loc_argstr) //logging

    if (g_hudmenu == nullptr) 
    {
        ERROR("LoadText({},{}) - ERROR - CAN'T LOAD UI!!",a_root,loc_argstr) //logging
        return -1; 
    }

    auto loc_res = INVOKEARGRESET(a_root,loc_argstr,".loadText")

    LOG("LoadText({},{}) - New ID = {}",a_root,loc_argstr,loc_res.GetNumber()) //logging

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

    LOG("loadWidget({},{}) called",a_root,loc_argstr) //logging

    if (g_hudmenu == nullptr) 
    {
        ERROR("loadWidget({},{}) - ERROR - CAN'T LOAD UI!!",a_root,loc_argstr) //logging
        return -1; 
    }

    auto loc_res = INVOKEARGRESET(a_root,loc_argstr,".loadWidget")

    LOG("loadWidget({},{}) - New ID = {}",a_root,loc_argstr,loc_res.GetNumber()) //logging

    return ROUND(loc_res.GetNumber());
}

void IWW::SetPos(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_xpos, int a_ypos)
{
    std::string     loc_argstr1 = std::string(
        std::to_string(a_id)    + "|" + 
        std::to_string(a_xpos)
    );
    std::string     loc_argstr2 = std::string(
        std::to_string(a_id)    + "|" + 
        std::to_string(a_ypos)
    );

    LOG("SetPos({},{},{}) called",a_root,loc_argstr1,loc_argstr2) //logging

    VALIDATEID(a_id,)

    if (g_hudmenu == nullptr) return;

    INVOKEARGNORES2(a_root,loc_argstr1,loc_argstr2,".setXPos",".setYPos")
}

void IWW::SetSize(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_height, int a_width)
{
    std::string     loc_argstr1 = std::string(
        std::to_string(a_id)    + "|" + 
        std::to_string(a_height)
    );
    std::string     loc_argstr2 = std::string(
        std::to_string(a_id)    + "|" + 
        std::to_string(a_width)
    );

    LOG("SetSize({},{},{}) called",a_root,loc_argstr1,loc_argstr2) //logging

    VALIDATEID(a_id,)

    if (g_hudmenu == nullptr) return;

    INVOKEARGNORES2(a_root,loc_argstr1,loc_argstr2,".setHeight",".setWidth")
}

int IWW::GetSize(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_type)
{
    std::string loc_argstr = std::string(std::to_string(a_id));

    LOG("GetSize({},{}) called, type = {}",a_root,loc_argstr,a_type) //logging

    VALIDATEID(a_id,0)

    if (g_hudmenu == nullptr) return 0;

    if (a_type == 0) 
    {
        auto loc_res = INVOKEARGNORESRESET(a_root,loc_argstr,".getXsize")
        return ROUND(std::stoi(loc_res.GetString()));
    }
    else 
    {
        auto loc_res = INVOKEARGNORESRESET(a_root,loc_argstr,".getYsize")
        return ROUND(std::stoi(loc_res.GetString()));
    }
}

void IWW::SetZoom(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_xscale, int a_yscale)
{
    std::string     loc_argstr1 = std::string(
        std::to_string(a_id)    + "|" + 
        std::to_string(a_xscale)
    );
    std::string     loc_argstr2 = std::string(
        std::to_string(a_id)    + "|" + 
        std::to_string(a_yscale)
    );

    LOG("SetZoom({},{},{}) called",a_root,loc_argstr1,loc_argstr2) //logging

    VALIDATEID(a_id,)

    if (g_hudmenu == nullptr) return;

    INVOKEARGNORES2(a_root,loc_argstr1,loc_argstr2,".setXScale",".setYScale")
}

void IWW::SetVisible(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_visible)
{
    std::string loc_argstr = std::string(std::to_string(a_id) + "|" + std::to_string(a_visible));

    LOG("SetVisible({},{}) called",a_root,loc_argstr) //logging

    VALIDATEID(a_id,)

    if (g_hudmenu == nullptr) return;

    INVOKEARGNORES(a_root,loc_argstr,".setVisible")
}

void IWW::SetRotation(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_rotation)
{
    std::string loc_argstr = std::string(std::to_string(a_id) + "|" + std::to_string(a_rotation));

    LOG("SetRotation({},{}) called",a_root,loc_argstr) //logging

    VALIDATEID(a_id,)

    if (g_hudmenu == nullptr) return;

    INVOKEARGNORES(a_root,loc_argstr,".setRotation")
}

void IWW::SetTransparency(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_alpha)
{
    std::string loc_argstr = std::string(std::to_string(a_id) + "|" + std::to_string(a_alpha));

    LOG("SetTransparency({},{}) called",a_root,loc_argstr) //logging

    VALIDATEID(a_id,)

    if (g_hudmenu == nullptr) return;

    INVOKEARGNORES(a_root,loc_argstr,".setAlpha")
}

void IWW::SetRGB(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_r, int a_g, int a_b)
{
    std::string     loc_argstr = std::string(
        std::to_string(a_id)   + "|" + 
        std::to_string(((a_r & 0xFF) << 16) | ((a_g & 0xFF) << 8) | (a_b & 0xFF))
    );

    LOG("SetRGB({},{}) called",a_root,loc_argstr) //logging

    VALIDATEID(a_id,)

    if (g_hudmenu == nullptr) return;

    INVOKEARGNORES(a_root,loc_argstr,".setColor")
}

void IWW::Destroy(PAPYRUSFUNCHANDLE, std::string a_root, int a_id)
{
    std::string     loc_argstr = std::string(
        std::to_string(a_id)
    );
    
    LOG("Destroy({},{}) called",a_root,loc_argstr) //logging
    
    VALIDATEID(a_id,)
    
    if (g_hudmenu == nullptr) return;
    INVOKEARGNORES(a_root,loc_argstr,".destroy")
}

void IWW::SetMeterPercent(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_perc)
{
    std::string loc_argstr = std::string(std::to_string(a_id) + "|" + std::to_string(a_perc));

    LOG("SetMeterPercent({},{}) called",a_root,loc_argstr) //logging

    VALIDATEID(a_id,)

    if (g_hudmenu == nullptr) return;

    INVOKEARGNORES(a_root,loc_argstr,".setMeterPercent")
}

void IWW::SetMeterFillDirection(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, std::string a_direction)
{
    std::string loc_argstr = std::string(std::to_string(a_id) + "|" + a_direction);

    LOG("SetMeterFillDirection({},{}) called",a_root,loc_argstr) //logging

    VALIDATEID(a_id,)

    if (g_hudmenu == nullptr) return;

    INVOKEARGNORES(a_root,loc_argstr,".setMeterFillDirection")
}

void IWW::SendToBack(PAPYRUSFUNCHANDLE, std::string a_root, int a_id)
{
    std::string loc_argstr = std::string(std::to_string(a_id));

    LOG("SendToBack({},{}) called",a_root,loc_argstr) //logging

    VALIDATEID(a_id,)

    if (g_hudmenu == nullptr) return;

    INVOKEARGNORES(a_root,loc_argstr,".sendToBack")
}

void IWW::SendToFront(PAPYRUSFUNCHANDLE, std::string a_root, int a_id)
{
    std::string loc_argstr = std::string(std::to_string(a_id));

    LOG("SendToFront({},{}) called",a_root,loc_argstr) //logging

    VALIDATEID(a_id,)

    if (g_hudmenu == nullptr) return;

    INVOKEARGNORES(a_root,loc_argstr,".sendToFront")
}

void IWW::DoMeterFlash(PAPYRUSFUNCHANDLE, std::string a_root, int a_id)
{
    std::string loc_argstr = std::string(std::to_string(a_id));

    LOG("DoMeterFlash({},{}) called",a_root,loc_argstr) //logging

    VALIDATEID(a_id,)

    if (g_hudmenu == nullptr) return;

    INVOKEARGNORES(a_root,loc_argstr,".doMeterFlash")
}

void IWW::SetMeterRGB(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_lightR, int a_lightG, int a_lightB, int a_darkR, int a_darkG, int a_darkB, int a_flashR, int a_flashG, int a_flashB)
{
    std::string     loc_argstr = std::string(
        std::to_string(a_id)   + "|" + 
        std::to_string(((a_lightR & 0xFF) << 16) | ((a_lightG & 0xFF) << 8) | (a_lightB & 0xFF)) + "|" +
        std::to_string(((a_darkR & 0xFF) << 16) | ((a_darkG & 0xFF) << 8) | (a_darkB & 0xFF)) + "|" +
        std::to_string(((a_flashR & 0xFF) << 16) | ((a_flashG & 0xFF) << 8) | (a_flashB & 0xFF))
    );

    LOG("SetMeterRGB({},{}) called",a_root,loc_argstr) //logging

    VALIDATEID(a_id,)

    if (g_hudmenu == nullptr) return;

    INVOKEARGNORES(a_root,loc_argstr,".setMeterColors")
}

void IWW::SetText(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, std::string a_text)
{
    std::string     loc_argstr = std::string(
        std::to_string(a_id)   + "|" + 
        a_text
    );

    LOG("SetText({},{}) called",a_root,loc_argstr) //logging

    VALIDATEID(a_id,)

    if (g_hudmenu == nullptr) return;

    INVOKEARGNORES(a_root,loc_argstr,".setText")
}

void IWW::AppendText(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, std::string a_text)
{
    std::string     loc_argstr = std::string(
        std::to_string(a_id)   + "|" + 
        a_text
    );

    LOG("AppendText({},{}) called",a_root,loc_argstr) //logging

    VALIDATEID(a_id,)

    if (g_hudmenu == nullptr) return;

    INVOKEARGNORES(a_root,loc_argstr,".appendText")
}

void IWW::SwapDepths(PAPYRUSFUNCHANDLE, std::string a_root, int a_id1, int a_id2)
{
    std::string     loc_argstr = std::string(
        std::to_string(a_id1)   + "|" + 
        std::to_string(a_id2)
    );

    LOG("SwapDepths({},{}) called",a_root,loc_argstr) //logging

    VALIDATEID(a_id1,)
    VALIDATEID(a_id2,)

    if (g_hudmenu == nullptr) return;

    INVOKEARGNORES(a_root,loc_argstr,".swapDepths")
}

void IWW::DrawShapeLine(PAPYRUSFUNCHANDLE, std::string a_root, std::vector<int> a_list, int a_XPos, int a_YPos, int a_XChange, int a_YChange, bool a_skipInvisible, bool a_skipAlpha0)
{
    std::string     loc_argstr = std::string(
        std::to_string(a_XPos)              + "|" + 
        std::to_string(a_YPos)              + "|" +
        std::to_string(a_XChange)           + "|" +
        std::to_string(a_YChange)           + "|" +
        std::to_string(static_cast<int>(a_skipInvisible))     + "|" +
        std::to_string(static_cast<int>(a_skipAlpha0))
    );

    for(auto&& it : a_list)
    {
        loc_argstr += std::string("|" + std::to_string(it));
    }

    LOG("DrawShapeLine({},{}) called",a_root,loc_argstr) //logging

    if (g_hudmenu == nullptr) return;

    INVOKEARGNORES(a_root,loc_argstr,".drawLine")
}

void IWW::DrawShapeCircle(PAPYRUSFUNCHANDLE, std::string a_root, std::vector<int> a_list, int a_XPos, int a_YPos, int a_Radius, int a_StartAngle, int a_DegreeChange, bool a_skipInvisible, bool a_skipAlpha0, bool a_AutoSpace)
{
    std::string     loc_argstr = std::string(
        std::to_string(a_XPos)                                  + "|" + 
        std::to_string(a_YPos)                                  + "|" +
        std::to_string(a_Radius)                                + "|" +
        std::to_string(a_StartAngle)                            + "|" +
        std::to_string(a_DegreeChange)                          + "|" +
        std::to_string(static_cast<int>(a_skipInvisible))       + "|" +
        std::to_string(static_cast<int>(a_skipAlpha0))          + "|" +
        std::to_string(static_cast<int>(a_AutoSpace))
    );

    for(auto&& it : a_list)
    {
        loc_argstr += std::string("|" + std::to_string(it));
    }

    LOG("DrawShapeCircle({},{}) called",a_root,loc_argstr) //logging

    if (g_hudmenu == nullptr) return;

    INVOKEARGNORES(a_root,loc_argstr,".drawCircle")
}

void IWW::DrawShapeOrbit(PAPYRUSFUNCHANDLE, std::string a_root, std::vector<int> a_list, int a_XPos, int a_YPos, int a_Radius, int a_StartAngle, int a_DegreeChange, bool a_skipInvisible, bool a_skipAlpha0, bool a_AutoSpace)
{
    std::string     loc_argstr = std::string(
        std::to_string(a_XPos)                                  + "|" + 
        std::to_string(a_YPos)                                  + "|" +
        std::to_string(a_Radius)                                + "|" +
        std::to_string(a_StartAngle)                            + "|" +
        std::to_string(a_DegreeChange)                          + "|" +
        std::to_string(static_cast<int>(a_skipInvisible))       + "|" +
        std::to_string(static_cast<int>(a_skipAlpha0))          + "|" +
        std::to_string(static_cast<int>(a_AutoSpace))
    );

    for(auto&& it : a_list)
    {
        loc_argstr += std::string("|" + std::to_string(it));
    }

    LOG("DrawShapeOrbit({},{}) called",a_root,loc_argstr) //logging

    if (g_hudmenu == nullptr) return;

    INVOKEARGNORES(a_root,loc_argstr,".drawOrbit")
}

void IWW::DoTransitionByTime(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_targetValue, float a_seconds, std::string a_targetAttribute, std::string a_easingClass, std::string a_easingMethod, float a_delay)
{
    std::array<std::string,7> loc_array;
    loc_array[0] = std::to_string(a_id);
    loc_array[1] = std::to_string(a_targetValue);
    loc_array[2] = std::to_string(a_seconds);

    //convert to lower case
    boost::algorithm::to_lower(a_targetAttribute);
    boost::algorithm::to_lower(a_easingClass);
    boost::algorithm::to_lower(a_easingMethod);

    if (a_targetAttribute == "x" || a_targetAttribute == "y" || a_targetAttribute == "xscale" || a_targetAttribute == "yscale" || a_targetAttribute == "rotation")
    {
        loc_array[3] = "_" + a_targetAttribute;
    }
    else if (a_targetAttribute == "meterpercent")
    {
        loc_array[1] = std::to_string(a_targetValue/100.0);
        loc_array[3] = a_targetAttribute;
    }
    else
    {
        loc_array[3] = "_alpha";
    }

    if (a_easingClass == "regular" || a_easingClass == "bounce" || a_easingClass == "back" || a_easingClass == "elastic" || a_easingClass == "strong")
    {
        loc_array[4] = a_easingClass;
    }
    else
    {
        loc_array[4] = "none";
    }

	if      (a_easingMethod == "in")    loc_array[5] = "easeIn";
	else if (a_easingMethod == "out")   loc_array[5] = "easeOut";
	else if (a_easingMethod == "inout") loc_array[5] = "easeInOut";
	else
    {
        loc_array[4] = "none";
        loc_array[5] = ""    ;
    }

    loc_array[6] = std::to_string(a_delay);

    std::string loc_argstr = _SelializeArray<7>(loc_array);

    LOG("DoTransitionByTime({},{}) called",a_root,loc_argstr) //logging

    VALIDATEID(a_id,)

    if (g_hudmenu == nullptr) return;

    INVOKEARGNORES(a_root,loc_argstr,".doTransition")
}

void IWW::_UpdateWidget(RE::GPtr<RE::GFxMovieView> a_view)
{
    //update by very small time so internal AS vars are updated
    if (a_view.get() != nullptr) a_view->Advance(0.0001f);
    else ERROR("Cant update movie because it is none")
}

inline bool IWW::_UpdateHud()
{
    #define CHECKHUDERROR(ptr,errvalue,msg)    \
    {                               \
        if (ptr == errvalue)        \
        {                           \
        ERROR(msg)               \
        return false;               \
        }                           \
    }

    if (g_hudmenu != nullptr) return true;

    g_ui = RE::UI::GetSingleton();
    CHECKHUDERROR(g_ui,nullptr,"Failed getting hud - g_ui => null")
    auto loc_hud = g_ui->menuMap.find("HUD Menu");
    CHECKHUDERROR(loc_hud,g_ui->menuMap.end(),"Failed getting hud - HUD not found in menu map")
    RE::GPtr<RE::IMenu> loc_hudmenu = loc_hud->second.menu; 
    CHECKHUDERROR(loc_hudmenu.get(),nullptr,"Failed getting hud - loc_hudmenu => null")
    RE::GPtr<RE::GFxMovieView> loc_movie = loc_hudmenu->uiMovie;
    CHECKHUDERROR(loc_movie.get(),nullptr,"Failed getting hud - loc_movie => null")

    g_hudmenu = loc_hudmenu->uiMovie;

    LOG("HUD Loaded!")

    #undef CHECKHUDERROR

    return true;
}

void IWW::INVOKE2_fun(std::string a_root, std::string a_arg1, std::string a_arg2, std::string a_fun1, std::string a_fun2)
{
    if (IWW::Config::GetSingleton()->GetVariable<bool>("General.UseUITask",true))
    {
        SKSE::GetTaskInterface()->AddUITask([a_root,a_arg1,a_arg2,a_fun1,a_fun2]
        {
            LOG("INVOKE2_fun 1 start")
            INVOKESTART 
            const std::string     loc_pathloadmeter1 = (a_root + a_fun1);
            RE::GFxValue    loc_arg1;
            RE::GFxValue*   loc_argptr1 = NULL;
            uint32_t        loc_argnum1 = 0;

            if (a_arg1 != "")
            {
                loc_arg1.SetString(a_arg1);
                loc_argptr1 = &loc_arg1;
                loc_argnum1 += 2;
            }
        
            g_hudmenu->InvokeNoReturn(loc_pathloadmeter1.c_str(),loc_argptr1,loc_argnum1);
            _UpdateWidget(g_hudmenu);

            INVOKEEND
            LOG("INVOKE2_fun 1 end")
        });

        SKSE::GetTaskInterface()->AddUITask([a_root,a_arg1,a_arg2,a_fun1,a_fun2]
        {
            LOG("INVOKE2_fun 2 start")
            INVOKESTART
            const std::string     loc_pathloadmeter2 = (a_root + a_fun2);
            RE::GFxValue    loc_arg2;
            RE::GFxValue*   loc_argptr2 = NULL;
            uint32_t        loc_argnum2 = 0;

            if (a_arg2 != "")
            {
                loc_arg2.SetString(a_arg2);
                loc_argptr2 = &loc_arg2;
                loc_argnum2 += 1;
            }

            g_hudmenu->InvokeNoReturn(loc_pathloadmeter2.c_str(),loc_argptr2,loc_argnum2);
            _UpdateWidget(g_hudmenu);

            INVOKEEND
            LOG("INVOKE2_fun 2 end")
        });
    }
    else
    {
        LOG("INVOKE2_fun start")
        INVOKESTART 
        const std::string     loc_pathloadmeter1 = (a_root + a_fun1);
        const std::string     loc_pathloadmeter2 = (a_root + a_fun2);

        RE::GFxValue    loc_arg1;
        RE::GFxValue*   loc_argptr1 = NULL;
        uint32_t        loc_argnum1 = 0;

        if (a_arg1 != "")
        {
            loc_arg1.SetString(a_arg1);
            loc_argptr1 = &loc_arg1;
            loc_argnum1 += 2;
        }
        
        g_hudmenu->InvokeNoReturn(loc_pathloadmeter1.c_str(),loc_argptr1,loc_argnum1);
        _UpdateWidget(g_hudmenu);

        RE::GFxValue    loc_arg2;
        RE::GFxValue*   loc_argptr2 = NULL;
        uint32_t        loc_argnum2 = 0;

        if (a_arg2 != "")
        {
            loc_arg2.SetString(a_arg2);
            loc_argptr2 = &loc_arg2;
            loc_argnum2 += 1;
        }

        g_hudmenu->InvokeNoReturn(loc_pathloadmeter2.c_str(),loc_argptr2,loc_argnum2);
        _UpdateWidget(g_hudmenu);

        INVOKEEND
        LOG("INVOKE2_fun end")
    }
}

void IWW::INVOKE_fun(std::string a_root, std::string a_arg, std::string a_fun)
{
    if (IWW::Config::GetSingleton()->GetVariable<bool>("General.UseUITask",true))
    {
        SKSE::GetTaskInterface()->AddUITask([a_root,a_arg,a_fun]
        {
            LOG("INVOKE_fun start")
            INVOKESTART
            const std::string loc_pathloadmeter = (a_root + a_fun);
            RE::GFxValue*   loc_argptr = NULL;
            RE::GFxValue    loc_arg;
            uint32_t        loc_argnum = 0;

            if (a_arg != "")
            {
                loc_arg.SetString(a_arg);
                loc_argptr  = &loc_arg;
                loc_argnum += 1;
            }

            g_hudmenu->InvokeNoReturn(loc_pathloadmeter.c_str(),loc_argptr,loc_argnum);
            _UpdateWidget(g_hudmenu); 
            INVOKEEND
            LOG("INVOKE_fun end")
        });
    }
    else
    {
        INVOKESTART
        const std::string loc_pathloadmeter = (a_root + a_fun);
        RE::GFxValue*   loc_argptr = NULL;
        RE::GFxValue    loc_arg;
        uint32_t        loc_argnum = 0;

        if (a_arg != "")
        {
            loc_arg.SetString(a_arg);
            loc_argptr  = &loc_arg;
            loc_argnum += 1;
        }

        g_hudmenu->InvokeNoReturn(loc_pathloadmeter.c_str(),loc_argptr,loc_argnum);
        _UpdateWidget(g_hudmenu);
        LOG("INVOKE_fun") 
        INVOKEEND
    }
}

RE::GFxValue IWW::INVOKERES_fun(std::string a_root, std::string a_arg, std::string a_fun)
{
    {
        LOG("INVOKERES_fun start")
        INVOKESTART 
        const std::string loc_pathloadmeter = (a_root + a_fun);

        RE::GFxValue*   loc_argptr = NULL;
        RE::GFxValue    loc_arg;
        RE::GFxValue    loc_res;
        uint32_t        loc_argnum = 0;

        if (a_arg != "")
        {
            loc_arg.SetString(a_arg);
            loc_argptr  = &loc_arg;
            loc_argnum += 1;
        }
        
        g_hudmenu->Invoke(loc_pathloadmeter.c_str(),&loc_res,loc_argptr,loc_argnum);
        _UpdateWidget(g_hudmenu);

        RE::GFxValue loc_tmpres; 
        const std::string loc_pathresetoutput = (a_root + "._getOutputMessage");
        g_hudmenu->Invoke(loc_pathresetoutput.c_str(),&loc_tmpres,NULL,0);
        _UpdateWidget(g_hudmenu);

        INVOKEEND
        LOG("INVOKERES_fun end - {}",ROUND(loc_res.GetNumber()))
        return loc_res;
    }
}
