# ESP01S WiFi Communication with ESP-NOW 📶

[中文文档](https://github.com/HychoX/ESPNOW-Serial/blob/main/README_zh.md)

This project demonstrates how to use the **ESP01S** module with **ESP-NOW** for wireless communication between two devices. It's a simple yet powerful way to send and receive data without the overhead of a full Wi-Fi connection.

---

## 🌟 Features

- **Wireless Communication**: Utilizes ESP-NOW protocol for fast and efficient data transfer.
- **Serial Interface**: Send data via the serial monitor and it will be transmitted wirelessly.
- **Auto MAC Address Detection**: Automatically prints the MAC address of the device for easy peer configuration.
- **Channel 14**: Uses channel 14, which is less crowded (except in Japan).

---

## 🛠️ Hardware Requirements

- **ESP01S Module** × 2
- **USB to Serial Converter** (for programming and serial communication)
- **Breadboard & Jumper Wires** (optional, for prototyping)

---

## 🚀 Getting Started

### 1. Install Dependencies

Make sure you have the following libraries installed in your Arduino IDE:

- [WiFiEspNow](https://github.com/raphaelbs/esp-now-wifi-esp8266)
- [ESP8266WiFi](https://github.com/esp8266/Arduino)

You can install them via the Arduino Library Manager.

### 2. Configure MAC Addresses

Each device needs to know the MAC address of the other device to communicate. Follow these steps:

1. **Upload the code** to both devices.
2. Open the **Serial Monitor** (`Ctrl+Shift+M`) at `115200` baud rate.
3. Note down the MAC address printed on each device.
4. Update the `PEER[]` array in the code with the MAC address of the other device.

```cpp
// Example: Replace this with the MAC address of the other device
static uint8_t PEER[] {0xEA, 0x9F, 0x6D, 0x83, 0xD4, 0x91};
```

### 3. Upload the Code

- Upload the code to both ESP01S modules.
- Ensure both devices are using the same **WiFi channel** (default is `14`).

### 4. Test Communication

- Open the **Serial Monitor** for both devices.
- Type a message in the Serial Monitor of one device and press `Enter`.
- The message should appear on the other device's Serial Monitor.

---

## 📝 Code Explanation

### Key Functions

- **`SetAP()`**: Configures the ESP01S in AP mode and sets up the WiFi channel.
- **`Init_ESP_NOW()`**: Initializes the ESP-NOW protocol and adds the peer device.
- **`Send_data(String str)`**: Sends data to the peer device via ESP-NOW.
- **`printReceivedMessage()`**: Callback function that handles incoming data.
- **`Handler(String read_data)`**: Processes the received data and prints it to the Serial Monitor.

---

## 🔧 Configuration

### Changing the WiFi Channel

If you want to use a different WiFi channel, modify the `channel` variable:

```cpp
const uint8_t channel = 14; // Change to your desired channel
```

### Adjusting Data Length

The maximum data length is set to `60` characters. You can increase this by modifying the `data` array size in the `Send_data()` function:

```cpp
char data[60]; // Increase this value if needed
```

---

## 📚 Example Usage

1. **Device A** sends a message:
   ```
   Hello from Device A!
   ```

2. **Device B** receives the message:
   ```
   Hello from Device A!
   ```

---

## 📋 Notes

- **Channel 14**: This channel is not commonly used outside Japan, so it's ideal for avoiding interference. However, Bluetooth devices may still use this channel.
- **MAC Address**: Each ESP01S has a unique MAC address. Make sure to update the `PEER[]` array with the correct MAC address of the other device.
- **Error Handling**: If ESP-NOW fails to initialize, the device will restart automatically.

---

## 🤝 Contributing

Feel free to fork this repository and submit pull requests! Any contributions or improvements are welcome. 😊

---

## 📜 License

This project is licensed under the **GPL License**. See the [LICENSE](LICENSE) file for more details.

---

## 🙏 Acknowledgments

- Thanks to the creators of the [WiFiEspNow](https://github.com/raphaelbs/esp-now-wifi-esp8266) library for making ESP-NOW easy to use with ESP8266.
