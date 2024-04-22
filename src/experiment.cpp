#include "../include/Experiment.h"

#include <list>
#include <vector>
#include <utility>
#include <limits>
#include <iterator>
#include <iostream>
#include <fstream>
#include <numeric>
#include <string>

#include "../include/Result.h"
#include "../include/Instance.h"
#include "../include/NearestNeighborSolver.h"
#include "../include/GreedyCycleSolver.h"


void Experiment::add_result(int alg, int route, std::string algo, std::string data, std::string LST, std::string iC, float duration)
{

	results[alg].push_back(route);
	dataset[alg].push_back(data);
	algorithm[alg].push_back(algo);
	LocalSearchType[alg].push_back(LST);
	internalChange[alg].push_back(iC);
	times[alg].push_back(duration);
};

void Experiment::resizer(int exp)
{
	results.resize(exp);
	dataset.resize(exp);
	algorithm.resize(exp);
	LocalSearchType.resize(exp);
	internalChange.resize(exp);
	times.resize(exp);
};

void Experiment::show_results()
{
	
	for (int i = 0; i < results.size(); i++)
	{
		for (int j = 0; j < results[i].size(); j++)
		{
			std::cout << results[i][j] << " ";
		}
		std::cout << std::endl;
	}
};

void Experiment::save_results(const std::filesystem::path& path)
{
	std::ofstream file(path);

	//for (int j = 0; j < algorithm.size(); j++)
	//{
	//	std::cout << algorithm[j] << ";" << dataset[j] << std::endl;
	//}
	int j = 0;
	for (int i = 0; i < results.size(); i++)
	{
		if (results[i].size() == 0) continue;
		std::pair<int, int> min = get_min(i);
		std::pair<int, int> max = get_max(i);
		std::pair<int, int> min_time = get_min_time(i);
		std::pair<int, int> max_time = get_max_time(i);
		//alg/mean/min/max
		file << algorithm[i][0] << ";" << dataset[i][0] << ";" << get_mean(i) << ";" << min.first << ";" << min.second << ";" << max.first << ";" << max.second << ";" << LocalSearchType[i][0] << ";" << internalChange[i][0] << ";" << get_mean_time(i) << ";" << min_time.first << ";" << max_time.first << std::endl;
		j += results[i].size();
	}
	file.close();
};

int Experiment::get_mean(int alg)
{
	int sum = 0;
	int count  = static_cast<int>(results[alg].size());

	return std::reduce(results[alg].begin(), results[alg].end()) / std::max(1,count);
};

std::pair<int, int> Experiment::get_min(int alg)
{
	int min = std::numeric_limits<int>::max();
	int best = 0;

	for (int i = 0; i < results[alg].size(); i++)
	{
		if (results[alg][i] < min)
		{
			min = results[alg][i];
			best = i;
		}

	}
	return { min, best };
};

std::pair<int, int> Experiment::get_max(int alg)
{
	int max = 0;
	int best = 0;

	for (int i = 0; i < results[alg].size(); i++)
	{

		if (results[alg][i] > max)
		{
			max = results[alg][i];
			best = i;
		}
	}
	return { max, best };
};

int Experiment::get_mean_time(int alg)
{
	int sum = 0;
	int count = static_cast<int>(times[alg].size());

	return std::reduce(times[alg].begin(), times[alg].end()) / std::max(1, count);
};

std::pair<int, int> Experiment::get_min_time(int alg)
{
	int min = std::numeric_limits<int>::max();
	int best = 0;

	for (int i = 0; i < times[alg].size(); i++)
	{
		if (times[alg][i] < min)
		{
			min = times[alg][i];
			best = i;
		}

	}
	return { min, best };
};

std::pair<int, int> Experiment::get_max_time(int alg)
{
	int max = 0;
	int best = 0;

	for (int i = 0; i < times[alg].size(); i++)
	{

		if (times[alg][i] > max)
		{
			max = times[alg][i];
			best = i;
		}
	}
	return { max, best };
};