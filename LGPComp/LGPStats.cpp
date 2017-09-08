#include "stdafx.h"
#include "LGPStats.h"
#include <iomanip>
#include <sstream>

LGPStats::LGPStats(LGPPop *lgpPop)
: m_lgpPop(lgpPop)
{
	LGPConfig* lgpConfig=lgpPop->GetConfig();
	m_iPopLogInterval=lgpConfig->GetPopLogInterval();
	m_PopLogFilePath=lgpConfig->GetPopLogFilePath();
	m_StatsLogFilePath=lgpConfig->GetStatsLogFilePath() + ".txt";
	m_RunLogFilePath=lgpConfig->GetRunLogFilePath();

	m_stats_logfile.open(m_StatsLogFilePath.c_str());
}

LGPStats::~LGPStats()
{
	m_stats_logfile.close();
}

void LGPStats::Log()
{
	if(m_lgpPop->GetCurrentGeneration() % m_iPopLogInterval == 0)
	{
		LogPopulation();
	}
	LogStatistics();
}

void LGPStats::LogPopulation()
{
	std::ostringstream oss;
	oss << m_PopLogFilePath << "_" << std::setw(5) << std::setfill('0') << m_lgpPop->GetCurrentGeneration() << std::endl;
	std::ofstream logfile(oss.str().c_str());

	logfile << m_lgpPop->ToString() << std::endl;

	logfile.close();
}

void LGPStats::LogStatistics()
{
	m_stats_logfile << "Current Generation: " << m_lgpPop->GetCurrentGeneration() << std::endl;

	m_dFitnessSum=0;
	m_iSizeSum=0;
	std::vector<LGPProgram*>::const_iterator pos_program;
	unsigned int iProgramCount=m_lgpPop->GetProgramCount();
	for(unsigned int i=0; i<iProgramCount; i++)
	{
		m_dFitnessSum+=m_lgpPop->GetProgram(i)->GetFitness();
		m_iSizeSum+=m_lgpPop->GetProgram(i)->GetInstructionCount();
	}

	double program_count=static_cast<double>(iProgramCount);
	m_dAverageFitness=m_dFitnessSum / program_count;
	m_dAverageProgramLength=m_iSizeSum / program_count;
	m_stats_logfile << std::left << std::setw(17) << "Average Fitness: " <<  m_dAverageFitness << std::endl;
	m_stats_logfile << std::left << std::setw(17) << "Average Program Length: " << m_dAverageProgramLength << std::endl;

	m_stats_logfile << "Current Best Program: " << std::endl;
	m_stats_logfile << m_lgpPop->GetFittestProgram()->ToString() << std::endl;
}
