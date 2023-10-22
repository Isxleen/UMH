#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lib.h"

//gcc lib.c main.c -o main.exe

int main(){
    char prompt[100] = "*";
    char com[100];
    char comaux[100];
    char nombre_bd[100] = "*";
    char nombre_tabla[100] = "*";

    int num_arg, i, j, auxiliar, num_argumentos, num_arg_aux;
    int aux_enteros, aux_comprobante;
    char s2[8] = " \n\t\r";//Separador

    char *comtok[100];
    char *comillas, *comillas2;
    char **nombre, **valores;
    TYPE *tipos;
    TABLE *LaGranTabla = NULL, *tabla_auxiliar = NULL, *tabla_auxiliar2 = NULL;
    ROW *LaGranLinea=NULL, *linea_auxiliar;

    mis_datos();

    while(1){

        printf("[%s]:>", prompt);

        gets(com);
        strcpy(comaux, com);
        num_arg = 0;
        comtok[num_arg] = strtok(com, s2);

        num_arg++;

        while((comtok[num_arg] = strtok(NULL, s2)) != NULL){
            num_arg++;
        }

        if(comtok[0] == NULL){ //si el prompt no ponen nada vuelve a ejecutarse
            continue;
        }

        if(strcmp(comtok[0], "exit") == 0){

            if(num_arg != 1){
                printf("ERROR: Numero de argumentos incorrectos\n");
                continue;
            }
            else{
                return 0;
            }
        }
        else if(strcmp(comtok[0], "new") == 0 && strcmp(comtok[1], "db") == 0){
            if(num_arg != 3){
                printf("ERROR: numero de argumentos introducidos incorrecto\n");
                continue;
            }

            aux_enteros = validar_caracteres(comtok[2]);

            if(aux_enteros == 0){
                crear_bd(comtok[2]);
            }
            else{
                printf("ERROR: el nombre introducido no es valido\n");
                continue;
            }
        }
        else if(strcmp(comtok[0], "use") == 0 && strcmp(comtok[1], "db") == 0){
            if(num_arg != 3){
                printf("ERROR: numero de argumentos incorrecto\n");
                continue;
            }

            if(strcmp(comtok[2], ".") == 0 || strcmp(comtok[2], "..") == 0){
                printf("Estas carpetas no se tocan\n");
                continue;
            }

            aux_enteros = entrar_dir(comtok[2]);// Comprobar si la bd existe

            if(aux_enteros == 0){

                strcpy(prompt, comtok[2]);
                strcpy(nombre_bd, comtok[2]);
                strcpy(nombre_tabla, "*");
            }
            else{
                continue;
            }

            if(LaGranTabla != NULL){
                if(LaGranLinea != NULL){
                    liberar_memoria_lineas(LaGranLinea, tabla_auxiliar->numCampos);
                    LaGranLinea = NULL;
                }

                liberar_memoria_tablas(LaGranTabla);
                LaGranTabla = NULL;

            }

            LaGranTabla = cargarTablas(nombre_bd);

            mostrar_tablas(LaGranTabla);

        }
        else if(strcmp(comtok[0], "new") == 0 && strcmp(comtok[1], "table") == 0){
  
            if(num_arg<5){
                printf("ERROR: Numero de comandos incorrecto\n");
                continue;
            }
            else if(num_arg % 2 == 0){
                printf("ERROR: Numero de comandos incorrecto, asegurate de introducir: TABLA CAMPO TIPO ...\n");
                continue;
            }
            else if(strcmp(prompt, "*") == 0){
                printf("ERROR: Base de Datos inactiva\n");
                continue;
            }

            for(i = 2; i<num_arg; i++){
                aux_enteros = validar_caracteres(comtok[i]);

                if(aux_enteros > 0){
                    printf("ERROR: Comprueba que este todo bien escrito\n");
                    break;
                }
            }

            if(aux_enteros>0){
                continue;
            }

            int num_campos = (num_arg - 3)/2;

      
            //malloc(tamaño // char 9)
            nombre = malloc(sizeof(char*)*(num_campos)); //reservamos memoria para el array de columnas de la tabla
            tipos = malloc(sizeof(TYPE*)*(num_campos)); // reservamos memoria para los tipos de la tabla
            auxiliar = 0;
            aux_comprobante = 0;     

            for(i=3; i<num_arg; i++){
                
                if(i % 2 == 1){
                    nombre[auxiliar] = strdup(comtok[i]);
                }
                else{
                    aux_enteros = validar_tipo(comtok[i]);

                    if(aux_enteros == 4){
                        printf("ERROR: tipos incorrectos\n");
                        aux_comprobante = 1;
                        break;
                    }

                    tipos[auxiliar] = validar_tipo(comtok[i]);
                    auxiliar++;
                }
            }

            i = ver_duplicados(nombre, auxiliar);
            j = entrar_tabla(nombre_bd, comtok[2]);

            if(j != 0){
                printf("error\n");
                continue;
            }

            if(aux_comprobante == 0 && i == 0 && j == 0){
                tabla_auxiliar2 = inicializar_tabla(num_campos, comtok[2], nombre, tipos);

                if(tabla_auxiliar != NULL){
                    if(LaGranTabla == NULL){
                        LaGranTabla = tabla_auxiliar2;
                        crear_tabla_tab(LaGranTabla, nombre_bd, comtok[2]);
                    }
                    else{
                        insertar_tabla(LaGranTabla, tabla_auxiliar2);
                        crear_tabla_tab(LaGranTabla, nombre_bd, comtok[2]);
                    }             
                }
                printf("La tabla %s ha sido creada con exito\n", tabla_auxiliar2->nombre);
            }       
        }
        else if(strcmp(comtok[0], "use") == 0 && strcmp(comtok[1], "table") == 0){
            if(num_arg != 3){
                printf("ERROR: numero de argumentos incorrecto\n");
                continue;
            }
            if(strcmp(prompt, "*") == 0){

                printf("ERROR: no hay una base de datos activa\n");
                continue;
            }

            aux_comprobante = entrar_tabla(nombre_bd, comtok[2]);

            if(aux_comprobante == 1){

                
                strcpy(prompt, nombre_bd);
                strcpy(nombre_tabla, comtok[2]);
                strcat(prompt, "/");
                strcat(prompt, nombre_tabla);

                if(LaGranLinea != NULL){
                    liberar_memoria_lineas(LaGranLinea, tabla_auxiliar->numCampos);
                
                }

                LaGranLinea = NULL;
                
            }
            else{
                continue;
            }

            tabla_auxiliar = buscar_tabla(nombre_tabla, LaGranTabla);
            LaGranLinea = cargar_linea(nombre_bd, nombre_tabla, tabla_auxiliar->numCampos, tabla_auxiliar->tipos);

        }
        else if(strcmp(comtok[0], "insert") == 0){
            
            if(strcmp(prompt, "*") == 0){
                printf("ERROR: base de datos inactiva\n");
                continue;
            }
            if(strcmp(prompt, nombre_bd) == 0){
                printf("ERROR: tabla inactiva\n");
                continue;
            }
            aux_comprobante = 0;
            comillas = strchr(comaux, '"');

            if(comillas != NULL){

                comillas2 = strchr(comillas+1, '"');

                if(comillas2== NULL){
                    //ERROR
                    printf("ERROR DE COMILLAS\n");
                    aux_comprobante++;
                    continue;
                }
                else{
                    //Llamamos a la funcion Mistrtok con las comillas activadas
                    num_arg_aux = 0;
                    comtok[num_arg_aux] = MiStrTok(comaux, s2, 0);
                    num_arg_aux++;
                    
                    while((comtok[num_arg_aux] = MiStrTok(NULL, s2, 1)) != NULL){ // Mistrtok con comillas activas
                        num_arg_aux++;
                    }
                }
            }
            else{
                //Llamamos a la funcion Mistrtok con las comillas desactivadas

                num_arg_aux = 0;
                comtok[num_arg_aux] = MiStrTok(comaux, s2, 0);
                num_arg_aux++;

                while((comtok[num_arg_aux] = MiStrTok(NULL, s2, 0)) != NULL){ //Mistrtok con las comillas desactivadas
                    num_arg_aux++;
                }

            }

            if(num_arg_aux == tabla_auxiliar->numCampos+1){

                for(i=0; i<tabla_auxiliar->numCampos; i++){

                    if(tabla_auxiliar->tipos[i] == NUM){
                        if(validardecimal(comtok[i+1]) == 0){
                            printf("ERROR: numero introducido invalido\n");
                            aux_comprobante++;
                            break;
                        }

                    }
                    else if(tabla_auxiliar->tipos[i] == DATE){
                        if(FechaValidarDMA(comtok[i+1]) == 0){
                            printf("ERROR: fecha introducida incorrecta\n");
                            aux_comprobante++;
                            break;

                        }

                    }
                    else if(tabla_auxiliar->tipos[i] == EMAIL){

                        if(validar_email(comtok[i+1]) != 0){
                            
                            printf("ERROR: email introducido incorrecto\n");
                            aux_comprobante++;
                            break;
                        }

                    }
                    else if(tabla_auxiliar->tipos[i] == TEXT){

                        if(validardecimal(comtok[i+1]) != 0 || FechaValidarDMA(comtok[i+1]) != 0 || validar_email(comtok[i+1]) == 0){
                            printf("ERROR: valor introducido ha de ser tipo TEXT\n");
                            aux_comprobante++;
                        }
                    }

                }

                if(aux_comprobante != 0){
                    continue;
                }

                valores = malloc(sizeof(char*)*tabla_auxiliar->numCampos);

                for(i = 0 ; i < tabla_auxiliar->numCampos; i++){
                    valores[i] = strdup(comtok[i+1]);
                }

                linea_auxiliar = inicializar_linea(valores);

                if(linea_auxiliar != NULL){
                    if(LaGranLinea == NULL){
                        LaGranLinea = linea_auxiliar;
                        actualizar_lineas(nombre_bd, LaGranLinea, tabla_auxiliar);
                    }
                    else{
                        insertar_ultima_linea(LaGranLinea, linea_auxiliar);
                        actualizar_lineas(nombre_bd, LaGranLinea, tabla_auxiliar);

                    }
                }

            }
            else{
                printf("ERROR: umero de argumentos incorrecto\n");
            }
        }
        else if(strcmp(comtok[0], "select") == 0){

            if(strcmp(prompt, "*") == 0){
                printf("ERROR: no hay una bd activa\n");
                continue;
            }

            if(strcmp(prompt, nombre_bd) == 0){
                printf("ERROR: no hay una tabla cargado\n");
                continue;
            }

            comillas = strchr(comaux, '"');

            if(comillas != NULL){

                comillas2 = strchr(comillas+1, '"');

                if(comillas2 == NULL){
                    printf("ERROR: comillas insuficientes\n");
                    break;
                }
                else{

                    //Llamamos a mistrtok con las comillas activadas

                    num_arg_aux = 0;
                    comtok[num_arg_aux] = MiStrTok(comaux, s2, 0);
                    num_arg_aux++;

                    while((comtok[num_arg_aux] = MiStrTok(NULL, s2, 1)) != NULL){
                        num_arg_aux++;
                    }
                }
            }
            else{
                //Llamamos a mistrtok con las comillas desactivadas

                num_arg_aux = 0;
                comtok[num_arg_aux] = MiStrTok(comaux, s2, 0);
                num_arg_aux++;

                while((comtok[num_arg_aux] = MiStrTok(NULL, s2, 0)) != NULL){
                    printf("%d, %s\n", num_arg_aux, comtok[num_arg_aux]);
                    num_arg_aux++;
                }

            }

            if(num_arg_aux == 1){ // SELECT
                impr_cabeceras(tabla_auxiliar);
                impr_todo(LaGranLinea, tabla_auxiliar->numCampos);

            }
            else if(num_arg_aux == 2){ // SELECT ASCENDENTE O DESCENDENTE
                
                if(strcmp(comtok[1], "DES") == 0){
                    impr_cabeceras(tabla_auxiliar);
                    impr_todo_DES(LaGranLinea, tabla_auxiliar->numCampos, tabla_auxiliar);

                }
                else if(strcmp(comtok[1], "ASC") == 0){
                    impr_cabeceras(tabla_auxiliar);
                    impr_todo_ASC(LaGranLinea, tabla_auxiliar->numCampos, tabla_auxiliar);

                }
                else{
                    printf("ERROR: segundo comando incorrecto\n");
                }
            }
            else if(num_arg_aux == 4){ // SELECT NOMBRE = VALOR
                
                for(i=0; i < tabla_auxiliar->numCampos; i++){
                    if(strcmp(tabla_auxiliar->campos[i], comtok[1]) == 0){
                        
                        if(tabla_auxiliar->tipos[i] == NUM){
                            
                            if(validardecimal(comtok[3]) == 1){
                                impr_cabeceras(tabla_auxiliar);
                                imprimir_valor_campo(tabla_auxiliar->numCampos, LaGranLinea, tabla_auxiliar->tipos[i], comtok[3], comtok[2], i);
                                break;
                                
                            }
                             else{
                                printf("ERROR: tipo de dato incorrecto\n");
                                break;
                            }
                        }
                        else if(tabla_auxiliar->tipos[i] == DATE){
                            
                            if(FechaValidarDMA(comtok[3]) == 1){
                                impr_cabeceras(tabla_auxiliar);
                                imprimir_valor_campo(tabla_auxiliar->numCampos, LaGranLinea, tabla_auxiliar->tipos[i], comtok[3], comtok[2], i);
                            }
                             else{
                                printf("ERROR: tipo de dato incorrecto\n");
                                break;
                            }
                        }
                        else if(tabla_auxiliar->tipos[i] == TEXT){
                            impr_cabeceras(tabla_auxiliar);
                            imprimir_valor_campo(tabla_auxiliar->numCampos, LaGranLinea, tabla_auxiliar->tipos[i], comtok[3], comtok[2], i);
                            break;
                        }
                        
                    }

                    if(i+1 == tabla_auxiliar->numCampos){
                        printf("ERROR: Campo no encontrado\n");
                    }
                }
            }
            else if(num_arg_aux == 5){ // SELECT NOMBRE = VALOR ASC/DESC
            
                if(strcmp(comtok[4], "ASC") == 0){

                    for(i=0; i < tabla_auxiliar->numCampos; i++){
                        if(strcmp(tabla_auxiliar->campos[i], comtok[1]) == 0){
                            
                            if(tabla_auxiliar->tipos[i] == NUM){
                                if(validardecimal(comtok[3]) == 1){
                                    impr_cabeceras(tabla_auxiliar);
                                    ordenar_asc(LaGranLinea, tabla_auxiliar, 0);

                                    imprimir_valor_campo(tabla_auxiliar->numCampos, LaGranLinea, tabla_auxiliar->tipos[i], comtok[3], comtok[2], i);
                                }
                                else{
                                    printf("ERROR: tipos con las columnas\n");
                                    break;
                                }
                            }
                            else if(tabla_auxiliar->tipos[i] == DATE){
                                if(FechaValidarDMA(comtok[3]) == 1){
                                    impr_cabeceras(tabla_auxiliar);
                                    ordenar_asc(LaGranLinea, tabla_auxiliar, 0);

                                    imprimir_valor_campo(tabla_auxiliar->numCampos, LaGranLinea, tabla_auxiliar->tipos[i], comtok[3], comtok[2], i);
                                }
                                 else{
                                    printf("ERROR: tipos con las columnas\n");
                                    break;
                                }
                            }
                            else if(tabla_auxiliar->tipos[i] == EMAIL){
                                if(validar_email(comtok[3]) == 1){
                                    impr_cabeceras(tabla_auxiliar);
                                    ordenar_asc(LaGranLinea, tabla_auxiliar, 0);

                                    imprimir_valor_campo(tabla_auxiliar->numCampos, LaGranLinea, tabla_auxiliar->tipos[i], comtok[3], comtok[2], i);
                                }
                                 else{
                                    printf("ERROR: tipos con las columnas\n");
                                    break;
                                }
                            }
                            else if(tabla_auxiliar->tipos[i] == TEXT){
                                impr_cabeceras(tabla_auxiliar);
                                ordenar_asc(LaGranLinea, tabla_auxiliar, 0);

                                imprimir_valor_campo(tabla_auxiliar->numCampos, LaGranLinea, tabla_auxiliar->tipos[i], comtok[3], comtok[2], i);
                            }
                            else{
                                printf("ERROR de tipos\n");
                                i++;
                                continue;
                            }
                        }

                        if(i+1 == tabla_auxiliar->numCampos){
                            printf("ERROR: campo no encontrado");
                        }
                    }
                }
                else if(strcmp(comtok[4], "DES") == 0){
                    for(i=0; i < tabla_auxiliar->numCampos; i++){
                        if(strcmp(tabla_auxiliar->campos[i], comtok[1]) == 0){
                            
                            if(tabla_auxiliar->tipos[i] == NUM){
                                if(validardecimal(comtok[3]) == 1){
                                    impr_cabeceras(tabla_auxiliar);
                                    ordenar_des(LaGranLinea, tabla_auxiliar, 0);

                                    imprimir_valor_campo(tabla_auxiliar->numCampos, LaGranLinea, tabla_auxiliar->tipos[i], comtok[3], comtok[2], i);
                                }
                                else{
                                    printf("ERROR: tipos con las columnas\n");
                                    break;
                                }
                            }
                            else if(tabla_auxiliar->tipos[i] == DATE){
                                if(FechaValidarDMA(comtok[3]) == 1){
                                    impr_cabeceras(tabla_auxiliar);
                                    ordenar_des(LaGranLinea, tabla_auxiliar, 0);

                                    imprimir_valor_campo(tabla_auxiliar->numCampos, LaGranLinea, tabla_auxiliar->tipos[i], comtok[3], comtok[2], i);
                                }
                                 else{
                                    printf("ERROR: tipos con las columnas\n");
                                    break;
                                }
                            }
                            else if(tabla_auxiliar->tipos[i] == TEXT){
                                impr_cabeceras(tabla_auxiliar);
                                ordenar_des(LaGranLinea, tabla_auxiliar, 0);

                                imprimir_valor_campo(tabla_auxiliar->numCampos, LaGranLinea, tabla_auxiliar->tipos[i], comtok[3], comtok[2], i);
                            }
                            else{
                                printf("ERROR de tipos\n");
                                i++;
                                continue;
                            }
                        }

                        if(i+1 == tabla_auxiliar->numCampos){
                            printf("ERROR: Campo no encontrado\n");
                        }
                    }
                }

            }
        }
        else if(strcmp(comtok[0], "list") == 0){

            if(num_arg != 1){
                printf("ERROR: Numero de argumentos incorrecto\n");
                continue;
            }

            mostrar_bd();

        }
        else if(strcmp(comtok[0], "delete") == 0){
            if(LaGranTabla == NULL){
                printf("ERROR: no hay una base de datos activa\n");
                continue;
            }
            if(strcmp(nombre_bd, prompt) == 0){
                printf("ERROR: no hay una tabla activa\n");
                continue;
            }

            comillas = strchr(comaux, '"');

            if(comillas != NULL){

                comillas2 = strchr(comillas+1, '"');

                if(comillas2 == NULL){
                    printf("ERROR: comillas insuficientes\n");
                    break;
                }
                else{

                    //Llamamos a mistrtok con las comillas activadas

                    num_arg_aux = 0;
                    comtok[num_arg_aux] = MiStrTok(comaux, s2, 0);
                    num_arg_aux++;

                    while((comtok[num_arg_aux] = MiStrTok(NULL, s2, 1)) != NULL){
                        printf("%d, %s\n", num_arg_aux, comtok[num_arg_aux]);
                        num_arg_aux++;
                    }
                }
            }
            else{
                //Llamamos a mistrtok con las comillas desactivadas

                num_arg_aux = 0;
                comtok[num_arg_aux] = MiStrTok(comaux, s2, 0);
                num_arg_aux++;

                while((comtok[num_arg_aux] = MiStrTok(NULL, s2, 0)) != NULL){
                    printf("%d, %s\n", num_arg_aux, comtok[num_arg_aux]);
                    num_arg_aux++;
                }

            }

            if(num_arg_aux != 4){ // delete canpo = valor
                printf("ERROR: numero incorrecto de argumentos");
                continue;
            }

            for(i=0; i<tabla_auxiliar->numCampos; i++){

                if(strcmp(tabla_auxiliar->campos[i], comtok[1])== 0){
                    if(tabla_auxiliar->tipos[i] == NUM && validardecimal(comtok[3]) == 1){

                        LaGranLinea = borrarLinea(tabla_auxiliar->numCampos, LaGranLinea, tabla_auxiliar->tipos[i], comtok[3], comtok[2], i);
                        actualizar_lineas(nombre_bd, LaGranLinea, tabla_auxiliar);
                        break;
                    } 
                    else if(tabla_auxiliar->tipos[i] == DATE && FechaValidarDMA(comtok[3]) == 1){
                        LaGranLinea = borrarLinea(tabla_auxiliar->numCampos, LaGranLinea, tabla_auxiliar->tipos[i], comtok[3], comtok[2], i);
                        actualizar_lineas(nombre_bd, LaGranLinea, tabla_auxiliar);
                        break;
                    }
                    else if(tabla_auxiliar->tipos[i] == EMAIL && validar_email(comtok[3]) == 1){
                        LaGranLinea = borrarLinea(tabla_auxiliar->numCampos, LaGranLinea, tabla_auxiliar->tipos[i], comtok[3], comtok[2], i);
                        actualizar_lineas(nombre_bd, LaGranLinea, tabla_auxiliar);
                        break;
                    }
                    else if(tabla_auxiliar->tipos[i] == TEXT && FechaValidarDMA(comtok[3]) == 1){
                        LaGranLinea = borrarLinea(tabla_auxiliar->numCampos, LaGranLinea, tabla_auxiliar->tipos[i], comtok[3], comtok[2], i);
                        actualizar_lineas(nombre_bd, LaGranLinea, tabla_auxiliar);
                        break;
                    }
                    else{
                        printf("ERROR: parametro introducido no encontrado\n");
                        continue;
                    }
                }
            }


        }
        else if(strcmp(comtok[0], "remove") == 0){
            if(num_arg != 2){
                printf("ERROR: numero de argumentos introdcidos incorrecto\n");
                continue;
            }

            if(strcmp(prompt, "*") == 0){
                printf("ERROR: no hay una base de datos activa\n");
                continue;
            }

            aux_comprobante = entrar_tabla(nombre_bd, comtok[1]);

            if(aux_comprobante == 0){
                printf("La tabla indicada no existe\n");
                continue;
            }

            if(strcmp(nombre_tabla, comtok[1]) == 0){
                strcpy(prompt, nombre_bd);
                strcpy(nombre_tabla, "*");
            }

            LaGranTabla = borrar_tabla(LaGranTabla, comtok[1]);


            // Eliminar de la carpeta 

            char aux_ruta[100] = "";

            strcpy(aux_ruta, nombre_bd);
            strcat(aux_ruta, "\\");
            strcat(aux_ruta, comtok[1]);
            strcat(aux_ruta, ".tab");

            remove(aux_ruta);
            editar_meta(nombre_bd, LaGranTabla);
        }
        else if(strcmp(comtok[0],"order") == 0){

            if(num_arg != 3){
                printf("ERROR: numero de argumentos introducidos incorrecto\n");
                continue;
            }

            if(strcmp(prompt,"*") == 0){
                printf("ERROR: base de datos inactiva\n");
                continue;
            }

            if(strcmp(prompt, nombre_bd) == 0){
                printf("ERROR: tabla inactiva\n");
                continue;
            }

            if(LaGranLinea == NULL){
                printf("ERROR: no hay datos que ordenar\n");
            }

            if(strcmp(comtok[2], "ASC") == 0){

                for(i = 0; i< tabla_auxiliar->numCampos; i++){
                    if(strcmp(tabla_auxiliar->campos[i], comtok[1]) == 0){
                        if(tabla_auxiliar->tipos[i] == NUM){

                            ordenar_asc(LaGranLinea, tabla_auxiliar, i);
                            actualizar_lineas(nombre_bd, LaGranLinea, tabla_auxiliar);
                            break;
                        }
                        if(tabla_auxiliar->tipos[i] == DATE){

                            ordenar_asc(LaGranLinea, tabla_auxiliar, i);
                            actualizar_lineas(nombre_bd, LaGranLinea, tabla_auxiliar);
                            break;
                        }
                        if(tabla_auxiliar->tipos[i] == EMAIL){

                            ordenar_asc(LaGranLinea, tabla_auxiliar, i);
                            actualizar_lineas(nombre_bd, LaGranLinea, tabla_auxiliar);
                            break;
                        }
                        if(tabla_auxiliar->tipos[i] == TEXT){

                            ordenar_asc(LaGranLinea, tabla_auxiliar, i);
                            actualizar_lineas(nombre_bd, LaGranLinea, tabla_auxiliar);
                            break;
                        }else{
                            printf("ERROR: tipo de campo no reconocido\n");
                        }
                    }
                    if(i+1 == tabla_auxiliar->numCampos){
                        printf("ERROR: el campo introducido no existe\n");
                    }
                }
            }
            if(strcmp(comtok[2], "DES") == 0){

                for(i = 0; i< tabla_auxiliar->numCampos; i++){
                    if(strcmp(tabla_auxiliar->campos[i], comtok[1]) == 0){
                        if(tabla_auxiliar->tipos[i] == NUM){

                            ordenar_des(LaGranLinea, tabla_auxiliar, i);
                            actualizar_lineas(nombre_bd, LaGranLinea, tabla_auxiliar);
                            break;
                        }
                        if(tabla_auxiliar->tipos[i] == DATE){

                            ordenar_des(LaGranLinea, tabla_auxiliar, i);
                            actualizar_lineas(nombre_bd, LaGranLinea, tabla_auxiliar);
                            break;
                        }
                        if(tabla_auxiliar->tipos[i] == EMAIL){

                            ordenar_des(LaGranLinea, tabla_auxiliar, i);
                            actualizar_lineas(nombre_bd, LaGranLinea, tabla_auxiliar);
                            break;
                        }
                        if(tabla_auxiliar->tipos[i] == TEXT){

                            ordenar_des(LaGranLinea, tabla_auxiliar, i);
                            actualizar_lineas(nombre_bd, LaGranLinea, tabla_auxiliar);
                            break;
                        }else{
                            printf("ERROR: tipo de campo no reconocido\n");
                        }
                    }
                    if(i+1 == tabla_auxiliar->numCampos){
                        printf("ERROR: el campo introducido no existe\n");
                    }
                }
            }
        }
        else if(strcmp(comtok[0], "import") == 0 && strcmp(comtok[1], "table") == 0 && strcmp(comtok[3], "from") == 0){
            if(num_arg != 5){
                printf("ERROR: numero de argumentos incorrecto\n");
                continue;
            }

            if(strcmp(prompt, "*") == 0){ // si no hay una base de datos activa
                printf("ERROR: base de datos inactiva\n");
                continue;
            }

            if(strcmp(nombre_bd, comtok[4]) == 0){
                printf("ERROR: la base de datos destino no puede ser la misma que la base de datos destino\n");
                continue;
            }


            if(entrar_dir(comtok[4]) == 1){
                printf("ERROR: la base de datos destino no existe\n");
                continue;
            }

            if(entrar_tabla(comtok[4], comtok[2]) == 0){
                printf("ERROR: la tabla a copiar no existe\n");
                continue;
            }

            if(entrar_tabla(nombre_bd, comtok[2]) == 1){
                printf("ERROR: la tabla a copiar ya existe\n");
                continue;
            }

            LaGranTabla = seleccionar_tablaBD(comtok[2], comtok[4], nombre_bd, LaGranTabla);
            mostrar_tablas(LaGranTabla);
        }
        else{
            printf("ERROR: orden no reconocida\n");
            continue;
        }
    }
}


