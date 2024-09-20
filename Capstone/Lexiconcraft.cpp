#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOL_LEN 100

typedef struct {
    char word[MAX_SYMBOL_LEN];
    char symbol[MAX_SYMBOL_LEN];
} SymbolPair;

typedef struct {
    SymbolPair *symbol_dict;
    int size;
} LanguageSymbolGenerator;

LanguageSymbolGenerator* create_symbol_generator() {
    LanguageSymbolGenerator *generator = (LanguageSymbolGenerator*)malloc(sizeof(LanguageSymbolGenerator));
    generator->symbol_dict = NULL;
    generator->size = 0;
    return generator;
}

char* generate_symbol(const char* word) {
    char *symbol = (char*)malloc(MAX_SYMBOL_LEN * sizeof(char));
    snprintf(symbol, MAX_SYMBOL_LEN, "Symbol for %s", word);
    return symbol;
}

void add_word_symbol(LanguageSymbolGenerator *generator, const char* word) {
    for (int i = 0; i < generator->size; i++) {
        if (strcmp(generator->symbol_dict[i].word, word) == 0) {
            printf("Symbol for '%s' already exists: %s\n", word, generator->symbol_dict[i].symbol);
            return;
        }
    }

    SymbolPair pair;
    strcpy(pair.word, word);
    strcpy(pair.symbol, generate_symbol(word));

    generator->size++;
    generator->symbol_dict = (SymbolPair*)realloc(generator->symbol_dict, generator->size * sizeof(SymbolPair));
    generator->symbol_dict[generator->size - 1] = pair;

    printf("Generated symbol for '%s': %s\n", word, pair.symbol);
}

char* customize_symbol(LanguageSymbolGenerator *generator, const char* word, const char* customization_options) {
    for (int i = 0; i < generator->size; i++) {
        if (strcmp(generator->symbol_dict[i].word, word) == 0) {
            char *customized_symbol = (char*)malloc(MAX_SYMBOL_LEN * sizeof(char));
            snprintf(customized_symbol, MAX_SYMBOL_LEN, "%s with customization: %s", generator->symbol_dict[i].symbol, customization_options);
            return customized_symbol;
        }
    }

    char *error_message = (char*)malloc(MAX_SYMBOL_LEN * sizeof(char));
    snprintf(error_message, MAX_SYMBOL_LEN, "No symbol found for '%s'", word);
    return error_message;
}

int main() {
    LanguageSymbolGenerator *symbol_generator = create_symbol_generator();
    add_word_symbol(symbol_generator, "apple");
    add_word_symbol(symbol_generator, "banana");

    char *customized_apple = customize_symbol(symbol_generator, "apple", "color=red,shape=circle");
    char *customized_cherry = customize_symbol(symbol_generator, "cherry", "color=purple,shape=heart");

    printf("%s\n", customized_apple);
    printf("%s\n", customized_cherry);

    free(customized_apple);
    free(customized_cherry);
    free(symbol_generator->symbol_dict);
    free(symbol_generator);

    return 0;
}

