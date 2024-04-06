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

	void add_result(int alg, int route, std::string algorithm, std::string dataset);

	void show_results();


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
	std::vector<std::vector<unsigned int>> results;
	std::vector<std::string> dataset;
	std::vector<std::string> algorithm;
//protected:

	//int RandomInt(int min, int max) const;
	//int GetRandomNode() const;
	//int GetTheFarthestNode(const std::vector<int>& fromNodes);
	//int CalcSumDistanceToNodes(int node, const std::vector<int>& otherNodes);

	//Instance* instance;
};