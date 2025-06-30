void formatarNomeCompleto(char text[50]);

void formatarNomeCompleto(char text[50]){ // Primeira letra de cada palavra em maiuscula e o resto em minuscula
    int i = 0;
    int tam = strlen(text);

    for (i = 0; i <= tam; i++) {
        if (i == 0 || text[i - 1] == ' '){ // Primeira letra da palavra
            if (97 <= text[i] && text[i] <= 122) { // A letra é Minuscula
                text[i] = (text[i] + 32); // -- Trasforma em Maiuscula
            }
        } else { // Restante da palavra
            if (65 <= text[i] && text[i] <= 90) { // A letra é Mainuscula
                text[i] = (text[i] + 32); // -- Trasforma em Minuscula
            }
        }
    }
}