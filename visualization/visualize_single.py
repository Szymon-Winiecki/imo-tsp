import networkx as nx
from matplotlib import pyplot as plt
import json
import sys

def get_route_color(route, num_of_routes):
    r = route / num_of_routes
    g = 1 - (route / num_of_routes)

    route = (route + num_of_routes // 2) % num_of_routes
    b = route / num_of_routes

    r = int(r * 255) % 255
    g = int(g * 255) % 255
    b = int(b * 255) % 255

    r = f'{r:0{2}x}'
    g = f'{g:0{2}x}'
    b = f'{b:0{2}x}'

    return f'#{r}{g}{b}'


if len(sys.argv) == 1:
    print('missing input file name')
    exit(1);

if len(sys.argv) == 2:
    print('missing output file name')
    exit(2);

input_file_name = sys.argv[1]
file = open(input_file_name, 'r')
graph_data = json.loads(file.read())

G = nx.Graph()

G.add_nodes_from(range(graph_data["num_nodes"]))

routes = []

for route in graph_data["routes"]:
    G.add_edges_from(route)
    routes.append({
        "nodes": set(sum(route, [])),
        "edges": route,
        "route_color": get_route_color(len(routes), len(graph_data["routes"])),
    })

positions = {}
i = 0
for position in graph_data["positions"]:
    positions[i] = position
    i += 1


for route in routes:
    nx.draw_networkx_nodes(G, positions, nodelist=route["nodes"], node_color=route["route_color"], node_size=50)
    nx.draw_networkx_edges(G, positions, edgelist=route["edges"], edge_color=route["route_color"], alpha=0.5, width=2)

output_file_name = sys.argv[2]

plt.title(f'Total length: {graph_data["objective_fun"]}')

plt.savefig(output_file_name)
plt.show()