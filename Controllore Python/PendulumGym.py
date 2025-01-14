from stable_baselines3 import DQN, SAC, PPO
from Pendolo_Inverso_DC_Motor import CartPoleEnv
from File_and_Serial_Manager import Manager
import time

LEARNING_STEP = 1
ALGORITHMS = ["DQN", "PPO"]

# Scelta dell'utente
user_choice = int(input(f"Vuoi allenare un modello o testarne uno già esistente? 1: Allenamento, 2: Test\n"))

if user_choice == 1:
    # Allenamento
    env = CartPoleEnv()

    user_choice = int(input(f"Quale algoritmo vuoi utilizzare? 1: DQN, 2: PPO\n"))

    algorithm = ALGORITHMS[user_choice - 1]

    if algorithm == "DQN":
        #DQN
        model = DQN("MlpPolicy", env, verbose=1,
                                exploration_fraction= 0.5,
                                exploration_final_eps= 0.05,
        )
    elif algorithm == "PPO":
        #PPO
        model = PPO("MlpPolicy", env, verbose=1)
    model.learn(total_timesteps=LEARNING_STEP, log_interval=10)

    save_choice = int(input(f"Vuoi salvare il modello in modo personalizzato? 1: Sì, 2: No\n"))

    if save_choice == 1:
        print("Allenamento completato, salvataggio del modello... (N.B.: la finestra di dialogo potrebbe essere nascosta)")
        manager = Manager()
        model.save(manager.save_file())
    else:
        model.save(f"{algorithm}_CartPole_{int(env.low_PWM)}_{int(env.high_PWM)}.zip")

    del model # remove to demonstrate saving and loading

elif user_choice == 2:

    env = CartPoleEnv(render_mode='human')
    print("Scegliere un modello da testare (N.B.: la finestra di dialogo potrebbe essere nascosta)")
    manager = Manager()
    model_file = manager.choose_file()

    try:
        algorithm, low, high = manager.extract_info(model_file)
        env.set_PWM_values(low_PWM=low, high_PWM=high)
    except:
        print("Il file non ha un formato valido, valori PWM predefiniti")

        user_choice = int(input(f"Quale algoritmo vuoi utilizzare? 1: DQN, 2: PPO\n"))
        algorithm = ALGORITHMS[user_choice - 1]

    if algorithm == "DQN":
        model = DQN.load(model_file, env)
    elif algorithm == "PPO":
        model = PPO.load(model_file, env)

    obs, info = env.reset()
    while True:
        action, _states = model.predict(obs, deterministic=True)
        print(env.state, env.action_to_torque(action))
        obs, reward, terminated, truncated, info = env.step(action)
        if terminated or truncated:
            obs, info = env.reset()
            print('You failed!')
            exit()
