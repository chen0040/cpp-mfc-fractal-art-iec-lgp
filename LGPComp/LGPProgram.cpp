#include "stdafx.h"
#include "LGPProgram.h"
#include "../LGPUtil/LGPRandom.h"
#include <sstream>
#include "../LGPConstants/LGPFlags.h"
#include "../LGPUtil/LGPExitSystem.h"
#include <iomanip>
#include <fstream>
#include <iostream>
#include "../tinyxml/tinyxml.h"
#include "../lgp_misc/string_manip.h"

LGPProgram::LGPProgram(LGPConfig* lgpConfig)
: m_dFitness(0)
, m_bFitnessValid(false)
, m_bSetup(false)
, m_lgpConfig(lgpConfig)
, m_lgpRegInitInstructionFactory(NULL)
, m_operator_set(NULL)
, m_register_set(NULL)
, m_constant_set(NULL)
{

}

LGPProgram::~LGPProgram()
{	
	Destroy();
}

void LGPProgram::Destroy()
{
	EraseInstructions();

	if(m_operator_set != NULL)
	{
		delete m_operator_set;
		m_operator_set = NULL;
	}

	if(m_register_set != NULL)
	{
		delete m_register_set;
		m_register_set = NULL;
	}

	if(m_constant_set != NULL)
	{
		delete m_constant_set;
		m_constant_set=NULL;
	}

	if(m_lgpRegInitInstructionFactory != NULL)
	{
		delete m_lgpRegInitInstructionFactory;
		m_lgpRegInitInstructionFactory=NULL;
	}

	m_bSetup=false;
	m_bFitnessValid=false;
	m_dFitness=0;
}

const LGPConfig* LGPProgram::GetConfig() const
{
	return m_lgpConfig;
}

void LGPProgram::EvaluateFitness(LGPEnvironment* env)
{
	this->MarkStructuralIntrons();

	unsigned int iFitnessCaseCount=env->GetFitnessCaseCount();
	std::vector<LGPFitnessCase*> cases;
	for(unsigned int i=0; i<iFitnessCaseCount; i++)
	{
		LGPFitnessCase* fitness_case=env->CreateFitnessCase(i);
		this->InitializeProgramRegisters(fitness_case);
		this->EvaluateFitnessCase(fitness_case);
		cases.push_back(fitness_case);
	}

	m_objective_value=EvaluateFitness(cases);
	if(this->GetConfig()->IsMaximization())
	{
		m_dFitness=m_objective_value;
	}
	else
	{
		m_dFitness=-m_objective_value;
	}

	for(unsigned int i=0; i<iFitnessCaseCount;  i++)
	{
		delete cases[i];
	}

	m_bFitnessValid=true;
}

void LGPProgram::EraseInstructions()
{
	for(size_t i=0; i<m_instructions.size(); ++i)
	{
		delete m_instructions[i];
	}
	m_instructions.clear();
}

std::string LGPProgram::GetFactoryInfo() const
{
	std::ostringstream oss;
	oss << "register initialization instruction: " << std::endl;
	oss << m_lgpRegInitInstructionFactory->ToString() << std::endl;

	return oss.str();
}

unsigned int LGPProgram::GetEffectiveInstructionCount() const
{
#ifdef LGP_DEBUG
	if(!m_bFitnessValid)
	{
		LGPExitSystem("LGPProgram::GetEffectiveInstructionCount() const", "Fitness not valid implying introns are not marked correctly at the current stage\nPlease call MarkedStructuralIntrons() first before calling this function");
	}
#endif

	std::vector<LGPInstruction*>::const_iterator pos_instruction;
	unsigned int count=0;
	for(pos_instruction=m_instructions.begin(); pos_instruction != m_instructions.end(); ++pos_instruction)
	{
		if(!(*pos_instruction)->IsStructuralIntron())
		{
			count++;
		}
	}
	return count;
}

LGPProgram::LGPProgram(const LGPProgram& rhs)
{
	m_bSetup=rhs.m_bSetup;
	m_dFitness=rhs.m_dFitness;
	m_objective_value=rhs.m_objective_value;
	m_bFitnessValid=rhs.m_bFitnessValid;

	m_register_set=rhs.m_register_set->Clone();
	m_operator_set=rhs.m_operator_set->Clone();
	m_constant_set=rhs.m_constant_set->Clone();

	m_instructions.reserve(rhs.m_instructions.size());

	for(size_t i=0; i<rhs.m_instructions.size(); i++)
	{
		m_instructions.push_back(rhs.m_instructions[i]->Clone());
		m_instructions[i]->SetOwnership(this);
	}

	m_lgpConfig=rhs.m_lgpConfig;
	m_lgpRegInitInstructionFactory=rhs.m_lgpRegInitInstructionFactory->Clone(); //this->CreateRegInitInstructionFactory(m_lgpConfig->GetScript("LGPRegInitInstructionFactory").c_str());
}

