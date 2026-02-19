
ispirato dal video di veritasium:
Something Strange Happens When You Trace How Connected We Are

vogliamo simulare il "gioco della banca" 
abbiamo una serie di individui collegati fra di loro
ad ogni ciclo, coppie di individui si sfidano al gioco

il gioco consiste nello scegliere se collaborare o meno. abbiamo quindi 4 possibilità
- entrambi collaborano
- il primo collabora e il secondo no
- il primo non collabora ma il secondo sì
- nessuno collabora

in base a come ogni giocatore ha scelto, vengono affidati dei punti a ogni giocatore

ci sono delle strategie secondo le quali i giocatori scelgono se collaborare o meno

vengono fatti alcuni turni in cui ogni volta i giocatori possono cambiare scelta

alla fine della partita ogni giocatore può scegliere se cambiare o meno strategia


Il paper lavora con una griglia quadrata 200x200. 
Inizialmente ad ogni cella viene assegnata una strategia casuale.
Ad ogni tempo avvengono dei giochi da capire meglio chi gioca e per quanto tempo.
Ogni volta che l'avversario vince viene valutata la posibilità di prendere la sua strategia.
La memoria serve a valutare quanto la strategia sia efficace.
La memoria è un valore che indica per quanti turni di fila il giocatore ha tenuto la stessa strategia.
Appena la strategia cambia, il contatore si azzera.

Ci sono dei parametri globali:
- M la dimensione massima della memoria
- T il guadagno ottenuto dal aver tradito l'avversario
- R = 1 il guadagno dalla collaborazione
- P = 0 il guadagno dal tradimento reciproco
- S = 0 il guadagno se si viene traditi mentre si collabora
- Beta il peso che viene dato alla memoria
- K quanto sono razionali gli individui (lower is better)


## Implementazione:

voglio una collezione di oggetti "giocatore" ognuno dei quali ha una serie di vicini sui quali posso ciclare

ci sono una serie di strategie che il giocatore può utilizzare. ogni giocatore può avere dichiarare una sola strategia.

Ogni giocatore ha un valore non modificabile esternamente che indica la memoria del giocatore
c'è un metodo che determina l'update della strategia. se la strategia viene cambiata allora devo cambiare la memoria.

c'è una classe game che prendere come input due giocatori e torna i punteggi che vengono dati ad ogni giocatore. 