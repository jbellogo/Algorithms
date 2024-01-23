# DiGraph Implementations 

# Naive mathematical implementaiton
#    V = [1,2,3]
#    E = [12, 13, 32]
# running time is bad for operations on E
# we want to be able instantly know where we can go from vertex v


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
        self.edges = edges
        self.order = top_order
        
    def get_nodes(self):
        return [key for key in self.edges.keys()]
    
    def get_nbrs(self, v):
        return self.edges[v]
    
    def get_order(self):
        return self.order
    
    def __str__(self):
        graph = ""
        for v, adj in self.edges.items():
            edges = [f'w({v + key})={val}' for key,val in adj]
            graph += f"vertex: {v}, edges: {edges}\n"
        return graph
