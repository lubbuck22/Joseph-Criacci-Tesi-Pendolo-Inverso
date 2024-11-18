from stable_baselines3 import DQN
from Pendolo_Inverso_DC_Motor import CartPoleEnv
from File_and_Serial_Manager import Manager

""" Se si è interessati solamente a testate un modello già esistente, commentare le righe 11÷15 """

LEARNING_STEP = 1000000
manager = Manager()
env = CartPoleEnv(render_mode='human')

""" model = DQN("MlpPolicy", env, verbose=1)
model.learn(total_timesteps=LEARNING_STEP, log_interval=5)
print("Allenamento completato, salvataggio del modello... (N.B.: la finestra di dialogo potrebbe essere nascosta)")
model.save(manager.save_file())

del model # remove to demonstrate saving and loading """

print("Scegliere un modello da testare (N.B.: la finestra di dialogo potrebbe essere nascosta)")
model_file = manager.choose_file()
low, high = manager.extract_low_high(model_file)
env.set_PWM_values(low_PWM=low, high_PWM=high)
model = DQN.load(model_file, env)
obs, info = env.reset()
while True:
    action, _states = model.predict(obs, deterministic=True)
    obs, reward, terminated, truncated, info = env.step(action)
    if terminated or truncated:
        obs, info = env.reset()
        print('You failed!')
