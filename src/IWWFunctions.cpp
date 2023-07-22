#include <IWWFunctions.h>

int IWW::LoadMeter(PAPYRUSFUNCHANDLE, std::string a_root, int a_xpos, int a_ypos, bool a_visible)
{
    std::string     loc_argstr = std::string(std::to_string(a_xpos) + "|" + std::to_string(a_ypos) + "|" + std::to_string(static_cast<int>(a_visible)));

    SKSELOG("LoadMeter({},{}) called",a_root,loc_argstr) //logging

    GETHUD(loc_uimovie,-1)
    INVOKEARG(a_root,loc_uimovie,loc_argstr,loc_res,".loadMeter")
    RESETOUTPUT(a_root)

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

    SKSELOG("LoadText({},{}) called",a_root,loc_argstr) //logging

    GETHUD(loc_uimovie,-1)
    INVOKEARG(a_root,loc_uimovie,loc_argstr,loc_res,".loadText")
    RESETOUTPUT(a_root)

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

    SKSELOG("loadWidget({},{}) called",a_root,loc_argstr) //logging

    GETHUD(loc_uimovie,-1)
    INVOKEARG(a_root,loc_uimovie,loc_argstr,loc_res,".loadWidget")
    RESETOUTPUT(a_root)

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

    SKSELOG("SetPos({},{},{}) called",a_root,loc_argstr1,loc_argstr2) //logging

    GETHUD(loc_uimovie,)
    INVOKEARGNORES2(a_root,loc_uimovie,loc_argstr1,loc_argstr2,".setXPos",".setYPos")
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

    SKSELOG("SetSize({},{},{}) called",a_root,loc_argstr1,loc_argstr2) //logging

    GETHUD(loc_uimovie,)
    INVOKEARGNORES2(a_root,loc_uimovie,loc_argstr1,loc_argstr2,".setHeight",".setWidth")
}

int IWW::GetSize(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_type)
{
    std::string loc_argstr = std::string(std::to_string(a_id));

    SKSELOG("GetPos({},{}) called",a_root,a_type) //logging

    GETHUD(loc_uimovie,0)

    if (a_type == 0) 
    {
        INVOKEARGNORES(a_root,loc_uimovie,loc_argstr,".getXsize") 
    }
    else 
    {
        INVOKEARGNORES(a_root,loc_uimovie,loc_argstr,".getYsize")
    }

    RESETOUTPUT(a_root)

    return ROUND(RESETOUTPUT_message.GetNumber());
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

    SKSELOG("SetZoom({},{},{}) called",a_root,loc_argstr1,loc_argstr2) //logging

    GETHUD(loc_uimovie,)
    INVOKEARGNORES2(a_root,loc_uimovie,loc_argstr1,loc_argstr2,".setXScale",".setYScale")
}

void IWW::SetVisible(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_visible)
{
    std::string loc_argstr = std::string(std::to_string(a_id) + "|" + std::to_string(a_visible));

    SKSELOG("SetVisible({},{}) called",a_root,loc_argstr) //logging

    GETHUD(loc_uimovie,)
    INVOKEARGNORES(a_root,loc_uimovie,loc_argstr,".setVisible")
}

void IWW::SetRotation(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_rotation)
{
    std::string loc_argstr = std::string(std::to_string(a_id) + "|" + std::to_string(a_rotation));

    SKSELOG("SetRotation({},{}) called",a_root,loc_argstr) //logging

    GETHUD(loc_uimovie,)
    INVOKEARGNORES(a_root,loc_uimovie,loc_argstr,".setRotation")
}

void IWW::SetTransparency(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_alpha)
{
    std::string loc_argstr = std::string(std::to_string(a_id) + "|" + std::to_string(a_alpha));

    SKSELOG("SetTransparency({},{}) called",a_root,loc_argstr) //logging

    GETHUD(loc_uimovie,)
    INVOKEARGNORES(a_root,loc_uimovie,loc_argstr,".setAlpha")
}

void IWW::SetRGB(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_r, int a_g, int a_b)
{
    std::string     loc_argstr = std::string(
        std::to_string(a_id)   + "|" + 
        std::to_string(((a_r & 0xFF) << 16) | ((a_g & 0xFF) << 8) | (a_b & 0xFF))
    );

    SKSELOG("SetRGB({},{}) called",a_root,loc_argstr) //logging

    GETHUD(loc_uimovie,)
    INVOKEARGNORES(a_root,loc_uimovie,loc_argstr,".setColor")
}

