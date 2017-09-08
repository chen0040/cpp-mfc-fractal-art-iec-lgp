#include "stdafx.h"
#include "PixelArtist.h"
#include "PAOperatorSet.h"
#include "../LGPComp/LGPPop.h"
#include "PAFitnessCase.h"
#include "../LGPUtil/LGPExitSystem.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "../tinyxml/tinyxml.h"
#include "../lgp_misc/string_manip.h"
#include "../lgp_misc/io_manip.h"
#include "../Viewport.h"
#include "../Resource.h"
#include "../DlgEvaluator.h"
#include "../XSUtil.h"

#define DEFAULT_IMAGE_WIDTH 400
#define DEFAULT_IMAGE_HEIGHT 300

PixelArtist::PixelArtist(LGPConfig* lgpConfig)
: LGPProgram(lgpConfig)
, m_image_width(DEFAULT_IMAGE_WIDTH)
, m_image_height(DEFAULT_IMAGE_HEIGHT)
{

}

PixelArtist::~PixelArtist()
{
	
}

LGPOperatorSet* PixelArtist::CreateOperatorSet()
{
	return new PAOperatorSet();
}

LGPProgram* PixelArtist::Clone() const
{
	return new PixelArtist(*this);
}

double PixelArtist::EvaluateFitness(std::vector<LGPFitnessCase*>& fitness_cases)
{
	LGPExitSystem("PixelArtist::EvaluateFitness(std::vector<LGPFitnessCase*>& fitness_cases)", "this method should not be called");
	
	return 0;
}

void PixelArtist::Paint(CImage& img)
{
	ASSERT(!m_image.IsNull());

	int image_width=img.GetWidth();
	int image_height=img.GetHeight();

	double offsetx=static_cast<double>(image_width) / 2.0;
	double offsety=static_cast<double>(image_height) / 2.0;

	for(int row=0; row < image_height; ++row)
	{
		for(int col=0; col < image_width; ++col)
		{
			BYTE* ptr=(BYTE*)img.GetPixelAddress(col, row);
			double color=0;

			PAFitnessCase fitness_case;
			double normalized_y=2.0*(static_cast<double>(row)-offsety) / image_height; //normalized y to be in the range of (-1, 1)
			double normalized_x=2.0*(static_cast<double>(col)-offsetx) / image_width;
			fitness_case.SetInput(normalized_x, 0);
			fitness_case.SetInput(normalized_y, 1);

			this->InitializeProgramRegisters(&fitness_case);
			this->EvaluateFitnessCase(&fitness_case);

			for(int k=0; k<3; ++k)
			{
				fitness_case.QueryLGPOutput(k, &color);
				ptr[k]=(BYTE)(color * 255);
			}
		}
	}
}

void PixelArtist::EvaluateFitness(LGPEnvironment* env)
{
	this->MarkStructuralIntrons();

	//std::cout << ToString(true) << std::endl;

	CDlgEvaluator dlgEvaluate;
	dlgEvaluate.CreateArt(this);

	dlgEvaluate.DoModal();

	m_objective_value=dlgEvaluate.GetScore();

	if(this->GetConfig()->IsMaximization())
	{
		m_dFitness=m_objective_value;
	}
	else
	{
		m_dFitness=-m_objective_value;
	}

	m_bFitnessValid=true;
}

