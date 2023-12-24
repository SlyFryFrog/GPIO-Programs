import Jetson.GPIO as GPIO
import time

code: list = [2, 1, 4] # Change passcode here

def setup_buttons_GPIO() -> list:
    """Returns a list of pin numbers used for buttons"""
    GPIO_buttons = [11, 12, 13, 15]
    return GPIO_buttons

def setup_lights_GPIO() -> list:
    """Returns a list of pin numbers used for lights"""
    GPIO_lights = [7]
    return GPIO_lights

def main():
    combination: list = [0, 0, 0]
    GPIO.cleanup()
    GPIO.setmode(GPIO.BOARD)

    print(f"Running version: {GPIO.VERSION}\nHardware info: {GPIO.JETSON_INFO}\n")
    
    GPIO_buttons = setup_buttons_GPIO()
    GPIO_lights = setup_lights_GPIO()

    for GPIO_button in GPIO_buttons:
        GPIO.setup(GPIO_button, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)  # Use pull-down resistors
    
    for GPIO_light in GPIO_lights:
        GPIO.setup(GPIO_light, GPIO.OUT)

    try:
        pressed = [False, False, False, False]

        while True:
            if code == combination:
                for GPIO_light in GPIO_lights:
                    GPIO.output(GPIO_light, GPIO.LOW)
            else:
                for GPIO_light in GPIO_lights:
                    GPIO.output(GPIO_light, GPIO.HIGH)

            
            for i, GPIO_button in enumerate(GPIO_buttons):
                button_state = GPIO.input(GPIO_button)

                if button_state == GPIO.HIGH and not pressed[i]:
                    pressed[i] = True
                    print(f"Button {GPIO_button} Pressed!")
                elif button_state == GPIO.LOW and pressed[i]:
                    if i < 3:
                        combination[i] += 1
                        print(combination)
                    elif i == 3:
                        combination = [0, 0, 0]
                        print(f"Combination reset!\n{combination}")

                    pressed[i] = False
                    print(f"Button {GPIO_button} Released!")

            time.sleep(0.1)

    except KeyboardInterrupt:
        GPIO.cleanup()

    finally:
        GPIO.cleanup()
        print("Exiting...")

if __name__ == '__main__':
    main()
