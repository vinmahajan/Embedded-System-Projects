// GSM Module: SIM800l  

const String APN = "airtelgprs.com";
const String USER = "";
const String PASS = "";
#define USE_SSL true

int main()
{
  Serial.begin(115200); // default configuration settings for serial port
  GSM.begin(9600);      // Serial UART communication for GSM

  while (1)
  {
    String URL = "https://www.example_site.com/";
    String Data = "{\"Data1\":22,\"Data2\":52}";
    Make_HTTP_Request(1, URL, Data);  //0: http GET request 1: http POST request
    delay(10000);
  }
}

String Make_HTTP_Request(int method, String URL, String data)
{
  while (!checkNetworkStatus())
  { // check if gsm connected to network
    Serial.println("SIM800L is not connected to the network.");
    delay(2000);
  }
  Send_AT_Command("AT+CGATT=0"); // Disconnect GPRS
  Send_AT_Command("AT+CFUN=1"); // Turning ON full functionality
  Send_AT_Command("AT+CMEE=2"); // Turn ON verbose error codes
  // SIM800.println("AT+CBATCHK=1");  //Enable battery checks
  // Send_AT_Command("AT+CREG?");  //Register Network (+CREG: 0,1 or +CREG: 0,5 for valid network)
  // SIM800.print("AT+CMGF=1\r");  //setting SMS text mode
  Send_AT_Command("AT+SAPBR=3,1,\"Contype\",\"GPRS\""); // Connecting to GPRS: GPRS - bearer profile 1
  Send_AT_Command("AT+SAPBR=3,1,\"APN\"," + APN); // sets the APN settings for your sim card network provider.
  if (USER != ""){
    Send_AT_Command("AT+SAPBR=3,1,\"USER\"," + USER); // sets the user name settings for your sim card network provider.
  }
  if (PASS != ""){
    Send_AT_Command("AT+SAPBR=3,1,\"PASS\"," + PASS); // sets the password settings for your sim card network provider.
  }
  Send_AT_Command("AT+SAPBR=1,1"); // enable the GPRS: enable bearer 1
  // delay(10000);
  Send_AT_Command("AT+SAPBR=2,1"); // Get IP Address - Query the GPRS bearer context status
  Send_AT_Command("AT+HTTPINIT"); // Start HTTP connection
  if (USE_SSL == true){
    Send_AT_Command("AT+HTTPSSL=1"); // Enabling SSL 1.0
  }
  Send_AT_Command("AT+HTTPPARA=\"CID\",1"); // Setting up parameters for HTTP session
  Send_AT_Command("AT+HTTPPARA=\"URL\",\"" + URL + "\""); // Set the HTTP URL
  Send_AT_Command("AT+HTTPPARA=\"REDIR\",1"); // Setting up re direct
  Send_AT_Command("AT+HTTPPARA=\"CONTENT\",\"application/json\""); // Setting up content type
  if (method == 1)
  {
    Send_AT_Command("AT+HTTPDATA=" + String(data.length()) + ",10000"); // Setting up Data Size  //+HTTPACTION: 1,601,0 - error occurs if data length is not correct
    Send_AT_Command(data); // Sending Data
    Send_AT_Command("AT+HTTPACTION=1"); // Sending HTTP POST request
  }
  else if (method == 0)
  {
    Send_AT_Command("AT+HTTPACTION=0"); // Sending HTTP GET request
  }
  delay(5000);
  String Response = Send_AT_Command("AT+HTTPREAD"); // Read the response
  Serial.println(Response);
  Send_AT_Command("AT+HTTPTERM"); // Stop HTTP connection
  Send_AT_Command("AT+CGATT=0"); // Disconnect GPRS
  return Response;
}

String Send_AT_Command(String command)
{
  String AT_Response = ""; // String response;

  // Serial.println(command);
  GSM.println(command);

  unsigned long previous = millis();
  while (GSM.available() || (millis() - previous) < 2000)
  {
    if (GSM.available() != 0)
    {
      char c = GSM.read();
      AT_Response.concat(c);
    }
  }

  return AT_Response;
}

bool checkNetworkStatus()
{
  GSM.println("AT+CREG?");
  delay(1000);

  while (GSM.available())
  {
    String response = GSM.readStringUntil('\n');
    if (response.indexOf("+CREG: 0,1") != -1 || response.indexOf("+CREG: 0,5") != -1)
    {
      // Registered on the network in home or roaming
      return true;
    }
    else if (response.indexOf("+CREG: 0,2") != -1 || response.indexOf("+CREG: 0,6") != -1)
    {
      // Trying to register
      return false;
    }
  }
  return false;
}
