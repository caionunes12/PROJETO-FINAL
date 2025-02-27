#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/font.h"

// Definições dos pinos e do endereço do display OLED
#define PORTA_I2C i2c1
#define PINO_SDA 14
#define PINO_SCL 15
#define ENDERECO 0x3C

// Definições dos botões e LEDs
#define BOTAO_JOYSTICK 22
#define BOTAO_INCREMENTO 5
#define BOTAO_LIGAR 6
#define LED_VERMELHO 13
#define LED_VERDE 11
#define SENHA "1234"

// Variáveis de estado do sistema
bool sistema_ativo = false;
bool acesso_liberado = false;

// Função para desenhar a tela de senha no display
void desenhar_tela_senha(ssd1306_t *ssd, char *entrada, int indice, int digito_atual) {
    ssd1306_fill(ssd, false);
    if (!sistema_ativo) {
        ssd1306_draw_string(ssd, "DESLIGADO", 15, 10);
    } else if (acesso_liberado) {
        ssd1306_draw_string(ssd, "ACESSO LIBERADO", 5, 10);
    } else {
        ssd1306_draw_string(ssd, "DIGITE A SENHA:", 10, 10);
        char senha_exibida[6] = "****";
        for (int i = 0; i < indice; i++) {
            senha_exibida[i] = entrada[i];
        }
        ssd1306_draw_string(ssd, senha_exibida, 40, 30);
        char info_digito[10];
        sprintf(info_digito, "DIGITO: %d", digito_atual);
        ssd1306_draw_string(ssd, info_digito, 40, 50);
    }
    ssd1306_send_data(ssd);
}

// Função para verificar se a senha digitada está correta
void verificar_senha(ssd1306_t *ssd, char *entrada) {
    ssd1306_fill(ssd, false);
    if (strcmp(entrada, SENHA) == 0) {
        ssd1306_draw_string(ssd, "CORRETO!", 20, 30);
        gpio_put(LED_VERDE, 1);
        acesso_liberado = true;
    } else {
        ssd1306_draw_string(ssd, "INCORRETO!", 15, 30);
    }
    ssd1306_send_data(ssd);
    sleep_ms(2000);
}

int main() {
    // Inicialização dos periféricos
    stdio_init_all();
    i2c_init(PORTA_I2C, 400 * 1000);
    gpio_set_function(PINO_SDA, GPIO_FUNC_I2C);
    gpio_set_function(PINO_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(PINO_SDA);
    gpio_pull_up(PINO_SCL);
    
    // Configuração dos botões como entrada
    gpio_init(BOTAO_JOYSTICK);
    gpio_set_dir(BOTAO_JOYSTICK, GPIO_IN);
    gpio_pull_up(BOTAO_JOYSTICK);
    
    gpio_init(BOTAO_INCREMENTO);
    gpio_set_dir(BOTAO_INCREMENTO, GPIO_IN);
    gpio_pull_up(BOTAO_INCREMENTO);
    
    gpio_init(BOTAO_LIGAR);
    gpio_set_dir(BOTAO_LIGAR, GPIO_IN);
    gpio_pull_up(BOTAO_LIGAR);
    
    // Configuração dos LEDs como saída
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_put(LED_VERMELHO, 0);
    
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_put(LED_VERDE, 0);
    
    // Inicialização do display OLED
    ssd1306_t ssd;
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, ENDERECO, PORTA_I2C);
    ssd1306_config(&ssd);
    
    // Variáveis para controle da senha digitada
    char entrada[5] = "0000";
    int indice = 0;
    int digito_atual = 0;
    
    while (true) {
        // Lógica para ligar ou desligar o sistema
        if (gpio_get(BOTAO_LIGAR) == 0) {
            sistema_ativo = !sistema_ativo;
            if (!sistema_ativo) {
                acesso_liberado = false;
                gpio_put(LED_VERDE, 0);
            }
            gpio_put(LED_VERMELHO, sistema_ativo);
            sleep_ms(500);
        }
        
        // Se o sistema estiver desligado, apenas exibe a tela
        if (!sistema_ativo) {
            desenhar_tela_senha(&ssd, entrada, indice, digito_atual);
            continue;
        }
        
        // Atualiza a tela com a senha
        desenhar_tela_senha(&ssd, entrada, indice, digito_atual);
        
        if (!acesso_liberado) {
            // Incrementa o valor do dígito ao pressionar o botão de incremento
            if (gpio_get(BOTAO_INCREMENTO) == 0) {
                digito_atual = (digito_atual + 1) % 10;
                desenhar_tela_senha(&ssd, entrada, indice, digito_atual);
                sleep_ms(300);
            }
            
            // Confirma o dígito ao pressionar o botão do joystick
            if (gpio_get(BOTAO_JOYSTICK) == 0) {
                entrada[indice] = '0' + digito_atual;
                indice++;
                digito_atual = 0;
                // Quando todos os 4 dígitos forem inseridos, verifica a senha
                if (indice == 4) {
                    entrada[4] = '\0';
                    verificar_senha(&ssd, entrada);
                    indice = 0;
                    memset(entrada, '0', 4);
                }
                sleep_ms(300);
            }
        }
        sleep_ms(100);
    }
}

