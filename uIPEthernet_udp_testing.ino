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
boolean streaming = false;

void setup() {
  int success;
  do{
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
    success = Udp.begin(localPort); //Initialize Udp
    Serial.print("\ninitialize: ");
    Serial.println(success ? "success" : "failed");
    delay(1500); //delay
  } while (!success);
}

void loop() {
  packetSize = Udp.parsePacket(); //Read the packetSize
  if (packetSize>0){
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE); //Reading the data request on the Udp
    String datReq(packetBuffer); //Convert packetBuffer array to string datReq
    //Serial.println("Received packet");
    //Serial.println(datReq);
    if(datReq=="start"){
      Serial.println("beginning stream");
      streaming = true;
    }
    if(datReq=="stop"){
      Serial.println("halting stream");
      streaming = false;
      Serial.println("waiting for start command");
      Udp.stop();
      Udp.begin(localPort);
    }
    memset(packetBuffer, 0, UDP_TX_PACKET_MAX_SIZE);
    //Udp.flush(); // doesnt clean buffer?
  }
  if(streaming){
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());  //Initialize Packet send
    Udp.print(micros()); //Send string back to client 
    Udp.endPacket(); //Packet has been sent
//    delay(2000);
  }
}
