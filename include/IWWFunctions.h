#pragma once

#include <boost/algorithm/string/case_conv.hpp>
#include <IWWConfig.h>
#include <IWWSpinlock.h>

namespace IWW
{
    class MainFunctions
    {
    SINGLETONHEADER(MainFunctions)
    public:
        bool UpdateHud();

        //load functions
        int LoadMeter(std::string a_root, int a_xpos, int a_ypos, bool a_visible);
        int LoadText(std::string a_root, std::string a_text, std::string a_font, int a_size, int a_xpos, int a_ypos, bool a_visible);
        int LoadWidget(std::string a_root, std::string a_filename, int a_xpos, int a_ypos, bool a_visible);
    
        //all
        void SetPos(std::string a_root, int a_id, int a_xpos, int a_ypos);
        void SetSize(std::string a_root, int a_id, int a_height, int a_width);
        int  GetSize(std::string a_root, int a_id, int a_type);
        void SetZoom(std::string a_root, int a_id, int a_xscale, int a_yscale);
        void SetVisible(std::string a_root, int a_id, int a_visible);
        void SetRotation(std::string a_root, int a_id, int a_rotation);
        void SetTransparency(std::string a_root, int a_id, int a_alpha);
        void SetRGB(std::string a_root, int a_id, int a_r, int a_g, int a_b);
        void Destroy(std::string a_root, int a_id);
    
        //meters
        void SetMeterPercent(std::string a_root, int a_id, int a_perc);
        void SetMeterFillDirection(std::string a_root, int a_id, std::string a_direction);
        void SendToBack(std::string a_root, int a_id);
        void SendToFront(std::string a_root, int a_id);
        void DoMeterFlash(std::string a_root, int a_id);
        void SetMeterRGB(std::string a_root, int a_id, int a_lightR = 255, int a_lightG = 255, int a_lightB = 255, int a_darkR = 0, int a_darkG = 0, int a_darkB = 0, int a_flashR = 127, int a_flashG = 127, int a_flashB = 127);

        //text
        void SetText(std::string a_root, int a_id, std::string a_text);
        void AppendText(std::string a_root, int a_id, std::string a_text);

        void SwapDepths(std::string a_root, int a_id1, int a_id2);

        //draw
        void DrawShapeLine(std::string a_root, std::vector<int> a_list, int a_XPos, int a_YPos, int a_XChange, int a_YChange, bool a_skipInvisible, bool a_skipAlpha0);
        void DrawShapeCircle(std::string a_root, std::vector<int> a_list, int a_XPos, int a_YPos, int a_Radius, int a_StartAngle, int a_DegreeChange, bool a_skipInvisible, bool a_skipAlpha0, bool a_AutoSpace);
        void DrawShapeOrbit(std::string a_root, std::vector<int> a_list, int a_XPos, int a_YPos, int a_Radius, int a_StartAngle, int a_DegreeChange, bool a_skipInvisible, bool a_skipAlpha0, bool a_AutoSpace);

        //transition
        void DoTransitionByTime(std::string a_root, int a_id, int targetValue, float a_seconds, std::string a_targetAttribute, std::string a_easingClass, std::string a_easingMethod, float a_delay);

        //hud ready
        //Return true if hud is ready. Also try to update HUD if its not. 
        //Return false if it still fails to get HUD data
        bool IsHudReady(); 
        void Reset(std::string a_root);
        void SetReseting(bool a_val) {_reseting = a_val;}
        bool IsResetting();
    private:
        void _UpdateWidget(RE::GPtr<RE::GFxMovieView> a_view);
        void INVOKE2_fun(std::string a_root,std::string a_arg1, std::string a_arg2, std::string a_fun1, std::string a_fun2);
        void INVOKE_fun(std::string a_root,std::string a_arg, std::string a_fun);
        RE::GFxValue INVOKERES_fun(std::string a_root,std::string a_arg, std::string a_fun);
        template<auto N> std::string _SelializeArray(const std::array<std::string,N> & a_array)
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
    private:
        Spinlock                    _spinlock;
        RE::GPtr<RE::GFxMovieView>  _hudmenu;
        RE::UI*                     _ui;
        std::atomic_bool            _reseting;

    };

    #define INVOKEARGNORES(root,argname,funname) INVOKE_fun(root,argname,funname);

    #define INVOKENOARGNORES(root,funname) INVOKE_fun(root,"",funname);

    #define INVOKEARGNORES2(root,argname1,argname2,funname1,funname2) INVOKE2_fun(root,argname1,argname2,funname1,funname2);

    #define INVOKEARGNORESRESET(root,argname,funname) INVOKERES_fun(root,argname,funname);

    #define INVOKEARGRESET(root,argname,funname) INVOKERES_fun(root,argname,funname);

    #define VALIDATEID(id,retvalue) \
    if (id < 1) {                   \
        WARN("Invalid id passed ({}) => skipping function call",id)\
        return retvalue;            \
    }

    void OnMessageReceived(SKSE::MessagingInterface::Message* a_msg);
}