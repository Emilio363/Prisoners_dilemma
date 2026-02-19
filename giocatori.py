from typing import Callable
import numpy as np
np.random.seed(42)

Max_memory = 10
K = 1.05
beta = 0.5

class giocatore:
    def __init__(self, strategia: Callable, name="None"):
        self.name = name
        self.strategia = strategia
        self.memoria = 0
        self.punteggio = 0
        self.vicini = []
    
    def memoria(self):
        return self.memoria
        
    def aggiungi_vicini(self, vicini):
        self.vicini.append(vicini)
        
    def gioca(self):
        mossa = self.strategia()
        return mossa
    
    def aggiorna_punteggio(self, punti):
        self.punteggio += punti
        
    def aggiorna_Strategia(self):
        eletto = np.random.choice(self.vicini)
        prob = H_x(self)*fermi(self, eletto)
        
        newstrategy = self.strategia
        if prob > np.random.rand():
            newstrategy = eletto.strategia
        if newstrategy == self.strategia:
            if self.memoria < Max_memory:
                self.memoria += 1
            self.strategia = newstrategy
        else:
            self.memoria = 0
            self.strategia = newstrategy
            
    def __str__(self):
        return f"Name: {self.name} Strategia: {self.strategia.__name__}, Punteggio: {self.punteggio}, Memoria: {self.memoria}"
    
    def my_name(self):
        return self.name
    
def fermi(p1: giocatore, p2: giocatore) -> float:
    prob = 1 / (1 + np.exp((p1.punteggio - p2.punteggio) / K))
    return prob
    
def H_x(player: giocatore) -> float:
    if Max_memory == 0:
        return 1
    else:
        return 1-(1-beta)*player.memoria/Max_memory