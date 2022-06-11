def dijkstra(g, b):
    """
    Dijkstra's algorithm for finding the shortest path from a source to all
    other vertices in a graph.(by Copilot)

    Parameters
    ----------
    g : graph
        The graph to find the shortest path in.
    b : vertex
        The source vertex.

    Returns
    -------
    d : dictionary
        The dictionary of shortest paths.
    p : dictionary
        The dictionary of predecessors.
    """
    d = {}
    p = {}
    for v in g.vertices:
        d[v] = float('inf')
        p[v] = None
    d[b] = 0
    Q = g.vertices.copy()
    while Q:
        u = min(Q, key=lambda v: d[v])
        Q.remove(u)
        for v in g.neighbors(u):
            alt = d[u] + g.distance(u, v)
            if alt < d[v]:
                d[v] = alt
                p[v] = u
    return d, p