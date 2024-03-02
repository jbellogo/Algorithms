import numpy as np
from graph_implementations import DiGraph, UndiGraph

G1 = DiGraph({
    'a':[
        ('c', 2),
        ('b', 3),
        ('f', 6)
    ], 
    'b':[], 
    'c':[
        ('f',2),
        ('b',1)
    ],
    'f':[],
    's':[
        ('a',1),
        ('c',5),
        ('r',2)
    ],
    'r':[
        ('f',4),
        ('b',3)
    ]
},
top_order = ['s', 'a', 'r', 'c', 'b', 'f']
)

G2 = DiGraph(
    {
        'A':[
            ('B', 10),
            ('C', 3)
        ],
        'B':[
            ('C', 1),
            ('D', 2),
        ],
        'C':[
            ('B', 4),
            ('D', 8),
            ('E', 2)
        ],
        'D': [
            ('E', 7),
        ],
        'E': [
            ('D', 9)
        ],
    },
    top_order = ['A', 'B', 'C', 'D', 'E']
)

# undirected 
V = ['a', 'c', 's', 'd', 'f', 't']
E = np.array([[0,2,5,3,2,1],
             [2,0,1,0,6,3],
             [5,1,0,2,0,0],
             [3,0,2,0,4,0],
             [2,6,0,4,0,2],
             [1,3,0,0,2,0]])

UDIG1 =  UndiGraph(V,E)