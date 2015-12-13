#include <UIPEthernet.h>
// The connection_data struct needs to be defined in an external file.
#include <UIPServer.h>
#include <UIPClient.h>

#define UDP_TX_PACKET_MAX_SIZE 24 // from normal arduino ethernetudp.h

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE}; //Assign a mac address
IPAddress ip(169,254,5,12); //Assign my IP adress
unsigned int localPort = 5000; //Assign a Port to talk over
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
String datReq; //String for our data
int packetSize; //Size of Packet
EthernetUDP Udp; //Define UDP Object

void setup() {
  
Serial.begin(9600); //Turn on Serial Port
  Ethernet.begin(mac, ip); //Initialize Ethernet
//  if (Ethernet.begin(mac) == 0) {
//    Serial.println("Failed to configure Ethernet using DHCP");
//    // no point in carrying on, so do nothing forevermore:
//    for(;;)
//      ;
//  }
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print("."); 
  }
  int success = Udp.begin(localPort); //Initialize Udp
  Serial.print("\ninitialize: ");
  Serial.println(success ? "success" : "failed");
  delay(1500); //delay
}

void loop() {
  
  packetSize = Udp.parsePacket(); //Read the packetSize
  
  if(packetSize>0){ //Check to see if a request is present
  
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE); //Reading the data request on the Udp
    String datReq(packetBuffer); //Convert packetBuffer array to string datReq
  
    if (datReq =="Red") { //See if Red was requested
  
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());  //Initialize Packet send
      Udp.print("You are Asking for Red"); //Send string back to client 
      Udp.endPacket(); //Packet has been sent
    }
    if (datReq =="Green") { //See if Green was requested
  
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());  //Initialize Packet send
      Udp.print("You are Asking for Green"); //Send string back to client 
      Udp.endPacket(); //Packet has been sent
    }
    if (datReq =="Blue") { //See if Red was requested
  
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());  //Initialize Packet send
      Udp.print("You are Asking for Blue"); //Send string back to client 
      Udp.endPacket(); //Packet has been sent
    }
  }
  memset(packetBuffer, 0, UDP_TX_PACKET_MAX_SIZE);
}
