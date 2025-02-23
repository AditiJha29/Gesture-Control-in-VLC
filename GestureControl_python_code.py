import serial  # Serial imported for Serial communication
import time    # Required to use delay functions
import pyautogui

# Establish a connection with the Arduino
ArduinoSerial = serial.Serial('COM6', 9600)  # Change to COM6
time.sleep(2)  # Wait for 2 seconds for the communication to get established

while True:
    incoming = str(ArduinoSerial.readline())  # Read the serial data and print it as a line
    print(incoming)  # Print the incoming message to the console

    # Check for commands from the Arduino and perform actions
    if 'Play/Pause' in incoming:
        pyautogui.typewrite(['space'], 0.2)  # Simulate space key press

    if 'Rewind' in incoming:
        pyautogui.hotkey('ctrl', 'left')  # Simulate Ctrl + Left Arrow

    if 'Forward' in incoming:
        pyautogui.hotkey('ctrl', 'right')  # Simulate Ctrl + Right Arrow

    if 'Vup' in incoming:
        pyautogui.hotkey('ctrl', 'down')  # Simulate Ctrl + Down Arrow

    if 'Vdown' in incoming:
        pyautogui.hotkey('ctrl', 'up')  # Simulate Ctrl + Up Arrow
