import os
import pandas as pd
import matplotlib.pyplot as plt

# Nome del file CSV
file_csv = "output_temptation.csv"
if os.path.exists(file_csv):
    df = pd.read_csv(file_csv, header=None, names=["x", "y", "classe"])
    classi = sorted(df["classe"].unique())
    markers = ['o', 's', '^', 'D', 'v', 'P', '*', 'X', '<', '>']
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
    plt.savefig("output_temptation.png")


# Nome del file
file_name = "output_percentSampling2.csv"
# Controllo esistenza file
if os.path.exists(file_name):
    df = pd.read_csv(file_name, header=None)
    df.columns = ["x", "y", "classe"]
    for classe in df["classe"].unique():
        subset = df[df["classe"] == classe]
        subset = subset.sort_values(by="x")
    plt.figure()
    for classe in df["classe"].unique():
        subset = df[df["classe"] == classe]
#        plt.scatter(subset["x"], subset["y"], label=f"M={classe}", s=5, alpha=0.5)
        plt.plot(subset["x"], subset["y"], label=f"M={classe}")
    plt.xscale("log")
    plt.xlabel("Ascisse (X)")
    plt.ylabel("Ordinate (Y)")
    plt.title("Grafico da CSV")
    plt.legend()
    plt.savefig("output_percentSampling2.png")



file_name = "output_percentSampling1.csv"
# Controllo esistenza file
if os.path.exists(file_name):
    df = pd.read_csv(file_name, header=None)
    df.columns = ["x", "y", "classe"]
    for classe in df["classe"].unique():
        subset = df[df["classe"] == classe]
        subset = subset.sort_values(by="x")
    plt.figure()
    for classe in df["classe"].unique():
        subset = df[df["classe"] == classe]
#        plt.scatter(subset["x"], subset["y"], label=f"M={classe}", s=5, alpha=0.5)
        plt.plot(subset["x"], subset["y"], label=f"M={classe}")
    plt.xscale("log")
    plt.xlabel("Ascisse (X)")
    plt.ylabel("Ordinate (Y)")
    plt.title("Grafico da CSV")
    plt.legend()
    plt.savefig("output_percentSampling1.png")



file_name = "output_beta.csv"
# Controllo esistenza file
if os.path.exists(file_name):
    df = pd.read_csv(file_name, header=None)
    df.columns = ["x", "y", "classe"]
    for classe in df["classe"].unique():
        subset = df[df["classe"] == classe]
        subset = subset.sort_values(by="x")
    plt.figure()
    for classe in df["classe"].unique():
        subset = df[df["classe"] == classe]
#        plt.scatter(subset["x"], subset["y"], label=f"M={classe}", s=5, alpha=0.5)
        plt.plot(subset["x"], subset["y"], label=f"Beta={classe}")
    plt.xscale("log")
    plt.xlabel("Ascisse (X)")
    plt.ylabel("Ordinate (Y)")
    plt.title("Grafico da CSV")
    plt.legend()
    plt.savefig("output_beta.png")