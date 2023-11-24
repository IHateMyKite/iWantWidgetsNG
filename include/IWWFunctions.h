#pragma once

#include <boost/algorithm/string/case_conv.hpp>
#include <IWWConfig.h>

namespace IWW
{
    //mutex for safety reason
    extern std::mutex           g_mutex;
    extern RE::GPtr<RE::GFxMovieView> g_hudmenu;
    extern RE::UI*              g_ui;

    extern std::atomic_bool     g_reseting;

    inline void _UpdateWidget(RE::GPtr<RE::GFxMovieView> a_view);
    inline bool _UpdateHud();

    template<auto N>
    inline std::string _SelializeArray(const std::array<std::string, N>& a_array)
    {
        if (a_array.size() > 0)
        {
            std::string loc_res = a_array[0];
            for(size_t i = 1; i < a_array.size(); i++)
            {
                loc_res += ("|" + a_array[i]);
            }
            return loc_res;
        }
        else return std::string("");
    }

    #define INVOKESTART             \
        {                           \
            LOG("INVOKESTART")      \
            g_mutex.lock();         \
        }

    #define INVOKEEND               \
        {                           \
            LOG("INVOKEEND")        \
            g_mutex.unlock();       \
        }

    #if (USETASK == 1)
        #define INVOKEARGNORES(root,hudname,argname,funname)                            \
        std::function<void()> INVOKEARGNORES_task = std::bind(INVOKE_fun,root,argname,funname); \
        SKSE::GetTaskInterface()->AddUITask(INVOKEARGNORES_task);
    #else
        #define INVOKEARGNORES(root,hudname,argname,funname)                        \
        INVOKE_fun(root,argname,funname);
    #endif

    #if (USETASK == 1)
        #define INVOKENOARGNORES(root,hudname,funname)                                  \
        std::function<void()> INVOKENOARGNORES_task = std::bind(INVOKE_fun,root,"",funname); \
        SKSE::GetTaskInterface()->AddUITask(INVOKENOARGNORES_task);
    #else
        #define INVOKENOARGNORES(root,hudname,funname)                                  \
        INVOKE_fun(root,"",funname);
    #endif

    #if (USETASK == 1)
        #define INVOKEARGNORES2(root,hudname,argname1,argname2,funname1,funname2)       \
        std::function<void()> INVOKEARGNORES2_task = std::bind(INVOKE2_fun,root,argname1,argname2,funname1,funname2); \
        SKSE::GetTaskInterface()->AddUITask(INVOKEARGNORES2_task);
    #else
        #define INVOKEARGNORES2(root,hudname,argname1,argname2,funname1,funname2)       \
        INVOKE2_fun(root,argname1,argname2,funname1,funname2);
    #endif

    #define INVOKEARGNORESRESET(root,hudname,argname,funname)                                               \
    INVOKESTART                                                                                             \
    std::string     INVOKEARGNORESRESET_path = (root + funname);                                            \
    RE::GFxValue    INVOKEARGNORESRESET_arg;                                                                \
    INVOKEARGNORESRESET_arg.SetString(argname);                                                             \
    hudname->Invoke(INVOKEARGNORESRESET_path.c_str(),NULL,&INVOKEARGNORESRESET_arg,1);                      \
    _UpdateWidget(hudname);                                                                                 \
    RE::GFxValue INVOKEARGNORESRESET_message;                                                               \
    std::string INVOKEARGNORESRESET_pathresetoutput = (a_root + "._getOutputMessage");                      \
    hudname->Invoke(INVOKEARGNORESRESET_pathresetoutput.c_str(),&INVOKEARGNORESRESET_message,NULL,0);       \
    _UpdateWidget(hudname);                                                                                 \
    INVOKEEND                                                                                               \
    LOG("INVOKEARGNORESRESET")

    #define INVOKEARGRESET(root,hudname,argname,resname,funname)                                \
    INVOKESTART                                                                                 \
    std::string     INVOKEARGRESET_path = (root + funname);                                     \
    RE::GFxValue    INVOKEARGRESET_arg;                                                         \
    RE::GFxValue    resname;                                                                    \
    INVOKEARGRESET_arg.SetString(argname);                                                      \
    hudname->Invoke(INVOKEARGRESET_path.c_str(),&resname,&INVOKEARGRESET_arg,1);                \
    _UpdateWidget(hudname);                                                                     \
    RE::GFxValue INVOKEARGRESET_message;                                                        \
    std::string INVOKEARGRESET_pathresetoutput = (a_root + "._getOutputMessage");               \
    hudname->Invoke(INVOKEARGRESET_pathresetoutput.c_str(),&INVOKEARGRESET_message,NULL,0);     \
    _UpdateWidget(hudname);                                                                     \
    INVOKEEND                                                                                   \
    LOG("INVOKEARGRESET")

    #define VALIDATEID(id,retvalue) \
    if (id < 1) {                   \
        /*ERROR("ERROR: id == -1 => skipping function call")*/  \
        return retvalue;            \
    }

    inline void INVOKE2_fun(std::string a_root,std::string a_arg1, std::string a_arg2, std::string a_fun1, std::string a_fun2)
    {        
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
        LOG("INVOKE2_fun")
    }

    inline void INVOKE_fun(std::string a_root,std::string a_arg, std::string a_fun)
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
        
        LOG("INVOKING")
        g_hudmenu->InvokeNoReturn(loc_pathloadmeter.c_str(),loc_argptr,loc_argnum);

        LOG("UPDATING")
        _UpdateWidget(g_hudmenu);

        INVOKEEND
        LOG("INVOKE_fun") 
    }

    template<auto N>
    std::string _SelializeArray(const std::array<std::string,N> & a_array);

    void OnMessageReceived(SKSE::MessagingInterface::Message* a_msg);

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

    //draw
    void DrawShapeLine(PAPYRUSFUNCHANDLE, std::string a_root, std::vector<int> a_list, int a_XPos, int a_YPos, int a_XChange, int a_YChange, bool a_skipInvisible, bool a_skipAlpha0);
    void DrawShapeCircle(PAPYRUSFUNCHANDLE, std::string a_root, std::vector<int> a_list, int a_XPos, int a_YPos, int a_Radius, int a_StartAngle, int a_DegreeChange, bool a_skipInvisible, bool a_skipAlpha0, bool a_AutoSpace);
    void DrawShapeOrbit(PAPYRUSFUNCHANDLE, std::string a_root, std::vector<int> a_list, int a_XPos, int a_YPos, int a_Radius, int a_StartAngle, int a_DegreeChange, bool a_skipInvisible, bool a_skipAlpha0, bool a_AutoSpace);

    //transition
    void DoTransitionByTime(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int targetValue, float a_seconds, std::string a_targetAttribute, std::string a_easingClass, std::string a_easingMethod, float a_delay);

    //hud ready
    //Return true if hud is ready. Also try to update HUD if its not. 
    //Return false if it still fails to get HUD data
    bool IsHudReady(PAPYRUSFUNCHANDLE); 
    void Reset(PAPYRUSFUNCHANDLE,std::string a_root);
    bool IsResetting(PAPYRUSFUNCHANDLE);
}