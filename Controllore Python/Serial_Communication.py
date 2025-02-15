import serial  # Libreria per la comunicazione seriale
import struct  # Libreria per la conversione dei dati in formato binario
import keyboard  # Libreria per gestire gli input della tastiera
import math # Libreria per le operazioni matematiche
from stable_baselines3 import DQN, PPO  # Algoritmo DQN per l'apprendimento per rinforzo
from Pendolo_Inverso_DC_Motor import CartPoleEnv  # Ambiente per il pendolo inverso
from File_and_Serial_Manager import Manager
import numpy as np

# Definizione di alcuni comandi da inviare tramite la comunicazione seriale
ENABLE = 1.0
HOME = 2.0
MOVE_CENTER = 3.0
MODE = 4.0
ENABLE_CONTROL = 5.0

# Carattere per pulire il terminale
CLEAN_TERMINAL = chr(27) + "[2J"

# Valore infinito, usato per sincronizzare la comunicazione
INF = float('inf')

# Algoritmi di apprendimento per rinforzo
ALGORITHMS = ["DQN", "PPO"]
# Variabili globali per il controllo dei vari comandi
enable_value = 0
home_value = 0
move_center_value = 0
mode_value = 0
enable_control_value = 0



# Variabile globale per il messaggio da inviare
message_to_send = 0

# Funzione per inviare un messaggio tramite la porta seriale
def send(message, ser):
    ser.write(struct.pack('f', message))  # Converte il messaggio in un formato binario (float)

# Funzione per leggere un messaggio dalla porta seriale
def read_line(ser):
    try:
        message = struct.unpack('f', ser.read(4))[0]  # Legge 4 byte (float)
    except:
        message = 0  # Se c'è un errore, ritorna 0
    return message

# Funzione per sincronizzarsi con Arduino, attende un valore di sincronizzazione specifico
def synchronize_with_arduino(ser):
    check = read_line(ser)
    while(check != INF):  # Verifica che il valore letto sia l'inizio della trasmissione
        check = read_line(ser)

# Funzione che gestisce gli eventi di pressione dei tasti
def on_key_event(event):
    global message_to_send
    button = event.name  # Nome del tasto premuto
    # Aggiorna i valori in base ai tasti premuti e imposta il messaggio da inviare
    if(button == '1'):
        message_to_send = ENABLE
        global enable_value
        enable_value = (enable_value + 1) % 2  # Cambia lo stato (0 o 1)

    elif (button == '2'):
        message_to_send = HOME
        global home_value
        home_value = (home_value + 1) % 2

    elif (button == '3'):
        message_to_send = MOVE_CENTER
        global move_center_value
        move_center_value = (move_center_value + 1) % 2

    elif (button == '4'):
        message_to_send = MODE
        global mode_value
        mode_value = (mode_value + 1) % 2

    elif(button == '5'):
        message_to_send = ENABLE_CONTROL
        global enable_control_value
        enable_control_value = (enable_control_value + 1) % 2


# Funzione principale del programma
def main():
    global ser
    global message_to_send
    
    manager = Manager()

    # Crea l'ambiente del CartPole e carica il modello DQN
    env = CartPoleEnv()
    print("Scegli un modello di allenamento (N.B.: la finestra di dialogo potrebbe essere nascosta)")
    model_file = manager.choose_file()

    try:
        algorithm= manager.extract_info(model_file)
    except:
        print("Il file non ha un formato valido, valori PWM predefiniti")

        user_choice = int(input(f"Quale algoritmo vuoi utilizzare? 1: DQN, 2: PPO\n"))
        algorithm = ALGORITHMS[user_choice - 1]

    if(algorithm == "DQN"):
        model = DQN.load(model_file, env)
    elif(algorithm == "PPO"):
        model = PPO.load(model_file, env)

    print("Scegli la porta seriale da utilizzare (N.B.: la finestra di dialogo potrebbe essere nascosta)")
    porta_seriale = manager.get_serial_port()
    baud_rate = 912600  # Baud rate per la velocità di comunicazione seriale

    # Apri la connessione seriale con il dispositivo
    ser = serial.Serial(porta_seriale, baud_rate, timeout=1)

    # Stampa un messaggio di connessione aperta
    print(f'Comunicazione apeta sulla porta {porta_seriale}')

    # Configura la porta seriale
    del manager

    # Imposta un listener per gli eventi della tastiera
    keyboard.on_press(on_key_event)

    # Pulisce il buffer di input e output della connessione seriale
    ser.flush()
    ser.flushInput()
    ser.flushOutput()

    # Variabile che memorizza il valore di coppia di uscita
    torqueOut = 0

    # Memorizza i valori di osservazione dell'ambiente
    states = []
    applied_action = 1
    observations = [[] for _ in range(10)]
    # Ciclo principale del programma
    try:
        while True:
            # Controlla se ci sono dati in arrivo dalla seriale
            if ser.in_waiting > 0:
                # Sincronizza la comunicazione con Arduino
                synchronize_with_arduino(ser)

                # Legge i valori dal dispositivo tramite seriale
                x = read_line(ser)
                x_dot = read_line(ser)
                phi = read_line(ser)
                phi_dot = read_line(ser)
                theta = math.pi + phi
                theta_dot = phi_dot

                theta = theta % (2*math.pi)
                # Aggiorna l'osservazione più recente
                newest_observation = [x, x_dot, theta, theta_dot, applied_action]
                # Aggiorna la lista delle osservazioni
                observations.insert(0, newest_observation)
                observations.pop()

                states.append(newest_observation)

                torqueOut = 0
                # Se i controlli sono attivi, calcola la coppia da inviare
                if (mode_value == 1 and enable_control_value == 1):


                    if(phi*180/np.pi < -10):
                        action = 2
                    elif(phi*180/np.pi > 10):
                        action = 0
                    else:
                    # Prevede l'azione da eseguire
                        action, _states = model.predict(observations, deterministic=True)

                    # Converte l'azione in coppia
                    torqueOut = env.action_to_torque(action)

                    # Memorizza l'azione applicata
                    applied_action = action
                
                # Invia il messaggio e il valore di coppia
                sent_message = message_to_send
                send(sent_message, ser)
                send(torqueOut, ser)

                if(enable_control_value == 0):
                    applied_action = 1
                # Resetta il messaggio dopo l'invio e mostra i valori sul terminale
                if(sent_message != 0):
                    message_to_send = 0
                    print(CLEAN_TERMINAL)
                    print(f'Enable: {enable_value}\nHome: {home_value}\nMove Center: {move_center_value}\nMode: {mode_value}\nEnable Control: {enable_control_value}')
    except KeyboardInterrupt:
        # Chiudi la connessione seriale quando viene premuto Ctrl+C
        print("Connessione seriale interrotta")
    ser.close()
    np.savetxt(f"Data_{algorithm}.csv", states, delimiter=',')
    print(f"Dati salvati correttamente nel file 'Data_{algorithm}.csv'")

        
# Esegue la funzione principale
main()