#include <IWWPapyrus.h>
#include <IWWFunctions.h>

bool IWW::RegisterPapyrusFunctions(RE::BSScript::IVirtualMachine* vm)
{
    const bool loc_unhook = IWW::Config::GetSingleton()->CFG_PAPYUNHOOK;

    #if (PAPYRUSUNHOOKFPSALL == 1)
        #define REGISTERPAPYRUSFUNC(name,unhook) {vm->RegisterFunction(#name, "iwant_widgets_native", IWW::name,loc_unhook);}
    #else
        #define REGISTERPAPYRUSFUNC(name,unhook) {vm->RegisterFunction(#name, "iwant_widgets_native", IWW::name,unhook && loc_unhook);}
    #endif

    REGISTERPAPYRUSFUNC(LoadMeter,false)
    REGISTERPAPYRUSFUNC(LoadText,false)
    REGISTERPAPYRUSFUNC(LoadWidget,false)

    REGISTERPAPYRUSFUNC(SetPos,true)
    REGISTERPAPYRUSFUNC(SetSize,true)
    REGISTERPAPYRUSFUNC(GetSize,false)
    REGISTERPAPYRUSFUNC(SetZoom,true)
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

    #undef REGISTERPAPYRUSFUNC
    return true;
}
