#include <Arduino.h>

#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Udp.h>
#include <SPI.h>

#include "mros_platformio.h"

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/int32.h>

EthernetUDP udp;

#define W5500_CS    14    // CS (Chip Select) PIN
#define W5500_RST   9     // Reset PIN (optional)
#define W5500_INT   10    // Interrupt PIN (optional)
#define W5500_MISO  12    // MISO PIN
#define W5500_MOSI  11    // MOSI PIN
#define W5500_SCK   13    // Serial Clock PIN

// Define MAC address
byte mac[] = { 0xDE, 0xAD, 0xAF, 0x91, 0x3E, 0xD7 };    // Mac address of ESP32
IPAddress client_ip(192, 168, 1, 200);                  // IP address of ESP32
IPAddress agent_ip(192, 168, 1, 10);                    // IP address of Micro ROS agent        
size_t agent_port = 8888;                               // Agent Port Number


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  delay(1000);
  Serial.println("Starting Ethernet Connection... ");

  // Initialize SPI with custom pin configuration
  SPI.begin(W5500_SCK, W5500_MISO, W5500_MOSI, W5500_CS);

  // Select CS PIN and initialize Ethernet with static IP settings (Selecting CS PIN required for ESP32 as the ardiuno default is different)
  Ethernet.init(W5500_CS);

  set_microros_eth_transports(mac, client_ip, agent_ip, agent_port);

}

void loop() {


}
