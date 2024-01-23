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
},
top_order = ['s', 'a', 'r', 'c', 'b', 'f']
)

G2 = Graph(
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