/*   ------------------------FUNCIONES EXTRA -------------------------

else if(strcmp(comtok[0], "rename") == 0){
            if(num_arg == 5) // rename <campo> x <valor> <valor_nuevo>
			{
				if(strcmp(prompt, "*") == 0)
				{
					printf("Todavia no hay una bd activa\n");
					continue;
				}

				if(strcmp(prompt, nombre_bd) == 0)
				{
					printf("Todavia no hay una tabla activa\n");
					continue; 
				}
				
				else
				{
					int CampoExistente = 0; 
					
					for(int i=0; i<tabla_auxiliar->numCampos; i++)
					{
						if(strcmp(tabla_auxiliar->campos[i], comtok[1]) == 0)
						{
							if((strcmp(comtok[2], "=") == 0) || (strcmp(comtok[2], "<") == 0) || (strcmp(comtok[2], ">") == 0))
							{
								if(tabla_auxiliar->tipos[i] == NUM && validardecimal(comtok[3]) == 1)
								{	
									CampoExistente++;
									impr_cabeceras(tabla_auxiliar);
									LaGranLinea = RenombrarLineaValorDeseado(tabla_auxiliar->numCampos, LaGranLinea, tabla_auxiliar->tipos[i], comtok[3], comtok[4], comtok[2], i);
									actualizar_lineas(nombre_bd, LaGranLinea, tabla_auxiliar);
									LaGranLinea = cargar_linea(nombre_bd, tabla_auxiliar->nombre, tabla_auxiliar->numCampos, tabla_auxiliar->tipos);
									break;
								}
                                if(tabla_auxiliar->tipos[i] == DATE && FechaValidarDMA(comtok[3]) == 1)
								{	
									CampoExistente++;
									impr_cabeceras(tabla_auxiliar);
									LaGranLinea = RenombrarLineaValorDeseado(tabla_auxiliar->numCampos, LaGranLinea, tabla_auxiliar->tipos[i], comtok[3], comtok[4], comtok[2], i);
									actualizar_lineas(nombre_bd, LaGranLinea, tabla_auxiliar);
									LaGranLinea = cargar_linea(nombre_bd, tabla_auxiliar->nombre, tabla_auxiliar->numCampos, tabla_auxiliar->tipos);
									break;
								}
                                if(tabla_auxiliar->tipos[i] == EMAIL && validar_email(comtok[3]) == 0)
								{	
									CampoExistente++;
									impr_cabeceras(tabla_auxiliar);
									LaGranLinea = RenombrarLineaValorDeseado(tabla_auxiliar->numCampos, LaGranLinea, tabla_auxiliar->tipos[i], comtok[3], comtok[4], comtok[2], i);
									actualizar_lineas(nombre_bd, LaGranLinea, tabla_auxiliar);
									LaGranLinea = cargar_linea(nombre_bd, tabla_auxiliar->nombre, tabla_auxiliar->numCampos, tabla_auxiliar->tipos);
									break;
								}
                                if(tabla_auxiliar->tipos[i] == TEXT && validardecimal(comtok[3]) == 1)
								{	
									CampoExistente++;
									impr_cabeceras(tabla_auxiliar);
									LaGranLinea = RenombrarLineaValorDeseado(tabla_auxiliar->numCampos, LaGranLinea, tabla_auxiliar->tipos[i], comtok[3], comtok[4], comtok[2], i);
									actualizar_lineas(nombre_bd, LaGranLinea, tabla_auxiliar);
									LaGranLinea = cargar_linea(nombre_bd, tabla_auxiliar->nombre, tabla_auxiliar->numCampos, tabla_auxiliar->tipos);
									break;
								}
								else
								{
									printf("ERROR de tipos\n");
									i++; 
									continue; 
								}
							}
							else
							{
								printf("ERROR de operadores relacionales.\n");
								continue; 
							}
							
						}
						
						if(i+1 == tabla_auxiliar->numCampos)
						{
							printf("ERROR: Campo no encontrado.\n");
							continue; 
						}
						if(CampoExistente == 0)
						{
							printf("ERROR: Campo no existente.\n");
							continue;
						}
					}
				}
				
				
			}

        }

        else if(strcmp(comtok[0], "update") == 0 && strcmp(comtok[1], "table") == 0) {
            if(num_arg != 4){
                printf("ERROR: numero de argumentos introducidos incorrecto");
                continue;
            }

            if(strcmp(prompt, "*") == 0){
                printf("ERROR: no hay una bd activa\n");
                continue;
            }

            if(strcmp(prompt, nombre_bd) == 0){
                printf("ERROR: no hay una tabla cargada\n");
                continue;
            }

            if(validar_caracteres(comtok[2]) != 0){
                printf("ERROR: nombre introducido no valido\n");
                continue;
            }

            if(strcmp(comtok[2], comtok[3]) == 0){
                printf("ERROR: no se puede renonmbrar con el mismo nombre\n");
                continue;
            }

            if(entrar_tabla(nombre_bd, comtok[2]) == 1){
                printf("ERROR: ya existe una tabla con ese nombre\n");
                continue;
            }

            tabla_auxiliar = buscar_tabla(comtok[3], LaGranTabla);
            strcpy(tabla_auxiliar->nombre, comtok[2]);


            if(strcmp(nombre_tabla, comtok[3]) == 0){

                strcpy(prompt, nombre_bd);
                strcpy(nombre_tabla, comtok[2]);
                strcat(prompt, "/");
                strcat(prompt, nombre_tabla);

            }

            char aux1[10] = ".tab";
            char aux2[5] = "\\";
            char aux3[100] = "";
            char aux4[100] = "";

            strcpy(aux3, nombre_bd);
            strcat(aux3, aux2);

            strcpy(aux4, aux3);

            strcat(aux3, comtok[3]);
            strcat(aux3, aux1);

            strcat(aux4, comtok[2]);
            strcat(aux4, aux1);


            if(rename(aux3, aux4) != 0){
                printf("ERROR: se ha producido un error al cambiar el nombre de la tabla\n");
                continue;
            }

            editar_meta(nombre_bd, LaGranTabla);
        }
        else if(strcmp(comtok[0], "update") == 0 && strcmp(comtok[1], "db") == 0){
            if(num_arg != 4){
                printf("ERROR: numero de argumentos introducidos incorrecto");
                continue;
            }

            if(strcmp(prompt, "*") == 0){
                printf("ERROR: no hay una bd activa\n");
                continue;
            }

            printf("%s , %s\n", comtok[2], comtok[3]);
            if(access(comtok[3], F_OK) == 0){ 
                printf("ERROR: Ya existe una db con ese nombre\n");
            }

            if(rename(comtok[2], comtok[3]) != 0){

                printf("ERROR: no se ha podido renombrar la bd\n");
                continue;
            }
            else{
                strcpy(prompt, comtok[3]);
            }
        }
        else if(strcmp(comtok[0], "join") == 0)
		{
			if(num_arg != 3)
			{
				printf("ERROR: Numero de parametros incorrecto.\n");
                continue;
			}
			
			if(strcmp(prompt, "*") == 0)
			{
				printf("Necesitamos una carpeta activa.\n");
				continue;
			}
			
			if(entrar_tabla(nombre_bd, comtok[1]) == 0) 
			{
				printf("ERROR: La primera tabla no existe.\n");
				continue; 
			}
			
			if(entrar_tabla(nombre_bd, comtok[2]) == 0) 
			{
				printf("ERROR: La segunda tabla no existe.\n");
				continue; 
			}
			
			UnirTablas(comtok[1], comtok[2], nombre_bd, LaGranTabla);
			contador++;
			
		}       
        else if(strcmp(comtok[0], "cut") == 0 && strcmp(comtok[1], "table") == 0 && strcmp(comtok[3], "from") == 0) 
		{
            if(num_arg != 5){
                printf("Error numero de argumentos\n");
                continue;
            }
			
			if(strcmp(prompt, "*") == 0)
			{
				printf("Necesitamos una carpeta activa.\n");
				continue;
			}
			
			if(entrar_dir(comtok[4]) == 1) // si no existe la bd de origen //
			{
				printf("ERROR: La bd de origen no existe.\n");
				continue; 
			}
			
			if(strcmp(nombre_bd, comtok[4]) == 0) // Si la base de datos origen se llama igual que la activa //
			{
				printf("ERROR: La bd de origen no se puede llamar igual que la activa.\n");
				continue; 
			}
			
			if(entrar_tabla(comtok[4], comtok[2]) == 0) // Si la tabla de origen no existe //
			{
				printf("ERROR: La tabla de origen no existe.\n");
				continue; 
			}
			
			if(entrar_tabla(nombre_bd, comtok[2]) == 1) // Si la tabla ya existe en el destino
			{
				printf("ERROR: La tabla a copiar ya existe en la base de datos de destino.\n");
				continue; 
			}
			
			TABLE *GranTabla2 = NULL;
			GranTabla2 = cargarTablas(comtok[4]); 
			
			LaGranTabla = seleccionar_tablaBD(comtok[2], comtok[4], nombre_bd, LaGranTabla);
			
			// borramos la tabla
			GranTabla2 = borrar_tabla(GranTabla2, comtok[2]);
		
			// borrar el fichero
			char ruta[100] = "";
			
			strcpy(ruta, comtok[4]);
			strcat(ruta, "\\");
			strcat(ruta, comtok[2]);
			strcat(ruta, ".tab");
			
			remove(ruta);
			
			
			// actualizamos el meta
			editar_meta(comtok[4], GranTabla2);
			
			
		}
        else if(strcmp(comtok[0], "alter") == 0){ // alter clientes EDADES NUM DIRECCION TEXT

            int campo1 = 0;
            int campo2 = 0;

            if(num_arg != 6){
                printf("ERROR: Numero de argumentos incorrecto\n");
                continue;
            }

            if(strcmp(prompt, "*") == 0){

                printf("ERROR: hay una base de datos activa\n");
                continue;
            }

            if(strcmp(prompt, nombre_bd) == 0){
                printf("ERROR: no hay ninguna tabla activa\n");
                continue;
            }

            if(validar_tipo(comtok[5]) == 4 || validar_tipo(comtok[3]) == 4){
                printf("ERROR: No se reconoce el tipo\n");
                continue;
            }


            for(i=0 ; i<tabla_auxiliar->numCampos ; i++){

                if(strcmp(comtok[2], tabla_auxiliar->campos[i]) == 0){

                    campo1++;

                }
                else if(strcmp(comtok[4], tabla_auxiliar->campos[i]) == 0){

                    campo2++;
                }
            }

            if(campo1 != 1 || campo2 != 0){

                printf("Error\n");
                continue;
            }

            for(i=2; i<num_arg; i++){
                aux_enteros = validar_caracteres(comtok[i]); //esto comprueba que en todo el chorizo esta bn escrito todo

                if(aux_enteros>0){
                    printf("Hay algo mal escrito\n");
                    break;
                }
            }

            if(aux_enteros>0){
                continue; // si algo salio mal nos salimos del comando       // alter clientes EDADES NUM DIRECCION TEXT
            }

            LaGranTabla = alter_campos(LaGranTabla, comtok[2], comtok[4], validar_tipo(comtok[3]), validar_tipo(comtok[5]), nombre_tabla, nombre_bd);

            editar_meta(nombre_bd, LaGranTabla);

            LaGranLinea = NULL;

        }
        



*/