void LGPProgram::CreateFromScript(std::string script_name)
{
	TiXmlDocument doc;
	if(!doc.LoadFile(script_name.c_str()))
	{
		std::ostringstream oss_err;
		oss_err << "Failed to load " << script_name;
		LGPExitSystem("LGPProgram::CreateFromScript(std::string script_name)", oss_err.str().c_str());
	}

	Destroy();

	ASSERT(m_bSetup==false);
	this->Setup();

	TiXmlElement* xml_root=doc.RootElement();

	for(TiXmlElement* xml_level1=xml_root->FirstChildElement(); xml_level1 != NULL; xml_level1=xml_level1->NextSiblingElement())
	{
		if(strcmp(xml_level1->Value(), "parameters")==0)
		{
			for(TiXmlElement* xml_level2=xml_level1->FirstChildElement(); xml_level2 != NULL; xml_level2=xml_level2->NextSiblingElement())
			{
				if(strcmp(xml_level2->Value(), "param")==0)
				{
					std::string param_name=xml_level2->Attribute("name");
					std::string param_value=xml_level2->Attribute("value");
					m_parameter_list[param_name]=param_value;
				}
			}
		}
		else if(strcmp(xml_level1->Value(), "code_segment")==0)
		{
			for(TiXmlElement* xml_level2=xml_level1->FirstChildElement(); xml_level2 != NULL; xml_level2=xml_level2->NextSiblingElement())
			{
				if(strcmp(xml_level2->Value(), "instruction")==0)
				{
					LGPInstruction* lgp_instruction=new LGPInstruction(this);		
					LGPOperator* op=NULL;
					LGPRegister* operand1=NULL;
					LGPRegister* operand2=NULL;
					LGPRegister* destination_register=NULL;

					for(TiXmlElement* xml_level3=xml_level2->FirstChildElement(); xml_level3 != NULL; xml_level3=xml_level3->NextSiblingElement())
					{
						if(strcmp(xml_level3->Value(), "op")==0)
						{
							int value;
							xml_level3->QueryIntAttribute("register_index", &value);
							unsigned int op_index=value;
							op=m_operator_set->GetOperator(op_index);
						}
						else if(strcmp(xml_level3->Value(), "operand_one")==0)
						{
							int value;
							xml_level3->QueryIntAttribute("register_index", &value);
							unsigned int register_index=value;
							if(strcmp(xml_level3->Attribute("type"), "register")==0)
							{
								operand1=m_register_set->GetRegister(register_index);
							}
							else if(strcmp(xml_level3->Attribute("type"), "constant")==0)
							{
								operand1=m_constant_set->GetRegister(register_index);
							}
						}
						else if(strcmp(xml_level3->Value(), "operand_two")==0)
						{
							int value;
							xml_level3->QueryIntAttribute("register_index", &value);
							unsigned int register_index=value;
							if(strcmp(xml_level3->Attribute("type"), "register")==0)
							{
								operand2=m_register_set->GetRegister(register_index);
							}
							else if(strcmp(xml_level3->Attribute("type"), "constant")==0)
							{
								operand2=m_constant_set->GetRegister(register_index);
							}
						}
						else if(strcmp(xml_level3->Value(), "destination_register")==0)
						{
							int value;
							xml_level3->QueryIntAttribute("register_index", &value);
							unsigned int register_index=value;
							destination_register=m_register_set->GetRegister(register_index);
						}
					}
					if(op==NULL || operand1==NULL || operand2==NULL || destination_register==NULL)
					{
						LGPExitSystem("LGPProgram::CreateFromScript(std::string script_name)", "Failed to interpret script");
					}

					lgp_instruction->Create(op, operand1, operand2, destination_register);
					m_instructions.push_back(lgp_instruction);
				}
			}
		}
	}
}

