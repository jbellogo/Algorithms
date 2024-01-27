import random 
###### Prim's Algorithm for Minimum Spanning Trees (MST)

def prims(G):
    V = G.get_nodes()
    s = random.choice(list(V))
    A = {s}
    T = {}
    # while V != A:
    _, edge_nbrs = G.get_nbrs_set(A)
    print(f"{A} has nbrs {edge_nbrs}")
    e = min(edge_nbrs, key = lambda edge : edge.weight())
    print(e)


