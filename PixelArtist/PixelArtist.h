#ifndef _H_PIXEL_ARTIST_H
#define _H_PIXEL_ARTIST_H

#include "../LGPComp/LGPProgram.h"
#include "../AppTypes.h"

class CViewport;

class PixelArtist : public LGPProgram
{
public:
	PixelArtist(LGPConfig* lgpConfig);
	virtual ~PixelArtist();

protected:
	virtual LGPOperatorSet* CreateOperatorSet();

public:
	virtual void EvaluateFitness(LGPEnvironment* env);
	virtual void Run();
	virtual void CreateFromScript(std::string script_name);
	virtual void BuildCodes(std::string script_name, std::string function_name="lgp_program", std::string output_location="lgp_codes");
protected:
	virtual double EvaluateFitness(std::vector<LGPFitnessCase*>& fitness_cases);

public:
	virtual LGPProgram* Clone() const;

public:
	virtual void Paint(CImage& img);

protected:
	int m_image_width;
	int m_image_height;
};

#endif