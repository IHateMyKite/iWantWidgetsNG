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

    class Spinlock
    {
    public:
        void Lock()
        {
            while(_state){int i = 0; i++;} 
            _state = true;
        }
        void Unlock()
        {
            _state = false;
        }
    private:
        bool _state = false;
    };

    extern Spinlock g_spinlock;

    #define INVOKESTART g_spinlock.Lock();
    #define INVOKEEND g_spinlock.Unlock();

    #define INVOKEARGNORES(root,argname,funname) INVOKE_fun(root,argname,funname);

    #define INVOKENOARGNORES(root,funname) INVOKE_fun(root,"",funname);

    #define INVOKEARGNORES2(root,argname1,argname2,funname1,funname2) INVOKE2_fun(root,argname1,argname2,funname1,funname2);

    #define INVOKEARGNORESRESET(root,argname,funname) INVOKERES_fun(root,argname,funname);

    #define INVOKEARGRESET(root,argname,funname) INVOKERES_fun(root,argname,funname);

    #define VALIDATEID(id,retvalue) \
    if (id < 1) {                   \
        /*ERROR("ERROR: id == -1 => skipping function call")*/  \
        return retvalue;            \
    }

    inline void INVOKE2_fun(std::string a_root,std::string a_arg1, std::string a_arg2, std::string a_fun1, std::string a_fun2);
    inline void INVOKE_fun(std::string a_root,std::string a_arg, std::string a_fun);
    inline RE::GFxValue INVOKERES_fun(std::string a_root,std::string a_arg, std::string a_fun);

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