#include "stdafx.h"
#include "LGPConfig.h"
#include "../tinyxml/tinyxml.h"
#include "../LGPUtil/LGPExitSystem.h"
#include "../LGPConstants/LGPFlags.h"
#include <sstream>
#include <iostream>
#include "../XSUtil.h"

LGPConfig::LGPConfig(const char* filename)
: m_dEpsilon(1E-10)
{
	TiXmlDocument doc;
	if(!doc.LoadFile(filename))
	{
		LGPExitSystem("LGPConfig::LGPConfig()", "Failed to load lgp_config.xml");
	}

	TiXmlElement* xmlRoot=doc.RootElement();
	for(TiXmlElement* xml_level1=xmlRoot->FirstChildElement(); xml_level1!=NULL; xml_level1=xml_level1->NextSiblingElement())
	{
		if(strcmp(xml_level1->Value(), "parameters")==0)
		{
			for(TiXmlElement* xml_level2=xml_level1->FirstChildElement(); xml_level2 != NULL; xml_level2=xml_level2->NextSiblingElement())
			{
				if(strcmp(xml_level2->Value(), "param")==0)
				{
					if(strcmp(xml_level2->Attribute("name"), "NumRegisters")==0)
					{
						int value=0;
						xml_level2->QueryIntAttribute("value", &value);
						m_iNumRegisters=value;
					}
					else if(strcmp(xml_level2->Attribute("name"), "PopulationSize")==0)
					{
						int value=0;
						xml_level2->QueryIntAttribute("value", &value);
						m_iPopulationSize=value;
					}
					else if(strcmp(xml_level2->Attribute("name"), "Epsilon")==0)
					{
						xml_level2->QueryDoubleAttribute("value", &m_dEpsilon);
					}
					else if(strcmp(xml_level2->Attribute("name"), "MaxGenerations")==0)
					{
						int value=0;
						xml_level2->QueryIntAttribute("value", &value);
						m_iMaxGenerations=value;
					}
					else if(strcmp(xml_level2->Attribute("name"), "Maximization")==0)
					{
						if(strcmp(xml_level2->Attribute("value"), "true")==0)
						{
							m_bMaximization=true;
						}
						else
						{
							m_bMaximization=false;
						}
					}
					else if(strcmp(xml_level2->Attribute("name"), "CrossoverRate")==0)
					{
						xml_level2->QueryDoubleAttribute("value", &m_crossover_rate);
					}
					else if(strcmp(xml_level2->Attribute("name"), "MacroMutationRate")==0)
					{
						xml_level2->QueryDoubleAttribute("value", &m_macro_mutation_rate);
					}
					else if(strcmp(xml_level2->Attribute("name"), "MicroMutationRate")==0)
					{
						xml_level2->QueryDoubleAttribute("value", &m_micro_mutation_rate);
					}
				}
			}
		}
		else if(strcmp(xml_level1->Value(), "log_parameters")==0)
		{
			for(TiXmlElement* xml_level2=xml_level1->FirstChildElement(); xml_level2 != NULL; xml_level2=xml_level2->NextSiblingElement())
			{
				if(strcmp(xml_level2->Value(), "param")==0)
				{
					if(strcmp(xml_level2->Attribute("name"), "PopLogFilePath")==0)
					{
						m_PopLogFilePath=xml_level2->Attribute("value");
					}
					else if(strcmp(xml_level2->Attribute("name"), "StatsLogFilePath")==0)
					{
						m_StatsLogFilePath=xml_level2->Attribute("value");
					}
					else if(strcmp(xml_level2->Attribute("name"), "RunLogFilePath")==0)
					{
						m_RunLogFilePath=xml_level2->Attribute("value");
					}
					else if(strcmp(xml_level2->Attribute("name"), "PopLogInterval")==0)
					{
						int value;
						xml_level2->QueryIntAttribute("value", &value);
						m_iPopLogInterval=value;
					}
				}
			}
		}
		else if(strcmp(xml_level1->Value(), "micro_mutation")==0)
		{
			for(TiXmlElement* xml_level2=xml_level1->FirstChildElement(); xml_level2 != NULL; xml_level2=xml_level2->NextSiblingElement())
			{
				if(strcmp(xml_level2->Value(), "mutation_type_probability")==0)
				{
					xml_level2->QueryDoubleAttribute("operator_mutation", &m_micro_mutate_operator_rate);
					xml_level2->QueryDoubleAttribute("register_mutation", &m_micro_mutate_register_rate);
					xml_level2->QueryDoubleAttribute("constant_mutation", &m_micro_mutate_constant_rate);
					double sum=m_micro_mutate_operator_rate + m_micro_mutate_register_rate + m_micro_mutate_constant_rate;
					m_micro_mutate_operator_rate/=sum;
					m_micro_mutate_register_rate/=sum;
					m_micro_mutate_constant_rate/=sum;
				}
				else if(strcmp(xml_level2->Value(), "constant_mutation")==0)
				{
					xml_level2->QueryDoubleAttribute("standard_deviation", &m_micro_mutate_constant_standard_deviation);
				}
			}
		}
		else if(strcmp(xml_level1->Value(), "constant_reg")==0)
		{
			for(TiXmlElement* xml_level2=xml_level1->FirstChildElement(); xml_level2 != NULL; xml_level2=xml_level2->NextSiblingElement())
			{
				if(strcmp(xml_level2->Value(), "constant")==0)
				{
					double value, weight;
					xml_level2->QueryDoubleAttribute("value", &value);
					xml_level2->QueryDoubleAttribute("weight", &weight);
					m_constant_regs.push_back(std::make_pair<double, double>(value, weight));
				}
			}
		}
		else if(strcmp(xml_level1->Value(), "lgp_scripts")==0)
		{
			for(TiXmlElement* xml_level2=xml_level1->FirstChildElement(); xml_level2 != NULL; xml_level2=xml_level2->NextSiblingElement())
			{
				if(strcmp(xml_level2->Value(), "script")==0)
				{
					std::string script_name=xml_level2->Attribute("name");
					std::string script_src=xsUtil.GetFullPath(xml_level2->Attribute("src"));
					m_lgp_scripts[script_name]=script_src;
				}
			}
		}
		else if(strcmp(xml_level1->Value(), "evolution")==0)
		{
			std::string strategy_name=xml_level1->Attribute("strategy");
			if(strategy_name.compare("steady_state")==0)
			{
				m_evolutionary_strategy=LGP_EVOLUTION_STRATEGY_STEADY_STATE;
			}
			else if(strategy_name.compare("generational")==0)
			{
				m_evolutionary_strategy=LGP_EVOLUTION_STRATEGY_GENERATIONAL;
			}
			else
			{
				LGPExitSystem("LGPConfig::LGPConfig(const char*)", "m_evolutionary_strategy is undefined");
			}
			for(TiXmlElement* xml_level2=xml_level1->FirstChildElement(); xml_level2 != NULL; xml_level2=xml_level2->NextSiblingElement())
			{
				if(strcmp(xml_level2->Value(), "strategy")==0)
				{
					if(strcmp(xml_level2->Attribute("name"), strategy_name.c_str())==0)
					{
						int value=0;
						xml_level2->QueryIntAttribute("elites", &value);
						if(value < 0) value=-value;
						m_elites=value;
					}
				}
			}
		}
	}
}

