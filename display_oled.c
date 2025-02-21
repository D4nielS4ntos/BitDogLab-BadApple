#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"
#include "inc/badapple.h"

#define BUTTON_A 11
#define BUTTON_B 6

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

int main() {
  stdio_init_all();   // Inicializa os tipos stdio padrão presentes ligados ao binário

  // Inicialização do i2c
  i2c_init(i2c1, ssd1306_i2c_clock * 1000);
  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA);
  gpio_pull_up(I2C_SCL);

  // Inicializa botão A
  gpio_init(BUTTON_A);             // Inicializa o pino do botão
  gpio_set_dir(BUTTON_A, GPIO_IN); // Configura o pino do botão como entrada
  gpio_pull_up(BUTTON_A);
  // Inicializa botão B
  gpio_init(BUTTON_B);             // Inicializa o pino do botão
  gpio_set_dir(BUTTON_B, GPIO_IN); // Configura o pino do botão como entrada
  gpio_pull_up(BUTTON_B);

  // Processo de inicialização completo do OLED SSD1306
  ssd1306_init();

  // Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
  struct render_area frame_area = {
      start_column : 0,
      end_column : ssd1306_width - 1,
      start_page : 0,
      end_page : ssd1306_n_pages - 1
  };

  // calculate_render_area_buffer_length(&frame_area);
  calculate_render_area_buffer_length(&frame_area);

  // zera o display inteiro
  uint8_t ssd[ssd1306_buffer_length];
  memset(ssd, 0, ssd1306_buffer_length);
  render_on_display(ssd, &frame_area);

  int animacao = 0;
  while (true)
  {
    int primeiro_loop = 1;
    if (animacao == 0)
    {
      //primeiro_loop == 0;
      char *text[] = {
        "  Pressione A   ",
        "  Para iniciar   ",
        " E B para parar "};
  
      // Parte do código para exibir a mensagem no display (opcional: mudar ssd1306_height para 32 em ssd1306_i2c.h)
      // /**
      int y = 0;
      for (uint i = 0; i < count_of(text); i++)
      {
          ssd1306_draw_string(ssd, 5, y, text[i]);
          y += 8;
      }
      render_on_display(ssd, &frame_area);
    }
    // inicia a animação e configura o display para a animação
    ssd1306_t ssd_bm;
    if (!gpio_get(BUTTON_A))
    {
      animacao = 1;
      ssd1306_init_bm(&ssd_bm, 128, 64, false, 0x3C, i2c1);
      ssd1306_config(&ssd_bm);
    }
      
    while (animacao == 1) 
    {
      for (int i = 0; i < badapple_epd_bitmap_allArray_LEN; i++) 
      {
        if (!gpio_get(BUTTON_B))
        {
          animacao = 0;
          break;
        }
        ssd1306_draw_bitmap(&ssd_bm, badapple_epd_bitmap_allArray[i]);
        sleep_ms(100);
      }
    }
  sleep_ms(1000);
  }
  return 0;
}