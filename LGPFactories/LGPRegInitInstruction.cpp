#include "stdafx.h"
#include "LGPRegInitInstruction.h"

LGPRegInitInstruction::LGPRegInitInstruction()
: m_default_register_value(1)
{

}

LGPRegInitInstruction::LGPRegInitInstruction(TiXmlElement* xml_level1)
: m_default_register_value(1)
{

}

LGPRegInitInstruction::~LGPRegInitInstruction()
{

}
