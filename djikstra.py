def djikstra(G):
    # still need priors for path reconstruction
    s = G.get_r()
    A = {s} # explored set
    V = set(G.get_v())
    l = {node : float('inf') for node in V} # current shortest path distances
    d = {s:0} # absolute shortest path distances
    while A != V:
        X = G.get_cut(A) #  X= [w(03)=7, w(01)=5, w(23)=7] ... Note 0,2 \in A and 3,1 \not\in A
#         print(f"\n CUT: {X}")
        w, lw = (0, float('inf'))
        for e in X:
            u, v = e.get_from_vtx(), e.get_to_vtx()
            l[v] = min([ l[v], d[u] + e.get_weight() ])
#             print(f"  e,l[v]: {e},{v},{l[v]}")
            if l[v] < lw:
                w, lw = (v, l[v])
        d[w] = l[w]
        A.add(w)
    return d



# def djikstra(G, s):
#     '''
#     Second Attempt
#     Mathematical implementation.
#     Very inefficient 
#     Only calculaltes shortest paths, it doesn't return them yet.
#     '''
#     A = {s} # explored set
#     l = {node : float('inf') for node in G.get_nodes()} # current shortest path distances
#     d = {s:0} # absolute shortest path distances
#     priors = {s:s} # for rebuilding the paths
#     V = G.get_nodes()
#     while A != V:
#         X, X_edges = G.get_nbrs_set(A) # unexplored nbrs, unexplored nbs edges (ie cut(A))
#         X_updates = []
#         for v in X:
#             # X =  ['r', 'f', 'b', 'c']
#             # X_edges = [w(s->c)=5, w(s->r)=2, w(a->c)=2, w(a->b)=3, w(a->f)=6]
#             U = [ux_edge for ux_edge in X_edges if ux_edge.get_to_vtx() == v] # vertices u in A incident with v in X ie edge uv exists
#             U = sorted(U, key = lambda edge : d[edge.get_from_vtx()] + edge.get_weight()) # sort edges based on d(u) + w(uv)
#             u = U[0] # first element of U is edge uv which minimizes d(u) + w(uv)
#             l[v] = min([ d[u.get_from_vtx()] + u.get_weight(), l[v] ])
#             X_updates.append((v, l[v]))        
#         w, _ = min(X_updates, key = lambda v : v[1]) # pick min (v, lv) based on lv
#         d[w] = l[w]
#         # priors[w] = refind it??? How? @TODO
#         A.add(w)
#     return (d, priors)




# def djikstra1(G, s, ordering):
#     '''
#     FIRST ATTEMPT
#     s is starting node
#     ordering is the topological sort of G: necessary for iterating through vertices 
#                 1) without recursion
#                 2) in BFS-fashion layers 
#     Assume G id directed acyclic
#     '''
#     ####### initialize #######
#     # d[u]      # current distance 
#     # prior[u] = v # prior of u of S.P
#     d = {node : [float('inf')] for node in G.get_nodes()} # will keep lists of all updated distances. 
#     d[s] = [0] # distance of root s
#     priors = {s:s} # indexed by vertices so name them whatever you want.
    
#     for v in ordering:
#         nbrs = G.get_nbrs(v)
#         # for all nbr of s consider:
#         #    1) their weights with v vertex (w(v, nbr))
#         #    2) their current S.P calculated  (d_nbr)
#         # then check if S.P should be updated by comparing d_nbr > d_v + w(v, nbr) 
#         for nbr, weight in nbrs:
#             d_new = weight + d[v][-1]
#             if nbr == "B":
#                 print(f"Current vertex: {v}\n Current nbr: {nbr}\n  w(nbr,v)+d[v]={d_new}\n  d[nbr]={d[nbr][-1]}")
#             if d_new < d[nbr][-1]:
#                 # we've found a new shortest path
#                 priors[nbr] = v # update prior vertex to current 
#                 d[nbr].append(d_new)
#     deltas = {v : distances[-1] for v,distances in d.items()}
#     print(f"Full distance history: {d}")
#     return (deltas, priors)

# # rewritting the path obtained from Djikstra priors::[] 
# def vs_path(v, root, priors):
#     '''
#     recursiveley calculates sv-path from root=s to v given a list of priors produced by Djikstra
#     '''
#     # base case
#     if v == root: 
#         return v
#     # return compound with recursion on strict input subset 
#     return vs_path(priors[v], root, priors) + v

def get_paths(priors, root):
    stp = {}
    for v in priors.keys():
        path= vs_path(v, root, priors)
        stp[v] = (path, weights[v]) 
    return stp


