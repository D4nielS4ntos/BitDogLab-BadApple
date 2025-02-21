# Tutorial: Girf na placa BitDogLab  
### (pi pico w (SDK, ssd1306 e i2c))  

![](images/girf_Embarcatech.gif)  

## 1º Etapa: Escolher um Girf de sua preferencia!  
no meu caso eu acabei escolhendo esse abaixo:

![](images/gawn_gura.gif)  

#### proporção: 128x64  
> Obs: não necessariamente o girf precisa ser esse tamanho, pode ser usado o site https://ezgif.com/resize ou https://ezgif.com/crop para ajustar o tamanho para 128x64 que é o tamanho do nosso display Oled.  

## 2º Etapa: Realizar o Split do seu girf, assim gerando os frames que ele possui.  

#### basta colocar seu girf https://ezgif.com/split é baixar o zip.  
![](images/girf_split.png)  

## 3º Etapa: convertendo os frames em Bitmap.  

#### selecione todos os frames para o site https://javl.github.io/image2cpp/  
![](images/img_to_cpp_SelectImages.png)  

#### Aplique as configurações conforme abaixo:  
![](images/img_to_cpp_ImageSettings.png)  

> OBS: Voce precisa Ajustar o **Brightness / alpha threshold** para melhorar a visualização da imagem, normalmente entre 190~230 é um bom valor, verifique o preview das imagens.  

#### Por fim, deixe conforme abaixo e clique em **Generate Code**.  
![](images/img_to_cpp_ImageOutput.png)  

## 4º crie um arquivo .h no meu exemplo: gawngura.h  

#### Após colar o codigo copiado, precisamos fazer 2 substituições, pois o codigo está para arduino.  
**atalho:  Ctrl + H**  

> **Substituir Tudo : Ctrl + Alt + Enter**  

> substituição 01 ->  "unsigned char" para "uint8_t", sem as aspas, conforme a imagem abaixo.  
![](images/replace_01.png)  

> substituição 02 -> " [] PROGMEM" para "[]", sem as aspas, conforme a imagem abaixo.  
![](images/replace_02.png)  

> copie o nome do seu array que voce gerou, no meu caso "**gawn_gura_girfallArray**"  
![](images/gawngura.h_array.png)  
atenção que seu codigo deve se parecer com esse aqui.  

#### faça o import do codigo, no meu caso:  
```  
#include "inc/gawngura.h"  
```  
![](images/import_incGawnGura.png)  

> substituir os nomes conforme abaixo:  
**gawn_gura_girfallArray** e **gawn_gura_girfallArray_LEN**  
![](images/main_code_array.png)  

## 5º Compilar, colocar a placa em modo boot cell, enviar o codigo para a placa.  

### resultado:  
![](images/girf_Embarcatech.gif)  

## 6º Considerações finais.  

Houve mudança de uma linha na biblioteca ssd1306 no metodo **ssd1306_draw_bitmap()**:  

arquivo: ssd1306_i2c.c  

de:  
```c  
void ssd1306_draw_bitmap(ssd1306_t *ssd, const uint8_t *bitmap) {
    for (int i = 0; i < ssd->bufsize - 1; i++) {
        ssd->ram_buffer[i + 1] = bitmap[i];
        ssd1306_send_data(ssd);
    }
}  
```  
para:  
```c  
void ssd1306_draw_bitmap(ssd1306_t *ssd, const uint8_t *bitmap) {
    for (int i = 0; i < ssd->bufsize - 1; i++) {
        ssd->ram_buffer[i + 1] = bitmap[i];
    }
    ssd1306_send_data(ssd);
}  
```  

essa mudança permite que os frames sejam carregados e enviados de uma sõ vez, caso o contrario os frames seriam carregados uma vez a cada loop isso cancelaria o efeito da animação pois a imagem seria gerada horizontalmente apenas após alguns segundos.  

## Creditos a [![YouTube Channel Subscribers](https://img.shields.io/badge/YouTube-FF0000?style=for-the-badge&logo=youtube&logoColor=white)](https://www.youtube.com/@profjivago9719)  **Profº Jivago** , pela [aula](https://www.youtube.com/watch?v=MLoararsJzA) que permitiu fazer o girf.

