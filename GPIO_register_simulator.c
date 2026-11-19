#include <stdio.h>
#include <stdint.h>

bool check_bit(const int place)
{
        if (place < 0 || place > 7){
                printf ("Invalid bit number!\n");
                return 0;
        }
        else return 1;
}

void print_register(uint8_t reg)
{
        printf("Current register:\nBIN: ");
        for (int8_t i = 7; i >= 0;i--) printf("%d", 1 & reg >> i);
        printf("\nDEC: %d\n", reg);
        printf("HEX: 0x%02x\n", reg);
}

int input_bit_number(){
        int place = -1;
        while (place < 0 || place > 7)
        {
                printf("Enter bit number: ");
                if (scanf("%d", &place) != 1){
                        printf("Input only numbers!\n");
                        int ch;
                        while ((ch = getchar()) != '\n' && ch != EOF);
                        continue;
                }       
        }
        return place;
}

uint8_t set_bit(uint8_t reg, const int place)
{
        if (!check_bit(place)) return reg;
        reg |= 1 << place;
        return reg;
}

uint8_t clear_bit(uint8_t reg, const int place)
{
        if (!check_bit(place)) return reg;
        reg &= ~(1 << place);
        return reg;
}

uint8_t toggle_bit(uint8_t reg, const int place)
{
        if (!check_bit(place)) return reg;
        reg ^=  1 << place;
        return reg;
}

int8_t read_bit(uint8_t reg, const int place)
{
        if (!check_bit(place)) return -1;
        return (1 & reg >> place);
}

uint8_t reset_register()
{
        return 0;
}

int main()
{
        uint8_t gpio = 0;
        int input = -1;
        while (input != 0){
                int n = 0;
                printf("================================\n    GPIO REGISTER SIMULATOR\n================================\n\n");
                print_register(gpio);
                printf("1. SET bit\n2. CLEAR bit\n3. TOGGLE bit\n4. READ bit\n5. RESET register\n0. EXIT\n\nSelect operation: ");
                if (scanf("%d", &input) != 1){
                        printf("Input only numbers!\n");
                        int ch;
                        while ((ch = getchar()) != '\n' && ch != EOF);
                        continue;
                }
                switch (input)
                {
                        case 0:
                                printf("Program terminated");
                                return 0;
                        case 1:
                                n = input_bit_number();
                                gpio = set_bit(gpio, n);
                                break;
                        case 2:
                                n = input_bit_number();
                                gpio = clear_bit(gpio, n);
                                break;
                        case 3:
                                n = input_bit_number();
                                gpio = toggle_bit(gpio, n);
                                break;
                        case 4:
                                n = input_bit_number();
                                int8_t tmp = read_bit(gpio, n);
                                if (tmp == - 1) break;
                                printf("Bit number %d is %d\n", n, tmp);
                                break;
                        case 5:
                                gpio = reset_register();
                                break;
                        default:
                                printf("Invalid operation!!\n");
                                break;
                }
        }
        return 0;
}