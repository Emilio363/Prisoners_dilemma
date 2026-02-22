import pandas as pd
import matplotlib.pyplot as plt

# Nome del file CSV
file_csv = "output.csv"

# Lettura del file (senza header)
df = pd.read_csv(file_csv, header=None, names=["x", "y", "classe"])

# Classi uniche
classi = sorted(df["classe"].unique())

# Marker diversi per classe (puoi aggiungerne altri se servono)
markers = ['o', 's', '^', 'D', 'v', 'P', '*', 'X', '<', '>']

# Creazione figura
plt.figure(figsize=(8, 6))

for i, classe in enumerate(classi):
    subset = df[df["classe"] == classe]
    plt.scatter(
        subset["x"],
        subset["y"],
        label=f"Classe {classe}",
        marker=markers[i % len(markers)],
        s=80
    )

plt.xlabel("Ascissa (x)")
plt.ylabel("Ordinata (y)")
plt.title("Scatterplot per classe")
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.savefig("grafico.png")