void LGPProgram::BuildCodes(std::string script_name, std::string function_name, std::string output_location)
{
	m_operator_set->WriteHeaderFiles(output_location, "lgp_operators.h");
	m_operator_set->WriteSourceFiles(output_location, "lgp_operators.cpp", "lgp_operators.h");

	TiXmlDocument doc;
	if(!doc.LoadFile(script_name.c_str()))
	{
		std::ostringstream oss_error;
		oss_error << "Failed to read the script file " << script_name;
		LGPExitSystem("LGPProgram::BuildCodes(std::string script_name)", oss_error.str().c_str());
	}

	std::ofstream program_header_file(lgp_join(output_location, "\\lgp_program.h").c_str());
	program_header_file << "#ifndef _H_LGP_PROGRAM_H\n";
	program_header_file << "#define _H_LGP_PROGRAM_H\n";
	program_header_file << "#include <vector>\n";
	program_header_file << "#include \"lgp_operators.h\"\n";
	program_header_file << "\n";

	program_header_file << "std::vector<double> " << function_name << "(double* input)\n";
	program_header_file << "{\n";

	TiXmlElement* xml_root=doc.RootElement();
	for(TiXmlElement* xml_level1=xml_root->FirstChildElement(); xml_level1 != NULL; xml_level1 = xml_level1->NextSiblingElement())
	{
		if(strcmp(xml_level1->Value(), "constant_segment")==0)
		{
			int constant_count=0;
			xml_level1->QueryIntAttribute("constant_count", &constant_count);
			
			for(TiXmlElement* xml_level2=xml_level1->FirstChildElement(); xml_level2 != NULL; xml_level2=xml_level2->NextSiblingElement())
			{
				if(strcmp(xml_level2->Value(), "constant")==0)
				{
					int index=0;
					xml_level2->QueryIntAttribute("index", &index);
					double value=0.0;
					xml_level2->QueryDoubleAttribute("value", &value);
					program_header_file << "\tstatic const double constant" << index << "=" << value << ";\n";
				}
			}

			if(constant_count > 0) program_header_file << "\n";
		}
		else if(strcmp(xml_level1->Value(), "register_segment")==0)
		{
			int register_count=0;
			xml_level1->QueryIntAttribute("register_count", &register_count);
			program_header_file << "\tstd::vector<double> registers(" << register_count << ", 0);\n";
			for(TiXmlElement* xml_level2=xml_level1->FirstChildElement(); xml_level2 != NULL; xml_level2=xml_level2->NextSiblingElement())
			{
				if(strcmp(xml_level2->Value(), "register")==0)
				{
					int index=0;
					xml_level2->QueryIntAttribute("index", &index);
					double default_value=0.0;
					xml_level2->QueryDoubleAttribute("default_value", &default_value);
					int input_alias_index=-1;
					xml_level2->QueryIntAttribute("input_alias_index", &input_alias_index);
					if(input_alias_index < 0)
					{
						program_header_file << "\tregisters[" << index << "]=" << default_value << ";\n";
					}
					else
					{
						program_header_file << "\tregisters[" << index << "]=input[" << input_alias_index << "];\n";
					}
				}
			}
			program_header_file << "\n";
		}
		else if(strcmp(xml_level1->Value(), "code_segment")==0)
		{
			for(TiXmlElement* xml_level2=xml_level1->FirstChildElement(); xml_level2 != NULL; xml_level2=xml_level2->NextSiblingElement())
			{
				if(strcmp(xml_level2->Value(), "instruction")==0)
				{
					std::string op;
					std::string operand1;
					std::string operand2;
					std::string destination_register;
					bool is_conditional_construct=false;
					for(TiXmlElement* xml_level3=xml_level2->FirstChildElement(); xml_level3 != NULL; xml_level3=xml_level3->NextSiblingElement())
					{
						if(strcmp(xml_level3->Value(), "op")==0)
						{
							op=xml_level3->Attribute("method_name");
							if(strcmp(xml_level3->Attribute("condictional_construct"), "true")==0)
							{
								is_conditional_construct=true;
							}
						}
						else if(strcmp(xml_level3->Value(), "operand_one")==0)
						{
							int register_index;
							xml_level3->QueryIntAttribute("register_index", &register_index);
							std::ostringstream oss_operand1;
							if(strcmp(xml_level3->Attribute("type"), "constant")==0)
							{
								oss_operand1 << "constant" << register_index;
							}
							else 
							{
								oss_operand1 << "registers[" << register_index << "]";
							}
							operand1=oss_operand1.str();
						}
						else if(strcmp(xml_level3->Value(), "operand_two")==0)
						{
							int register_index;
							xml_level3->QueryIntAttribute("register_index", &register_index);
							std::ostringstream oss_operand2;
							if(strcmp(xml_level3->Attribute("type"), "constant")==0)
							{
								oss_operand2 << "constant" << register_index;
							}
							else 
							{
								oss_operand2 << "registers[" << register_index << "]";
							}
							operand2=oss_operand2.str();
						}
						else if(strcmp(xml_level3->Value(), "destination_register")==0)
						{
							int register_index;
							xml_level3->QueryIntAttribute("register_index", &register_index);
							std::ostringstream oss_destination_register;
							oss_destination_register << "registers[" << register_index << "]";
							destination_register=oss_destination_register.str();
						}
					}

					program_header_file << "\t" 
						<< (is_conditional_construct ? "" : destination_register) 
						<< (is_conditional_construct ? "" : "=") << op 
						<< "(" << operand1 << ", " << operand2 << ")" 
						<< (is_conditional_construct ? "" : ";") << "\n";
				}
			}
		}
	}

	program_header_file << "\n";
	program_header_file << "\treturn registers;\n";
	program_header_file << "}\n";
	program_header_file << "#endif\n";
	program_header_file.close();

}

