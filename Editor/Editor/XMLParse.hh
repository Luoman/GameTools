#ifndef XMLPARSE_HH
#define XMLPARSE_HH

#include    "Map.hh"
#include	"./XML/tinyxml.h"

class XMLParse
{
public:
    XMLParse();

public:
    bool            serialize(const std::string &path, const std::string &fileName, Map *map);
    bool            serialize_background(const std::string &path, const std::string &fileName, Map *map);
    Map             *unserialize(const std::string &path, const std::string &fileName);
    bool             unserialize_background(const std::string &path, const std::string &fileName, Map *map);

private:
    TiXmlDocument	m_xDoc;
};

#endif // XMLPARSE_HH
