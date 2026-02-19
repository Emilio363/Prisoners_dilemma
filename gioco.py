# parameter

T = 1.05 # 1<T<2 il guadagno ottenuto dal aver tradito l'avversario
R = 1 #il guadagno dalla collaborazione
P = 0 #il guadagno dal tradimento reciproco
S = 0 #il guadagno se si viene traditi mentre si collabora

def game(player1, player2):
    mossa1 = player1.gioca()
    mossa2 = player2.gioca()
    if mossa1 not in ['C', 'D'] or mossa2 not in ['C', 'D']:
        raise ValueError("Le mosse devono essere 'C' o 'D'")
    
    if mossa1 == 'C' and mossa2 == 'C':
        punti1 = R
        punti2 = R
    elif mossa1 == 'C' and mossa2 == 'D':
        punti1 = S
        punti2 = T
    elif mossa1 == 'D' and mossa2 == 'C':
        punti1 = T
        punti2 = S
    else: # mossa1 == 'D' and mossa2 == 'D':
        punti1 = P
        punti2 = P
        
    return (punti1, punti2)