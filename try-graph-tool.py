import graph_tool as gt

g = gt.Graph(directed=False)
Score = g.new_vp("float")
Strategy = g.new_vp("object")
