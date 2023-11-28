#include "IWWCOnfig.h"

SINGLETONBODY(IWW::Config)

namespace IWW
{
    void Config::Setup()
    {
        _config = boost::property_tree::ptree();
        try
        {
            boost::property_tree::ini_parser::read_ini("Data\\skse\\plugins\\IWantWidgetsNative.ini", _config);
            _ready = true;
            LOG("IWantWidgetsNative.ini loaded succesfully")
        }
        catch( std::exception &ex )
        {
            ERROR("ERROR LOADING ini FILE: {}",ex.what())
            return;
        }

        //clean catche, so if game is reloaded, the catche will be also reloaded
        for (auto&& it : _catche) delete it.second;
        _catche.clear();
    }

    std::vector<std::string> Config::GetArrayRaw(std::string a_name, std::string a_sep) const
    {
        std::vector<std::string> loc_res;
        try
        {
            boost::split(loc_res,_config.get<std::string>(a_name),boost::is_any_of(a_sep));
        }
        catch(...)
        {
            ERROR("Can't get config array {} - Returning empty array",a_name)
            loc_res = std::vector<std::string>();
        }

        //remove additional spaces, and made the words lower case
        for (auto&& it : loc_res) 
        {
            const auto loc_first = it.find_first_not_of(' ');
            const auto loc_last  = it.find_last_not_of(' ');
            it = it.substr(loc_first,loc_last - loc_first + 1);
            std::transform(it.begin(), it.end(), it.begin(), ::tolower);
        }

        return loc_res;
    }

    template<typename T>
    T Config::GetVariable(std::string a_name, T a_def) const
    {
        if (!_ready) return a_def;
        void* loc_cres = _catche[a_name];
        if (loc_cres != nullptr) return *(T*)loc_cres;

        T loc_res;

        try
        {
            loc_res = _config.get<T>(a_name);
        }
        catch(...)
        {
            ERROR("Can't get config variable {} - Returning default value",a_name)
            loc_res = a_def;
        }

        _catche[a_name] = new T(loc_res);

        return loc_res;
    }

    template<typename T>
    std::vector<T> Config::GetArray(std::string a_name, std::string a_sep) const
    {
        if (!_ready) return std::vector<T>();

        void* loc_cres = _catche[a_name];
        if (loc_cres != nullptr) return *(std::vector<T>*)loc_cres;

        std::vector<std::string> loc_raw = GetArrayRaw(a_name,a_sep);
        std::vector<T> loc_res;

        for (auto&&it : loc_raw)
        {
            if (it != "") 
            {
                try
                {
                    loc_res.push_back(boost::lexical_cast<T>(it));
                }
                catch(...)
                {
                    ERROR("Cant cast {} to {} - Using default value",it,typeid(T).name())
                    loc_res.push_back(T());
                }
            }
        }

        _catche[a_name] = new std::vector<T>(loc_res);

        return loc_res;
    }

    template int Config::GetVariable<int>(std::string a_name, int a_def) const;
    template std::string Config::GetVariable<std::string>(std::string a_name, std::string a_def) const;
    template float Config::GetVariable<float>(std::string a_name, float a_def) const;
    template bool Config::GetVariable<bool>(std::string a_name, bool a_def) const;

    template std::vector<int> Config::GetArray<int>(std::string a_name, std::string a_sep) const;
    template std::vector<std::string> Config::GetArray<std::string>(std::string a_name, std::string a_sep) const;
    template std::vector<float> Config::GetArray<float>(std::string a_name, std::string a_sep) const;
    template std::vector<bool> Config::GetArray<bool>(std::string a_name, std::string a_sep) const;

}
