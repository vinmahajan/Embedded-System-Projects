# Paperless Billing System

## Overview
The Paperless Billing System is designed to streamline the billing process by leveraging modern technology to eliminate the need for paper receipts. The system utilizes a microcontroller, keypad, LCD display, and SIM800L module to fetch item data from the cloud, process user inputs, calculate total prices, generate digital bills, and send these bills via SMS to the customer's mobile number. Additionally, the system saves the bill information back to the cloud for record-keeping and further analysis.

## Features
- Fetch item data from the cloud
- User-friendly interface with keypad input and LCD display
- Real-time total price calculation
- Digital bill generation and SMS notification
- Bill data storage on the cloud

## Components
- **Microcontroller**: Arduino, ESP32, or similar
- **Keypad**: 4x4 matrix keypad
- **LCD Display**: 16x2 LCD or similar
- **SIM800L Module**: GSM module for SMS communication
- **Power Supply**: 5V DC power source

## Software Requirements
- Embedded C/C++ for microcontroller programming
- HTTP library for making GET requests
- GSM library for SMS communication
- Cloud server with API for data retrieval and storage

## Getting Started

### Hardware Setup
1. Connect the microcontroller to the keypad, LCD display, and SIM800L module.
2. Ensure the power supply is correctly connected to all components.

### Software Setup
1. Clone this repository:
   ```bash
   git clone https://github.com/vinmahajan/Embedded-System-Projects/tree/main/Paperless-Billing-System
   cd paperless-billing-system
   ```
2. Open the project in your preferred IDE (e.g., Arduino IDE for Arduino boards).
3. Upload the provided code to the microcontroller.
4. Ensure your cloud server is set up to handle HTTP GET and POST requests.

### Usage
1. **Initialization**: On startup, the microcontroller will fetch item data from the cloud.
2. **Input Item Codes**: The LCD display will prompt the user to input item codes using the keypad.
3. **Calculate Total**: The system will match input codes with the fetched data and calculate the total price.
4. **Generate Bill**: A digital bill will be generated, displayed on the LCD, and the total price will be shown.
5. **Send SMS**: The user will be prompted to enter the customer's mobile number. The bill will be sent via SMS.
6. **Save Bill**: The bill details will be saved to the cloud for future reference.

## Example Code

### Fetch Data from Cloud
```c
void fetchDataFromCloud() {
    // Initialize HTTP GET request to cloud server
    // Parse response and store item data locally
}
```

### Input Item Codes
```c
void inputItemCodes() {
    // Display prompt on LCD
    // Read input from keypad
    // Match input codes with stored item data
}
```

### Calculate Total Price
```c
float calculateTotalPrice() {
    float total = 0.0;
    // Loop through matched items and sum their prices
    return total;
}
```

### Generate and Display Bill
```c
void generateBill() {
    // Generate text bill with item details and total price
    // Display total price on LCD
}
```

### Send SMS
```c
void sendSMS(char* phoneNumber, char* message) {
    // Initialize SIM800L module
    // Send SMS with bill details to the provided phone number
    // Confirm SMS delivery
}
```

### Save Bill to Cloud
```c
void saveBillToCloud(char* billDetails) {
    // Initialize HTTP POST request to cloud server
    // Send bill details to server for storage
}
```

## Future Enhancements
- **QR Code Generation**: Generate a QR code for the bill for easy scanning and payment.
- **Voice Input**: Integrate voice recognition for inputting item codes and mobile numbers.
- **Mobile App Integration**: Develop a companion mobile app for customers to receive and manage their bills.
- **Real-Time Inventory Management**: Update inventory levels in real-time as items are billed.
- **Customer Loyalty Program**: Implement a loyalty program where customers earn points for each purchase.
- **Environmental Impact Analysis**: Display the environmental impact of going paperless, such as the number of trees saved.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contact
For any inquiries or issues, please contact Vinayak Mahajan at vinayakmahajan06@gmail.com.

---

Enjoy using the Paperless Billing System! Save trees, go digital!