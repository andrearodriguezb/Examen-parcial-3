#include <stdio.h>

#define MAX_COLUMNAS 3100
#define FILAS_A_PROCESAR 50
#define BUFFER_SIZE 1024 * 1024

int main() {
    const char *nombre_archivo_csv = "emails.csv";
    FILE *archivo_csv = fopen(nombre_archivo_csv, "r");
    if (!archivo_csv) {
        perror("Error al abrir el archivo CSV");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    int count[MAX_COLUMNAS] = {0};
    char palabras[MAX_COLUMNAS][50];  
    int fila_inicio = 676;
    int columna = -1;
    int i;

    
    for (i = 0; i < MAX_COLUMNAS; i++) {
        palabras[i][0] = '\0';
    }

    if (fgets(buffer, sizeof(buffer), archivo_csv) != NULL) {
        char *token = strtok(buffer, ",");
        int indice_columna = 0;
        while (token && indice_columna < MAX_COLUMNAS) {
            if (strcmp(token, "Email No.") == 0) {
                columna = indice_columna;
            } else {
                int i = 0;
                while (token[i] != '\0') {
                    palabras[indice_columna][i] = token[i];
                    i++;
                }
                palabras[indice_columna][i] = '\0';
            }
            token = strtok(NULL, ",");
            indice_columna++;
        }
    } else {
        fclose(archivo_csv);
        return 1;
    }

    for (i = 0; i < fila_inicio; ++i) {
        if (fgets(buffer, sizeof(buffer), archivo_csv) == NULL) {
            fclose(archivo_csv);
            return 1;
        }
    }

    for (i = 0; i < FILAS_A_PROCESAR; ++i) {
        if (fgets(buffer, sizeof(buffer), archivo_csv) == NULL) {
            break;
        }
        char *token = strtok(buffer, ",");
        int indice_columna = 0;
        while (token && indice_columna < MAX_COLUMNAS) {
            if (indice_columna != columna) {
                long val = 0;
                int i = 0;
                while (token[i] != '\0') {
                    val = val * 10 + (token[i] - '0');
                    i++;
                }
                count[indice_columna] += val;
            }
            token = strtok(NULL, ",");
            indice_columna++;
        }
    }

    fclose(archivo_csv);

    FILE *archivo_salida = fopen("180676.txt", "w");
    if (!archivo_salida) {
        perror("Error al abrir el archivo de salida");
        return 1;
    }

    for (i = 0; i < MAX_COLUMNAS; i++) {
        if (i != columna&& palabras[i][0] != '\0') {
            fprintf(archivo_salida, "%s, %d\n",palabras[i], count[i]);
        }
    }

    fclose(archivo_salida);
    printf("Cantidades en 180676.txt    \n");

    return 0;
}