void LGPProgram::BuildScript(std::string script_name, unsigned int input_count, unsigned int output_count, const ParamPairList& params, bool effective_only, bool print_fitness) const
{
	TiXmlDocument doc;
	doc.LinkEndChild(new TiXmlDeclaration("1.0", "", ""));

	TiXmlElement* xml_root=new TiXmlElement("LGPProgram");
	xml_root->SetAttribute("input_count", static_cast<int>(input_count));
	xml_root->SetAttribute("output_count", static_cast<int>(output_count));
	doc.LinkEndChild(xml_root);

	TiXmlElement* xml_parameters=new TiXmlElement("parameters");
	ParamPairList::const_iterator pos_param;
	for(pos_param=params.begin(); pos_param != params.end(); ++pos_param)
	{
		TiXmlElement* xml_param=new TiXmlElement("param");
		xml_param->SetAttribute("name", pos_param->first.c_str());
		xml_param->SetAttribute("value", pos_param->second.c_str());
		xml_parameters->LinkEndChild(xml_param);
	}
	xml_root->LinkEndChild(xml_parameters);

	TiXmlElement* xml_constant_segment=new TiXmlElement("constant_segment");
	xml_constant_segment->SetAttribute("constant_count", m_constant_set->GetRegisterCount());
	for(unsigned int i=0; i<m_constant_set->GetRegisterCount(); i++)
	{
		TiXmlElement* xml_register=new TiXmlElement("constant");
		xml_register->SetAttribute("index", static_cast<int>(i));
		xml_register->SetDoubleAttribute("value", m_constant_set->GetRegister(i)->ToDouble());
		xml_constant_segment->LinkEndChild(xml_register);
	}
	xml_root->LinkEndChild(xml_constant_segment);

	TiXmlElement* xml_register_segment=new TiXmlElement("register_segment");
	xml_register_segment->SetAttribute("register_count", m_register_set->GetRegisterCount());
	int input_initialized_reg_count=m_lgpRegInitInstructionFactory->GetInputInitializedRegisterCount();
	for(unsigned int i=0; i<m_register_set->GetRegisterCount(); ++i)
	{
		TiXmlElement* xml_register=new TiXmlElement("register");
		xml_register->SetAttribute("index", static_cast<int>(i));
		if(input_initialized_reg_count < 0) 
		{
			xml_register->SetAttribute("input_alias_index", static_cast<int>(i % input_count));
		}
		else
		{
			if(i < static_cast<unsigned int>(input_initialized_reg_count)) xml_register->SetAttribute("input_alias_index", static_cast<int>(i % input_count));
			else xml_register->SetAttribute("input_alias_index", -1);
		}
		xml_register->SetDoubleAttribute("default_value", m_lgpRegInitInstructionFactory->GetDefaultRegValue());
		xml_register_segment->LinkEndChild(xml_register);
	}
	xml_root->LinkEndChild(xml_register_segment);

	TiXmlElement* xml_code_segment=new TiXmlElement("code_segment");
	xml_root->LinkEndChild(xml_code_segment);
	for(size_t i=0; i<m_instructions.size(); i++)
	{
		if(effective_only)
		{
			if(!m_instructions[i]->IsStructuralIntron())
			{
				TiXmlElement* xml_instruction=new TiXmlElement("instruction");
				xml_code_segment->LinkEndChild(xml_instruction);

				xml_instruction->SetAttribute("line", static_cast<int>(i));

				unsigned int op_index=m_instructions[i]->GetOperatorRegisterIndex();
				std::string op=m_operator_set->GetOperator(op_index)->ToString();
				std::string method_name=m_operator_set->GetOperator(op_index)->GetMethodName();

				TiXmlElement* xml_op=new TiXmlElement("op");
				xml_op->SetAttribute("type", op.c_str());
				xml_op->SetAttribute("register_index", op_index);
				xml_op->SetAttribute("method_name", method_name.c_str());
				if(m_instructions[i]->IsConditionalConstruct())
				{
					xml_op->SetAttribute("condictional_construct", "true");
				}
				else
				{
					xml_op->SetAttribute("condictional_construct", "false");
				}
				xml_instruction->LinkEndChild(xml_op);

				TiXmlElement* xml_operand1=new TiXmlElement("operand_one");
				unsigned int operand1_index=m_instructions[i]->GetOperand1RegisterIndex();
				xml_operand1->SetAttribute("register_index", operand1_index);
				if(m_instructions[i]->IsOperand1ConstantRegister())
				{	
					xml_operand1->SetAttribute("type", "constant");
				}
				else
				{
					xml_operand1->SetAttribute("type", "register");
				}
				xml_instruction->LinkEndChild(xml_operand1);

				TiXmlElement* xml_operand2=new TiXmlElement("operand_two");
				unsigned int operand2_index=m_instructions[i]->GetOperand2RegisterIndex();
				xml_operand2->SetAttribute("register_index", operand2_index);
				if(m_instructions[i]->IsOperand2ConstantRegister())
				{
					xml_operand2->SetAttribute("type", "constant");
				}
				else
				{
					xml_operand2->SetAttribute("type", "register");
				}
				xml_instruction->LinkEndChild(xml_operand2);

				TiXmlElement* xml_destination_register=new TiXmlElement("destination_register");
				unsigned int destination_register_index=m_instructions[i]->GetDestinationRegisterIndex();
				xml_destination_register->SetAttribute("register_index", destination_register_index);
				xml_destination_register->SetAttribute("type", "register");
				xml_instruction->LinkEndChild(xml_destination_register);
			}
		}
		else
		{
			TiXmlElement* xml_instruction=new TiXmlElement("instruction");
			xml_code_segment->LinkEndChild(xml_instruction);

			xml_instruction->SetAttribute("line", static_cast<int>(i));
			if(m_instructions[i]->IsConditionalConstruct())
			{
				xml_instruction->SetAttribute("condictional_construct", "true");
			}
			else
			{
				xml_instruction->SetAttribute("condictional_construct", "false");
			}

			unsigned int op_index=m_instructions[i]->GetOperatorRegisterIndex();
			std::string op=m_operator_set->GetOperator(op_index)->ToString();
			std::string method_name=m_operator_set->GetOperator(op_index)->GetMethodName();

			TiXmlElement* xml_op=new TiXmlElement("op");
			xml_op->SetAttribute("type", op.c_str());
			xml_op->SetAttribute("register_index", op_index);
			xml_op->SetAttribute("method_name", method_name.c_str());
			xml_instruction->LinkEndChild(xml_op);

			TiXmlElement* xml_operand1=new TiXmlElement("operand_one");
			unsigned int operand1_index=m_instructions[i]->GetOperand1RegisterIndex();
			xml_operand1->SetAttribute("register_index", operand1_index);
			if(m_instructions[i]->IsOperand1ConstantRegister())
			{	
				xml_operand1->SetAttribute("type", "constant");
			}
			else
			{
				xml_operand1->SetAttribute("type", "register");
			}
			xml_instruction->LinkEndChild(xml_operand1);

			TiXmlElement* xml_operand2=new TiXmlElement("operand_two");
			unsigned int operand2_index=m_instructions[i]->GetOperand2RegisterIndex();
			xml_operand2->SetAttribute("register_index", operand2_index);
			if(m_instructions[i]->IsOperand2ConstantRegister())
			{
				xml_operand2->SetAttribute("type", "constant");
			}
			else
			{
				xml_operand2->SetAttribute("type", "register");
			}
			xml_instruction->LinkEndChild(xml_operand2);
		}
	}

	
	if(print_fitness)
	{
		TiXmlElement* xml_fitness=new TiXmlElement("program_fitness");
		
		if(m_bFitnessValid)
		{
			xml_fitness->SetDoubleAttribute("objective_value", m_objective_value);
			xml_fitness->SetDoubleAttribute("fitness", m_dFitness);
			xml_fitness->SetAttribute("valid", "true");
		}
		else
		{
			xml_fitness->SetDoubleAttribute("objective_value", 0);
			xml_fitness->SetDoubleAttribute("fitness", 0);
			xml_fitness->SetAttribute("valid", "false");
		}

		xml_root->LinkEndChild(xml_fitness);
	}

	doc.SaveFile(script_name.c_str());
}

