import random 
###### Prim's Algorithm for Minimum Spanning Trees (MST)

def prims(G):
    '''
    Takes in an undirected graph. G::UndirectedG() @TODO pydantic strong types
    ISSUE. Infinite loop, doesn't progress.
    '''
    V = G.get_nodes()
    s = random.choice(list(V))
    A = {s}
    T = []
    while V != A:
        delta_A = G.get_cut(A)
        delta_A = sorted(delta_A, key = lambda edge : edge.get_weight())
        # print(delta_A)
        e = delta_A[0]
        print(e)
        A.add(e.get_to_vtx())
        T.append(e)
    return T


