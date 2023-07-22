#include <IWWPapyrus.h>
#include <IWWFunctions.h>

bool IWW::RegisterPapyrusFunctions(RE::BSScript::IVirtualMachine* vm)
{
    #define REGISTERPAPYRUSFUNC(name) {vm->RegisterFunction(#name, "iwant_widgets_native", IWW::name);}

    REGISTERPAPYRUSFUNC(LoadMeter)
    REGISTERPAPYRUSFUNC(LoadText)
    REGISTERPAPYRUSFUNC(LoadWidget)

    REGISTERPAPYRUSFUNC(SetPos)
    REGISTERPAPYRUSFUNC(SetSize)
    REGISTERPAPYRUSFUNC(GetSize)
    REGISTERPAPYRUSFUNC(SetZoom)
    REGISTERPAPYRUSFUNC(SetVisible)
    REGISTERPAPYRUSFUNC(SetRotation)
    REGISTERPAPYRUSFUNC(SetTransparency)
    REGISTERPAPYRUSFUNC(SetRGB)
    REGISTERPAPYRUSFUNC(Destroy)

    REGISTERPAPYRUSFUNC(SetMeterPercent)
    REGISTERPAPYRUSFUNC(SetMeterFillDirection)
    REGISTERPAPYRUSFUNC(SendToBack)
    REGISTERPAPYRUSFUNC(SendToFront)
    REGISTERPAPYRUSFUNC(DoMeterFlash)
    REGISTERPAPYRUSFUNC(SetMeterRGB)

    REGISTERPAPYRUSFUNC(SetText)
    REGISTERPAPYRUSFUNC(AppendText)
    REGISTERPAPYRUSFUNC(SwapDepths)

    #undef REGISTERPAPYRUSFUNC
    return true;
}
