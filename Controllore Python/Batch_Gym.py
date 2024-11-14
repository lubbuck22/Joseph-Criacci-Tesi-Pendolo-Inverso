import os
from stable_baselines3 import DQN
from Pendolo_Inverso_DC_Motor import CartPoleEnv

LEARNING_STEP = 1000000

def gym_learning(env, high_PWM, low_PWM):
    model_path = f"Modelli Proposti/DQN_CartPole_{low_PWM}_{high_PWM}.zip"
    
    if high_PWM <= 150 and low_PWM >= 50 and high_PWM >= low_PWM and not os.path.exists(model_path):
        env.set_high_PWM(high_PWM)
        env.set_low_PWM(low_PWM)
        
        # Configura il modello DQN con i parametri di esplorazione
        model = DQN("MlpPolicy", env, verbose=1)        
        model.learn(total_timesteps=LEARNING_STEP, log_interval=100)
        model.save(model_path)
        
        del model
        gym_learning(env, high_PWM - 25, low_PWM)
        gym_learning(env, high_PWM, low_PWM + 25)
    
    if high_PWM <= 150 and low_PWM >= 50 and high_PWM >= low_PWM and os.path.exists(model_path):
        gym_learning(env, high_PWM - 25, low_PWM)
        gym_learning(env, high_PWM, low_PWM + 25)

cart_env = CartPoleEnv()
gym_learning(env=cart_env, high_PWM=150, low_PWM=50)
print(chr(27) + "[2J")
print("Allenamenti completati!!!")