std::string LGPProgram::ToString(bool effective_only, bool print_fitness) const
{
	std::ostringstream oss;

	bool first_line=true;

	for(size_t i=0; i<m_instructions.size(); i++)
	{
		if(effective_only)
		{
			if(!m_instructions[i]->IsStructuralIntron())
			{
				if(first_line)
				{
					first_line=false;	
				}
				else
				{
					oss << "\n";
				}
				oss << "instruction[" << std::setw(2) << std::setfill('0')  << i << "]: " << m_instructions[i]->ToString();
			}
		}
		else
		{
			if(i != 0)
			{
				oss << "\n";
			}
			oss << "instruction[" << std::setw(2) << std::setfill('0')  << i << "]: " << m_instructions[i]->ToString();
		}
	}

	if(print_fitness)
	{
		if(m_bFitnessValid)
		{
			oss << "\nobjective_value: " << m_objective_value << std::endl;
			oss << "fitness: " << m_dFitness;
		}
		else
		{
			oss << "\nInvalid Fitness";
		}
	}

	return oss.str();
}

void LGPProgram::EvaluateFitnessCase(LGPFitnessCase* lgpFitnessCase)
{
	std::vector<LGPInstruction*>::iterator pos_instruction;
	int command=LGP_EXECUTE_NEXT_INSTRUCTION;
	LGPInstruction* current_effective_instruction=NULL;
	LGPInstruction* prev_effective_instruction=NULL;
	for(pos_instruction=m_instructions.begin(); pos_instruction != m_instructions.end(); ++pos_instruction)
	{
		if((*pos_instruction)->IsStructuralIntron())
		{
			continue;
		}
		prev_effective_instruction=current_effective_instruction;
		current_effective_instruction=*pos_instruction;
		if(command==LGP_EXECUTE_NEXT_INSTRUCTION)
		{
			command=current_effective_instruction->Execute(lgpFitnessCase);
			(*pos_instruction)->UpdateFitnessCase(lgpFitnessCase);
		}
		else
		{
			// Xianshun says:
			// as suggested in Linear Genetic Programming
			// the condictional construct is restricted to single condictional construct
			// an example of single conditional construct would be
			// line 1: if(register[a])
			// line 2: <action1>
			// line 3: <action2>
			// if register[a]==true, then <action1> and <action2> are executed
			// if register[a]==false, then <action1> is skipped and <action2> is executed
			// <action1> and <action2> are restricted to effective instruction
#ifdef LGP_DEBUG
			if(prev_effective_instruction == NULL)
			{
				LGPExitSystem("LGPProgram::Execute()", "prev_effective_instruction == NULL");
			}
#endif
			if(prev_effective_instruction->IsConditionalConstruct())
			{
				command=LGP_EXECUTE_NEXT_INSTRUCTION;	
			}
		}
	}
	
	lgpFitnessCase->Update(this->m_register_set);
}

