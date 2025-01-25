from stable_baselines3 import DQN, PPO
from Pendolo_Inverso_DC_Motor import CartPoleEnv
from File_and_Serial_Manager import Manager
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import make_interp_spline
import time

# Funzione per visualizzare i risultati dell'allenamento
def display_pendulum_control(pendulum_states, time_step):
    states = np.array(pendulum_states)


    # Supponiamo che ogni passo di tempo corrisponda a 0.05 secondi

    labels = ['Posizione (m)', 'Velocità (m/s)', 'Posizione angolare (rad)', 'Velocità angolare (rad/s)', 'Azione']
    titles = ['Evoluzione della posizione nel tempo', 'Evoluzione della velocità nel tempo', 'Evoluzione della posizione angolare nel tempo', 'Evoluzione della velocità angolare nel tempo', "Evoluzione dell'azione nel tempo"]

    plt.figure(figsize=(15, 10))
    for i in range(5):
        plt.subplot(5, 1, i+1)
        
        if i<4:
        # Interpolazione spline per una curva liscia
            time = np.linspace(0, (len(states[:,i]) - 1) * time_step, len(states[:,i]))
            time_smooth = np.linspace(time.min(), time.max(), 500)

            spline = make_interp_spline(time, states[:, i])
            state_smooth = spline(time_smooth)

            plt.plot(time_smooth, state_smooth, label='Interpolazione Spline')
            plt.plot(time, states[:, i], 'o', label='Punti Originali')
        
        else:
            time = np.linspace(0, (len(states[:,i]) - 1) * time_step, len(states[:,i]))
            time_smooth = np.linspace(time.min(), time.max(), 500)

            plt.step(time, states[:, i], where='post')
            plt.plot(time, states[:, i], 'o')
        plt.xlabel('Tempo (s)')
        plt.ylabel(labels[i])
        plt.title(titles[i])
        plt.legend()
        plt.grid(True)
    
    plt.tight_layout()
    plt.show()

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
    else:
        user_log_interval = 1000
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
    user_choice = float(input("Durata massima dell'episodio in secondi: "))
    episode_length = user_choice

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

    time_step = env.period
    episode_steps = int(episode_length/time_step)

    obs, info = env.reset()
    states = []
    states.append(obs[0])

    i = 0
    while i<episode_steps:
        action, _states = model.predict(obs, deterministic=True)
        obs, reward, terminated, truncated, info = env.step(action)
        states.append(obs[0])
        time.sleep(time_step)
        if terminated:
            obs, info = env.reset()
            print("Episodio terminato anticipatamente")
            break
        i+=1

    display_pendulum_control(states, time_step)