void PixelArtist::BuildCodes(std::string script_name, std::string function_name, std::string output_location)
{
	LGPProgram::BuildCodes(script_name, function_name, output_location);

	std::string app_directory_path=CT2CA(xsUtil.GetApplicationDirectoryPath());
	lgp_copy_file(
		lgp_join(app_directory_path, "\\compile_dependencies\\algorithmic_image.h"), 
		lgp_join(output_location, "\\algorithmic_image.h").c_str());

	lgp_copy_file(
		lgp_join(app_directory_path, "\\compile_dependencies\\algorithmic_image.cpp"), 
		lgp_join(output_location, "\\algorithmic_image.cpp").c_str());
	lgp_copy_file(
		lgp_join(app_directory_path, "\\compile_dependencies\\main.cpp"), 
		lgp_join(output_location, "\\main.cpp").c_str());

	TiXmlDocument doc;
	doc.LoadFile(script_name.c_str());
	TiXmlElement* xml_root=doc.RootElement();
	int width, height;
	for(TiXmlElement* xml_level1=xml_root->FirstChildElement(); xml_level1 != NULL; xml_level1 = xml_level1->NextSiblingElement())
	{
		if(strcmp(xml_level1->Value(), "parameters")==0)
		{
			for(TiXmlElement* xml_level2=xml_level1->FirstChildElement(); xml_level2 != NULL; xml_level2=xml_level2->NextSiblingElement())
			{
				if(strcmp(xml_level2->Value(), "param")==0)
				{
					if(strcmp(xml_level2->Attribute("name"), "width")==0)
					{
						xml_level2->QueryIntAttribute("value", &width);
					}
					else if(strcmp(xml_level2->Attribute("name"), "height")==0)
					{
						xml_level2->QueryIntAttribute("value", &height);
					}
				}
			}
		}
	}

	std::ofstream constants_file(lgp_join(output_location, "\\lgp_constants.h").c_str());

	constants_file << "#ifndef _H_LGP_CONSTANTS_H\n";
	constants_file << "#define _H_LGP_CONSTANTS_H\n";

	constants_file << "const int IMAGE_WIDTH=" << width << ";\n";
	constants_file << "const int IMAGE_HEIGHT=" << height << ";\n";

	constants_file << "#endif\n";

	constants_file.close();
}

void PixelArtist::CreateFromScript(std::string script_name)
{
	LGPProgram::CreateFromScript(script_name);

	ParamPairList::iterator pos_param=m_parameter_list.find("width");
	if(pos_param != m_parameter_list.end())
	{
		m_image_width=lgp_string2int(pos_param->second);
	}

	pos_param=m_parameter_list.find("height");
	if(pos_param != m_parameter_list.end())
	{
		m_image_height=lgp_string2int(pos_param->second);
	}
}

void PixelArtist::Run()
{
	/*
	this->MarkStructuralIntrons();

	std::cout << ToString(true) << std::endl;

	IplImage* img=cvCreateImage(cvSize(m_image_width, m_image_height), IPL_DEPTH_8U, 3);

	double offsetx=static_cast<double>(img->width) / 2.0;
	double offsety=static_cast<double>(img->height) / 2.0;
	for(int row=0; row < img->height; ++row)
	{
		uchar* ptr=(uchar*)(img->imageData+img->widthStep * row);
		for(int col=0; col < img->width; ++col)
		{
			double color=0;
			PAFitnessCase fitness_case;
			double normalized_y=2.0*(static_cast<double>(row)-offsety) / img->height; //normalized y to be in the range of (-1, 1)
			double normalized_x=2.0*(static_cast<double>(col)-offsetx) / img->width;
			fitness_case.SetInput(normalized_x, 0);
			fitness_case.SetInput(normalized_y, 1);

			this->InitializeProgramRegisters(&fitness_case);
			this->EvaluateFitnessCase(&fitness_case);
			for(int k=0; k<img->nChannels; ++k)
			{
				fitness_case.QueryLGPOutput(k, &color);
				ptr[col * img->nChannels+k]=(uchar)(color * 255);
			}
		}
	}

	cvNamedWindow("Pixel Artist");

	cvShowImage("Pixel Artist", img);

	bool done=false;
	int option=0;
	do{
		option=cvWaitKey(0);
		if(option==115 || option==83) //key: s or S
		{
			int rnd_index= rand() ;
			std::ostringstream oss_image;
			oss_image << rnd_index << ".jpg"; 
			cvSaveImage(oss_image.str().c_str(), img);
		}
		else
		{
			option=0;
			done=true;
		}
	}while(!done);

	cvReleaseImage(&img);
	cvDestroyWindow("Pixel Artist");
	*/
}

