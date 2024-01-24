# DiGraph Implementations 

# Naive mathematical implementaiton
#    V = [1,2,3]
#    E = [12, 13, 32]
# running time is bad for operations on E
# we want to be able instantly know where we can go from vertex v

class Edge():
    def __init__(self, from_vtx, to_vtx, weight):
        self.from_vtx = from_vtx
        self.to_vtx = to_vtx
        self.weight = weight 
    def get_to_vtx(self):
        return self.to_vtx
    def get_weight(self):
        return self.weight
    def __str__(self):
        return f"w({self.from_vtx}->{self.to_vtx})={self.weight}"

    def __repr__(self):
        '''
        to be able to print lists of Edges
        '''
        return self.__str__()

            

# Graph = { Vertex : [WeightedEdge] }


class GraphAdjacencyList():
    '''
    E = {
        v:[(u,w(v,u)) forall u in N(v)]
        forall v in V

    }
    '''
    def __init__(self, edges, top_order):
        '''
        top_order is topological_order
        '''
        self.edges = {v : self._tuples_to_edges(v, nbrs) for v, nbrs in edges.items()}
        self.order = top_order
        self.nodes = self._get_nodes()
        
    def _tuples_to_edges(self, v, nbrs):
        return [Edge(v, x, wx) for x,wx in nbrs]

    def _get_nodes(self):
        return [key for key in self.edges.items()]

    def get_nodes(self):
        return self.nodes
    
    def get_nbrs(self, v):
        return self.edges[v]


    def get_nbrs_set(self, myset):
        # asume set is subset of V={nodes}
        result = []
        for v in myset:
            result += [edge.get_to_vtx() for edge in self.edges[v] if edge.get_to_vtx() not in (myset+result) ]
        return result
    
    def get_order(self):
        return self.order
    
    def __str__(self):
        graph = ""
        for v, edges in self.edges.items():
            graph += f"vertex: {v}, edges: {edges}\n"
        return graph
