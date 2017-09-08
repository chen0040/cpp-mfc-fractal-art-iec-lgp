#include "stdafx.h"
#include "LGPProtectedDefinition.h"
#include "../tinyxml/tinyxml.h"
#include "../LGPUtil/LGPExitSystem.h"
#include <iostream>
#include "../XSUtil.h"

LGPProtectedDefinition::LGPProtectedDefinition()
{
	TiXmlDocument doc;
	if(!doc.LoadFile(xsUtil.GetFullPath("LGPUndefined.xml").c_str()))
	{
		LGPExitSystem("LGPUndefined::LGPUndefined()", "Failed to load LGPUndefined.xml");
	}

	TiXmlElement* xml_root=doc.RootElement();
	for(TiXmlElement* xml_level1=xml_root->FirstChildElement(); xml_level1 != NULL; xml_level1=xml_level1->NextSiblingElement())
	{
		if(strcmp(xml_level1->Value(), "C_undef")==0)
		{
			for(TiXmlElement* xml_level2=xml_level1->FirstChildElement(); xml_level2 != NULL; xml_level2=xml_level2->NextSiblingElement())
			{
				if(strcmp(xml_level2->Value(), "param")==0)
				{
					if(strcmp(xml_level2->Attribute("name"), xml_level1->Attribute("use"))==0)
					{
						xml_level2->QueryDoubleAttribute("value", &m_C_UNDEFINED);
					}
				}
			}
		}
		else if(strcmp(xml_level1->Value(), "LGP_REG_POSITIVE_INF")==0)
		{
			xml_level1->QueryDoubleAttribute("value", &m_REG_POSITIVE_INFINITE);
		}
		else if(strcmp(xml_level1->Value(), "LGP_REG_NEGATIVE_INF")==0)
		{
			xml_level1->QueryDoubleAttribute("value", &m_REG_NEGATIVE_INFINITE);
		}
	}
}

LGPProtectedDefinition::~LGPProtectedDefinition()
{

}

LGPProtectedDefinition* LGPProtectedDefinition::Instance()
{
	static LGPProtectedDefinition theInstance;
	return &theInstance;
}