void LGPProgram::MarkStructuralIntrons(unsigned int stop_point, std::set<unsigned int>& Reff)
{
	 /*
	Source: Brameier, M 2004  On Linear Genetic Programming (thesis)

	Algorithm 3.1 (detection of structural introns)
	1. Let set R_eff always contain all registers that are effective at the current program
	   position. R_eff := { r | r is output register }.
	   Start at the last program instruction and move backwards.
	2. Mark the next preceding operation in program with:
		destination register r_dest element-of R_eff.
	   If such an instruction is not found then go to 5.
	3. If the operation directly follows a branch or a sequence of branches then mark these
	   instructions too. Otherwise remove r_dest from R_eff .
	4. Insert each source (operand) register r_op of newly marked instructions in R_eff
	   if not already contained. Go to 2.
	5. Stop. All unmarked instructions are introns.
	*/

	// Xianshun says:
	// this is a variant of Algorithm 3.1 that run Algorithm 3.1 until stop_point and return the Reff at that stage

	unsigned int instruction_count=static_cast<unsigned int>(m_instructions.size());

#ifdef LGP_DEBUG
	if(instruction_count ==  0)
	{
		LGPExitSystem("LGPProgram::MarkStructuralIntrons(unsigned int stop_point, std::set<unsigned int>& Reff)", "instruction_count ==  0");
	}
#endif

	for(unsigned int i=instruction_count-1; i > stop_point; i--)
	{
		m_instructions[i]->SetStructuralIntronFlag(true);
	}

	Reff.clear();
	unsigned int iNumRegisters=m_lgpConfig->GetNumRegisters();
	for(unsigned int i=0; i < iNumRegisters; ++i)
	{
		Reff.insert(i);
	}

	LGPInstruction* current_instruction=NULL;
	LGPInstruction* prev_instruction=NULL; // prev_instruction is the last visited instruction from bottom up of the program 
	for(unsigned int i=instruction_count - 1; i > stop_point; i--)
	{
		prev_instruction=current_instruction;
		current_instruction=m_instructions[i];
		// prev_instruction is not an structural intron and the current_instruction
		// is a condictional construct then, the current_instruction is not structural intron either
		// this directly follows from Step 3 of Algorithm 3.1
		if(current_instruction->IsConditionalConstruct() && prev_instruction != NULL)
		{
			if(!prev_instruction->IsStructuralIntron())
			{
				current_instruction->SetStructuralIntronFlag(false);
			}
		}
		else
		{
			if(Reff.find(current_instruction->GetDestinationRegisterIndex()) != Reff.end())
			{
				current_instruction->SetStructuralIntronFlag(false);
				Reff.erase(current_instruction->GetDestinationRegisterIndex());

				if(!current_instruction->IsOperand1ConstantRegister())
				{
					Reff.insert(current_instruction->GetOperand1RegisterIndex());
				}
				if(!current_instruction->IsOperand2ConstantRegister())
				{
					Reff.insert(current_instruction->GetOperand2RegisterIndex());
				}
			}
		}
	}
}

