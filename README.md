# Cliente HTTP em ESP32

Este código serve para enviar requisições HTTP GET (apenas rota + parâmetros) para uma API através de um ESP32 da Heltec: WIFI Lora (V2). 

## Dependências

### 1. São necessários os pacotes de gerenciamento de placas da Heltec! Adicione esses links (como estam) às preferências da ArduinoIDE, na parte de "Gerenciadores de placa Adicionais"

```
http://arduino.esp8266.com/stable/package_esp8266com_index.json,https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/releases/download/0.0.7/package_heltec_esp32_index.json
```
#### Exemplo:
![image](https://github.com/Twelve-Sports/esp32/assets/95541125/0aa35ff7-56c0-4f6e-baa9-d94d03fec34d)

### 2. Adicione o pacote da "Heltec" através do "Board Maganer".

### 3. Adicione o pacote da "Heltec" através da "Library Manager".

### 4. Adicione o pacote da "ArduinoHttpClient" através da "Library Manager".

### 5. Altere nomeDaRede, senhaDaRede, enderecoIP, porta e rotaDaAPI conforme necessário

#### Exemplo:
![image](https://github.com/Twelve-Sports/esp32/assets/95541125/8ba787ff-585a-45dc-8bba-2363c037c81f)

### 6. Compile e faça upload para o ESP32.

### 7. (TODO: Adicionar instrução de montagem do protótipo)
