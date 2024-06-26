import networkx as nx
from matplotlib import pyplot as plt
import json
import sys
import os

paths1 = [[0, 26,24186], [1, 73,27205], [2, 90,26304]]
paths2 = [[0, 38,26782],[1, 12,27180],[2, 23,27180]]
names = ["Heurystyka najbliższego sąsiada","Heurystyka oparta na żalu","Metoda rozbudowy cyklu"]
datasets = ["kroA100","kroB100"]

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


def visualize(dataset,length,name,path,save_path,LocalSearch,Internal):

    input_file_name = path
    file = open(input_file_name, 'r')
    graph_data = json.loads(file.read())

    G = nx.Graph()

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

    title = name + " - " + str(length) + ", '" + dataset + "'," + LocalSearch + "," + Internal
    plt.title(title)
    output_file_name = os.path.join(os.getcwd(),title)
    #output_file_name = os.path.join("charts",file_names[x] + ".jpg")

    plt.savefig(output_file_name)
    plt.clf()
    #plt.show()
    G.clear()

#file_names = []
if len(sys.argv) > 1:
    folder = sys.argv[1]
else:
    folder = os.path.abspath(os.path.join(os.getcwd(),os.pardir)) + "\\imo_tsp_2\\results"
#print(folder)
#print("------")
f = open(os.path.join(folder,"results.txt"),"r")

for line in f:
    data = list(line.split(';'))
    data[-1] = data[-1][:-1]
    #min
    print("Wykresy")
    print(data)
    path = os.path.join(folder,data[4] + "_" + data[0] + "_" + data[1] + "_" + data[7] + "_" + data[8] + "_e.json")
    visualize(data[1],data[3],data[0],path,folder,data[7],data[8])