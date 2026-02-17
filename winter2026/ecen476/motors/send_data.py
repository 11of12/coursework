import serial
import struct
import time

# Serial port configuration (adjust these as needed)
PORT = '/dev/ttyUSB0'  # Example for a USB-to-serial adapter, change if different
BAUDRATE = 115200         # Set the baud rate of the device
TIMEOUT = 1             # Timeout for reading from the serial port


# Set up the serial connection
ser = serial.Serial(PORT, BAUDRATE, timeout=TIMEOUT)

# The float32 value to send
# float_value = 3.14159    # Example float value (can be any float32 number)

while True:
# Packing the float into a byte string using struct.pack
    float_value = input("Give it to me!")
    if float_value == "q":
        break
    else:
        float_value = float(float_value)

    packed_data = struct.pack('<f', float_value)
    # Check if the serial connection was established successfully
    if not ser.is_open:
        print(f"Failed to open port {PORT}")
        exit()

    print(f"Sending float {float_value} packed as bytes: {packed_data.hex()}")

    # Send the packed data over the serial port
    ser.write(packed_data)

    # Optionally, you can also read the response from the device (if any)
    # response = ser.read(100)  # Example to read up to 100 bytes from the device
    # print("Received:", response)

    # Close the serial connection


ser.close()
print("Serial connection closed.")
