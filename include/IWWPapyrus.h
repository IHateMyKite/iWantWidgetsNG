#pragma once
#include <IWWConfig.h>
#include <IWWFunctions.h>

namespace IWW
{
    bool RegisterPapyrusFunctions(RE::BSScript::IVirtualMachine *vm);

    //load functions
    inline int LoadMeter(PAPYRUSFUNCHANDLE, std::string a_root, int a_xpos, int a_ypos, bool a_visible)
    {
        return MainFunctions::GetSingleton()->LoadMeter(a_root,a_xpos,a_ypos,a_visible);
    }
    inline int LoadText(PAPYRUSFUNCHANDLE, std::string a_root, std::string a_text, std::string a_font, int a_size, int a_xpos, int a_ypos, bool a_visible)
    {
        return MainFunctions::GetSingleton()->LoadText(a_root,a_text,a_font,a_size,a_xpos,a_ypos,a_visible);
    }
    inline int LoadWidget(PAPYRUSFUNCHANDLE, std::string a_root, std::string a_filename, int a_xpos, int a_ypos, bool a_visible)
    {
        return MainFunctions::GetSingleton()->LoadWidget(a_root,a_filename,a_xpos,a_ypos,a_visible);
    }

    //all
    inline void SetPos(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_xpos, int a_ypos)
    {
        return MainFunctions::GetSingleton()->SetPos(a_root,a_id,a_xpos,a_ypos);
    }
    inline void SetSize(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_height, int a_width)
    {
        return MainFunctions::GetSingleton()->SetSize(a_root,a_id,a_height,a_width);
    }
    inline int  GetSize(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_type)
    {
        return MainFunctions::GetSingleton()->GetSize(a_root,a_id,a_type);
    }
    inline void SetZoom(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_xscale, int a_yscale)
    {
        return MainFunctions::GetSingleton()->SetZoom(a_root,a_id,a_xscale,a_yscale);
    }
    inline void SetVisible(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_visible)
    {
        return MainFunctions::GetSingleton()->SetVisible(a_root,a_id,a_visible);
    }
    inline void SetRotation(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_rotation)
    {
        return MainFunctions::GetSingleton()->SetRotation(a_root,a_id,a_rotation);
    }
    inline void SetTransparency(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_alpha)
    {
        return MainFunctions::GetSingleton()->SetTransparency(a_root,a_id,a_alpha);
    }
    inline void SetRGB(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_r, int a_g, int a_b)
    {
        return MainFunctions::GetSingleton()->SetRGB(a_root,a_id,a_r,a_g,a_b);
    }
    inline void Destroy(PAPYRUSFUNCHANDLE, std::string a_root, int a_id)
    {
        return MainFunctions::GetSingleton()->Destroy(a_root,a_id);
    }
    
    //meters
    inline void SetMeterPercent(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_perc)
    {
        return MainFunctions::GetSingleton()->SetMeterPercent(a_root,a_id,a_perc);
    }
    inline void SetMeterFillDirection(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, std::string a_direction)
    {
        return MainFunctions::GetSingleton()->SetMeterFillDirection(a_root,a_id,a_direction);
    }
    inline void SendToBack(PAPYRUSFUNCHANDLE, std::string a_root, int a_id)
    {
        return MainFunctions::GetSingleton()->SendToBack(a_root,a_id);
    }
    inline void SendToFront(PAPYRUSFUNCHANDLE, std::string a_root, int a_id)
    {
        return MainFunctions::GetSingleton()->SendToFront(a_root,a_id);
    }
    inline void DoMeterFlash(PAPYRUSFUNCHANDLE, std::string a_root, int a_id)
    {
        return MainFunctions::GetSingleton()->DoMeterFlash(a_root,a_id);
    }
    inline void SetMeterRGB(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_lightR = 255, int a_lightG = 255, int a_lightB = 255, int a_darkR = 0, int a_darkG = 0, int a_darkB = 0, int a_flashR = 127, int a_flashG = 127, int a_flashB = 127)
    {
        return MainFunctions::GetSingleton()->SetMeterRGB(a_root,a_id,a_lightR,a_lightG,a_lightB,a_darkR,a_darkG,a_darkB,a_flashR,a_flashG,a_flashB);
    }

    //text
    inline void SetText(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, std::string a_text)
    {
        return MainFunctions::GetSingleton()->SetText(a_root,a_id,a_text);
    }
    inline void AppendText(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, std::string a_text)
    {
        return MainFunctions::GetSingleton()->AppendText(a_root,a_id,a_text);
    }
    inline void SwapDepths(PAPYRUSFUNCHANDLE, std::string a_root, int a_id1, int a_id2)
    {
        return MainFunctions::GetSingleton()->SwapDepths(a_root,a_id1,a_id2);
    }

    //draw
    inline void DrawShapeLine(PAPYRUSFUNCHANDLE, std::string a_root, std::vector<int> a_list, int a_XPos, int a_YPos, int a_XChange, int a_YChange, bool a_skipInvisible, bool a_skipAlpha0)
    {
        return MainFunctions::GetSingleton()->DrawShapeLine(a_root,a_list,a_XPos,a_YPos,a_XChange,a_YChange,a_skipInvisible,a_skipAlpha0);
    }
    inline void DrawShapeCircle(PAPYRUSFUNCHANDLE, std::string a_root, std::vector<int> a_list, int a_XPos, int a_YPos, int a_Radius, int a_StartAngle, int a_DegreeChange, bool a_skipInvisible, bool a_skipAlpha0, bool a_AutoSpace)
    {
        return MainFunctions::GetSingleton()->DrawShapeCircle(a_root,a_list,a_XPos,a_YPos,a_Radius,a_StartAngle,a_DegreeChange,a_skipInvisible,a_skipAlpha0,a_AutoSpace);
    }
    inline void DrawShapeOrbit(PAPYRUSFUNCHANDLE, std::string a_root, std::vector<int> a_list, int a_XPos, int a_YPos, int a_Radius, int a_StartAngle, int a_DegreeChange, bool a_skipInvisible, bool a_skipAlpha0, bool a_AutoSpace)
    {
        return MainFunctions::GetSingleton()->DrawShapeOrbit(a_root,a_list,a_XPos,a_YPos,a_Radius,a_StartAngle,a_DegreeChange,a_skipInvisible,a_skipAlpha0,a_AutoSpace);
    }

    //transition
    inline void DoTransitionByTime(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int targetValue, float a_seconds, std::string a_targetAttribute, std::string a_easingClass, std::string a_easingMethod, float a_delay)
    {
        return MainFunctions::GetSingleton()->DoTransitionByTime(a_root,a_id,targetValue,a_seconds,a_targetAttribute,a_easingClass,a_easingMethod,a_delay);
    }

    //hud ready
    //Return true if hud is ready. Also try to update HUD if its not. 
    //Return false if it still fails to get HUD data
    inline bool IsHudReady(PAPYRUSFUNCHANDLE)
    {
        return MainFunctions::GetSingleton()->IsHudReady();
    }
    inline void Reset(PAPYRUSFUNCHANDLE,std::string a_root)
    {
        return MainFunctions::GetSingleton()->Reset(a_root);
    }
    inline bool IsResetting(PAPYRUSFUNCHANDLE)
    {
        return MainFunctions::GetSingleton()->IsResetting();
    }
}