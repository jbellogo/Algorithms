# DiGraph Implementations 
import numpy as np
from abc import ABC, abstractmethod 
# Lets say all inputs are in matrix form. [[2,3,4][0,0,1]]
# Input V :: [] , E :: [[]]
# Then I want to create internal edge structures. # @Note for assignment we can skip ahead to this!
# E = [ EdgeObject ]  # But this again is bad
# Keep the matrix and add an adjacency list. 
# Adjacency list
# E = {v1: [Edges(from=v1, )]
#      v2: } 

# Graph = { Vertex : [WeightedEdge] }
# should make an abstract parent class for Graph!



class DiGraph():
    '''
    Directed
    E = {
        v:[(u,w(v,u)) forall u in N(v)]
        forall v in V

    }
    '''
    # edges is list of Adjacency lists. 
    def __init__(self, edges):
        self.edges = {v : self._tuples_to_edges(v, nbrs) for v, nbrs in edges.items()}
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

    def get_nodes(self):
        return set(self.V)

    def get_cut(self, S):
        '''S \subset V'''
        indices = [] # 0,1,2,3
        cut = []
        for v in S:
            indices.append(self._get_index(v))
        # O(n*f(m)) operation
        for row_index, col in enumerate(self.E):
            for col_index, edge_bool in enumerate(col):
                include = not is_subset(set([row_index, col_index]), set(indices))
                include &= (row_index in indices or col_index in indices)
                if include:
                    weight = self.E[row_index][col_index]
                    if weight > 0:
                        cut.append(Edge(self.V[row_index], self.V[col_index], weight))
                if row_index == col_index:
                    break # stop after diagonal. Don't repeat yourself+ O(nm) avoided
        return cut


# class Graph():
#     def __init__(self, V, E = None, directed = False):
#         '''
#         V : [] # List of vertices
#         E :: [[]] # Matrix of weights indexed by from,to vertices.
#         '''
#         self.V = V
#         # Keep both, initialize with E=[[w]] as this is easier to type ups
#         self.edgesMtx = E # Some future applications may benefit from it but it is not implemented rn
#         self.edgesAdj = {v : [Edge(v, self.V[u_i] , w) for u_i,w in enumerate(self.edgesMtx[v_i]) if w != 0] for v_i, v in enumerate(V)}
        
#     def get_v(self):
#         return self.V
#     def get_vnbrs(v):
#         return self.edgesAdj[v]
#     def get_cut(S):
#         cut = []
#         for v in S:
#             cut += self.edgesAdj[v]
#     def __str__(self):
#         graph = ""
#         for v, edges in self.edgesAdj.items():
#             graph += f"vtx: {v}, incident edges: {edges}\n"
#         return graph
#     def addE(self, from_v, to_v, w):

#         # Add to Adjacency lists
#         self.edgesAdj[from_v].append(Edge(from_v, to_v, w))
#         # Add to matrix 

