from graph_implementations import GraphAdjacencyList as Graph

G1 = Graph({
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
})
