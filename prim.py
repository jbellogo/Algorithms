import random 
###### Prim's Algorithm for Minimum Spanning Trees (MST)


def prim(G):
    V, s = set(G.get_v()), G.get_r()
    A, T = {s}, []
    Tw = 0
    while V != A:
        deltaA = G.get_cut(A) # ideally this should be inside this algorithm
        e = deltaA[0] # first element has minimum weight
        A.add(e.get_to_vtx())
        Tw += e.get_weight()
        T.append(e)
    return (T, Tw)

def primInv(G):
    '''
    returns Max Spanning Tree... needs more testing
    '''
    V, s = set(G.get_v()), G.get_r()
    A, T = {s}, []
    Tw = 0
    while V != A:
        deltaA = G.get_cut(A)
        e = deltaA[-1] # last element has max weight
        A.add(e.get_to_vtx())
        Tw += e.get_weight()
        T.append(e)
    return (T, Tw)

