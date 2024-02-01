# DiGraph Implementations 
import numpy as np
# Naive mathematical implementaiton
#    V = [1,2,3]
#    E = [12, 13, 32]
# running time is bad for operations on E
# we want to be able instantly know where we can go from vertex v

class Edge():
    '''
    Same class can be used for directed or undirected graphs, just specify in Graph class
    '''
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
    def __str__(self):
        return f"w({self.from_vtx}->{self.to_vtx})={self.weight}"

    def __repr__(self):
        '''
        to be able to print lists of Edges
        '''
        return self.__str__()

            

# Graph = { Vertex : [WeightedEdge] }


class DiGraph():
    '''
    Directed
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
        return {key for key in self.edges.keys()} # :: set

    def get_nodes(self):
        return self.nodes
    
    def get_nbrs(self, v):
        return self.edges[v]


    def get_nbrs_set(self, myset):
        # asume set is subset of V={nodes}
        # returns set of edges! 
        # print(myset)
        result_vertices, result_edges = [],[]
        for v in myset:
            for edge in self.edges[v]:
                if edge.get_to_vtx() not in myset: # cant say not in (myset+result_vertices) cuz I care about all edges
                    result_vertices.append(edge.get_to_vtx())
                    ### not quite working!!!!! @TODO 
                    result_edges.append(edge)
        # remove duplicates in list of vertices 
        return (list(set(result_vertices)), result_edges) # (vertices, edges)
    
    def get_order(self):
        return self.order
    
    def __str__(self):
        graph = ""
        for v, edges in self.edges.items():
            graph += f"vertex: {v}, edges: {edges}\n"
        return graph



def is_subset(subset, bigset):
    return subset.intersection(bigset) == subset


class UndiGraph():
    def __init__(self, V, E):
        '''
        Let E be a numpy array matrix
        '''
        self.V = V
        self.E = E
    def _get_index(self, v):
        '''v in V'''
        return self.V.index(v)

    def get_cut(self, S):
        '''S \subset V'''
        indices = [] # 0,1,2,3
        cut = []
        for v in S:
            indices.append(self._get_index(v))
        for row_index, col in enumerate(self.E):
            for col_index, edge_bool in enumerate(col):
                include = not is_subset(set([row_index, col_index]), set(indices))
                include &= (row_index in indices or col_index in indices)
                if include:
                    weight = self.E[row_index][col_index]
                    if weight > 0:
                        cut.append(Edge(self.V[row_index], self.V[col_index], weight))
                if row_index == col_index:
                    break # stop after diagonal. Don't repeat yourself!
        return cut