void LGPProgram::MarkStructuralIntrons()
{
	 /*
	Source: Brameier, M 2004  On Linear Genetic Programming (thesis)

	Algorithm 3.1 (detection of structural introns)
	1. Let set R_eff always contain all registers that are effective at the current program
	   position. R_eff := { r | r is output register }.
	   Start at the last program instruction and move backwards.
	2. Mark the next preceding operation in program with:
		destination register r_dest element-of R_eff.
	   If such an instruction is not found then go to 5.
	3. If the operation directly follows a branch or a sequence of branches then mark these
	   instructions too. Otherwise remove r_dest from R_eff .
	4. Insert each source (operand) register r_op of newly marked instructions in R_eff
	   if not already contained. Go to 2.
	5. Stop. All unmarked instructions are introns.
	*/

	std::vector<LGPInstruction*>::reverse_iterator ri;
	for(ri=m_instructions.rbegin(); ri !=m_instructions.rend(); ++ri)
	{
		(*ri)->SetStructuralIntronFlag(true);
	}

	std::set<unsigned int> Reff;
	unsigned int iNumRegisters=m_lgpConfig->GetNumRegisters();
	for(unsigned int i=0; i < iNumRegisters; ++i)
	{
		Reff.insert(i);
	}

	LGPInstruction* current_instruction=NULL;
	LGPInstruction* prev_instruction=NULL; // prev_instruction is the last visited instruction from bottom up of the program 
	for(ri=m_instructions.rbegin(); ri != m_instructions.rend(); ++ri)
	{
		prev_instruction=current_instruction;
		current_instruction=*ri;
		// prev_instruction is not an structural intron and the current_instruction
		// is a condictional construct then, the current_instruction is not structural intron either
		// this directly follows from Step 3 of Algorithm 3.1
		if(current_instruction->IsConditionalConstruct() && prev_instruction != NULL)
		{
			if(!prev_instruction->IsStructuralIntron())
			{
				current_instruction->SetStructuralIntronFlag(false);
			}
		}
		else
		{
			if(Reff.find(current_instruction->GetDestinationRegisterIndex()) != Reff.end())
			{
				current_instruction->SetStructuralIntronFlag(false);
				Reff.erase(current_instruction->GetDestinationRegisterIndex());

				if(!current_instruction->IsOperand1ConstantRegister())
				{
					Reff.insert(current_instruction->GetOperand1RegisterIndex());
				}
				if(!current_instruction->IsOperand2ConstantRegister())
				{
					Reff.insert(current_instruction->GetOperand2RegisterIndex());
				}
			}
		}
	}
}

void LGPProgram::Create(unsigned int size)
{
	Destroy();

	ASSERT(m_bSetup==false);
	this->Setup();

	// Xianshun says:
	// In this method, the instruction created is not garanteed to be structurally effective
	for(unsigned int i=0; i<size; i++)
	{
		LGPInstruction* lgp_instruction=new LGPInstruction(this);
		lgp_instruction->Create();
		m_instructions.push_back(lgp_instruction);
	}
}

void LGPProgram::MicroMutate()
{
	// Xianshun says:
	// the micro-mutation is derived from Linear Genetic Programming 2004 chapter 6 section 6.2.2
	// three type selection probability are first determined and roulette wheel is used to decide which
	// mutation type is to be performed
	// 1. if micro-mutate-operator type is selected, then randomly pick an instruction and
	// randomly select an instruction and mutate its operator to some other operator from the operator set
	// 2. if micro-mutate-register type is selected, then randomly pick an instruction and 
	// randomly select one of the two operands, then
	// 2.1 with a constant selection probability p_{const}, a randomly selected constant register is assigned to the selected operand
	// 2.2 with probability 1-p_{const}, a randomly selected variable register is assigned to the selected operand
	// p_{const} is the proportion of instruction that holds a constant value.
	// 3. if micro-mutate-constant type is selected, then randomly pick an effective instruction with a constant as one
	// of its register value, mutate the constant to c+$N(0, \omega_{\mu}$
	double micro_mutate_operator_rate=m_lgpConfig->GetMicroMutateOperatorRate();
	double micro_mutate_register_rate=m_lgpConfig->GetMicroMutateRegisterRate();
	double micro_mutate_constant_rate=m_lgpConfig->GetMicroMutateConstantRate();

	double operator_sector=micro_mutate_operator_rate;
	double register_sector=operator_sector + micro_mutate_register_rate;
	
	double r=lgpRandom.nextDouble();
	if(r < operator_sector)
	{
		MutateInstructionOperator();
	}
	else if(r < register_sector)
	{
		MutateInstructionRegister();
	}
	else
	{
		MutateInstructionConstant();
	}

	this->TrashFitness();
}