LGPConfig::~LGPConfig()
{

}

std::string LGPConfig::ToString() const
{
	std::ostringstream oss;

	oss << "////////////////////////////////////////////////////" << std::endl;

	oss << "parameters: " << std::endl;
	oss << "NumRegisters: " << m_iNumRegisters << std::endl;
	oss << "PopulationSize: " << m_iPopulationSize << std::endl;
	oss << "Epsilon: " << m_dEpsilon << std::endl;
	oss << "MaxGenerations: " << m_iMaxGenerations << std::endl;
	oss << "Maximization: " << (m_bMaximization ? "true" : "false") << std::endl;

	oss << "////////////////////////////////////////////////////" << std::endl;

	oss << "log_parameters: " << std::endl;
	oss << "PopLogInterval: " << m_iPopLogInterval << std::endl;
	oss << "PopLogFilePath: " << m_PopLogFilePath << std::endl;
	oss << "StatsLogFilePath: " << m_StatsLogFilePath << std::endl;
	oss << "RunLogFilePath: " << m_RunLogFilePath << std::endl;

	oss << "////////////////////////////////////////////////////" << std::endl;

	oss << "micro mutation type selection probability: " << std::endl;
	oss << ">> operator(" << m_micro_mutate_operator_rate * 100 << "%) " << std::endl;
	oss << ">> register(" << m_micro_mutate_register_rate * 100 << "%) " << std::endl;
	oss << ">> constant(" << m_micro_mutate_constant_rate * 100 << "%)" << std::endl;
	
	oss << "micro mutate constant: " << std::endl;
	oss << ">> standard deviation = " << m_micro_mutate_constant_standard_deviation << std::endl;

	oss << "////////////////////////////////////////////////////" << std::endl;

	oss << "constant registers: " << std::endl;
	for(unsigned int i=0; i<m_constant_regs.size(); i++)
	{
		oss << "constants[" << i << "]: " << m_constant_regs[i].first << " (weight=" << m_constant_regs[i].second << ")" << std::endl;
	}

	return oss.str();
}

std::string LGPConfig::GetScript(std::string script_name) const
{
	std::map<std::string, std::string>::const_iterator pos=m_lgp_scripts.find(script_name);
#ifdef LGP_DEBUG
	
	if(pos==m_lgp_scripts.end())
	{
		LGPExitSystem("LGPConfig::GetScript(std::string script_name) const", "iterator==m_lgp_scripts.end()");
	}
#endif

	return pos->second;
}