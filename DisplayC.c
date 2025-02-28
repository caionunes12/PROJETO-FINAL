#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"
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

// Adicione após as definições no início do arquivo
#define BUZZER 10  // Defina o pino do buzzer
#define FREQ_DIGITO 4000  // 4000Hz - Som agudo para confirmação
#define FREQ_ACESSO 2000  // 2000Hz - Som mais grave para acesso permitido

// Variáveis de estado do sistema
bool sistema_ativo = false;
bool acesso_liberado = false;
uint32_t tempo_bloqueio = 0;
bool sistema_bloqueado = false;
int tentativas = 0;

// Função para desenhar a tela de senha no display
void desenhar_tela_senha(ssd1306_t *ssd, char *entrada, int indice, int digito_atual) {
    ssd1306_fill(ssd, false);
    if (!sistema_ativo) {
        ssd1306_draw_string(ssd, "Desligado", 25, 10);
    } else if (sistema_bloqueado) {
        ssd1306_draw_string(ssd, "Bloqueado!", 25, 10);
        char tempo_str[20];
        uint32_t segundos_restantes = (tempo_bloqueio - time_us_32() / 1000000);
        sprintf(tempo_str, "Aguarde... %lus", segundos_restantes);
        ssd1306_draw_string(ssd, tempo_str, 5, 30);
    } else if (acesso_liberado) {
        ssd1306_draw_string(ssd, "Acesso Liberado", 5, 10);
    } else {
        ssd1306_draw_string(ssd, "Digite a Senha:", 5, 10);
        char senha_exibida[6] = "****";
        for (int i = 0; i < indice; i++) {
            senha_exibida[i] = entrada[i];
        }
        ssd1306_draw_string(ssd, senha_exibida, 50, 30);
        char info_digito[10];
        sprintf(info_digito, "Digito: %d", digito_atual);
        ssd1306_draw_string(ssd, info_digito, 30, 50);
    }
    ssd1306_send_data(ssd);
}

// Função para verificar se a senha digitada está correta
void verificar_senha(ssd1306_t *ssd, char *entrada) {
    ssd1306_fill(ssd, false);
    if (strcmp(entrada, SENHA) == 0) {
        ssd1306_draw_string(ssd, "Senha Correta!", 5, 30);
        gpio_put(LED_VERDE, 1);
        acesso_liberado = true;
        tocar_buzzer_acesso();  // Toca o buzzer de acesso permitido
    } else {
        ssd1306_draw_string(ssd, "Senha Invalida!", 5, 30);
        tentativas++;
        
        if (tentativas >= 3) {
            sistema_bloqueado = true;
            tempo_bloqueio = time_us_32() / 1000000 + 60;
        }
    }
    ssd1306_send_data(ssd);
    sleep_ms(2000);
}

// Adicione esta nova função
void tocar_buzzer_digito() {
    gpio_set_function(BUZZER, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(BUZZER);
    
    // Configura PWM para frequência aguda (4000Hz) com 10% do volume
    pwm_set_wrap(slice_num, 31250);
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 3125); // 10% de 31250
    pwm_set_enabled(slice_num, true);
    
    sleep_ms(50);  // Toca por 50ms
    
    // Desliga o buzzer
    pwm_set_enabled(slice_num, false);
    gpio_set_function(BUZZER, GPIO_FUNC_NULL);
}

void tocar_buzzer_acesso() {
    gpio_set_function(BUZZER, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(BUZZER);
    
    // Configura PWM para frequência mais grave (2000Hz) com 10% do volume
    pwm_set_wrap(slice_num, 62500);
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 6250); // 10% de 62500
    pwm_set_enabled(slice_num, true);
    
    sleep_ms(200);  // Toca por 200ms
    
    // Desliga o buzzer
    pwm_set_enabled(slice_num, false);
    gpio_set_function(BUZZER, GPIO_FUNC_NULL);
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
                sistema_bloqueado = false;
                tentativas = 0;
                gpio_put(LED_VERDE, 0);
                // Reset completo da senha ao desligar
                indice = 0;
                digito_atual = 0;
                memset(entrada, '0', 4);
            }
            gpio_put(LED_VERMELHO, sistema_ativo);
            sleep_ms(500);
        }
        
        // Verifica se o tempo de bloqueio já passou
        if (sistema_bloqueado && (time_us_32() / 1000000) >= tempo_bloqueio) {
            sistema_bloqueado = false;
            tentativas = 0;
        }
        
        // Se o sistema estiver desligado ou bloqueado, apenas exibe a tela
        if (!sistema_ativo || sistema_bloqueado) {
            desenhar_tela_senha(&ssd, entrada, indice, digito_atual);
            sleep_ms(100);
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
                tocar_buzzer_digito();  // Toca o buzzer ao confirmar dígito
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
