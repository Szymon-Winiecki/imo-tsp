#pragma once

#include <cstdlib>
#include <ctime>
#include <vector>
#include <filesystem>
#include <string>

class Solve;
class Instance;
class Result;
class GreedyCycleSolver;
class NearestNeighborSolver;

class Experiment
{
public:

	Experiment(int alg)
	{
		results.resize(alg);
	}

	void save_results(const std::filesystem::path& path);

	void add_result(int alg, int route, std::string algorithm, std::string dataset, std::string LocalSearchType, std::string internalChange, float duration);

	void show_results();

	void resizer(int exp);


	/*
	Solver(Instance* instance, unsigned int seed) : instance{ instance }
	{
		std::srand(seed);
	}

	void SetInstance(Instance* instance)
	{
		this->instance = instance;
	}

	Instance* GetInstance() const {
		return instance;
	}

	virtual Result* Solve(int routes = 2) = 0;
	*/
private:
	std::pair<int, int> get_min(int alg);
	std::pair<int, int> get_max(int alg);
	int get_mean(int alg);
	std::pair<int, int> get_min_time(int alg);
	std::pair<int, int> get_max_time(int alg);
	int get_mean_time(int alg);
	std::vector<std::vector<unsigned int>> results;
	std::vector<std::vector<float>> times;
	std::vector<std::vector<std::string>> dataset;
	std::vector<std::vector<std::string>> algorithm;
	std::vector<std::vector<std::string>> LocalSearchType;
	std::vector<std::vector<std::string>> internalChange;
//protected:

	//int RandomInt(int min, int max) const;
	//int GetRandomNode() const;
	//int GetTheFarthestNode(const std::vector<int>& fromNodes);
	//int CalcSumDistanceToNodes(int node, const std::vector<int>& otherNodes);

	//Instance* instance;
};