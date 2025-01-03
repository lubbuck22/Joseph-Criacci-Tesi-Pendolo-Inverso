import os
from stable_baselines3 import DQN
from Pendolo_Inverso_DC_Motor import CartPoleEnv

LEARNING_STEP = 1000000

def gym_learning(env, high_PWM, low_PWM, step):
    model_path = f"test/DQN_CartPole_{low_PWM}_{high_PWM}.zip"
    
    if high_PWM <= 120 and low_PWM >= 60 and high_PWM >= low_PWM:
        if (not os.path.exists(model_path)):
            env.set_PWM_values(low_PWM=low_PWM, high_PWM=high_PWM)            
            # Configura il modello DQN con i parametri di esplorazione
            model = DQN("MlpPolicy", env, verbose=1)        
            model.learn(total_timesteps=LEARNING_STEP, log_interval=100)
            model.save(model_path) 
            
            del model
        gym_learning(env, high_PWM - step, low_PWM, step)
        gym_learning(env, high_PWM, low_PWM + step, step)
    

cart_env = CartPoleEnv()
gym_learning(env=cart_env, high_PWM=120, low_PWM=60, step=10)
print(chr(27) + "[2J")
print("Allenamenti completati!!!")
