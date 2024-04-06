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


void Experiment::add_result(int alg, int route, std::string algo, std::string data)
{
	results[alg].push_back(route);
	dataset.push_back(data);
	algorithm.push_back(algo);
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

	for (int i = 0; i < results.size(); i++)
	{
		std::pair<int, int> min = get_min(i);
		std::pair<int, int> max = get_max(i);
		//alg/mean/min/max
		file << algorithm[i] << ";" << dataset[i] << ";" << get_mean(i) << ";" << min.first << ";" << min.second << ";" << max.first << ";" << max.second << std::endl;

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