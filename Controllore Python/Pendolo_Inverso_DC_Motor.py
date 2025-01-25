import math
from typing import Optional, Union

import numpy as np

import gymnasium as gym
from gymnasium import logger, spaces
from gymnasium.envs.classic_control import utils
from gymnasium.error import DependencyNotInstalled


class CartPoleEnv(gym.Env[np.ndarray, Union[int, np.ndarray]]):
    """
    ## Descrizione

    Questo ambiente corrisponde a una versione modificata del problema del cart-pole (pendolo su carrello) 
    descritto da Barto, Sutton e Anderson. Il problema originale è documentato in 
    ["Neuronlike Adaptive Elements That Can Solve Difficult Learning Control Problem"].
    (https://ieeexplore.ieee.org/document/6313077)
    
    Un'asta (il pendolo) è collegata tramite un giunto non attuato a un carrello che si muove su una pista.
    Il pendolo è inizialmente posizionato verticalmente sul carrello, e l'obiettivo è bilanciare l'asta applicando forze 
    a sinistra o a destra sul carrello.

    ## Spazio delle azioni

    Lo spazio delle azioni è un array unidimensionale che può assumere valori {0, 1, 2}. La direzione verso cui indirizzare la forza.
    
    |       Azione                 |                Effetto                      |
    |------------------------------|---------------------------------------------|
    |           0:                 |        Spingi nella direzione negativa      |
    |           1:                 |                Stai fermo                   |
    |           2:                 |        Spingi nella direzione positiva      |
    |______________________________|_____________________________________________|

    **Nota**: L'azione 1 non ha effetto sul sistema, ma è stata aggiunta per completezza.


    ## Spazio delle osservazioni

    L'osservazione è un array con forma `(10,5)` ciascuna riga rappresenta lo stato del sistema in un determinato istante.:

    | Num | Osservazione                  | Min                 | Max               |
    |-----|-------------------------------|---------------------|-------------------|
    | 0   | Posizione del carrello        | -0.8                | 0.8               |
    | 1   | Velocità del carrello         | -Inf                | Inf               |
    | 2   | Angolo del pendolo            | ~ -0.418 rad (-24°) | ~ 0.418 rad (24°) |
    | 3   | Velocità angolare del pendolo | -Inf                | Inf               |
    | 4   | Azione                        | 0                   | 2                 |
    |_____|_______________________________|_____________________|___________________|

    **Nota:** Sebbene i limiti sopra indichino i valori possibili per ogni elemento dello spazio di osservazione,
    non riflettono necessariamente i valori consentiti nello stato dell'episodio. In particolare:
    - La posizione del carrello può variare tra `(-0.8, 0.8)`, ma l'episodio termina se il carrello esce dalla gamma `(-0.4, 0.4)`.
    - L'angolo del pendolo può essere osservato tra `(-0.418, 0.418)` radianti (o **±24°**), ma l'episodio termina
      se l'angolo non rientra nel range `(-0.2095, 0.2095)` (o **±12°**).

    ## Ricompense
    L'obiettivo è mantenere l'asta in equilibrio il più a lungo possibile. Viene data una ricompensa per ogni passo, compreso il passo finale.
    La soglia di ricompensa predefinita è 500.
    Inoltre, la ricompensa è proporzionale alla posizione del carrello, con maggiori ricompense se il carrello è vicino al centro.


    ## Fine dell'episodio
    L'episodio termina se una delle seguenti condizioni si verifica:

    1. Terminazione: L'angolo del pendolo è maggiore di ±12°
    2. Terminazione: La posizione del carrello è maggiore di ±0.4 (il centro del carrello raggiunge il bordo dello schermo)
    3. Troncamento: La lunghezza dell'episodio supera 500 reward.

    ## Argomenti

    CartPole ha solo `render_mode` come parola chiave per `gymnasium.make`.
    Al reset, il parametro `options` permette di cambiare i limiti usati per determinare lo stato casuale.

    """

    metadata = {
        "render_modes": ["human", "rgb_array"],
        "render_fps": 50,
    }

    def __init__(
        self, render_mode: Optional[str] = None
    ):
        self.gravity = 9.81  # Gravità terrestre

        #### Valori nominali 
        self.masscart_nominal = 0.6  # Massa del carrello
        self.masspole_nominal = 0.1528  # Massa del pendolo
        self.length_nominal = 0.4  # Lunghezza del pendolo
        self.inertia_nominal = 0.000814971   # Momento d'inerzia del pendolo
        self.friction_coefficient_nominal = 0.0000765  # Coefficiente di attrito
        
        self.uncertainty = 0.0 # Margine di errore per i valori nominali

        #### Valori reali
        self.masscart = self.apply_error(self.masscart_nominal, self.uncertainty)
        self.masspole = self.apply_error(self.masspole_nominal, self.uncertainty)
        self.length = self.apply_error(self.length_nominal, self.uncertainty)
        self.inertia = self.apply_error(self.inertia_nominal, self.uncertainty)
        self.friction_coefficient = self.apply_error(self.friction_coefficient_nominal, self.uncertainty)


        self.total_mass = self.masspole + self.masscart  # Massa totale del sistema
        self.polemass_length = self.masspole * self.length  # Prodotto tra la massa del pendolo e la sua lunghezza

        
        """ L'Arduino esegue il loop ogni self.tau = 0.005 secondi, ma comunica con Python ogni self.period = 0.05 secondi.
        Tra due comunicazioni, Arduino continua ad applicare l'ultimo segnale di controllo generato. """
        self.period = 0.05  # Periodo di comunicazione con Arduino (in secondi)
        self.tau = 0.005  # Secondi tra gli aggiornamenti di stato


        """ Il codice Arduino traduce il segnale di controllo in un valore PWM secondo la relazione: PWM = torque/5.8824 """
        self.torque_pwm_constant = 5.8824  # Costante per convertire in coppia il valore PWM

        # Angolo oltre il quale l'episodio fallisce
        self.theta_threshold_radians = 12 * (2*math.pi) / 360  # ±12° in radianti
        self.x_threshold = 0.4  # Posizione limite del carrello

        self.max_reward = 500  # Ricompensa massima
        self.current_reward = 0  # Ricompensa attuale
        # Imposta il limite dell'angolo a 2 * theta_threshold_radians per garantire che l'osservazione rimanga valida        
        high = np.array(
            [
                self.x_threshold * 2,
                np.inf,
                self.theta_threshold_radians * 2,
                np.inf,
                np.inf,
            ],
            dtype=np.float32,
        )
        # Ripeti l'array `high` per creare una matrice di dimensioni (10, 5)
        high_matrix = np.tile(high, (10, 1))

        # Spazio delle azioni e delle osservazioni
        self.action_space = spaces.Discrete(3)
        self.observation_space = spaces.Box(-high_matrix, high_matrix, dtype=np.float32)


        self.render_mode = render_mode

        # Variabili per il rendering
        self.screen_width = 700
        self.screen_height = 500
        self.screen = None
        self.clock = None
        self.isopen = True
        self.state = []

        self.steps_beyond_terminated = None



    # Metodo che aggiorna il sistema
    def step(self, action):
        assert self.action_space.contains(
            action
        ), f"{action!r} ({type(action)}) invalid"
        assert self.state is not None, "Call reset before using step method."
        x, x_dot, theta, theta_dot, applied_action = self.state[0]

        # Mantieni l'angolo tra 0 e 2*pi
        theta = theta % (2*math.pi)

        pendulum_state = np.array([x, x_dot, theta, theta_dot])

        for i in range(int(self.period/self.tau)):  
            # Ricalcola la forza
            force = self.action_to_force(action, pendulum_state)          
            x, x_dot, theta, theta_dot = self.apply_force(force, pendulum_state)
            theta = theta % (2*math.pi)
            # Aggiorniamo lo stato a seguito dell'applicazione dell'azione
            pendulum_state = np.array([x, x_dot, theta, theta_dot])

        # Aggiorna lo stato del sistema
        self.state.insert(0, [x, x_dot, theta, theta_dot, action]) # Aggiunge il nuovo stato in cima alla lista
        self.state.pop() # Rimuove l'ultimo stato per mantenere la lista di lunghezza 10

        # Controlla se l'episodio deve terminare
        terminated = bool(
            x < -self.x_threshold
            or x > self.x_threshold
            or theta < math.pi -self.theta_threshold_radians
            or theta > math.pi + self.theta_threshold_radians
        )
        truncated = False

        # Ricompensa in base allo stato del sistema
        if not terminated:
            reward = (self.x_threshold-abs(x))/self.x_threshold
            self.current_reward += reward

        elif self.steps_beyond_terminated is None:
            # Il pendolo è appena caduto
            self.steps_beyond_terminated = 0

            reward = 1.0
        else:
            if self.steps_beyond_terminated == 0:
                logger.warn(
                    "You are calling 'step()' even though this environment has already returned terminated = True. "
                    "You should always call 'reset()' once you receive 'terminated = True' -- any further steps are undefined behavior."
                )
            self.steps_beyond_terminated += 1

            reward = 0.0

        if(self.current_reward > self.max_reward):
            truncated = True
        # Renderizza il sistema se richiesto
        if self.render_mode == "human":
            self.render()

        return np.array(self.state, dtype=np.float32), reward, terminated, truncated, {}


    """ Questa funzione riceve in ingresso la forza da applicare al carrello,e attraverso l'equazione del moto
    calcola l'accelerazione lineare del carrello e l'accelerazione angolare del pendolo.
    L'integrazione di Runge-Kutta del 4° ordine viene utilizzata per incrementare le posizioni e le velocità """
    def apply_force(self, force, pendulum_state):

        # Funzione ausiliaria per calcolare la derivata del vettore di stato
        def derivatives(pendulum_state, force):
            x, x_dot, theta, theta_dot = pendulum_state
            costheta = np.cos(theta)
            sintheta = np.sin(theta)
            tantheta = np.tan(theta)

            # Forza di attrito
            friction_force = self.friction_coefficient * x_dot

            # Equazioni del moto
            q = (-self.total_mass*(self.inertia + self.polemass_length*self.length) + (self.polemass_length * costheta)**2)/(self.polemass_length * costheta)

            theta_acc = (-friction_force + self.gravity*self.total_mass*tantheta + self.polemass_length*(theta_dot**2)*sintheta + force)/q

            x_acc = -((self.inertia + self.polemass_length*self.length)*theta_acc)/(self.polemass_length*costheta) - self.gravity*tantheta

            return np.array([x_dot, x_acc, theta_dot, theta_acc])

        tau = self.tau

        k1 = tau*derivatives(pendulum_state, force)
        k2 = tau*derivatives(pendulum_state + k1/2.0, force)
        k3 = tau*derivatives(pendulum_state + k2/2.0, force)
        k4 = tau*derivatives(pendulum_state + k3, force)

        new_state = pendulum_state + (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4)

        x, x_dot, theta, theta_dot = new_state
        return x, x_dot, theta, theta_dot
    
    
    def action_to_force(self, action, pendulum_state):

        x, x_dot, theta, theta_dot = pendulum_state

        force = 0

        if (action == 0): #Forza negativa
            force =  -(2.6909 - 3.1548*(-x_dot))
            if(force > 0):
                force = 0
        elif (action == 1): #Forza nulla
            force = 0
        elif (action == 2): #Forza positiva
            force = 2.6909 - 3.1548*x_dot
            if(force < 0):
                force = 0
        
        return force


    """ Converte l'azione in coppia applicata al motore """
    def action_to_torque(self, action):
        PWM_value = 127 # Valore PWM di 6V
        torque = 0
        if action == 0:  # Coppia negativa
            torque = -PWM_value*self.torque_pwm_constant
        elif action == 1:  # Coppia nulla
            torque = 0
        elif action == 2:  # Coppia positiva
            torque = PWM_value*self.torque_pwm_constant
        return torque

    """ Modifica i valori reali dai valori nominale con una variazione percentuale definita dalla variabile self.uncertainty """
    def apply_error(self, nominal, error):
        return nominal*(self.np_random.uniform(1-error, 1+error))

    def apply_uncertainty(self):
        self.masscart = self.apply_error(self.masscart_nominal, self.uncertainty)
        self.masspole = self.apply_error(self.masspole_nominal, self.uncertainty)
        self.length = self.apply_error(self.length_nominal, self.uncertainty)
        self.inertia = self.apply_error(self.inertia_nominal, self.uncertainty)
        self.friction_coefficient = self.apply_error(self.friction_coefficient_nominal, self.uncertainty)


        ### Ricalcola i valori tenendo conto dell'incertezza
        self.total_mass = self.masspole + self.masscart  # Massa totale del sistema
        self.polemass_length = self.masspole * self.length  # Prodotto tra la massa del pendolo e la sua lunghezza


    """ Metodo di reset dell'ambiente """
    def reset(
        self,
        *,
        seed: Optional[int] = None,
        options: Optional[dict] = None,
    ):
        super().reset(seed=seed)
        # Note that if you use custom reset bounds, it may lead to out-of-bound
        # state/observations.
        
        self.state = []
        low, high = utils.maybe_parse_reset_bounds(
            options, -0.15, 0.15  # default low
        ) # default high
        x, x_dot, phi, phi_dot = self.np_random.uniform(low=low, high=high, size=(4,))


        for i in range(10):
            self.state.append([x, x_dot, math.pi + phi, phi_dot, 1])
        self.steps_beyond_terminated = None
        self.current_reward = 0

        # Applica variazioni ai valori nominali
        self.apply_uncertainty()
        

        if self.render_mode == "human":
            self.render()
        return np.array(self.state, dtype=np.float32), {}


    """ Metodo per renderizzare l'ambiente """
    def render(self):
        if self.render_mode is None:
            assert self.spec is not None
            gym.logger.warn(
                "You are calling render method without specifying any render mode. "
                "You can specify the render_mode at initialization, "
                f'e.g. gym.make("{self.spec.id}", render_mode="rgb_array")'
            )
            return

        try:
            import pygame
            from pygame import gfxdraw
        except ImportError as e:
            raise DependencyNotInstalled(
                'pygame is not installed, run `pip install "gymnasium[classic-control]"`'
            ) from e

        if self.screen is None:
            pygame.init()
            if self.render_mode == "human":
                pygame.display.init()
                self.screen = pygame.display.set_mode(
                    (self.screen_width, self.screen_height)
                )
            else:  # mode == "rgb_array"
                self.screen = pygame.Surface((self.screen_width, self.screen_height))
        if self.clock is None:
            self.clock = pygame.time.Clock()

        world_width = self.x_threshold * 2
        scale = self.screen_width / world_width
        polewidth = 10.0
        polelen = scale * (self.length)
        cartwidth = 50.0
        cartheight = 30.0

        if self.state is None:
            return None

        x = self.state[0]

        self.surf = pygame.Surface((self.screen_width, self.screen_height))
        self.surf.fill((255, 255, 255))

        l, r, t, b = -cartwidth / 2, cartwidth / 2, cartheight / 2, -cartheight / 2
        axleoffset = cartheight / 4.0
        cartx = x[0] * scale + self.screen_width / 2.0  # MIDDLE OF CART
        carty = 100  # TOP OF CART
        cart_coords = [(l, b), (l, t), (r, t), (r, b)]
        cart_coords = [(c[0] + cartx, c[1] + carty) for c in cart_coords]
        gfxdraw.aapolygon(self.surf, cart_coords, (0, 0, 0))
        gfxdraw.filled_polygon(self.surf, cart_coords, (0, 0, 0))

        l, r, t, b = (
            -polewidth / 2,
            polewidth / 2,
            polelen - polewidth / 2,
            -polewidth / 2,
        )

        pole_coords = []
        for coord in [(l, b), (l, t), (r, t), (r, b)]:
            coord = pygame.math.Vector2(coord).rotate_rad((x[2])-math.pi)
            coord = (coord[0] + cartx, coord[1] + carty + axleoffset)
            pole_coords.append(coord)
        gfxdraw.aapolygon(self.surf, pole_coords, (202, 152, 101))
        gfxdraw.filled_polygon(self.surf, pole_coords, (202, 152, 101))

        gfxdraw.aacircle(
            self.surf,
            int(cartx),
            int(carty + axleoffset),
            int(polewidth / 2),
            (129, 132, 203),
        )
        gfxdraw.filled_circle(
            self.surf,
            int(cartx),
            int(carty + axleoffset),
            int(polewidth / 2),
            (129, 132, 203),
        )

        gfxdraw.hline(self.surf, 0, self.screen_width, carty, (0, 0, 0))

        self.surf = pygame.transform.flip(self.surf, False, True)
        self.screen.blit(self.surf, (0, 0))
        if self.render_mode == "human":
            pygame.event.pump()
            self.clock.tick(self.metadata["render_fps"])
            pygame.display.flip()

        elif self.render_mode == "rgb_array":
            return np.transpose(
                np.array(pygame.surfarray.pixels3d(self.screen)), axes=(1, 0, 2)
            )

    """ Metodo per chiudere l'ambiente """
    def close(self):
        if self.screen is not None:
            import pygame

            pygame.display.quit()
            pygame.quit()
            self.isopen = False
