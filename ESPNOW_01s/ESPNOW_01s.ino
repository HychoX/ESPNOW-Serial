#include <WifiEspNow.h>
#include <ESP8266WiFi.h>

//先烧录程序，通过串口打印的本机MAC地址，可以记下来，同理，记下两个设备的MAC地址
//A 设备使用 B 设备的MAC，同理， B 设备使用 A 设备的MAC地址。
// 接收设备的MAC地址。必须针对每个设备对其进行修改。
//static uint8_t PEER[] {0x5A, 0xBF, 0x25, 0xD0, 0xAF, 0x52}; //A的地址
static uint8_t PEER[] {0xEA, 0x9F, 0x6D, 0x83, 0xD4, 0x91}; //B的地址
const uint8_t channel = 14;//用14通道，除了日本，没有wifi会用这个通道，不过蓝牙有可能会用

void setup()
{
  Serial.begin(115200);
  SetAP();          //运行在AP模式，设置一些参数，并打印输出本机MAX地址
  Init_ESP_NOW();   //初始化配置ESPNOW
}

void loop()
{
  if (Serial.available() > 0)//判读是否串口有数据
  {
    String comdata = "";//缓存清零
    while (Serial.available() > 0)//循环串口是否有数据
    {
      comdata += char(Serial.read());//叠加数据到comdata
      delay(2);//延时等待串口传输
    }
    if (comdata.length() > 0)//如果comdata有数据
    {
      Send_data(comdata);
    }
  }
}

//配置AP
void SetAP()
{
  WiFi.persistent(false);;//不保存任何wifi配置到flash
  WiFi.mode(WIFI_AP);
  WiFi.disconnect();
  WiFi.softAP("ESPNOW", nullptr, channel);//信道填14也可以
  WiFi.softAPdisconnect(false);
  // 必须打开WiFi才能使用ESP-NOW单播。
  // 它可以是AP或STA模式，并且不必连接。
  // 为获得最佳效果，请确保两台设备使用相同的WiFi通道。
  /*Serial.print("此节点的MAC地址为 ");
  Serial.println(WiFi.softAPmacAddress());
  uint8_t mac[6];
  WiFi.softAPmacAddress(mac);
  Serial.println();//输出本机Mac，调试用
  Serial.println("您可以将以下内容粘贴到其他设备的程序中：");
  Serial.printf("static uint8_t PEER[]{0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X};\n", mac[0],
                mac[1], mac[2], mac[3], mac[4], mac[5]);
  Serial.println();*/
}

//初始化ESPNOW
void Init_ESP_NOW()
{
  bool ok = WifiEspNow.begin();
  if (!ok) {//初始化失败，重启ESPNOW服务
    ESP.restart();
  }
  WifiEspNow.onReceive(printReceivedMessage, nullptr);
  ok = WifiEspNow.addPeer(PEER, channel, NULL);
  if (!ok) {//初始化失败，重启ESPNOW服务
    ESP.restart();
  }
}

//ESPNOW发送函数
void Send_data(String str)
{
  //字符长度最大250，如果需要，可以把60改成更大的
  char data[60];
  int len = str.length();
  if (len >= sizeof(data)) {
    return;
  }
  str.toCharArray(data, sizeof(data));//调用C++内部方法
  bool f = WifiEspNow.send(PEER, reinterpret_cast<const uint8_t*>(data), len);
  //if (f){}//可以在这里加入发送失败的动作，用来在持续失败时提示
}

//ESP NOW数据接收回调函数
void printReceivedMessage(const uint8_t mac[WIFIESPNOW_ALEN], const uint8_t* buf, size_t count,
                          void* arg)
{
  String data = "";
  for (int i = 0; i < static_cast<int>(count); ++i) {
    data += char(buf[i]);
  }
  Handler(data);
}

//数据接收判断处理函数
void Handler(String read_data)
{
  if (read_data != "")
  {
    Serial.print(read_data);
  }
}
