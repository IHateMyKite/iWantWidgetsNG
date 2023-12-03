#include <IWWPapyrus.h>
#include <IWWFunctions.h>

bool IWW::RegisterPapyrusFunctions(RE::BSScript::IVirtualMachine* vm)
{
    const bool loc_unhook = IWW::Config::GetSingleton()->GetVariable<bool>("General.UnhookPapyrus",true);

    #if (PAPYRUSUNHOOKFPSALL == 1)
        #define REGISTERPAPYRUSFUNC(name,unhook) {vm->RegisterFunction(#name, "iwant_widgets_native", IWW::name,loc_unhook);}
    #else
        #define REGISTERPAPYRUSFUNC(name,unhook) {vm->RegisterFunction(#name, "iwant_widgets_native", IWW::name,unhook && loc_unhook);}
    #endif

    REGISTERPAPYRUSFUNC(LoadMeter,true)
    REGISTERPAPYRUSFUNC(LoadText,true)
    REGISTERPAPYRUSFUNC(LoadWidget,true)

    REGISTERPAPYRUSFUNC(SetPos,true)
    REGISTERPAPYRUSFUNC(SetPosX,true)
    REGISTERPAPYRUSFUNC(SetPosY,true)
    REGISTERPAPYRUSFUNC(SetSize,true)
    REGISTERPAPYRUSFUNC(SetSizeH,true)
    REGISTERPAPYRUSFUNC(SetSizeW,true)
    REGISTERPAPYRUSFUNC(GetSize,true)
    REGISTERPAPYRUSFUNC(SetZoom,true)
    REGISTERPAPYRUSFUNC(SetZoomX,true)
    REGISTERPAPYRUSFUNC(SetZoomY,true)
    REGISTERPAPYRUSFUNC(SetVisible,true)
    REGISTERPAPYRUSFUNC(SetRotation,true)
    REGISTERPAPYRUSFUNC(SetTransparency,true)
    REGISTERPAPYRUSFUNC(SetRGB,true)
    REGISTERPAPYRUSFUNC(Destroy,true)

    REGISTERPAPYRUSFUNC(SetMeterPercent,true)
    REGISTERPAPYRUSFUNC(SetMeterFillDirection,true)
    REGISTERPAPYRUSFUNC(SendToBack,true)
    REGISTERPAPYRUSFUNC(SendToFront,true)
    REGISTERPAPYRUSFUNC(DoMeterFlash,true)
    REGISTERPAPYRUSFUNC(SetMeterRGB,true)

    REGISTERPAPYRUSFUNC(SetText,true)
    REGISTERPAPYRUSFUNC(AppendText,true)
    REGISTERPAPYRUSFUNC(SwapDepths,true)

    REGISTERPAPYRUSFUNC(DrawShapeLine,true)
    REGISTERPAPYRUSFUNC(DrawShapeCircle,true)
    REGISTERPAPYRUSFUNC(DrawShapeOrbit,true)

    REGISTERPAPYRUSFUNC(DoTransitionByTime,true)

    REGISTERPAPYRUSFUNC(IsHudReady,true)
    REGISTERPAPYRUSFUNC(Reset,true)
    REGISTERPAPYRUSFUNC(IsResetting,true)
    REGISTERPAPYRUSFUNC(GetOutput,true)

    #undef REGISTERPAPYRUSFUNC
    return true;
}
