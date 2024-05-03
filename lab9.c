#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

struct elm{
    char cuv[30];
    struct elm* next;
};

typedef struct elm nod;

uint8_t sum_hash(const uint8_t *str)
{
    uint8_t c;
    uint8_t hash = 0;

    while ((c = *str ++))
        hash += c;
    hash = hash % 256;
    return hash ;
}

uint16_t DJB2_hash(const uint8_t *str)
{
    uint16_t hash = 5381;
    uint8_t c;
    while((c = *str ++))
        hash =(( hash << 5)+ hash) + c;
    return hash ;
}
uint16_t sum_hash2(const uint8_t *str)
{
    uint8_t c;
    uint16_t hash = 0;

    while ((c = *str++))
        hash += c;

    hash = hash % 65536;
    return hash;
}

void calc_procent(nod** tabela)
{

    float nr_col = 0.0;

    for(int j = 0; j<256; j++)
    {
        int nr = 0;
        nod *slot = tabela[j];

        while(slot->next != NULL){
            slot = slot->next;
            nr++;
        }
        nr_col += (--nr);
    }

    float p = (nr_col/370105)*100;
    printf("%f", p);

}

void calc_procentDJB2(nod** tabela)
{

    float nr_col = 0.0;

    for(int j = 0; j<65536; j++)
    {
        int nr = 0;
        nod *slot = tabela[j];

        while(slot->next != NULL){
            slot = slot->next;
            nr++;
        }
        nr_col += (--nr);
    }

    float p = (nr_col/370105)*100;
    printf("%f", p);

}

int main()
{
    nod** tabela = (nod**)calloc(256, sizeof(nod*));

    FILE *f;
    if((f=fopen("words_alpha.txt", "rt")) == NULL)
    {
        puts("Eroare la deschidere fisier!");
        exit(1);
    }

    char word[30];
//a
    while(!feof(f))
    {
        fscanf(f,"%s", word);
        uint16_t index = sum_hash2(word);

        if(tabela[index] == NULL)
        {
            nod *new_nod = (nod*)malloc(sizeof(nod));
            strcpy(new_nod->cuv, word);

            new_nod->next = NULL;
            tabela[index] = new_nod;

        }

        else{
            nod *aux = tabela[index];

            while(aux->next != NULL){
                aux = aux->next;
            }

            nod *new_nod = (nod*)malloc(sizeof(nod));
            strcpy(new_nod->cuv, word);

            new_nod->next = NULL;
            aux->next = new_nod;
        }
    }

    fclose(f);

    nod *afisare2 = tabela[2];
    for (int i = 0; i < 20 && afisare2 != NULL; i++)
    {
        printf("%s\n", afisare2->cuv);
        afisare2 = afisare2->next;
    }

//b
    for(int j = 0; j<100; j++)
    {
        int nr = 0;
        nod *slot = tabela[j];

        while(slot->next != NULL){
            slot = slot->next;
            nr++;
        }

        printf("%d\n", nr);
    }

    for(int j = 0; j<100; j++)
    {
        int nr = 0;
        nod *slot = tabela[j];

        while(slot->next != NULL){
            slot = slot->next;
            nr++;
        }

        printf("%d\n", nr);
    }
//c
    printf("Procent coliziuni (sum_hash): ");
    calc_procent(tabela);

    printf("Procent coliziuni (DJB2_hash): ");
    calc_procentDJB2(tabela);

//d

   for (int i = 0; i < 256; i++)
   {
        nod *temp;
        while (tabela[i] != NULL)
        {
            temp = tabela[i];
            tabela[i] = tabela[i]->next;
            free(temp);
        }
    }

}


