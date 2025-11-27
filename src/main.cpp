#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>

#define W5500_CS    14    // CS (Chip Select) PIN
#define W5500_RST   9     // Reset PIN (optional)
#define W5500_INT   10    // Interrupt PIN (optional)
#define W5500_MISO  12    // MISO PIN
#define W5500_MOSI  11    // MOSI PIN
#define W5500_SCK   13    // Serial Clock PIN

// Define MAC address
byte mac[] = { 0xDE, 0xAD, 0xAF, 0x91, 0x3E, 0xD7 };

// Static IP Configuration
IPAddress ip(192, 168, 1, 200);         // Static IP address
IPAddress dns(0, 0, 0, 0);              // DNS server
IPAddress gateway(192, 168, 1, 1);      // Gateway address
IPAddress subnet(255, 255, 255, 0);     // Subnet mask

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  while (!Serial) {}      // Waits until Serial Monitor is open

  delay(1000);
  Serial.println("Starting Ethernet Connection... ");

  // Initialize SPI with custom pin configuration
  SPI.begin(W5500_SCK, W5500_MISO, W5500_MOSI, W5500_CS);

  // Select CS PIN and initialize Ethernet with static IP settings (Selecting CS PIN required for ESP32 as the ardiuno default is different)
  Ethernet.init(W5500_CS);

  // Start the Ethernet Connection
  Ethernet.begin(mac, ip, dns, gateway, subnet);

  // Check if the Ethernet Hardware is detected
  Serial.println("Checking Ethernet hardware...");
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("ERROR: No Ethernet hardware detected!");
    return;
  } else {
    Serial.println("Ethernet hardware detected!");
  }

  // Check if the IP addressing is properly assigned
    if (Ethernet.localIP() == IPAddress(0, 0, 0, 0)) {
    Serial.println("Failed to configure Ethernet with static IP");
    while (true); // Halt on failure
  }

  // Check if the cable is connected to the ESP and link is validate.
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Link is OFF. Check cable connection.");
  } else {
    Serial.println("Link is ON. Check cable connection.");
    Serial.print("To test connection, Please ping: ");
    Serial.print(Ethernet.localIP());
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);

}