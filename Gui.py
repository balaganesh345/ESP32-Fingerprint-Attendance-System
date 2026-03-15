import serial
import tkinter as tk

ser = serial.Serial('COM3',115200)

window = tk.Tk()
window.title("Fingerprint Attendance System")

text = tk.Text(window,height=20,width=50)
text.pack()

def read_serial():
    if ser.in_waiting:
        data = ser.readline().decode()
        text.insert(tk.END,data)
    window.after(100,read_serial)

read_serial()
window.mainloop()
