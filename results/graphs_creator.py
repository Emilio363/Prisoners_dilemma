import os
import pandas as pd
import matplotlib.pyplot as plt

# Nome del file CSV
def temptation():
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

def percentSampling2():
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
        plt.xlabel("Iteration")
        plt.ylabel("Percent of Cooperation")
        plt.title("epoc for different M values")
        plt.legend()
        plt.savefig("output_percentSampling2.png")

def percentSampling1():
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
        plt.xlabel("Iteration")
        plt.ylabel("Percent of Cooperation")
        plt.title("epoc for different M values")
        plt.legend()
        plt.savefig("output_percentSampling1.png")

def outBeta():
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

def tempBetaMem0():
    file_csv = "temp_beta_mem_0.csv"
    if os.path.exists(file_csv):
        df = pd.read_csv(file_csv, header=None, names=["x", "y", "beta"])
        classi = sorted(df["beta"].unique())
        markers = ['o', 's', '^', 'D', 'v', 'P', '*', 'X', '<', '>']
        plt.figure(figsize=(8, 6))

        for i, classe in enumerate(classi):
            subset = df[df["beta"] == classe].sort_values(by="x")
#            plt.scatter(subset["x"], subset["y"], label=f"Beta={classe}", marker=markers[i % len(markers)], s=80)
            plt.plot(
                subset["x"],
                subset["y"],
                linestyle='-',
                label=f"Beta={classe}"
            )
        
        plt.xlabel("Temptation (T)")
        plt.ylabel("Percent of Cooperation")
        plt.title("Tempation for different Beta values (Memory=0)")
        plt.legend()
        plt.grid(True)
        plt.tight_layout()
        plt.savefig("temp_beta_mem_0.png")

def tempBetaMem3():
    file_csv = "temp_beta_mem_3.csv"
    if os.path.exists(file_csv):
        df = pd.read_csv(file_csv, header=None, names=["x", "y", "beta"])
        classi = sorted(df["beta"].unique())
        markers = ['o', 's', '^', 'D', 'v', 'P', '*', 'X', '<', '>']
        plt.figure(figsize=(8, 6))

        for i, classe in enumerate(classi):
            subset = df[df["beta"] == classe].sort_values(by="x")
#            plt.scatter(subset["x"], subset["y"], label=f"Beta={classe}", marker=markers[i % len(markers)], s=80)
            plt.plot(
                subset["x"],
                subset["y"],
                linestyle='-',
                label=f"Beta={classe}"
            )

        plt.xlabel("Temptation (T)")
        plt.ylabel("Percent of Cooperation")
        plt.title("Tempation for different Beta values (Memory=3)")
        plt.legend()
        plt.grid(True)
        plt.tight_layout()
        plt.savefig("temp_beta_mem_3.png")

def tempBetaMem9():
    file_csv = "temp_beta_mem_9.csv"
    if os.path.exists(file_csv):
        df = pd.read_csv(file_csv, header=None, names=["x", "y", "beta"])
        classi = sorted(df["beta"].unique())
        markers = ['o', 's', '^', 'D', 'v', 'P', '*', 'X', '<', '>']
        plt.figure(figsize=(8, 6))

        for i, classe in enumerate(classi):
            subset = df[df["beta"] == classe]
            plt.scatter(
                subset["x"],
                subset["y"],
                label=f"Beta={classe}",
                marker=markers[i % len(markers)],
                s=80
            )
        plt.xlabel("Temptation (T)")
        plt.ylabel("Percent of Cooperation")
        plt.title("Tempation for different Beta values (Memory=9)")
        plt.legend()
        plt.grid(True)
        plt.tight_layout()
        plt.savefig("temp_beta_mem_9.png")

def tempBetaMem27():
    file_csv = "temp_beta_mem_27.csv"
    if os.path.exists(file_csv):
        df = pd.read_csv(file_csv, header=None, names=["x", "y", "beta"])
        classi = sorted(df["beta"].unique())
        markers = ['o', 's', '^', 'D', 'v', 'P', '*', 'X', '<', '>']
        plt.figure(figsize=(8, 6))

        for i, classe in enumerate(classi):
            subset = df[df["beta"] == classe]
            plt.scatter(
                subset["x"],
                subset["y"],
                label=f"Beta={classe}",
                marker=markers[i % len(markers)],
                s=80
            )
        plt.xlabel("Temptation (T)")
        plt.ylabel("Percent of Cooperation")
        plt.title("Tempation for different Beta values (Memory=9)")
        plt.legend()
        plt.grid(True)
        plt.tight_layout()
        plt.savefig("temp_beta_mem_27.png")

def percBetaMulti01():
    df = pd.read_csv("K_beta_multi_.csv", header=None, names=["x", "y", "classe1", "classe2"])

    # media di y per (x, classe1), ignorando classe2
    df_media = df.groupby(["x", "classe1"], as_index=False)["y"].mean()

    # plot
    classi = sorted(df_media["classe1"].unique())

    for classe in classi:
        subset = df_media[df_media["classe1"] == classe].sort_values(by="x")
        plt.plot(subset["x"], subset["y"], label=f"beta={classe}")

    plt.xlabel("Iteration")
    plt.ylabel("mean percent of cooperation")
    plt.legend()
    plt.savefig("perc_beta_multi_k_01.png")

#tempBetaMem0()
tempBetaMem3()