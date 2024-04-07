#include "../include/Result.h"

#include "../include/Instance.h"

#include <sstream>
#include <fstream>
#include <iostream>

Result::Result(Instance* instance, int routesCount)
{
    this->instance = instance;

    if (instance == nullptr) {
        return;
    }

	int asymetricMargin = 0;
	if (instance->Size() % routesCount != 0) {
		asymetricMargin = 1;
	}
	
	for (int i = 0; i < routesCount; ++i) {
		routes.push_back(EdgeList_t());
		routes[routes.size() - 1].reserve(instance->Size() / routesCount + asymetricMargin);
	}

}

void Result::AddEdge(int route, int start, int end)
{
	routes[route].push_back({ start, end });
}
 
void Result::Plot()
{
    
}

void Result::ExportAsJSON(const std::filesystem::path& path, bool pretty)
{
    std::stringstream JSON_Constructor("");


    // GRAPH INFO
    JSON_Constructor << "{\"num_nodes\":" << instance->Size() << ",";
    JSON_Constructor << "\"num_routes\":" << routes.size() << ",";
    JSON_Constructor << "\"route_length\":[";

    for (int i = 0; i < routes.size(); ++i) 
    {
        JSON_Constructor << routes[i].size();
        if (i != routes.size() - 1) 
        {
            JSON_Constructor << ",";
        }
    }
    JSON_Constructor << "],";

    // NODES POSITIONS
    JSON_Constructor << "\"positions\":[";
    for (int i = 0; i < instance->Size(); ++i)
    {
        JSON_Constructor << "[" << instance->PositionX_Normalized(i) << "," << instance->PositionY_Normalized(i) << "]";
        if (i != instance->Size() - 1)
        {
            JSON_Constructor << ",";
        }
    }
    JSON_Constructor << "],";

    // ROUTES
    JSON_Constructor << "\"routes\":[";
    for (int i = 0; i < routes.size(); ++i)
    {
        // EDGES IN ROUTE
        JSON_Constructor << "[";
        for (int j = 0; j < routes[i].size(); ++j)
        {
            JSON_Constructor << "[" << routes[i][j][0] << "," << routes[i][j][1] << "]";
            if (j != routes[i].size() - 1)
            {
                JSON_Constructor << ",";
            }
        }
        JSON_Constructor << "]";
        if (i != routes.size() - 1)
        {
            JSON_Constructor << ",";
        }
    }
    JSON_Constructor << "]";

    JSON_Constructor << "}";

    std::ofstream file(path);
    file << JSON_Constructor.str();
    file.close();
}

int Result::getRouteLength()
{
	int length = 0;
    std::cout << routes[0].size() + routes[1].size() << std::endl;
    for (int i = 0; i < routes.size(); ++i)
    {
        for (int j = 0; j < routes[i].size(); ++j)
        {
			length += instance->Distance(routes[i][j][0], routes[i][j][1]);
		}
	}
	return length;
}

void Result::ListToVectors()
{
    //std::cout<<routes.size()<<std::endl;
    for (int i = 0; i < routes.size(); ++i)
    {
        cycles.push_back(std::vector<int>());
        for (int j = 0; j < routes[i].size(); ++j)
        {
			cycles[i].push_back(routes[i][j][0]);
			//std::cout << routes[i][j][0] << " " << routes[i][j][1] << std::endl;
		}
	}
}

