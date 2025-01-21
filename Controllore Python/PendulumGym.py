from stable_baselines3 import DQN, PPO
from Pendolo_Inverso_DC_Motor import CartPoleEnv
from File_and_Serial_Manager import Manager
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import make_interp_spline
import time
from scipy import signal

ALGORITHMS = ["DQN", "PPO"]

# Scelta dell'utente
user_choice = int(input(f"Vuoi allenare un modello o testarne uno già esistente? 1: Allenamento, 2: Test\n"))

if user_choice == 1:
    # Allenamento
    env = CartPoleEnv()

    user_choice = int(input(f"Quale algoritmo vuoi utilizzare? 1: DQN, 2: PPO\n"))

    algorithm = ALGORITHMS[user_choice - 1]

    learning_step = int(input(f"Inserisci il numero di step di apprendimento: "))

    user_choice = int(input(f"Vuoi ricevere informazioni durante l'allenamento? 1: Sì, 2: No\n"))
    user_verbose = 1 if user_choice == 1 else 0

    if(user_verbose == 1):
        user_log_interval = int(input(f"Inserisci ogni quanti episodi desideri ricevere informazioni di log: "))

    if algorithm == "DQN":
        user_exploration = float(input(f"Inserisci la frazione di esplorazione compreso tra 0 e 1 (DEFAULT = 0.5): "))
        user_final_eps = float(input(f"Inserisci il valore finale di epsilon compreso tra 0 e 1 (DEFAULT = 0.05): "))
        model = DQN("MlpPolicy", env, verbose=user_verbose,
                                exploration_fraction= user_exploration,
                                exploration_final_eps= user_final_eps,
        )
    elif algorithm == "PPO":
        model = PPO("MlpPolicy", env, verbose=user_verbose)
    
    model.learn(total_timesteps=learning_step, log_interval=user_log_interval)

    save_choice = int(input(f"Vuoi salvare il modello in modo personalizzato? 1: Sì, 2: No\n"))

    if save_choice == 1:
        print("Allenamento completato, salvataggio del modello... (N.B.: la finestra di dialogo potrebbe essere nascosta)")
        manager = Manager()
        model.save(manager.save_file())
    else:
        model.save(f"{algorithm}_CartPole_DEFAULTNAME.zip")

    del model # remove to demonstrate saving and loading

elif user_choice == 2:

    print("Scegliere un modello da testare (N.B.: la finestra di dialogo potrebbe essere nascosta)")
    manager = Manager()
    model_file = manager.choose_file()

    try:
        algorithm= manager.extract_info(model_file)
    except:
        print("Il file non ha un formato valido")

        user_choice = int(input(f"Quale algoritmo vuoi utilizzare? 1: DQN, 2: PPO\n"))
        algorithm = ALGORITHMS[user_choice - 1]

    env = CartPoleEnv(render_mode='human')
    if algorithm == "DQN":
        model = DQN.load(model_file, env)
    elif algorithm == "PPO":
        model = PPO.load(model_file, env)

    obs, info = env.reset()
    states = []

    i = 0
    while i<50:
        action, _states = model.predict(obs, deterministic=True)
        states.append(obs)
        obs, reward, terminated, truncated, info = env.step(action)
        time.sleep(0.05)
        if terminated:
            obs, info = env.reset()
            print("Episodio fallito")
            break
        i+=1

    
    print("Episodio completato")
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

    plt.tight_layout()
    plt.show()