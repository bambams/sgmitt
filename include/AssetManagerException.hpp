#ifndef ASSET_MANAGER_EXCEPTION_HPP
    #define ASSET_MANAGER_EXCEPTION_HPP

    #include <al5poly/Exception.hpp>

class AssetManagerException;

class AssetManagerException:
    public al5poly::Exception
{
public:
    AssetManagerException(const std::string &);
};

#endif
