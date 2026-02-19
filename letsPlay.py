import gioco
import giocatori as gioc
import strategie as sta

import networkx as nx
import matplotlib.pyplot as plt
import numpy as np

def draw_graph(nodi):
    G = nx.Graph()
    # Add nodes
    for node in nodi:
        G.add_node(node.name)
    # Add edges
    for node in nodi:
        for vicino in node.vicini:
            G.add_edge(node.name, vicino.name)
    # Draw
    nx.draw(G, with_labels=True, node_color='lightblue', edge_color='gray')
    plt.show()
    
def percent(nodi: list[gioc.giocatore]):
    valori = dict()
    dim = len(nodi)
    for node in nodi:
        name = node.strategia.__name__
        if  name not in valori:
            valori[name] = 1/dim
        else:
            valori[name] += 1/dim
    return valori
    
def punteggioZero(nodi: list[gioc.giocatore]):
    for i in nodi:
        i.punteggio = 0

def test1():
    p1 = gioc.giocatore(sta.Defection, name="Player 1")
    p2 = gioc.giocatore(sta.Cooperation, name="Player 2")

    p1.aggiungi_vicini(p2)
    p2.aggiungi_vicini(p1)

    for _ in range(10):
        p1.punteggio = 0
        p2.punteggio = 0
        
        ris1, ris2 = gioco.game(p1, p2)

        p1.aggiorna_punteggio(ris1)
        p2.aggiorna_punteggio(ris2)

        p1.aggiorna_Strategia()
        p2.aggiorna_Strategia()

    print("Test1 passato")

def test2():
    # Creazione doni
    nodi = []
    for i in range(10):
        strat = sta.Defection if i%4 == 0 else sta.Cooperation
        nodi.append(gioc.giocatore(strat, name=f"Player {i}"))
    
    # Creazione collegamenti
    for prescelto in nodi:
        for i in nodi:
            if i != prescelto:
                if len(i.vicini):
                    i.aggiungi_vicini(prescelto)
                    prescelto.aggiungi_vicini(i)
                elif np.random.rand()>0.7 and i not in prescelto.vicini:
                    i.aggiungi_vicini(prescelto)
                    prescelto.aggiungi_vicini(i)
                
        # print(prescelto)
    
    # tutti i turni
    for _ in range(10):
        punteggioZero(nodi)
        
        for i in nodi:
            for j in i.vicini:
                risi, risj = gioco.game(i, j)
                i.aggiorna_punteggio(risi)
                #j.aggiorna_punteggio(risj)
            print(i)
        #punti = [i.punteggio for i in nodi]
        
        
        print(percent(nodi))
        for i in nodi:
            i.aggiorna_Strategia()
        
    draw_graph(nodi)
    print("Test2 passato")
test1()
test2()