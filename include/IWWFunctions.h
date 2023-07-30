#pragma once

#include <boost/algorithm/string/case_conv.hpp>

namespace IWW
{
    //mutex for safety reason
    extern std::mutex g_mutex;
    extern RE::GFxMovieView* g_hudmenu;
    extern bool g_IsReloaded;

    inline void _UpdateWidget(RE::GFxMovieView* a_view);
    inline void _UpdateHud();

    template<auto N>
    inline std::string _SelializeArray(const std::array<std::string, N>& a_array)
    {
        if (a_array.size() > 0)
        {
            std::string loc_res = a_array[0];
            for(size_t i = 1; i < a_array.size(); i++)
            {
                loc_res += "|" + a_array[i];
            }
            return loc_res;
        }
        else return std::string("");
    }

    #define INVOKEARG(root,hudname,argname,resname,funname)             \
    g_mutex.lock();                                                     \
    std::string     INVOKEARG_pathloadmeter = (root + funname);         \
    RE::GFxValue    INVOKEARG_arg;                                      \
    RE::GFxValue    resname;                                            \
    INVOKEARG_arg.SetString(argname);                                   \
    hudname->Invoke(INVOKEARG_pathloadmeter.c_str(),&resname,&INVOKEARG_arg,1); \
    _UpdateWidget(hudname);                                             \
    g_mutex.unlock();

    #define INVOKEARGRESET(root,hudname,argname,resname,funname)                                \
    g_mutex.lock();                                                                             \
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
    g_mutex.unlock();

    #define INVOKEARGNORES(root,hudname,argname,funname)                        \
    g_mutex.lock();                                                             \
    std::string     INVOKEARGNORES_pathloadmeter = (root + funname);            \
    RE::GFxValue    INVOKEARGNORES_arg;                                         \
    INVOKEARGNORES_arg.SetString(argname);                                      \
    hudname->InvokeNoReturn(INVOKEARGNORES_pathloadmeter.c_str(),&INVOKEARGNORES_arg,1); \
    _UpdateWidget(hudname);                                                     \
    g_mutex.unlock(); 

    #define INVOKEARGNORESRESET(root,hudname,argname,funname)                                               \
    g_mutex.lock();                                                                                         \
    std::string     INVOKEARGNORESRESET_path = (root + funname);                                            \
    RE::GFxValue    INVOKEARGNORESRESET_arg;                                                                \
    INVOKEARGNORESRESET_arg.SetString(argname);                                                             \
    hudname->Invoke(INVOKEARGNORESRESET_path.c_str(),NULL,&INVOKEARGNORESRESET_arg,1);                      \
    _UpdateWidget(hudname);                                                                                 \
    RE::GFxValue INVOKEARGNORESRESET_message;                                                               \
    std::string INVOKEARGNORESRESET_pathresetoutput = (a_root + "._getOutputMessage");                      \
    hudname->Invoke(INVOKEARGNORESRESET_pathresetoutput.c_str(),&INVOKEARGNORESRESET_message,NULL,0);       \
    _UpdateWidget(hudname);                                        \
    g_mutex.unlock();     

    #define INVOKEARGNORES2(root,hudname,argname1,argname2,funname1,funname2) \
    g_mutex.lock();                                                           \
    std::string     INVOKEARGNORES_pathloadmeter1 = (root + funname1);        \
    std::string     INVOKEARGNORES_pathloadmeter2 = (root + funname2);        \
    RE::GFxValue    INVOKEARGNORES_arg1;                                      \
    INVOKEARGNORES_arg1.SetString(argname1);                                  \
    RE::GFxValue    INVOKEARGNORES_arg2;                                      \
    INVOKEARGNORES_arg2.SetString(argname2);                                  \
    hudname->InvokeNoReturn(INVOKEARGNORES_pathloadmeter1.c_str(),&INVOKEARGNORES_arg1,1); \
    _UpdateWidget(hudname);                                                                \
    hudname->InvokeNoReturn(INVOKEARGNORES_pathloadmeter2.c_str(),&INVOKEARGNORES_arg2,1); \
    _UpdateWidget(hudname);                                                   \
    g_mutex.unlock();

    #define VALIDATEID(id,retvalue) \
    if (id < 1) {                   \
        ERRORLOG("ERROR: id == -1 => skipping function call") \
        return retvalue;            \
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

    //util
    bool IsReloaded(PAPYRUSFUNCHANDLE);
    void ResetReload(PAPYRUSFUNCHANDLE);
}