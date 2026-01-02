import pandas as pd
import matplotlib.pyplot as plt
import os

# Nome del file generato dal C++
filename = 'result.csv'

# Verifica se il file esiste
if not os.path.exists(filename):
    print(f"Errore: Il file {filename} non esiste.")
    exit()

# Leggi i dati
try:
    df = pd.read_csv(filename)
except Exception as e:
    print(f"Errore nella lettura del CSV: {e}")
    exit()

# Imposta la dimensione del grafico
plt.figure(figsize=(12, 6))

# --- PLOT 1: Dati Grezzi ---
# Li disegniamo in grigio chiaro/trasparente per vedere la varianza
plt.plot(df['update'], df['avg_reward'], 
         label='Reward Istantaneo (Raw)', 
         color='gray', 
         alpha=0.3, 
         linewidth=1)

# --- PLOT 2: Media Mobile (Trend) ---
# Calcola la media degli ultimi N valori per lisciare la curva
window_size = 50  # Modifica questo valore se vuoi più o meno "lisciatura"
df['rolling_avg'] = df['avg_reward'].rolling(window=window_size).mean()

plt.plot(df['update'], df['rolling_avg'], 
         label=f'Trend (Media Mobile {window_size})', 
         color='blue', 
         linewidth=2)

# --- Formattazione ---
plt.title('Performance Agente: Reward per Update', fontsize=16)
plt.xlabel('Updates (M)', fontsize=12)
plt.ylabel('Average Reward', fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()

# Salva il grafico e mostralo
output_img = 'training_plot.png'
plt.savefig(output_img)
print(f"Grafico salvato come {output_img}")
plt.show()
