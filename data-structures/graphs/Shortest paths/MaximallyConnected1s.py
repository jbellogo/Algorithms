import sys

#### veryyyy slow - even c+++ version

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

class Graph2():
    def __init__(self, k):
        self.ones = []
        self.k = k        
    def get_k(self):
        return self.k    
    def get_lst_ones(self):
        return self.ones
    def addE(self, from_v, to_v, w):
        if w == 1:
            self.ones.append(Edge(from_v, to_v, w))

def MCksubTree(G):
    k = G.get_k()
    ones_clusters = []
    count = 0 # number of EDGES in maximally connected tree component
    for e in G.get_lst_ones():
        if count >= k:
            break
        u,v = e.get_from_vtx(), e.get_to_vtx()
        if ones_clusters == []:
            ones_clusters.append(set({u,v}))
            count = 1
            continue
        for myset in ones_clusters:
            bu = u in myset
            bv = v in myset
            if bu and bv:
                continue # don't add cycles
            elif bu:
                myset.add(v)
            elif bv:
                myset.add(u)
            else: 
                ones_clusters.append(set({u,v}))
            if len(myset) > count:
                count = len(myset)-1
    if count > k:
        count = k
    return 2*k-count

def main():
    G,n,k,lim = 0,0,0,0
    # READ INPUT
    for i, line in enumerate(sys.stdin):
        if 'Exit' == line.rstrip():
            break
        lst = line.split()
        if i == 0:
            # first line
            n = int(lst[0]) # size of V
            k = int(lst[1])
            G = Graph2(n,k)
            lim = int(n*(n-1)/2)
        else:
            u = int(lst[0])
            v = int(lst[1])
            w = int(lst[2])
            G.addE(u,v,w)            
        if i >= lim: 
            break
    # SOLUTION:
    if isinstance(G, Graph2):
        print((MCksubTree(G)))

        
if __name__ == "__main__":
    main()