import pandas as pd
import matplotlib.pyplot as plt
from datetime import datetime
import sys

# Lectura
sys.path.append("./python")
archivo = "./output/informe_entregas_nn.csv"
df_raw = pd.read_csv(archivo)

# Entregas no asignadas
entregas_no_asignadas     = df_raw[df_raw["ID Vehiculo"].isna()]
ids_no_entregadas         = entregas_no_asignadas["ID Entrega"].dropna().tolist()

# Vehículos sin entregas asignadas
vehiculos_total           = {f"V{str(i).zfill(3)}" for i in range(1, 11)}
df                        = df_raw.dropna(subset=["ID Vehiculo"]).copy()
df["ID Vehiculo"]         = df["ID Vehiculo"].astype(str)
vehiculos_con_entregas    = set(df["ID Vehiculo"])
vehiculos_sin_entregas    = sorted(vehiculos_total - vehiculos_con_entregas)

# Convertir tiempos
df["Inicio"]   = pd.to_datetime(df["Inicio del Viaje"], format="%H:%M")
df["Fin"]      = pd.to_datetime(df["Fin del Viaje"],    format="%H:%M")
df["Duración"] = df["Fin"] - df["Inicio"]

# Colores y posiciones Y
vehiculos     = sorted(df["ID Vehiculo"].unique())
color_map     = {veh: f"C{i}" for i, veh in enumerate(vehiculos)}
veh_ypos      = {veh: i for i, veh in enumerate(vehiculos)}
df["BaseY"]   = df["ID Vehiculo"].map(veh_ypos)

# Offset para solapamientos
offset_step   = 0.15
df["Y_offset"]= 0.0
for veh in vehiculos:
    ocupados = []
    for idx, row in df[df["ID Vehiculo"] == veh].sort_values("Inicio").iterrows():
        s, e      = row["Inicio"], row["Fin"]
        overlaps  = [t for t in ocupados if not (e <= t[0] or s >= t[1])]
        df.at[idx, "Y_offset"] = len(overlaps) * offset_step
        ocupados.append((s, e))

# Dibujo de Gantt y espacio en blanco lateral 
fig = plt.figure(figsize=(12, 8))
# Eje principal Gantt, ocupa 65% del ancho
ax  = fig.add_axes([0.05, 0.1, 0.65, 0.8])

min_inicio = df["Inicio"].min()
# Barras
for _, row in df.iterrows():
    start_min    = (row["Inicio"] - min_inicio).total_seconds() / 60
    duration_min = row["Duración"].total_seconds()      / 60
    y            = row["BaseY"] + row["Y_offset"]
    ax.barh(y, duration_min, left=start_min, height=0.12,
            color=color_map[row["ID Vehiculo"]], edgecolor="black")
    ax.text(start_min + 2, y, row["ID Entrega"],
            va="center", ha="left", fontsize=8,
            color="white" if row["ID Vehiculo"] in ["V001","V008"] else "black")

# Formato ejes Gantt
ax.set_yticks(list(veh_ypos.values()))
ax.set_yticklabels(list(veh_ypos.keys()))
ax.set_ylabel("Vehículos")
xticks = pd.date_range(df["Inicio"].min(), df["Fin"].max(), freq="30min")
xpos   = [(t - min_inicio).total_seconds() / 60 for t in xticks]
ax.set_xticks(xpos)
ax.set_xticklabels([t.strftime("%H:%M") for t in xticks], rotation=45)
ax.set_xlabel("Hora del Día")
ax.set_title("Carta Gantt de Entregas por Vehículo")
plt.grid(axis="x", linestyle="--", alpha=0.5)

# espacio en blanco para la tabla 
ax2 = fig.add_axes([0.75, 0.1, 0.2, 0.8])
ax2.axis("off")

#cabeceras  
tabla  = []
tabla.append(f"{'D no Assign':<12}  V no Assign")
maxr   = max(len(ids_no_entregadas), len(vehiculos_sin_entregas))
for i in range(maxr):
    d = ids_no_entregadas[i]      if i < len(ids_no_entregadas)   else ""
    v = vehiculos_sin_entregas[i] if i < len(vehiculos_sin_entregas) else ""
    tabla.append(f"{d:<12}  {v}")

# pintado de la tabla
y0    = 0.95
dy    = 0.04
for i, line in enumerate(tabla):
    ax2.text(0, y0 - i*dy, line,
             va="top", ha="left", fontsize=10,
             family="monospace")

plt.savefig("./plots/carta_gantt_nn.png", dpi=150, bbox_inches="tight")
plt.close()
print("Carta Gantt con tabla lateral compacta guardada en ./plots/carta_gantt_nn.png\n")
