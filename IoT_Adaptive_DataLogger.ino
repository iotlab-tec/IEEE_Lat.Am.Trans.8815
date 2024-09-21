#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SD.h>
#define CS_PIN 15
const char* ssid = "..."; const char* password = "...";
  String htmlPage;  String TempData;  String HumyData;
  String TimeData;  String RTime2;  String TempArray[100];
  String HumArray[100];  String TimeArray[100];
  int TempMax;  int TempMin=100;  float TempInt;
  float TempInt2;  float e;  int HumMax;  int HumMin=100;
  int HumInt;  int TimeWait=100;  int C=0;  int Count=0;
IPAddress staticIP(192, 168, 0, 94); 
IPAddress gateway(192, 168, 0, 1);   
IPAddress subnet(255, 255, 255, 0);  
IPAddress dns(8, 8, 8, 8); 
const char* deviceName = "Server_Device";
ESP8266WebServer server(80);
void handleURL(){
  Serial.println();  String RID;  String RTemp;  String RHum;
  String RLat;  String RLon;  String RDay;  String RMonth;
  String RYear;  String RTime;
  if (server.hasArg("Time")){
    RID =server.arg("ID");
    RTemp =server.arg("Temp");
    RHum =server.arg("Hum");
    RLat =server.arg("Lat");
    RLon =server.arg("Lon");
    RDay =server.arg("Day");
    RMonth =server.arg("Month");
    RYear =server.arg("Year");
    RTime =server.arg("Time");
    server.send(200, "text/html", "Data received");
  TempInt=RTemp.toFloat();
  if(RTime==RTime2){
  }else{
  if(C==0){ TempInt2=TempInt; C=C+1; }
  if(Count==TimeWait){
  Count=0; digitalWrite(2,LOW);
  File dataFile = SD.open("Data.csv", FILE_WRITE);
  if (dataFile) {
  dataFile.print(RID+",");
  dataFile.print(RDay+"/"+RMonth+"/"+RYear+",");
  dataFile.print(RTime+",");
  dataFile.print(RTemp+",");
  dataFile.print(RHum+",");
  dataFile.print(RLat+",");
  dataFile.println(RLon);
  dataFile.close();
  }
  e=fabs(TempInt2-TempInt);if(e<0.1){  if(!(TimeWait==1600)){ TimeWait=TimeWait*2; }
  } if(e>0.1){if(!(TimeWait==100)){TimeWait=TimeWait/2;}
  } TempInt2=TempInt; }
  delay(1000);digitalWrite(2,HIGH);
  }}
  RTime2=RTime;
  HumInt=RHum.toFloat();
    for(int y=0;y<99;y++){
      TempArray[y]=TempArray[y+1];
      HumArray[y]=HumArray[y+1];
      TimeArray[y]=TimeArray[y+1];
      TempData=TempData+TempArray[y]+",";
      HumyData=HumyData+HumArray[y]+",";
      TimeData=TimeData+TimeArray[y]+",";
      if(TempInt>TempMax){TempMax=TempInt+5;}
      if(TempInt<TempMin){TempMin=TempInt-5;}
      if(HumInt>HumMax){HumMax=HumInt+5;}
      if(HumInt<HumMin){HumMin=HumInt-5;}
    }
    TempArray[99]=RTemp;
    HumArray[99]=RHum;
    TimeArray[99]="'"+RTime+"'";
    TempData=TempData+TempArray[99];
    HumyData=HumyData+HumArray[99];
    TimeData=TimeData+TimeArray[99];
htmlPage = 
"<!DOCTYPE html>"
"<html>"
"<head>"
"<meta charset=\"UTF-8\">"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
"<meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">"
"<script src=\"https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.6.0/Chart.min.js\"></script>"
"<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\">"
"<title>Theses HMI</title>"
"</head>"
"<meta name='viewport' content='width=device-width, initial-scale=1.0'/>"
"<meta charset='utf-8'>"
"<meta http-equiv='refresh' content='30'>"                                      //Refresh time
"<body style=\"background-color: #fff;  font: normal 16px Arial, Helvetica, "
"sans-serif; line-height: 1.6em; margin: 0;\">"
"<header>"
"<div style=\"background-color: #fff; color: #185fe0ff; padding: 30px; "
"position: relative; height: 120px;\">"
"<h1 style=\"text-align: center; \">Design and validation of a platform system for remote" 
"real time monitoring of environmental variables</h1>"
"<img src=\"https://oi1126.photobucket.com/albums/l616/clon_yael/TEC_3_zpsmso6wulf.png\"" 
"style=\"position: absolute; right: 2%; top: 10%;\">"
"</div></header>"
"<nav style=\" background-color:#185fe0ff ;  color:#fff;\">"
"    <div style=\"display:flex; width:80%; margin:auto; overflow:hidden;\">"
"      <ul style=\"flex:3; padding:0; list-style: none;\">"
"        <li style=\"display:inline;\"><a href=\"#\" style=\"color:#fff;" 
"        text-decoration: none; font-size:18px; padding-right:15px;\">Home</a></li>"
"        <li style=\"display:inline;\"><a href=\"#\" style=\"color:#fff; "
"        text-decoration: none; font-size:18px; padding-right:15px;\">About</a></li>"
"        <li style=\"display:inline;\"><a href=\"#\" style=\"color:#fff; "
"        text-decoration: none; font-size:18px; padding-right:15px;\">Services</a></li>"
"        <li style=\"display:inline;\"><a href=\"#\" style=\"color:#fff; "
"        text-decoration: none; font-size:18px; padding-right:15px;\">Contact</a></li>"
"      </ul>"
"      <h3 style=\"flex:2; margin-bottom: 20px;\">Date: "+RDay+"/"+RMonth+"/"+RYear+"</h3>" //Date Data
"      <h3 style=\"flex:2; margin-bottom: 20px;\">Time: "+RTime+"</h3>"                     //Time Data
"    </div>"
"  </nav>"
"<section style=\"  background-color: #DBE2F1;"
"background-position:center;  min-height:200px;  margin-bottom:30px;  text-align: center; "
"background-repeat: no-repeat; \">"
"<div style=\"width: 80%; margin: auto;\">"
"<p style=\"color:#1f83c9ff;  font-size:30px;  line-height: 1.6em;  padding-top:30px;\">This page "
"presents the real time reading of temperature and humidity, and the position were the reading"
"are being made is shown in a Google Maps. The historic of the measurements is shown at the bottom"
"of the page. The page is reloaded every # seconds.</p>"
"</div></section>"
"<div style=\"width: 80%; margin: auto\">"
"  <div style=\"display:flex\">"
"    <div style=\"padding:10px; flex:1;\">"
"      <h2 style=\"color: #185fe0ff; text-align: center;\">Environmental Variables</h2>"
"      <h3 style=\"margin-bottom: 20px;\">Temperature: "+RTemp+"C</h3>"        //Temperature Data
"      <h3 style=\"margin-bottom: 20px;\">Humidity: "+RHum+"%</h3>"             //Humidity Data
"    </div>"
"    <div style=\"padding:10px; flex:1\">"
"      <h2 style=\"color: #185fe0ff; text-align: center;\">Geographical Coordinates</h2>"
"      <h3 style=\"margin-bottom: 20px;\">Latitude: "+RLat+"</h3>"           //Latitude Data
"      <h3 style=\"margin-bottom: 20px;\">Longitude: "+RLon+"</h3>"          //Longitude Data
"    </div>"
"    <div id=\"map\" style=\"flex:3; width: 400px; height: 300px; border: 5px #1f83c9ff solid\"></div>"
"  </div>"
"</div>"
"    <script type=\"text/javascript\">"
"    function initMap() {"
"      var location = {lat:"+RLat+", lng:"+RLon+"};" 
"      var map = new google.maps.Map(document.getElementById(\"map\"),"
"        {zoom:12,center:location});"
"      var marker = new google.maps.Marker({position:location,map:map});}"
"    </script>"
"    <script async defer src=\"https://maps.googleapis.com/maps/api/js?key="
"    AIzaSyAKFtUbpmzsNCV1rRKTkdGXfnRISkPzOjg&callback=initMap\"></script>"
"<div style=\"display:flex; margin-top: 20px;border: 5px #1f83c9ff solid\">"
"  <div style=\"padding:10px; flex:1; \">"
"    <canvas id=\"TempChart\" height=\"100\"></canvas>"
"  </div>"
"  <div style=\"padding:10px; flex:1;\">"
"    <canvas id=\"HumChart\" height=\"100\"></canvas>"
"  </div>"
" </div>"
"  <script>"
"    let TempChart = document.getElementById('TempChart').getContext('2d');"
"    let ThesesChartTemp = new Chart(TempChart, {type:'line',"
"      data:{labels:["+TimeData+"],"                                       //Time labels                         
"      datasets:[{label:'C'," 
"        data:["+TempData+"],"                                            //Temperature historic data
"        borderWidth:1,"
"        borderColor:'red',"
"        }]},"
"      options:{"
"        title:{display:true,text:'Temperature Over Time', fontSize:25},"
"        legend:{display:true,position:'right',labels:{fontColor:'#000'}},"
"        layout:{padding:{left:50,right:0,bottom:0,top:0}},"
"        tooltips:{enabled:true},"
"        scales:{yAxes:[{ticks:{suggestedMin: "+String(TempMin)+", suggestedMax: "+String(TempMax)+"}}]}"   //Y Axis
"        }"
"    });"
"  </script>"
"  <script>"
"    let HumChart = document.getElementById('HumChart').getContext('2d');"
"    let ThesesChartHum = new Chart(HumChart, {type:'line',"
"      data:{labels:["+TimeData+"],"                                       //Time labels
"      datasets:[{label:'RH%',"
"        data:["+HumyData+"],"                                             //Humidity historic data
"        borderWidth:1,"
"        borderColor:'blue',"
"        }]},"
"      options:{"
"        title:{display:true,text:'Relative Humidity Over Time', fontSize:25},"
"        legend:{display:true,position:'right',labels:{fontColor:'#000'}},"
"        layout:{padding:{left:50,right:0,bottom:0,top:0}},"
"        tooltips:{enabled:true},"
"        scales:{yAxes:[{ticks:{suggestedMin: "+String(HumMin)+", suggestedMax: "+String(HumMax)+"}}]}"   //Y Axis
"        }"
"    });"
"  </script>"
"  <footer style=\"background: #185fe0ff; color:#fff; text-align: center; padding:20px; margin-top: 50px\">"
"    <p>Copyright &copy; 2019 Jose Yael Lopez Hernandez</p></footer>"
"</body>"
"</html>";

TempData=" ";
HumyData=" ";
TimeData=" ";
TempMax=0;
TempMin=100;
HumMax=0;
HumMin=100;
Count=Count+100;
}
void setup() {
  Serial.begin(115200);
   pinMode(2, OUTPUT);
  WiFi.begin(ssid, password);
  WiFi.disconnect(); 
  WiFi.hostname(deviceName);
  WiFi.config(staticIP, gateway, subnet, dns);
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  server.on("/DATA/", HTTP_GET, handleURL);
  server.on("/", []() {server.send(200, "text/html", htmlPage);});
  server.begin();
 if (!SD.begin(CS_PIN)) {
  return;
  }}
void loop() {
  server.handleClient();
}