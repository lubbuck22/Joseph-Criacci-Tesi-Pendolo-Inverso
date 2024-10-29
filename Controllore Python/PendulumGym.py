import gymnasium as gym
from stable_baselines3 import DQN
from Pendolo_Inverso_DC_Motor import CartPoleEnv
from File_and_Serial_Manager import Manager
import time
""" Se si è interessati solamente a testate un modello già esistente, commentare le righe 11÷15 """

LEARNING_STEP = 1000000
env = CartPoleEnv(render_mode='human')
manager = Manager()

""" model = DQN("MlpPolicy", env, verbose=1)
model.learn(total_timesteps=LEARNING_STEP, log_interval=5)
model.save(manager.save_file())

del model # remove to demonstrate saving and loading """

model = DQN.load(manager.choose_file(), env)
obs, info = env.reset()
while True:
    action, _states = model.predict(obs, deterministic=True)
    obs, reward, terminated, truncated, info = env.step(action)
    PWM_value = env.action_to_PWM(action)
    [x, x_dot, theta, theta_dot] = env.state
    force = (env.K/(env.Ra*env.r))*(env.max_nominal_voltage - env.K*x_dot/env.r)
    torque = env.action_to_torque(action)
    print(f'PWM: {PWM_value},   Torque: {torque},   Applied Force: {force} N')
    if terminated or truncated:
        obs, info = env.reset()
