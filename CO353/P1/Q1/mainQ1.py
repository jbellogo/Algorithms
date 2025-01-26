import sys


class Edge():
    def __init__(self, from_vtx, to_vtx, weight):
        self.from_vtx = from_vtx
        self.to_vtx = to_vtx
        self.weight = weight 
    def get_from_vtx(self):
        return self.from_vtx
    def get_to_vtx(self):
        return self.to_vtx
    def get_weight(self):
        return self.weight
    def update_weight(self, w):
        self.weight = w
    def __eq__(self, other):
        if not isinstance(other, Edge):
            return NotImplemented
        a = self.from_vtx == other.get_from_vtx()
        b = self.to_vtx == other.get_to_vtx()
        c = self.weight == other.get_weight()
        return a and b and c 
    ###### For testing #######
    def __str__(self):
        return f"w({self.from_vtx}{self.to_vtx})={self.weight}"
    def __repr__(self):
        return self.__str__()



class Graph():
    def __init__(self, V, r):
        '''
        V : number of vertices 
        r : distinguished vertex # Matrix of weights indexed by from,to vertices.
        '''
        self.V = list(range(V))
        self.r = r
        self.AdjE = {v : [] for v in self.V}

    def get_v(self):
        return self.V
    def get_r(self):
        return self.r
    def set_r(self, nr):
        self.r = nr
    def get_vnbrs(v):
        return self.AdjE[v]
    def __str__(self):
        graph = ""
        for v, edges in self.AdjE.items():
            root = "**" if v == self.r else ""
            graph += f"{v}{root}, incident edges: {edges}\n"
        return graph
    
    def addE(self, from_v, to_v, w):
        # MAKE ASSERTIONS
        w = int(w)
        self.AdjE[from_v].append(Edge(from_v, to_v, w))
        self.AdjE[to_v].append(Edge(to_v, from_v, w))
        
    def get_cut(self, S):
        cut = []
        for v in S:
            for e in self.AdjE[v]:
                # both of these operations are linear!
                cond_a = e not in cut # don't repeat
                cond_b = e.get_to_vtx() not in S
                if cond_a and cond_b:
                    # add e to cut
                    we = e.get_weight()
                    # keep smallest w at begining, largest at end
                    if cut != [] and we <= cut[0].get_weight():
                        cut.insert(0, e)
                    elif cut != [] and we <= cut[-1].get_weight():
                        cut.insert(-1, e)
                    else:
                        cut.append(e)
        return cut
    
    def update_edge_weights(self, wts):
        '''
        updates edge weights from input vertex weights. w(e) = min (w(u), w(v))
        Assume v_wts contains all vertices as keys
        '''
        for v, nbrs in self.AdjE.items():
            for e in nbrs:
                u = e.get_to_vtx()
                wnew = min([wts[u], wts[v]])
                e.update_weight(wnew)
                

def djikstra(G):
    s = G.get_r()
    A = {s} # explored set
    V = set(G.get_v())
    l = {node : float('inf') for node in V} # current shortest path distances
    d = {s:0} # absolute shortest path distances
    while A != V:
        X = G.get_cut(A)
        w, lw = (0, float('inf'))
        for e in X:
            u, v = e.get_from_vtx(), e.get_to_vtx()
            l[v] = min([ l[v], d[u] + e.get_weight() ])
            if l[v] < lw:
                w, lw = (v, l[v])
        d[w] = l[w]
        A.add(w)
    return d

def MaxMinCloseness(G):
    '''
    Modified prim's to get both MST weight and MaxST weight
    '''
    V, s = set(G.get_v()), G.get_r()
    Amax, Amin = {s}, {s}
    maxC, minC = 0, 0
    while V != Amax and V != Amin:
        if V != Amax:
            # primInv
            deltaA = G.get_cut(Amax)
            e = deltaA[-1] # last elem has max weight
            Amax.add(e.get_to_vtx())
            maxC += e.get_weight()
        if V != Amin:
            # prim
            deltaA = G.get_cut(Amin)
            e = deltaA[0] # first elem has min weight
            Amin.add(e.get_to_vtx())
            minC += e.get_weight()
    return (minC, maxC)



def myfunc(G):
    out_dj = djikstra(G)
    G.update_edge_weights(out_dj)
    return MaxMinCloseness(G)

def main():
    G,n,m,r = 0,0,0,0
    # READ INPUT
    for i, line in enumerate(sys.stdin):
        if 'Exit' == line.rstrip():
            break
        lst = line.split()
        if i == 0:
            # first line
            n = int(lst[0]) # size of V
            m = int(lst[1]) # size of E
            r = int(lst[2]) # root vtx r
            G = Graph(n,r)
        else:
            u = int(lst[0])
            v = int(lst[1])
            w = int(lst[2])
            G.addE(u,v,w)            
        if i >= m: 
            break
    # SOLUTION:
    if isinstance(G, Graph):
        a,b = myfunc(G)
        print(f"{a} {b}")
        
if __name__ == "__main__":
    main()



