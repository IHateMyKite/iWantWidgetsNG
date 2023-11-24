#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

namespace IWW
{
    class Config
    {
    SINGLETONHEADER(Config)
    public:
        void Update();
        
        bool IsInstalled(){return _installed;} 
        bool CFG_PAPYUNHOOK = true;
        bool CFG_USETASK    = true;
        int  CFG_LOGGING    = 2;
    private:
        boost::property_tree::ptree _config; 
        bool _installed = false;
    };

}