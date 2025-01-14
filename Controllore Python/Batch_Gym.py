import os
from stable_baselines3 import DQN, PPO
from Pendolo_Inverso_DC_Motor import CartPoleEnv

LEARNING_STEP = 1000000

LOW_DEFAULT_PWM = 70
HIGH_DEFAULT_PWM = 110
DEFAULT_STEP = 10

def gym_learning(env, high_PWM, low_PWM, step, algorithm):
    model_path = f"Nuove equazioni di Moto/{algorithm}/{algorithm}_CartPole_{low_PWM}_{high_PWM}.zip"
    
    if high_PWM <= HIGH_DEFAULT_PWM and low_PWM >= LOW_DEFAULT_PWM and high_PWM >= low_PWM:
        if (not os.path.exists(model_path)):
            print(f"Sto allenando il modello {algorithm} con PWM da {low_PWM} a {high_PWM}")
            env.set_PWM_values(low_PWM=low_PWM, high_PWM=high_PWM)            
            # Configura il modello
            if(algorithm == "DQN"):
                model = DQN("MlpPolicy", env, verbose=0)
                model.learn(total_timesteps=1000000, log_interval=1000)
            elif(algorithm == "PPO"):
                model = PPO("MlpPolicy", env, verbose=0)
                model.learn(total_timesteps=100000, log_interval=5)
            print(f"Finito di allenare il modello {algorithm} con PWM da {low_PWM} a {high_PWM}")
            model.save(model_path) 
            
            del model
        gym_learning(env, high_PWM - step, low_PWM, step, algorithm)
        gym_learning(env, high_PWM, low_PWM + step, step, algorithm)


cart_env = CartPoleEnv()
gym_learning(env=cart_env, high_PWM=HIGH_DEFAULT_PWM, low_PWM=LOW_DEFAULT_PWM, step=DEFAULT_STEP, algorithm="PPO")

gym_learning(env=cart_env, high_PWM=HIGH_DEFAULT_PWM, low_PWM=LOW_DEFAULT_PWM, step=DEFAULT_STEP, algorithm="DQN")


print(chr(27) + "[2J")
print("Allenamenti completati!!!")