void IWW::Destroy(PAPYRUSFUNCHANDLE, std::string a_root, int a_id)
{
    std::string     loc_argstr = std::string(
        std::to_string(a_id)
    );

    SKSELOG("Destroy({},{}) called",a_root,loc_argstr) //logging

    GETHUD(loc_uimovie,)
    INVOKEARGNORES(a_root,loc_uimovie,loc_argstr,".destroy")
}

void IWW::SetMeterPercent(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_perc)
{
    std::string loc_argstr = std::string(std::to_string(a_id) + "|" + std::to_string(a_perc));

    SKSELOG("SetMeterPercent({},{}) called",a_root,loc_argstr) //logging

    GETHUD(loc_uimovie,)
    INVOKEARGNORES(a_root,loc_uimovie,loc_argstr,".setMeterPercent")
}

void IWW::SetMeterFillDirection(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, std::string a_direction)
{
    std::string loc_argstr = std::string(std::to_string(a_id) + "|" + a_direction);

    SKSELOG("SetMeterFillDirection({},{}) called",a_root,loc_argstr) //logging

    GETHUD(loc_uimovie,)
    INVOKEARGNORES(a_root,loc_uimovie,loc_argstr,".setMeterFillDirection")
}

void IWW::SendToBack(PAPYRUSFUNCHANDLE, std::string a_root, int a_id)
{
    std::string loc_argstr = std::string(std::to_string(a_id));

    SKSELOG("SendToBack({},{}) called",a_root,loc_argstr) //logging

    GETHUD(loc_uimovie,)
    INVOKEARGNORES(a_root,loc_uimovie,loc_argstr,".sendToBack")
}

void IWW::SendToFront(PAPYRUSFUNCHANDLE, std::string a_root, int a_id)
{
    std::string loc_argstr = std::string(std::to_string(a_id));

    SKSELOG("SendToFront({},{}) called",a_root,loc_argstr) //logging

    GETHUD(loc_uimovie,)
    INVOKEARGNORES(a_root,loc_uimovie,loc_argstr,".sendToFront")
}

void IWW::DoMeterFlash(PAPYRUSFUNCHANDLE, std::string a_root, int a_id)
{
    std::string loc_argstr = std::string(std::to_string(a_id));

    SKSELOG("DoMeterFlash({},{}) called",a_root,loc_argstr) //logging

    GETHUD(loc_uimovie,)
    INVOKEARGNORES(a_root,loc_uimovie,loc_argstr,".doMeterFlash")
}

void IWW::SetMeterRGB(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, int a_lightR, int a_lightG, int a_lightB, int a_darkR, int a_darkG, int a_darkB, int a_flashR, int a_flashG, int a_flashB)
{
    std::string     loc_argstr = std::string(
        std::to_string(a_id)   + "|" + 
        std::to_string(((a_lightR & 0xFF) << 16) | ((a_lightG & 0xFF) << 8) | (a_lightB & 0xFF)) + "|" +
        std::to_string(((a_darkR & 0xFF) << 16) | ((a_darkG & 0xFF) << 8) | (a_darkB & 0xFF)) + "|" +
        std::to_string(((a_flashR & 0xFF) << 16) | ((a_flashG & 0xFF) << 8) | (a_flashB & 0xFF))
    );

    SKSELOG("SetMeterRGB({},{}) called",a_root,loc_argstr) //logging

    GETHUD(loc_uimovie,)
    INVOKEARGNORES(a_root,loc_uimovie,loc_argstr,".setMeterColors")
}

void IWW::SetText(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, std::string a_text)
{
    std::string     loc_argstr = std::string(
        std::to_string(a_id)   + "|" + 
        a_text
    );

    SKSELOG("SetText({},{}) called",a_root,loc_argstr) //logging

    GETHUD(loc_uimovie,)
    INVOKEARGNORES(a_root,loc_uimovie,loc_argstr,".setText")
}

void IWW::AppendText(PAPYRUSFUNCHANDLE, std::string a_root, int a_id, std::string a_text)
{
    std::string     loc_argstr = std::string(
        std::to_string(a_id)   + "|" + 
        a_text
    );

    SKSELOG("AppendText({},{}) called",a_root,loc_argstr) //logging

    GETHUD(loc_uimovie,)
    INVOKEARGNORES(a_root,loc_uimovie,loc_argstr,".AppendText")
}

void IWW::SwapDepths(PAPYRUSFUNCHANDLE, std::string a_root, int a_id1, int a_id2)
{
    std::string     loc_argstr = std::string(
        std::to_string(a_id1)   + "|" + 
        std::to_string(a_id2)
    );

    SKSELOG("SwapDepths({},{}) called",a_root,loc_argstr) //logging

    GETHUD(loc_uimovie,)
    INVOKEARGNORES(a_root,loc_uimovie,loc_argstr,".SwapDepths")
}
