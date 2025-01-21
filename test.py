import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import make_interp_spline
import time
from scipy import signal

def carica_matrice_csv(nome_file):
    matrice = np.loadtxt(nome_file, delimiter=',')
    return matrice

# Carica la matrice dal file CSV
states = carica_matrice_csv("Data_DQN.csv")

states = np.array(states)


# Supponiamo che ogni passo di tempo corrisponda a 0.05 secondi
time_step = 0.05
time = np.arange(0, len(states) * time_step, time_step)
time_smooth = np.linspace(time.min(), time.max(), 500)

plt.figure(figsize=(15, 10))

########################################
# Plotta la posizione
########################################
plt.subplot(5, 1, 1)
# Interpolazione spline per una curva liscia
spline = make_interp_spline(time, states[:, 0])
state_smooth = spline(time_smooth)

# Plotta tutti e tre gli elementi sullo stesso grafico
plt.plot(time_smooth, state_smooth, label='Interpolazione Spline')
#plt.plot(time, states[:, i], label='Dati Originali')
plt.plot(time, states[:, 0], 'o', label='Punti Originali')

plt.xlabel('Tempo (s)')
plt.ylabel(f'Posizione (m)')
plt.title(f'Evoluzione della posizione nel tempo')
plt.legend()
plt.grid(True)


########################################
# Plotta la velocità
########################################
plt.subplot(5, 1, 2)
# Interpolazione spline per una curva liscia
spline = make_interp_spline(time, states[:, 1])
state_smooth = spline(time_smooth)

# Plotta tutti e tre gli elementi sullo stesso grafico
plt.plot(time_smooth, state_smooth, label='Interpolazione Spline')
plt.plot(time, states[:, 1], 'o', label='Punti Originali')

plt.xlabel('Tempo (s)')
plt.ylabel(f'Velocità (m/s)')
plt.title(f'Evoluzione della velocità nel tempo')
plt.legend()
plt.grid(True)


########################################
# Plotta la posizione angolare
########################################
plt.subplot(5, 1, 3)
# Interpolazione spline per una curva liscia
spline = make_interp_spline(time, states[:, 2])
state_smooth = spline(time_smooth)

# Plotta tutti e tre gli elementi sullo stesso grafico
plt.plot(time_smooth, state_smooth, label='Interpolazione Spline')
plt.plot(time, states[:, 2], 'o', label='Punti Originali')

plt.xlabel('Tempo (s)')
plt.ylabel(f'Posizione angolare (rad)')
plt.title(f'Evoluzione della posizione angolare nel tempo')
plt.legend()
plt.grid(True)


########################################
# Plotta la velocità angolare
########################################
plt.subplot(5, 1, 4)
# Interpolazione spline per una curva liscia
spline = make_interp_spline(time, states[:, 3])
state_smooth = spline(time_smooth)

# Plotta tutti e tre gli elementi sullo stesso grafico
plt.plot(time_smooth, state_smooth, label='Interpolazione Spline')
plt.plot(time, states[:, 3], 'o', label='Punti Originali')

plt.xlabel('Tempo (s)')
plt.ylabel(f'Velocità angolare (rad/s)')
plt.title(f'Evoluzione della velocità angolare nel tempo')
plt.legend()
plt.grid(True)


########################################
# Plotta l'azione
########################################
plt.subplot(5, 1, 5)

plt.step(time, states[:, 4], where='post')
plt.plot(time, states[:, 4], 'o')    
plt.xlabel('Tempo (s)')
plt.ylabel(f'Azione')
plt.title(f"Evoluzione dell'azione nel tempo")
plt.grid(True)

""" for i in range(states.shape[1]):
plt.subplot(5, 1, i + 1)
# Interpolazione spline per una curva liscia
spline = make_interp_spline(time, states[:, i])
time_smooth = np.linspace(time.min(), time.max(), 500)
state_smooth = spline(time_smooth)

# Plotta tutti e tre gli elementi sullo stesso grafico
plt.plot(time_smooth, state_smooth, label='Interpolazione Spline')
#plt.plot(time, states[:, i], label='Dati Originali')
plt.plot(time, states[:, i], 'o', label='Punti Originali')

plt.xlabel('Tempo (s)')
plt.ylabel(f'Stato {i+1}')
plt.title(f'Evoluzione dello Stato {i+1} nel Tempo')
plt.legend()
plt.grid(True) """

plt.tight_layout()
plt.show()

