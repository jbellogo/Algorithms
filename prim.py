import random 
###### Prim's Algorithm for Minimum Spanning Trees (MST)

def prims(G):
    '''
    Takes in an undirected graph. G::UndirectedG() @TODO pydantic strong types
    '''
    V = G.get_nodes()
    s = random.choice(list(V))
    A = {s}
    T = {}
    while V != A:
        delta_A = G.get_cut(A)
        e = min(delta_A, key = lambda edge : edge.get_weight())
        A.add(e.to_vtx())
        T.add(e)
    return T


