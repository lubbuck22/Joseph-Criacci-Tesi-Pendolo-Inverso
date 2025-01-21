from stable_baselines3 import DQN, PPO
from Pendolo_Inverso_DC_Motor import CartPoleEnv
import pyautogui
import time

env = CartPoleEnv()

learning_step = 1000000

user_exploration = 0.25
user_final_eps = 0.05
model = DQN("MlpPolicy", env, verbose=1,
                        exploration_fraction= user_exploration,
                        exploration_final_eps= user_final_eps,
    )
start_time = time.time()
model.learn(total_timesteps=learning_step, log_interval=1)
end_time = time.time()
print("Allenamento completato, salvataggio del modello...")
print(f"Tempo impiegato: {end_time - start_time} secondi")
model.save(f"DQN_CartPole_1MLS_25EF_NEW.zip")
screenshot = pyautogui.screenshot()
screenshot.save("screenshot_DQN_CartPole_1MLS_25EF_NEW.png")
del model # remove to demonstrate saving and loading



learning_step = 1000000
user_exploration = 0.75
model = DQN("MlpPolicy", env, verbose=1,
                        exploration_fraction= user_exploration,
                        exploration_final_eps= user_final_eps,
    )

start_time = time.time()
model.learn(total_timesteps=learning_step, log_interval=1)
end_time = time.time()
print("Allenamento completato, salvataggio del modello...")
print(f"Tempo impiegato: {end_time - start_time} secondi")
model.save(f"DQN_CartPole_1MLS_75EF_NEW.zip")
screenshot = pyautogui.screenshot()
screenshot.save("screenshot_DQN_CartPole_1MLS_75EF_NEW.png")
del model # remove to demonstrate saving and loading