void LGPProgram::MutateInstructionRegister()
{
	LGPInstruction* lgp_instruction=m_instructions[lgpRandom.nextInt(this->GetInstructionCount())];
	double p_const=0;
	std::vector<LGPInstruction*>::const_iterator pos_instruction;
	for(pos_instruction=m_instructions.begin(); pos_instruction != m_instructions.end(); ++pos_instruction)
	{
#ifdef LGP_DEBUG
		if((*pos_instruction)->IsOperand1ConstantRegister() && (*pos_instruction)->IsOperand2ConstantRegister())
		{
			LGPExitSystem("LGPProgram::MutateInstructionRegister()", "(*pos_instruction)->IsOperand1ConstantRegister() && (*pos_instruction)->IsOperand2ConstantRegister()");
		}
#endif
		if((*pos_instruction)->IsOperand1ConstantRegister() || (*pos_instruction)->IsOperand2ConstantRegister())
		{
			p_const+=1.0;
		}
	}
	p_const /= static_cast<double>(this->GetInstructionCount());

	lgp_instruction->MutateRegister(p_const);
}

void LGPProgram::MutateInstructionOperator()
{
	LGPInstruction* lgp_instruction=m_instructions[lgpRandom.nextInt(this->GetInstructionCount())];
	lgp_instruction->MutateOperator();
}

void LGPProgram::MutateInstructionConstant()
{
	// Xianshun says:
	// this is derived from the micro mutation implementation in section
	// 6.2.2 of Linear Genetic Programming
	// 1. randomly select an (effective) instruction with a constant c
	// 2. change constant c through a standard deviation from the current value
	// c:=c + normal(mean:=0, standard_deviation)
	std::vector<LGPInstruction*>::iterator pos_instruction;
	LGPInstruction* selected_instruction=NULL;
	for(pos_instruction=m_instructions.begin(); pos_instruction != m_instructions.end(); ++pos_instruction)
	{
		if((!(*pos_instruction)->IsStructuralIntron()) && ((*pos_instruction)->IsOperand1ConstantRegister() || (*pos_instruction)->IsOperand2ConstantRegister()))
		{
			if(selected_instruction == NULL)
			{
				selected_instruction=*pos_instruction;
			}
			else if(lgpRandom.nextDouble() < 0.5)
			{
				selected_instruction=*pos_instruction;
			}
		}
	}

	if(selected_instruction != NULL)
	{
		selected_instruction->MutateConstant(this->GetConfig()->GetMicroMutateConstantStandardDeviation());
	}
}

bool LGPProgram::IsBetterThan(const LGPProgram* rhs) const
{
#ifdef LGP_DEBUG
	if(!this->HasValidFitness())
	{
		LGPExitSystem("LGPProgram::IsBetterThan(const LGPProgram* rhs) const", "!this->HasValidFitness()");
	}
	if(!rhs->HasValidFitness())
	{
		LGPExitSystem("LGPProgram::IsBetterThan(const LGPProgram* rhs) const", "!rhs->HasValidFitness()");
	}
#endif
	return m_dFitness > rhs->GetFitness();
}

double LGPProgram::GetFitness() const
{
#ifdef LGP_DEBUG
	if(!this->HasValidFitness())
	{
		LGPExitSystem("LGPProgram::GetFitness() const", "!this->HasValidFitness()");
	}
#endif
	return m_dFitness;
}

double LGPProgram::GetObjectiveValue() const
{
#ifdef LGP_DEBUG
	if(!this->HasValidFitness())
	{
		LGPExitSystem("LGPProgram::GetObjectiveValue() const", "!this->HasValidFitness()");
	}
#endif

	return this->m_objective_value;
}

void LGPProgram::Setup()
{
	if(m_bSetup == false)
	{
		m_operator_set=this->CreateOperatorSet();
		m_register_set=this->CreateRegisterSet();
		m_constant_set=this->CreateConstantSet();

		m_lgpRegInitInstructionFactory=this->CreateRegInitInstructionFactory(m_lgpConfig->GetScript("LGPRegInitInstructionFactory").c_str());

		m_bSetup=true;
	}
}

LGPRegInitInstructionFactory* LGPProgram::CreateRegInitInstructionFactory(const char* filename)
{
	return new LGPRegInitInstructionFactory(filename);
}

void LGPProgram::InitializeProgramRegisters(const LGPFitnessCase* fitness_case)
{
	m_lgpRegInitInstructionFactory->InitializeRegisters(m_register_set, m_constant_set, fitness_case);
}

LGPRegisterSet* LGPProgram::CreateRegisterSet()
{
	LGPRegisterSet* reg_set=new LGPRegisterSet();
	unsigned int iNumReg=this->GetConfig()->GetNumRegisters();
	for(unsigned int i=0; i<iNumReg; i++)
	{
		reg_set->AddRegister(new LGPRegister());
	}

	return reg_set;
}

LGPConstantSet* LGPProgram::CreateConstantSet()
{
	LGPConstantSet* constant_set=new LGPConstantSet();
	const LGPConfig* lgpConfig=this->GetConfig();
	unsigned int iConstantRegCount=lgpConfig->GetConstantRegCount();
	for(unsigned int i=0; i<iConstantRegCount; i++)
	{
		constant_set->AddConstant(lgpConfig->GetConstantRegValue(i), lgpConfig->GetConstantRegWeight(i));
	}

	return constant_set;
}