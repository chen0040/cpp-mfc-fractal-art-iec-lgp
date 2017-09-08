#ifndef _H_LGP_STATS_H
#define _H_LGP_STATS_H

#include <string>
#include <fstream>
#include <iostream>
#include "LGPPop.h"

class LGPStats
{
public:
	LGPStats(LGPPop* lgpPop);
	virtual ~LGPStats();

public:
	virtual void Log();
	virtual void LogPopulation();
	virtual void LogStatistics();

private:
	LGPPop* m_lgpPop;

private:
	std::string m_PopLogFilePath;
	std::string m_StatsLogFilePath;
	std::string m_RunLogFilePath;
	unsigned int m_iPopLogInterval;
public:
	std::string GetPopLogFilePath() const { return m_PopLogFilePath; }
	std::string GetStatsLogFilePath() const { return m_StatsLogFilePath; }
	std::string GetRunLogFilePath() const { return m_RunLogFilePath; }
	unsigned int GetPopLogInterval() const { return m_iPopLogInterval; }

protected:
	unsigned int m_iSizeSum;
	double m_dFitnessSum;
	double m_dAverageFitness;
	double m_dAverageProgramLength; 
public:
	double GetAverageFitness() const { return m_dAverageFitness; }
	double GetAverageProgramLength() const { return m_dAverageProgramLength; } 

protected:
	std::ofstream m_stats_logfile;
};

#endif
