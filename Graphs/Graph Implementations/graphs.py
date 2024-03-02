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
    def __str__(self):
        return f"w({self.from_vtx}{self.to_vtx})={self.weight}"
    def __repr__(self):
        return self.__str__()
    def __eq__(self, other):
        if not isinstance(other, Edge):
            return NotImplemented
        a = self.from_vtx == other.get_from_vtx()
        b = self.to_vtx == other.get_to_vtx()
        c = self.weight == other.get_weight()
        return a and b and c 




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
                
                
        

