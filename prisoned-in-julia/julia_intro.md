# Introduzione a julia
[video di introduzione](www.youtube.com/watch?v=4igzy3bGVkQ&list=PLP8iPy9hna6SCcFv3FvY_qjAmtTsNYHQE)
julia è indicizzato a 1!!!!
Julia è un linguaggio di programmazione non tipizzato non ad oggetti

### Installare julia

[link standard](https://julialang.org/downloads/)


## Variabili

le variabili non sono tipizzate
`typeof()` per sapere il tipo della variabile

### Tipi

Distinguiamo i tipi in astratti e concreti. I tipi concreti sono quelli che di fatto definiscono come è letto un valore, quelli astratti ci servono per organizzare la gerarchia dei tipi e poter lavorare meglio sulle astrazioni. Di fatto non possiamo avere nessun dato con un tipo astratto perché questo non ci può definire come leggere i bit in memoria.

I tipi sono organizzati con una struttura gerarchica. Per vedere quali tipi ci sono per un tipo astratto `subtypes([type_name])`; mentre per vedere da quale tipo astratto deriva un tipo dato `supertype([type_name])`.

Le funzioni hanno tipo `Function`

## Commenti
`#` per il oneline `#= \\ =#` per il multiline

## Operatori
`^` per eseguire le potenze

## Stringe
`'a'` vengono usati per definire caratteri, non stringhe
`"ciao"` e `"""ciao"""` vengono usati per delimitare stringhe estese.
per inserire variabili all'interno di una stringa usiamo `$`. Esempio

```julia
var = 3
"io ho $var anni"
```
Se provo ad assegnare una stringa a più variabili, questa verra interpretata come un array di caratteri, assegnando ad ogni variabile il carattere in posizione corrispondente.

### Concatenazione

Per concatenare stringhe possiamo usare `*` tra le due stringhe che possono essere anche variabili

```julia
var1 = "Mosca + bicarbonato"
var2 = " = pericolo"
string(var1, var2)
var1*var2
```

## Strutture dati

### Struct
Abbiamo le struct come in C, vengono nominate in CamelCase perché sono di fatto dei tipi di dati.
Di base sono immutabili, quindi una volta che creo un oggetto, non potrò modificarne gli attributi.
```julia
struct Name
    data_name::DataType
end
```
Posso creare delle strutture mutabili ma con svantaggi sulle performance.
```julia
mutable struct Name
    data_name::DataType
end
```

### Dizionari
**Dichiarazione:** `name_dict = Dict("chiave"=> <valore>)`
aggiungiamo un valore con `name_dict["chiave"] = <valore>`

per fare take and remove di un valore `pop!(name_dict. "chiave")`

### Tuple

**Dichiarazione:** `name = ([val1], [val2] , ...)`
le tuple sono oggetti immutabili quindi non posso riassegnare un valore a una delle posizioni della tupla.

accesso come gli array

### Array

**Dichiarazione:** `name = [[val1], [val2] , ...]`
possono essere di qualsiasi tipo. se tutti gli elementi dell'array hanno lo stesso tipo, l'array avrà tipo concorde con questi elementi. Posso forzare il tipo dell'array con `<type>[[val1], [val2] , ...]`
A differenza delle Tuple, posso rimpiazzare il valore di una posizione qualsiasi.

`push!(array_name, value)` ci permettere di aggiungere un elemento in coda all'array

`pop!` rimuove l'ultimo elemento dell'array

### Generazione di range
Il range è una successione di numeri, probabilmente un iterabile, che si definisce con `init:step:end`. `init` è il primo numero della successione, `step` è quanto aggiungere per calcolare i valori successivi e `end` è il massimo numero rappresentabile nella lista. `step` di default è uno e si può omettere `n:m`

### Rand
è una funzione che ci permette di creare array di una qualsiasi dimensione con elementi estratti da un uniforme 0, 1 oppure a partire da collezioni già esistenti. guardare [documentazione](docs.julialang.org/en/v1/stdlib/Random/)

## Loop

### While
**sintassi**
```julia
while [condizione]
    {corpo}
end
```

### for
**sintassi**
```julia
for <var> in <iterabile>
    {corpo}
end
```
for annidati
```julia
for <var> in <iterabile>, <var> in <iterabile>
    {corpo}
end
```

### array compreension

`C = [i+j for i in 1:10, j in 1:5]`

## Condizioni
```julia
if [cond1]
    body
elseif [cond2]
    body
else
    body
end
```

- `||` = OR
- `&&` = AND

### inline if
`<cond1> ? <option1> : <option2> end`

Ricordiamo che in julia se ho un and condizionale, se la prima condizione è falsa, allora la seconda non verrà valutata. Possiamo forzare questa potenzialità per esprimere cose del tipo
`(x<y) && println("$x è più piccolo di $y")`

## Funzioni

I nomi delle funzioni vengono espressi in snakeCase
### Dichiarazione

Dichiarazione standard
```julia
function <name>(param)
    {body}
end
```

oneline function `name(parameter) = {body}`

Per specificare il tipo di un parametro inseriamo `::<type>` dopo il nome del parametro. In questo caso, la funzione verrà richiamata soltanto quando i tipi di input corrispondono con quelli specificati, quindi potremmo non vedere la funzione in alcuni casi. Per non mettere vincoli su certi parametri possiamo usare `::Any`

### Lambda
```julia
lambda_name = [parameters] -> {body}
```
### Multiple dispatch
Abbiamo visto che possiamo definire più funzioni con lo stesso nome se cambiamo il tipo dei parametri di input. quindi a seconda di quali tipi passaremo alla chiamata, verrà scelta la funzione che accetta quei parametri. Se ci sono più funzioni che accettano quella combinazione di input, allora verrà scelta quella con specificità maggiore. Se non riesce a risolvere la specificità, torna errore

### Mutating function
Le funzioni mutanti sono funzioni che modificano direttamente l'input. Contrariamente le funzini non mutanti sono funzioni che lasciano intatti gli input.

Le funzioni mutanti vengono indicate con `!` nel nome

## Pacchetti
keywords: importare, librerie, moduli
Per installare pacchetti nel nostro ambiente, dobbiamo prima entrare nel Pakacge manager con `]`, quindi installare i pacchetti con `add("package_name")`

Usare un pacchetto `using package_name`

Per sapere quali pacchetti sono installati `status`

### Plotting
per rappresentare grafici, usamo il pacchetto `Plots`

Ci sono diversi tipi di grafici che possiamo tracciare a partire dalla struttura che li sorregge. Ad esempio `gr()` o `plotlys()`. Questa dovrà essere specificata prima di cominciare a tracciare il grafico.

Salvo la prima, le funzioni successive andranno a modificare il grafico quindi dovranno essere delle funzioni mutanti. Altrimenti andrebbero a sovrascrivere il grafico già creato.

**Funzioni utili:**
- **plot!(x,y)** per tracciare un grafico a partire dai miei dati. Se si passa come argomento degli altri oggetti `plot`, possiamo rappresentare più grafici nella stessa figura.
- **scatter!(x,y)** per traccire uno scatterplot dei miei dati. tracciare i punti
- **`xlabel!("labelname")`** per rinominare l'asse delle X
- **ylabel!** per rinominare l'asse delle Y
- **title!** rinominare il grafico tutto

## Multiple dispatch
In julia possiamo avere più funzioni con lo stesso nome, che prendono come input parametri diversi per numero e tipo. Nel momento in cui chiamiamo la funzione con diversi parametri, verrà scelta quale funzione in particolare verrà usata.

Per vedere tutte le funzioni con lo stesso nome `methods(<function_name>)`

Per vedere quale funzione sta venendo usata `@which <funzione con parametri>`.
`@which` è chiamata **macro**.

## Basic linear algebra

Avendo precedentemente dichiarato se impongo `B=A` sto di fatto copiando il puntatore all'elemento, quindi se modifico `B`, modifico anche `A`.

### Trasposta

La trasposta di una matrice viene indicata con `A.'` da non confondere con `A'` che è la trasposta coniugata, quindi la trasposta con tutte le parti immaginarie dei comlessi cambiate di segno

### Soluzione di sistemi lineari
Possiamo risolvere facilmente i sistemi lineari con `A\b` computando quindi la soluzione di $Ax=b$.
Possiamo usare questo operatore per risolvese sistemi sia sovra, che sotto determinati

## Complessità
Per sapere quanto tempo di mette il nostro codice ad eseguire, possiamo usare il pacchetto `BenchmarkTools`

## Fattorizzazioni
- `lu()` ci torna due matrici che sono la fattorizzazione LU della matrice passata come argomento. Di defalut esegue pivoting sulla matrice per ridurre la cancellazione numerica
- `lufact()` ci torna la fattorizzazione LU come un oggetto che contiene: la matrice di permutazione P, L come matrice triangolare inferiore e U matrice Triangolare superiore. Per accedere agli attributi dell'oggetto `obj_name[:<attribute>]` Questo oggetto può essere usato anche per risolvere sistemi lineari.
- `qrfact()` esegue la fattorizzazione QR senza pivoting; ma ouò essere forzato a usare il pivoting. Come `lufact`, questa funzione torna un oggetto con le matrici Q e R come attributi. Anche questo può essere usato per risolvere sistemi lineari.
- `eigfact()` per eseguire una decomposizione in autovalori e autovettori. Torna un oggetto con attributi `:value` e `:vectors`.
- `svdfact()` per eseguire la fattorizzazione SVD e torna un oggetto

## Special Matrix Structures
posso specificare le caratteristiche di certe matrici in maniera da poter ottimizzare i conti su queste matrici. Questo viene fatto tramite determinate funzioni che prendono come input una matrice e un vettore e tornano una pseudomatrice con le caratteristiche specificate.
- `Diagonal`
- `Symmetric`
- `LowerTriangular`
- `Hermitian`
- `Tridiagonal` 
- `SymTridiagonal` matrice tridiagonale con diagonali minori simili


## Scope
da approfondire come funziona con while e for
Per le funzioni, queste possono vedere soltanto variabili locali e definite globali, quindi se il valore di una variabile viene definito al di fuori del corpo della funzione, questo non potrà essere visto a meno che non venga passato il puntatore.

