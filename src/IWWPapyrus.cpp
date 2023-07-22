#include <IWWPapyrus.h>
#include <IWWFunctions.h>

bool IWW::RegisterPapyrusFunctions(RE::BSScript::IVirtualMachine* vm)
{
    #define REGISTERPAPYRUSFUNC(name) {vm->RegisterFunction(#name, "iwant_widgets_native", IWW::name);}

    REGISTERPAPYRUSFUNC(LoadMeter)
    REGISTERPAPYRUSFUNC(LoadText)
    REGISTERPAPYRUSFUNC(LoadWidget)

    #undef REGISTERPAPYRUSFUNC
    return true;
}
