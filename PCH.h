#pragma once

#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"

//we are not making nasa sw, so stfu
#pragma warning( disable : 4100 ) 
#pragma warning( disable : 4244 )

using namespace std::literals;

#define PAPYRUSFUNCHANDLE RE::StaticFunctionTag*
#define PAPYRUSUNHOOKFPS true

#define ROUND(x) std::floor(static_cast<float>(x + 0.5f))

// 2=TRACE,1=ERROR,0=OFF
#define LOGGING 0  

#if(LOGGING > 0)
    #include <spdlog/sinks/basic_file_sink.h>
    #define ERRORLOG(...) { SKSE::log::info(__VA_ARGS__); }
    #if (LOGGING > 1)
        #define SKSELOG(...) { SKSE::log::info(__VA_ARGS__); }
    #else
        #define SKSELOG(...) {}
    #endif
#else
    #define SKSELOG(...) {}
    #define ERRORLOG(...) {}
#endif

