#include <heltec.h>
#include <WiFi.h>
#include <ArduinoHttpClient.h>

// Configuração de rede e API
const char nomeDaRede[] = "thorg100";
const char senhaDaRede[] = "thor1234";
const char enderecoIP[] = "192.168.182.49";
const int porta = 3002;
const char rotaDaAPI[] = "/dateNow/";

// Configuarção dos Pinos dos Botões
const int botao1 = 13;
const int botao2 = 12;

// Instanciando wifi e cliente http
WiFiClient wifi;
HttpClient client = HttpClient(wifi, enderecoIP, porta);

// Controle de estado dos botões
bool ultimoEstadoBotao1 = false;
bool ultimoEstadoBotao2 = false;

void setup() {
  Serial.begin(115200);           // Inicializa Serial
  inicializarDisplay()
  pinMode(botao1, INPUT_PULLUP);  // Inicializa botão 1 no modo INPUT_PULLUP
  pinMode(botao2, INPUT_PULLUP);  // Inicializa botão 2 no modo INPUT_PULLUP
  conectarAoWifi();
}

void loop() {
  checarConexaoWIFI();
  checarBotoes();
  mostrarEmTela("Pressione um botão!");

  ultimoEstadoBotao1 = digitalRead(botao1); // Atualiaza estado do botão 1
  ultimoEstadoBotao2 = digitalRead(botao2); // Atualiaza estado do botão 2
  delay(100);
}

void inicializarDisplay() {
  Heltec.begin(true, false, true);
  Heltec.display->clear();
}

void conectarAoWifi() {
  WiFi.disconnect(true);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.setAutoConnect(true);
  WiFi.begin(nomeDaRede, senhaDaRede);

  byte count = 0;
  while (WiFi.status() != WL_CONNECTED && count < 10) {
    count++;
    delay(500);
    mostrarEmTela("Conectando...");
  }

  mostrarEstadoDaConexao();
}

void mostrarEstadoDaConexao() {
  Heltec.display->clear();
  if (WiFi.status() == WL_CONNECTED) {
    mostrarEmTela("Conectedo");
    delay(500);
  } else {
    Heltec.display->clear();
    mostrarEmTela("Falha ao conectar");
  }
  mostrarEmTela("WiFi pronto!");
  delay(500);
}

void mostrarEmTela(const char* mensagem) {
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, mensagem);
  Heltec.display->display();
}

void checarConexaoWIFI() {
  if (WiFi.status() != WL_CONNECTED) {
    mostrarEmTela("Sem conexão.");
    delay(500);
    conectarAoWifi();
  }
}

void checarBotoes() {
  bool atualEstadoBotao1 = digitalRead(botao1);
  bool atualEstadoBotao2 = digitalRead(botao2);

  checarEstadoDoBotao(atualEstadoBotao1, ultimoEstadoBotao1, "1");
  checarEstadoDoBotao(atualEstadoBotao2, ultimoEstadoBotao2, "2");
}

void checarEstadoDoBotao(bool atualEstado, bool &ultimoEstado, const char* parametro) {
  if (atualEstado != ultimoEstado) {
    if (atualEstado == LOW) {
      enviarGETpara((String(rotaDaAPI) + parametro).c_str());
      delay(1000);
    } else {
      delay(50);
    }
  }
}

void enviarGETpara(const char* rota) {
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "Enviando para:");
  Heltec.display->drawString(0, 10, rota);
  Heltec.display->display();
  
  client.get(rota);

  int statusCode = client.responseStatusCode();
  String resposta = client.responseBody();

  Heltec.display->drawString(0, 30, resposta);
  Heltec.display->display();

  client.flush();
}