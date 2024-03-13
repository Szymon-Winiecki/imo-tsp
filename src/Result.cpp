#include "../include/Result.h"

#include "../include/Instance.h"

#include <matplot/matplot.h>

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
    int numberOfEdges = 0;
    for (auto route : routes) {
        numberOfEdges += route.size();
    }

    using namespace matplot;
    std::vector<std::pair<size_t, size_t>> edges{};
    edges.resize(numberOfEdges);

    int e = 0;
    for (auto route : routes) {
        for (auto edge : route) {
            edges[e++] = { edge[0], edge[1] };
        }
    }

    if (edges.empty()) {
        edges = { {0, 0} }; // add self-loop, because matplot++ can't create graph without edges
    }

    vector_1d x_data(instance->Size());
    vector_1d y_data(instance->Size());

    for (int i = 0; i < instance->Size(); ++i) {
        x_data[i] = instance->PositionX(i);
        y_data[i] = instance->PositionY(i);
    }

    auto g = graph(edges);
    g->show_labels(false);

    g->x_data(x_data);
    g->y_data(y_data);

    show();
}