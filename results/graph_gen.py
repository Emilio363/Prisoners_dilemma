import os
import pandas as pd
import matplotlib.pyplot as plt

# Cartella di lavoro (puoi cambiarla)
cartella = "."

# Trova tutti i file CSV
files_csv = [f for f in os.listdir(cartella) if f.endswith(".csv")]

if not files_csv:
    print("Nessun file CSV trovato.")
    exit()

for file in files_csv:
    path = os.path.join(cartella, file)
    
    try:
        df = pd.read_csv(path, header=None)
        df.columns = ["x", "y", "classe"]
    except Exception as e:
        print(f"Errore nel file {file}: {e}")
        continue

    plt.figure()

    for classe in df["classe"].unique():
        subset = df[df["classe"] == classe]
        subset = subset.sort_values(by="x")

        # linea + punti
        plt.plot(subset["x"], subset["y"], label=f"M={classe}")
        plt.scatter(subset["x"], subset["y"], s=10)

    # scala logaritmica sulle ascisse
    plt.xscale("log")

    plt.xlabel("X")
    plt.ylabel("Y")
    plt.title(f"Grafico: {file}")
    plt.legend()

    # nome file output
    output_name = file.replace(".csv", "gen.png")
    plt.savefig(output_name)
    plt.close()

    print(f"Creato: {output_name}")