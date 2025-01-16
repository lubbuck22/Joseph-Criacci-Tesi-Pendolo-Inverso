from stable_baselines3 import DQN, PPO
from Pendolo_Inverso_DC_Motor import CartPoleEnv
from File_and_Serial_Manager import Manager

ALGORITHMS = ["DQN", "PPO"]

# Scelta dell'utente
user_choice = int(input(f"Vuoi allenare un modello o testarne uno già esistente? 1: Allenamento, 2: Test\n"))

if user_choice == 1:
    # Allenamento
    env = CartPoleEnv()

    user_choice = int(input(f"Quale algoritmo vuoi utilizzare? 1: DQN, 2: PPO\n"))

    algorithm = ALGORITHMS[user_choice - 1]

    learning_step = int(input(f"Inserisci il numero di step di apprendimento: "))
    if algorithm == "DQN":
        user_exploration = float(input(f"Inserisci la frazione di esplorazione compreso tra 0 e 1 (DEFAULT = 0.5): "))
        user_final_eps = float(input(f"Inserisci il valore finale di epsilon compreso tra 0 e 1 (DEFAULT = 0.05): "))
        model = DQN("MlpPolicy", env, verbose=1,
                                exploration_fraction= user_exploration,
                                exploration_final_eps= user_final_eps,
        )
    elif algorithm == "PPO":
        model = PPO("MlpPolicy", env, verbose=1)
    model.learn(total_timesteps=learning_step, log_interval=1)

    save_choice = int(input(f"Vuoi salvare il modello in modo personalizzato? 1: Sì, 2: No\n"))

    if save_choice == 1:
        print("Allenamento completato, salvataggio del modello... (N.B.: la finestra di dialogo potrebbe essere nascosta)")
        manager = Manager()
        model.save(manager.save_file())
    else:
        model.save(f"{algorithm}_CartPole_DEFAULTNAME.zip")

    del model # remove to demonstrate saving and loading

elif user_choice == 2:

    env = CartPoleEnv(render_mode='human')
    print("Scegliere un modello da testare (N.B.: la finestra di dialogo potrebbe essere nascosta)")
    manager = Manager()
    model_file = manager.choose_file()

    try:
        algorithm= manager.extract_info(model_file)
    except:
        print("Il file non ha un formato valido")

        user_choice = int(input(f"Quale algoritmo vuoi utilizzare? 1: DQN, 2: PPO\n"))
        algorithm = ALGORITHMS[user_choice - 1]

    if algorithm == "DQN":
        model = DQN.load(model_file, env)
    elif algorithm == "PPO":
        model = PPO.load(model_file, env)

    obs, info = env.reset()
    while True:
        action, _states = model.predict(obs, deterministic=True)
        obs, reward, terminated, truncated, info = env.step(action)
        if terminated:
            obs, info = env.reset()
            print("Episodio fallito")
