#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lib.h"

void mis_datos(){

    printf("Maria Isabel, Salinas Perez\n");
    printf("maria.salinas08@goumh.umh.es\n");

}

int validar_caracteres(char* nombre_bd){
    char cadena[100]="";
    int j = 0, errores = 0;

    strcpy(cadena, nombre_bd); // aqui copiamos en cadena el parametro

    while(cadena[j] != '\0'){ // Aqui vamos recorriendo la cadena caracter a caracter para comprobarlo

        if(cadena[j] == '_'){
            j++;
            continue;
        }
        if(cadena[j]>='0' && cadena[j]<='9'){
            j++;
            continue;
        }
        if(cadena[j]>='a' && cadena[j]<='z'){
            j++;
            continue;
        }
        if(cadena[j]>='A' && cadena[j]<='Z'){
            j++;
            continue;
        }
        errores++;
        break;
    }
    return errores;
}

void crear_bd(char *nombre_bd){
    char aux[15] = "\\meta.db";
    char nombre_aux[50] = "";

    strcpy(nombre_aux, nombre_bd);
    strcat(nombre_aux, aux);
    
    if(access(nombre_bd, F_OK) == 0){ //Si se puede acceder a la carpeta es porque ya existe
        printf("Ya existe una carpeta con ese nombre\n");
    }
    else{
        mkdir(nombre_bd); //Crea carpeta
        crear_meta(nombre_bd, nombre_aux);
        printf("BD creada con exito\n");
    }
}

void crear_meta(char *nombre_bd, char *aux){

    DIR *dir;

    if(dir = opendir(nombre_bd)){

        FILE *fichero;
        fichero = fopen(aux,"w");

        if(fichero != NULL){
            fprintf(fichero, "TABLAS: 0\n");
            fprintf(fichero, "-----------------------------\n");

            fclose(fichero);
        }
        else{
            printf("Algo salio mal");
        }
    }
}

int entrar_dir(char *nombre_bd){
    DIR *dir;
    if(dir = opendir(nombre_bd)){
        return 0;
    }
    else{
        printf("La base de datos %s no existe", nombre_bd);
        return 1;
    }
}

TYPE validar_tipo(char *valor) // Comprueba los tipos introducidos 
{
    if(strcmp(valor, "NUM") == 0){
        return NUM;
    }
    else if(strcmp(valor, "DATE") == 0){
        return DATE;
    }
    else if(strcmp(valor, "EMAIL") == 0){
        return EMAIL;
    }
    else if(strcmp(valor, "TEXT") == 0){
        return TEXT;
    }
    else{
        return ERR;
    }
}

void Trim(char *cad) //ESTA FUNCION QUITA LOS ESPACIOS EN BLANCO
{
	int c, i, j, n=strlen(cad);
	
	if (cad==NULL || n<1)
		return;
	n--;
	while(n>=0 && ((c=cad[n])==' ' || c=='\t' || c=='\n' || c=='\r' || c=='"'))
		n--;
	cad[n+1]='\0';
	i=0;
	while (i<=n && ((c=cad[i])==' ' || c=='\t' || c=='\n' || c=='\r' || c=='"'))
		i++;
	for (j=0 ; j<=n-i+1; j++)
		cad[j]=cad[j+i];
}

int validardecimal(char *cadena){ // DEVUELVE 1 SI CORRECTO
    int i, p=0; // p de punto

    if(cadena[0] == '+' || cadena[0] == '-'){
        i = 1;
    }
    else{
        i=0;
    }

    if(strlen(cadena)==1 && i == 1){ // caso de que solo escribe + o -
        return 0;
    }

    if(strlen(cadena) == 0){
        return 0;
    }

    if(i == 1 && strlen(cadena) == 2 && cadena[1] == '.'){ //caso de +. o -.
        return 0;
    }
    if(strlen(cadena) == 1 && i == 0 && cadena[0] == '.'){ //caso de .
        return 0;
    }

    for(i; i<strlen(cadena); i++){
        
        if(cadena[i]<'0' || cadena[i]>'9'){ 
            
            if(cadena[i] == '.'){
                p++; 
            }
            else{
                return 0;
            }
        }
        if(p==2){ // caso de que se haya introducido mas de una coma
            return 0;
        }
    }

    return 1; 
}

int FechaValidarDMA(char *cadena){ 

    int i, d, m, a;
    
    if(strlen(cadena) != 10){
        return 0;
    }

    for(i = 0; i < 10; i++){

        if(i != 2 && i != 5){

            if(cadena[i]<'0' || cadena[i] > '9'){
                return 0;
            }
        }
    }

    if(cadena[2] != '/' || cadena[5] != '/'){
      
        return 0;
    }

    d=(cadena[0]-'0')*10 +(cadena[1]-'0');
    m=(cadena[3]-'0')*10 +(cadena[4]-'0');
    a=(cadena[6]-'0')*1000 +(cadena[7]-'0')*100+(cadena[8]-'0')*10+ (cadena[9]-'0'); 

    if(d<1 || m<1 || a<1000 || d>31 || m>12 || a>9999){
     
        return 0;
    }
    else if((m == 4 || m == 6 || m == 9 || m == 11) && d>30){
  
        return 0;
    }
    else if( m == 2 && a%4 == 0 && d>29){ // año bisiesto

        return 0;
    }
    else if(m == 2 && a%4!= 0 && d>28 && a%100!= 0 || a%400 == 0){ // año no bisiesto
        return 0;
    }

    return 1;

}


/* **********************   FUNCIONES TABLAS    ************************   */

TABLE* inicializar_tabla(int num_campos, char *nombre_tabla, char **campos, TYPE *tipos)
{
    
    TABLE *tabla = malloc(sizeof(TABLE));// Reservamos memoria para una tabla

    if(tabla == NULL){
        return NULL;
    }
    strcpy(tabla->nombre, nombre_tabla);
    tabla->numCampos = num_campos;
    tabla->campos = campos;
    tabla->tipos = tipos;
    tabla->ant = NULL;
    tabla->sig = NULL;

    return tabla;
}

void crear_tabla_tab(TABLE *tabla, char *nombre_bd, char *nombre_tabla)
{
    char aux1[5] = ".tab";
    char aux2[5] = "\\";
    char aux3[100] = "";

    strcpy(aux3, nombre_bd);
    strcat(aux3, aux2);
    strcat(aux3,nombre_tabla);
    strcat(aux3, aux1);

    if(access(aux3, F_OK) == 0){

        printf("La tabla %s ya existe\n", nombre_tabla);

    }
    else{

        DIR *dir;
        if(dir = opendir(nombre_bd)){

            FILE *fichero;
            fichero = fopen(aux3, "w");

            if(fichero != NULL){
                editar_meta(nombre_bd, tabla);
            }
            fclose(fichero);
        }
        else{
            printf("Algo salio mal\n");
        }
    }
}

void editar_meta(char *nombre_bd, TABLE *tabla){

    DIR *dir;

    char aux1[11] = "\\meta.db";
    char aux2[100] = "";
    char aux_tipos[50] = "";
    int num_tablas = 0, i;

    strcpy(aux2, nombre_bd);
    strcat(aux2, aux1);

    num_tablas = contar_tablas(nombre_bd);

    if(dir = opendir(nombre_bd)){
        FILE *fichero;
        fichero = fopen(aux2, "w");

        if(fichero != NULL){

            fprintf(fichero, "TABLAS: %d\n", num_tablas);
            fprintf(fichero, "---------------------\n");

            while (tabla != NULL)
            {
                fprintf(fichero, "%s: %d\n", tabla->nombre, tabla->numCampos);

                for(i=0; i < tabla->numCampos; i++){
                    if(tabla->tipos[i] == 0){
    
                        strcpy(aux_tipos, "NUM");
                    }
                    else if(tabla->tipos[i] == 1){
                        
                        strcpy(aux_tipos, "DATE");
                    }
                    else if(tabla->tipos[i] == 2){
                        
                        strcpy(aux_tipos, "EMAIL");
                    }
                     else if(tabla->tipos[i] == 3){
                        
                        strcpy(aux_tipos, "TEXT");
                    }

                    fprintf(fichero, "%s: %s \n", tabla->campos[i], aux_tipos);
                }

                if(tabla->sig == NULL){
                    break;
                }

                fprintf(fichero, "---------------------\n");
                tabla = tabla->sig;

            }
            
        }

        fclose(fichero);
    }
}

int contar_tablas(char *nombre_bd){

    DIR *dir;
    struct dirent *f; //habilita trabajar con los ficheros de la carpeta
    int num = 0;

    if(dir = opendir(nombre_bd)){
        while(f = readdir(dir)){
            num++;
        }
    }

    num = num - 3;
    return num;
}

void insertar_tabla(TABLE *LaGranTabla, TABLE *tabla_auxiliar){

    TABLE *LaGranTabla_aux;

    LaGranTabla_aux = LaGranTabla;

    while(LaGranTabla_aux->sig != NULL){
        LaGranTabla_aux = LaGranTabla_aux->sig;
    }

    LaGranTabla_aux->sig = tabla_auxiliar;
    tabla_auxiliar->ant = LaGranTabla_aux;
}

int ver_duplicados(char **cadena, int num_arg)//Comprueba que no se repitan los campos de una misma tabla
{
    int i,j;

    for(i=0; i < num_arg; i++){
        for (j= i+1; j<num_arg; j++){
            if(strcmp(cadena[i], cadena[j]) == 0){
                printf("No se pueden repetir los campos\n");
                return 1;
            }
        }
    }
    return 0;
}

int entrar_tabla(char *nombre_db, char *nombre_tabla)
{
    DIR *dir;
    char aux1[10] = ".tab";
    char aux2[5] = "\\";
    char aux3[100] = "";

    strcpy(aux3, nombre_db);
    strcat(aux3, aux2);
    strcat(aux3, nombre_tabla);
    strcat(aux3, aux1);

    printf("%s\n", aux3);

    if(access(aux3, F_OK) == 0){
        if(dir = opendir(nombre_db)){
            return 1;
        }
    }
    else{
        return 0;
    }
}

char *ObtenerCampo(char *lin, char *sep, int id, char *val){
    
    int i, tamSep = 1;
    char *p1, *p2;

    if(lin == NULL || lin[0] == '\0'){
        return NULL;
    }

    p1 = lin;

    p2 = strstr(lin, sep);

    for(i=0; i<id; i++){
        p1 = p2+tamSep;
        p2 = strstr(p1, sep);
    }

    if(p2 == NULL){
        strcpy(val, p1);
    }
    else{
        strncpy(val, p1, p2-p1);
        val[p2-p1] = '\0';
    }

    return val;
}

char *MiStrTok(char *chorizo, char *sep, int comillas){ //si comillas activadas = 1 y si comillas desactivadas = 0

    static char *pt1 = NULL;
    static char *pt2 = NULL;
    static char *ptFinal;

    if(chorizo != NULL){
        pt1 = chorizo;
        ptFinal = pt1 + strlen(chorizo);
    }
    else{
        pt1 = pt2+1;
    }

    if(comillas == 1){

        while(pt1[0] != '\0' && pt1 < ptFinal && strchr(sep, pt1[0]) != NULL && pt1[0] != '"'){
            pt1++;
        }

        if(pt1[0] == '"'){
            pt1++;
            pt2 = pt1+1;
            while(pt2[0] != '\0' && pt2[0] != '"'){
                
                pt2++;
            }

            if(pt2[0] == '\0'){
                pt1 = pt2 = ptFinal = NULL;
                return NULL;

            }
            else{
                pt2[0]='\0';
                return pt1;
            }





        }
    }
    else{

        while(pt1[0] != '\0' && pt1<ptFinal && strchr(sep, pt1[0]) != NULL){
            pt1++;
        }
    }

    if(pt1>=ptFinal){
        pt1 = pt2 = ptFinal = NULL;
        return NULL;
    }

    pt2 = pt1 +1;

    while(pt2[0] != '\0' && strchr(sep, pt2[0]) == NULL){
        pt2++;
    }

    pt2[0]='\0';

    return pt1;

}

TABLE *buscar_tabla(char *nombre_tabla, TABLE *tabla){

    TABLE *tabla2 = tabla;

    if(tabla2 != NULL){

        while(tabla2 != NULL){
            if(strcmp(tabla2->nombre, nombre_tabla) == 0){
                return tabla2;
            }

            tabla2 = tabla2->sig;
        }
    }
    else{
        return tabla2;
    }
}

TABLE *cargarTablas(char *nombre_bd){

    TABLE *tabla=NULL, *tablanueva;
    FILE *meta;
    char aux1[11]="\\meta.db";
    char aux2[50]="";
    char aux3[50]="";
    char linea[1000],val[100];
    int num_tabla,num_campos, i, j;
    char *nombre_tabla;
    char **nombre_campo;
    TYPE *tipos; 
    

    strcpy(aux2,nombre_bd);
    strcat(aux2,aux1);

    meta = fopen(aux2, "r"); // abrimos el meta en modo lectura
    if(meta == NULL){
        printf("ERROR inesperado");
        return 0;
    }
    fgets(linea,1000,meta); // leemos los primeros mil caracteres de una linea
    ObtenerCampo(linea,":",1,val); // optenemos el valor del campo 1
    Trim(val);                  // le quitamos los espacios al valor
    num_tabla = atoi(val);      // lo convertimos a numero

    for(i=0; i<num_tabla;i++){ // vamos a hacer este proceso tantas veces como tablas tengamos en el meta

        fgets(linea,1000,meta); // IGNORAMOS LOS GUIONES DEL META
        fgets(linea,1000,meta); // cogemos la linea del nombre de la tabla y num de campos. "CANDELA: 2"
        ObtenerCampo(linea, ":", 0,val); // cogemos el primer valor de la linea hasta los dos puntos "CANDELA"
        Trim(val);                  // Quita los espacios
        nombre_tabla=strdup(val);   // apuntamos nombre_tabla al valor de val
        ObtenerCampo(linea,":",1,val); // cogemos el numero de campos "2"
        Trim(val);                  //quita los espacios
        num_campos=atoi(val);       // convertimos a numero el valor de numcampos "2" 

        nombre_campo = malloc(sizeof(char*)*num_campos); // reservamos memoria tipo puntero para los parametros
        tipos = malloc(sizeof(TYPE*)*num_campos); //Reservmos memoria para los tipos
        
        for(j=0;j<num_campos;j++){ // lo vamos a hacer por cada columna de la tabla
            fgets(linea,1000,meta); // cogemos la linea
            ObtenerCampo(linea,":",0,val);  // vemos el nombre del campo
            Trim(val);
            nombre_campo[j]=strdup(val); // lo copiamos en la caja de nombre_campo que es un puntero doble
            ObtenerCampo(linea,":",1,val); // cogemos el tipo
            Trim(val);
            tipos[j]=validar_tipo(val); // lo metemos en la caja de tipos

        }

        tablanueva = inicializar_tabla(num_campos,nombre_tabla, nombre_campo, tipos); // creamos la tabla

        if(tabla==NULL){ // si es la primera tabla
            tabla=tablanueva;
                    
        }
        else{ // sino la insertamos la ultima
            insertar_tabla(tabla, tablanueva);          
        }

    }
    fclose(meta); // cerramos el meta
    return tabla;
}

void liberar_memoria_tablas(TABLE *LaGranTabla){

    TABLE *tabla_sig;
    int i;

    if(LaGranTabla == NULL){
        return;
    }

    while(LaGranTabla != NULL){
        
        tabla_sig = LaGranTabla->sig;

        for(i=0; i<LaGranTabla->numCampos; i++){
            free(LaGranTabla->campos[i]);
        }

        free(LaGranTabla->campos);
        free(LaGranTabla->tipos);
        free(LaGranTabla);

        LaGranTabla = tabla_sig;

    }
}


/* **********************   FUNCIONES LINEAS    ************************   */

ROW *inicializar_linea(char **valores){

    ROW *linea = malloc(sizeof(ROW));

    if(linea == NULL){
        return NULL;
    }

    linea->valores = valores;
    linea->sig = NULL;
    linea->ant = NULL;

    return linea;

}

void insertar_ultima_linea(ROW *LaGranLinea, ROW *linea_auxiliar){
    ROW *LaGranLinea2 = LaGranLinea;

    while(LaGranLinea2->sig != NULL){
        LaGranLinea2 = LaGranLinea2->sig;
    }

    LaGranLinea2->sig = linea_auxiliar;
    linea_auxiliar->ant = LaGranLinea2;
    linea_auxiliar->sig = NULL;
}

void actualizar_lineas(char *nombre_db, ROW *linea, TABLE *tabla){

    DIR *dir;

    char aux1[11] = ".tab";
    char aux2[50] = "\\";
    char aux3[50] = "";

    strcpy(aux3, nombre_db);
    strcat(aux3, aux2);
    strcat(aux3, tabla->nombre);
    strcat(aux3, aux1);


    if(dir = opendir(nombre_db)){

        FILE *fichero;
        fichero = fopen(aux3, "w");

        if(fichero != NULL){

            //escribir todas las lineas
            while(linea != NULL){

                for(int i = 0; i<tabla->numCampos ; i++){ 

                    if(tabla->tipos[i] == TEXT && i == tabla->numCampos-1){ 
                        fprintf(fichero, "\"%s\"\n", linea->valores[i]);
                    }
                    else if( tabla->tipos[i] == TEXT){
                        fprintf(fichero, "\"%s\", ", linea->valores[i]);
                    }
                    else if(tabla->numCampos-1 == i){
                        fprintf(fichero, "%s\n", linea->valores[i]);
                    }
                    else{
                        fprintf(fichero, "%s, ", linea->valores[i]);
                    }
                }

                if(linea->sig == NULL){
                    break;
                }

                linea = linea->sig;
            }
            
            fclose(fichero);
        }
        else{
            printf("algo salio mal\n");
        }

    }
    else{
        printf("Extraño caso no nos deja entrar a la carpeta\n");
    }


}

ROW *cargar_linea(char *nombre_db, char *nombre_tabla ,int num_campos,  TYPE* tipos){

    char aux1[5]=".tab";
    char aux2[5]="\\";
    char aux3[100]="";
    FILE *fichero;
    char linea[1000];
    int i,comillas;
    long final;
    char *token, *lineaaux;
    char **valores;
    ROW *fila = NULL, *filanueva;

    strcpy(aux3,nombre_db);
    strcat(aux3,aux2);
    strcat(aux3,nombre_tabla);
    strcat(aux3,aux1);

    if(access(aux3,F_OK) == 0 ){ // si podemos acceder a la ruta entramos

        fichero = fopen(aux3, "r"); // abrimos el fichero en modo lectura

        fseek( fichero, 0, SEEK_END ); // situa el cursor en la ultima posicion

        if (ftell( fichero ) == 0 ) // dime donde esta el cursor en el fichero, y si esta en la posicion 0 entramos
        {
            fclose(fichero);
            return fila;
        }

        final=ftell(fichero); // dime donde esta la posicion del fichero
        fseek(fichero,0,SEEK_SET); // mueve el cursor al principio del fichero, es decir, a la posicion 0


        while(final != ftell(fichero)){ // mientras el cursor no llegue al final del fichero

            fgets(linea,1000,fichero); // cogemos la linea

            valores = malloc(sizeof(char*)*num_campos); //  reservamos memoria del tamanyo de los num_campos

            for(i=0;i<num_campos;i++){
             
                comillas = (tipos[i] == TEXT); // si hay un campo de tipo texto comillas valdra 1
            
                if(i == 0){
                    lineaaux = linea;
                }
                else{
                    lineaaux = NULL;
                }
                token = MiStrTok(lineaaux,",\n",comillas); //dividimos la linea en tokens con las comillas activadas
                valores[i]=strdup(token);
                Trim(valores[i]);
            }

            filanueva = inicializar_linea(valores); //creamos la estructura de la linea

            if(fila==NULL){ // si es la primera linea
                fila=filanueva;       
            }
            else{
                insertar_ultima_linea(fila, filanueva); // insertamos la linea la ultima  
            }
        }                 
    }
    else{
        printf("ERROR inesperado");
        return 0;
    }

    fclose(fichero);
    return fila;
}

void liberar_memoria_lineas(ROW *LaGranLinea, int numCampos){
    ROW *linea_sig;
    int i;

    if(LaGranLinea == NULL){
        return;
    }
    else{
        linea_sig = LaGranLinea->sig;

        for(i=0; i<numCampos; i++){
             free(LaGranLinea->valores[i]);
        }

        free(LaGranLinea->valores); // liberamos la caja de valores
        free(LaGranLinea); //liberamos la linea
        
        LaGranLinea = linea_sig;
    }
}


void impr_cabeceras(TABLE *tabla){
    int i;

    for(i = 0; i < tabla->numCampos; i++){
        printf("%s,\t", tabla->campos[i]);
    }

    printf("\n");
}

void impr_todo(ROW *LaGranLinea, int numcampos){

    int i, contador = 1;
    ROW *linea = LaGranLinea;

    if(linea == NULL){
        printf("No hay datos en la tabla introducida\n");
    }
    else{

        while(linea != NULL){
            printf("%d - ", contador);
            for(i = 0; i< numcampos-1; i++){
                printf("%s, ", linea->valores[i]);

            }
            printf("%s\n", linea->valores[numcampos-1]);
            contador++;

            linea = linea->sig;

        }
    }
}

void impr_todo_ASC(ROW *LaGranLinea, int numcampos, TABLE *tabla){

    int i, contador = 1;
    ROW *linea = LaGranLinea;

    if(linea == NULL){
        printf("No hay datos en la tabla");
    }
    else{

        ordenar_asc(linea, tabla, 0);

        while(linea != NULL){
            printf("%d - ", contador);
            for(i = 0; i< numcampos-1; i++){
                printf("%s, ", linea->valores[i]);

            }
            printf("%s \n", linea->valores[numcampos-1]);
            contador++;

            linea = linea->sig;

        }
    }
}

void impr_todo_DES(ROW *LaGranLinea, int numcampos, TABLE *tabla){

    printf("Imprimir todo DES");
    int i, contador=1;
    ROW *linea_auxiliar = LaGranLinea;

    if(linea_auxiliar == NULL){
        printf("No hay datos en la tabla\n");
    }
    else{

        //Ordenar des
        ordenar_des(LaGranLinea, tabla, 0);

        while(linea_auxiliar != NULL){

            printf("%d - ", contador);

            for(i=0; i<numcampos-1; i++){
                printf("%s, ", linea_auxiliar->valores[i]);
            }

            printf("%s\n", linea_auxiliar->valores[numcampos-1]);

            contador++;

            linea_auxiliar = linea_auxiliar->sig;
        }
    }

}

void ordenar_asc(ROW *LaGranLinea, TABLE *tabla_aux, int orden_campo){

    ROW *i, *j;

    if(tabla_aux->tipos[orden_campo] == NUM){
        for(i=LaGranLinea; i != NULL; i = i->sig){
            for(j=i; j != NULL; j = j->sig){
                
                if(atof(i->valores[orden_campo]) > atof(j->valores[orden_campo])){
                    
                    intercambiar_valores(i, j);
                }
            }
        }
    }
    if(tabla_aux->tipos[orden_campo] == DATE){
        for(i=LaGranLinea; i != NULL; i = i->sig){
            for(j=i; j != NULL; j = j->sig){
                
                if(Fecha_a_numero(i->valores[orden_campo]) > Fecha_a_numero(i->valores[orden_campo])){

                    intercambiar_valores(i, j);
                }
            }
        }
    }
    if(tabla_aux->tipos[orden_campo] == TEXT){
        for(i=LaGranLinea; i != NULL; i = i->sig){
            for(j=i; j != NULL; j = j->sig){
                
                if(strcmp(i->valores[orden_campo], j->valores[orden_campo])>0){
                    intercambiar_valores(i, j);
                }
            }
        }
    }
}

void ordenar_des(ROW *LaGranLinea, TABLE *tabla_aux, int orden_campo){
    ROW *i, *j;

    if(tabla_aux->tipos[orden_campo] == NUM){
        for(i=LaGranLinea; i != NULL; i = i->sig){
            
            for(j=i; j != NULL; j = j->sig){
        
                if(atof(i->valores[orden_campo]) < atof(j->valores[orden_campo])){
                    
                    intercambiar_valores(i, j);
                }
            }
        }
    }
    else if(tabla_aux->tipos[orden_campo] == DATE){
        for(i=LaGranLinea; i != NULL; i = i->sig){

            for(j=i; j != NULL; j = j->sig){
                if(Fecha_a_numero(i->valores[orden_campo]) < Fecha_a_numero(i->valores[orden_campo])){
                    
                    intercambiar_valores(i, j);
                }
            }
        }
    }
    else if(tabla_aux->tipos[orden_campo] == TEXT){
        for(i=LaGranLinea; i != NULL;i = i->sig){

            for(j=i; j != NULL; j = j->sig){
                if(strcmp(i->valores[orden_campo], j->valores[orden_campo]) < 0){
                    
                    intercambiar_valores(i, j);
                }
            }
        }
    }
}

void intercambiar_valores(ROW *i, ROW *j){
    char **lineaux;

    lineaux = i->valores;
    i->valores = j->valores;
    j->valores = lineaux;

}

int Fecha_a_numero(char *cad){
    int res, dia, mes, anyo;
	dia=(cad[0]-'0')*10 +(cad[1]-'0');
    mes=(cad[3]-'0')*10 +(cad[4]-'0');
    anyo=(cad[6]-'0')*1000 +(cad[7]-'0')*100+(cad[8]-'0')*10+ (cad[9]-'0');
	res=dia;

	if (mes==1)
		res=res;
	else if (mes==2)
		res=res+31;
	else if (mes==3 && (anyo%4)!=0)
		res=res+59;
	else if (mes==3 && (anyo%4)==0)
		res=res+60;
	else if (mes==4 && (anyo%4)!=0)
		res=res+90;
	else if (mes==4 && (anyo%4)==0)
		res=res+91;
	else if (mes==5 && (anyo%4)!=0)
		res=res+120;
	else if (mes==5 && (anyo%4)==0)
		res=res+121;
	else if (mes==6 && (anyo%4)!=0)
		res=res+151;
	else if (mes==6 && (anyo%4)==0)
		res=res+152;
	else if (mes==7 && (anyo%4)!=0)
		res=res+181;
	else if (mes==7 && (anyo%4)==0)
		res=res+182;
	else if (mes==8 && (anyo%4)!=0)
		res=res+212;
	else if (mes==8 && (anyo%4)==0)
		res=res+213;
	else if (mes==9 && (anyo%4)!=0)
		res=res+243;
	else if (mes==9 && (anyo%4)==0)
		res=res+244;
	else if (mes==10 && (anyo%4)!=0)
		res=res+273;
	else if (mes==10 && (anyo%4)==0)
		res=res+274;
	else if (mes==11 && (anyo%4)!=0)
		res=res+304;
	else if (mes==11 && (anyo%4)==0)
		res=res+305;
	else if (mes==12 && (anyo%4)!=0)
		res=res+334;
	else if (mes==12 && (anyo%4)==0)
		res=res+335;

	res=(res+(anyo-1)*365);
	res=(res+(anyo-1)/4);


	return res;
}

void imprimir_valor_campo(int numcampos, ROW *LaGranLinea, TYPE tipo, char *valor, char *simbolo, int posicion){
    int i, contador = 1;
    ROW *linea_auxiliar = LaGranLinea;


    if(linea_auxiliar == NULL){
        printf("No hay datos en la tabla\n");
    }
    else{
        if(tipo == NUM){
            if(strcmp(simbolo, "=") == 0){
                while(linea_auxiliar != NULL){
                    if(atof(valor) == atof(linea_auxiliar->valores[posicion])){
                        printf("%d - ", contador);

                        for(i = 0; i<numcampos-1; i++ ){
                            printf("%s, ", linea_auxiliar->valores[i]);
                        }

                        printf("%s\n", linea_auxiliar->valores[numcampos-1]);

                        contador++;
                    }

                    linea_auxiliar = linea_auxiliar->sig;
                }

                if(contador == 1){
                    printf("No hay datos para mostrar\n");
                }
            }
            else if(strcmp(simbolo,">") == 0){
                while(linea_auxiliar != NULL){
                    if(atof(valor) > atof(linea_auxiliar->valores[posicion])){
                        printf("%d - ", contador);

                        for(i = 0; i<numcampos-1; i++ ){
                            printf("%s, ", linea_auxiliar->valores[i]);
                        }

                        printf("%s\n", linea_auxiliar->valores[numcampos-1]);

                        contador++;
                    }

                    linea_auxiliar = linea_auxiliar->sig;
                }

                if(contador == 1){
                    printf("No hay datos para mostrar\n");
                }
            }
            else if(strcmp(simbolo, "<") == 0){
                while(linea_auxiliar != NULL){
                    if(atof(valor) < atof(linea_auxiliar->valores[posicion])){
                        printf("%d - ", contador);

                        for(i = 0; i<numcampos-1; i++ ){
                            printf("%s, ", linea_auxiliar->valores[i]);
                        }

                        printf("%s\n", linea_auxiliar->valores[numcampos-1]);

                        contador++;
                    }

                    linea_auxiliar = linea_auxiliar->sig;
                }

                if(contador == 1){
                    printf("No hay datos para mostrar\n");
                }
            }
            else{
                printf("Error con los simbolos\n");
                return;
            }
        }
        else if(tipo == DATE){
            if(strcmp(simbolo, "=") == 0){
                while(linea_auxiliar != NULL){
                    if(Fecha_a_numero(valor) == Fecha_a_numero(linea_auxiliar->valores[posicion])){
                        printf("%d - ", contador);

                        for(i = 0; i<numcampos-1; i++ ){
                            printf("%s, ", linea_auxiliar->valores[i]);
                        }

                        printf("%s\n", linea_auxiliar->valores[numcampos-1]);

                        contador++;
                    }

                    linea_auxiliar = linea_auxiliar->sig;
                }

                if(contador == 1){
                    printf("No hay datos para mostrar\n");
                }
            }
            else if(strcmp(simbolo,">") == 0){
                while(linea_auxiliar != NULL){
                    if(Fecha_a_numero(valor) > Fecha_a_numero(linea_auxiliar->valores[posicion])){
                        printf("%d - ", contador);

                        for(i = 0; i<numcampos-1; i++ ){
                            printf("%s, ", linea_auxiliar->valores[i]);
                        }

                        printf("%s\n", linea_auxiliar->valores[numcampos-1]);

                        contador++;
                    }

                    linea_auxiliar = linea_auxiliar->sig;
                }

                if(contador == 1){
                    printf("No hay datos para mostrar\n");
                }
            }
            else if(strcmp(simbolo, "<") == 0){
                while(linea_auxiliar != NULL){
                    if(Fecha_a_numero(valor) < Fecha_a_numero(linea_auxiliar->valores[posicion])){
                        printf("%d - ", contador);

                        for(i = 0; i<numcampos-1; i++ ){
                            printf("%s, ", linea_auxiliar->valores[i]);
                        }

                        printf("%s\n", linea_auxiliar->valores[numcampos-1]);

                        contador++;
                    }

                    linea_auxiliar = linea_auxiliar->sig;
                }

                if(contador == 1){
                    printf("No hay datos para mostrar\n");
                }
            }
            else{
                printf("Error con los simbolos\n");
                return;
            }
        }
        else if(tipo == TEXT){
            if(strcmp(simbolo, "=") == 0){
                
                while(linea_auxiliar != NULL){
                    if(strcmp(valor, linea_auxiliar->valores[posicion]) == 0){
                        printf("%d - ", contador);

                        for(i = 0; i<numcampos-1; i++ ){
                            printf("%s, ", linea_auxiliar->valores[i]);
                        }

                        printf("%s\n", linea_auxiliar->valores[numcampos-1]);

                        contador++;
                    }

                    linea_auxiliar = linea_auxiliar->sig;
                }

                if(contador == 1){
                    printf("No hay datos para mostrar\n");
                }
            }
            else if(strcmp(simbolo,">") == 0){
                while(linea_auxiliar != NULL){
                    if(strcmp(valor, linea_auxiliar->valores[posicion]) > 0){
                        printf("%d - ", contador);

                        for(i = 0; i<numcampos-1; i++ ){
                            printf("%s, ", linea_auxiliar->valores[i]);
                        }

                        printf("%s\n", linea_auxiliar->valores[numcampos-1]);

                        contador++;
                    }

                    linea_auxiliar = linea_auxiliar->sig;
                }

                if(contador == 1){
                    printf("No hay datos para mostrar\n");
                }
            }
            else if(strcmp(simbolo, "<") == 0){
                while(linea_auxiliar != NULL){
                    if(strcmp(valor, linea_auxiliar->valores[posicion]) < 0){
                        printf("%d - ", contador);

                        for(i = 0; i<numcampos-1; i++ ){
                            printf("%s, ", linea_auxiliar->valores[i]);
                        }

                        printf("%s\n", linea_auxiliar->valores[numcampos-1]);

                        contador++;
                    }

                    linea_auxiliar = linea_auxiliar->sig;
                }

                if(contador == 1){
                    printf("No hay datos para mostrar\n");
                }
            }
            else{
                printf("Error con los simbolos\n");
                return;
            }
        }
    }
}


/* -----------------------  DICIEMBRE -----------------------------*/

void mostrar_tablas(TABLE *LaGranTabla){

    TABLE *tabla_aux = LaGranTabla;

    int num_tablas = 0;

    while(tabla_aux != NULL){
        num_tablas++;

        printf("%s\n", tabla_aux->nombre);

        if(tabla_aux->sig == NULL){
            break;
        }

        tabla_aux = tabla_aux->sig;
    }

    if(num_tablas == 0){
        printf("No hay tablas en la bd activa\n");
    }

}

void mostrar_bd(){
    DIR *d;
    struct dirent *f;
    int j=0;

    d = opendir(".");

    if(d == NULL){
        printf("No hay bases de datos disponibles\n");
    }
    else{

        while((f = readdir(d)) != NULL){

            if(strcmp(f->d_name, ".") != 0 && strcmp(f->d_name, "..") != 0){

                if(validar_caracteres_bd(f->d_name) == 0){

                    printf("%s\n", f->d_name);
                    j++;

                }
            }
        }

        if(j==0){
            printf("No hay bases de datos disponibles\n");
        }

    }

    closedir(d);
}

int validar_caracteres_bd(char *nombre_bd){

    char copia[100] = "";
    int j = 0, errores = 0;

    strcpy(copia, nombre_bd);

    while(copia[j] != '\0'){

        if(copia[j] != '.'){
            j++;
        }
        else{
            errores++;
            break;
        }
    }

    return errores;

}

int validar_email(char *email){ //devuelve 1 error devuelve 0 correcto

    char copia[100] = "";
    int i = 0, errores = 0, punto = 0, arroba = 0;

    strcpy(copia, email);

    int g = strlen(copia);

    if(g < 5){
        return 1;
    }

    if(copia[g-1] == '.'){
        return 1;
    }

    if(copia[0] == '.' || copia[0] == '@'){
        errores++;
        return errores;

    }

    while(copia[i] != '\0'){

        if(copia[i] >= 'a' && copia[i] <= 'z'){
            i++;
        }
        else if(copia[i] >= 'A' && copia[i] <= 'Z'){
            i++;
        }
        else if(copia[i] >= '0' && copia[i] <= '9'){
            i++;
        }
        else if(copia[i] == '.' && punto < 1){
            if(arroba == 0){
                errores ++;
                return errores;
            }
            i++;
            punto++;
        }
        else if(copia[i] == '@' && arroba < 1){

            if(punto != 0){

                errores++;
                return errores;
            }

            i++;
            arroba++;
        }
        else{
            errores++;
            return errores;
        }
    }

    if(errores != 0 || arroba != 1 || punto != 1){
        return 1;
    }

    return errores;
}

ROW *borrarLinea(int numcampos, ROW *linea, TYPE tipo, char *valor, char *simbolo, int posicion){

    int i, k;
    ROW *lineaux = linea, *lineasiguiente, *lineaanterior;

    if(linea == NULL){
        printf("No hay valores a borrar\n");
    }
    else{
        if(tipo == NUM){
          if(strcmp(simbolo, "=") == 0){

                while(lineaux != NULL){

                    lineasiguiente = lineaux->sig;
                    lineaanterior = lineaux->ant;

                    if(atof(valor) == atof(lineaux->valores[posicion])){

                        if(lineaux == linea && lineaux->sig == NULL){ //SER EL UNICO VALOR
                            linea = NULL;
                        }
                        else if(lineaux == linea && lineaux->ant == NULL){ //SER EL PRIMER VALOR
                            linea = lineaux->sig;
                            lineasiguiente->ant = NULL;
                            lineaux->sig = NULL;
                        }
                        else if(lineaux->sig == NULL){ // SER EL ULTIMO VALOR
                            lineaanterior->sig = NULL;
                            lineaux->ant = NULL;
                        }
                        else{ // SER UN VALOR DE EN MEDIO

                            lineaanterior->sig = lineaux->sig; //lineasiguiente
                            lineasiguiente->ant = lineaux->ant; // lineanterior
                        }
                        
                        //FREE

                        for(i=0; i<numcampos; i++){
                            free(lineaux->valores[i]);
                        }

                        free(lineaux->valores);
                        free(lineaux);

                    }

                    lineaux = lineasiguiente;

                }

                return linea;

            }
            else if(strcmp(simbolo, "<") == 0){

                while(lineaux != NULL){

                    lineasiguiente = lineaux->sig;
                    lineaanterior = lineaux->ant;

                    if(atof(valor) > atof(lineaux->valores[posicion])){

                        if(lineaux == linea && lineaux->sig == NULL){ //SER EL UNICO VALOR
                            linea = NULL;
                        }
                        else if(lineaux == linea && lineaux->ant == NULL){ //SER EL PRIMER VALOR
                            linea = lineaux->sig;
                            lineasiguiente->ant = NULL;
                            lineaux->sig = NULL;
                        }
                        else if(lineaux->sig == NULL){ // SER EL ULTIMO VALOR
                            lineaanterior->sig = NULL;
                            lineaux->ant = NULL;
                        }
                        else{ // SER UN VALOR DE EN MEDIO

                            lineaanterior->sig = lineaux->sig; //lineasiguiente
                            lineasiguiente->ant = lineaux->ant; // lineanterior
                        }
                        
                        //FREE

                        for(i=0; i<numcampos; i++){
                            free(lineaux->valores[i]);
                        }

                        free(lineaux->valores);
                        free(lineaux);

                    }

                    lineaux = lineasiguiente;

                }

                return linea;

            }
            else if(strcmp(simbolo, ">") == 0){

                while(lineaux != NULL){

                    lineasiguiente = lineaux->sig;
                    lineaanterior = lineaux->ant;

                    if(atof(valor) < atof(lineaux->valores[posicion])){

                        if(lineaux == linea && lineaux->sig == NULL){ //SER EL UNICO VALOR
                            linea = NULL;
                        }
                        else if(lineaux == linea && lineaux->ant == NULL){ //SER EL PRIMER VALOR
                            linea = lineaux->sig;
                            lineasiguiente->ant = NULL;
                            lineaux->sig = NULL;
                        }
                        else if(lineaux->sig == NULL){ // SER EL ULTIMO VALOR
                            lineaanterior->sig = NULL;
                            lineaux->ant = NULL;
                        }
                        else{ // SER UN VALOR DE EN MEDIO

                            lineaanterior->sig = lineaux->sig; //lineasiguiente
                            lineasiguiente->ant = lineaux->ant; // lineanterior
                        }
                        
                        //FREE

                        for(i=0; i<numcampos; i++){
                            free(lineaux->valores[i]);
                        }

                        free(lineaux->valores);
                        free(lineaux);

                    }

                    lineaux = lineasiguiente;

                }

                return linea;

            }else{
                printf("ERROR: operador introducido no reconocido");
            }
        }
        else if(tipo == DATE){

            if(strcmp(simbolo, "=") == 0){

                while(lineaux != NULL){

                    lineasiguiente = lineaux->sig;
                    lineaanterior = lineaux->ant;

                    if(Fecha_a_numero(valor) == Fecha_a_numero(lineaux->valores[posicion])){

                        if(lineaux == linea && lineaux->sig == NULL){ //SER EL UNICO VALOR
                            linea = NULL;
                        }
                        else if(lineaux == linea && lineaux->ant == NULL){ //SER EL PRIMER VALOR
                            linea = lineaux->sig;
                            lineasiguiente->ant = NULL;
                            lineaux->sig = NULL;
                        }
                        else if(lineaux->sig == NULL){ // SER EL ULTIMO VALOR
                            lineaanterior->sig = NULL;
                            lineaux->ant = NULL;
                        }
                        else{ // SER UN VALOR DE EN MEDIO

                            lineaanterior->sig = lineaux->sig; //lineasiguiente
                            lineasiguiente->ant = lineaux->ant; // lineanterior
                        }

                        for(i=0; i<numcampos; i++){
                            free(lineaux->valores[i]);
                        }

                        free(lineaux->valores);
                        free(lineaux);
                    }

                    lineaux = lineasiguiente;
                }

                return linea;
            }
            else if(strcmp(simbolo,">") == 0){
                while(lineaux != NULL){

                    lineasiguiente = lineaux->sig;
                    lineaanterior = lineaux->ant;

                    if(Fecha_a_numero(valor) < Fecha_a_numero(lineaux->valores[posicion])){

                        if(lineaux == linea && lineaux->sig == NULL){ //SER EL UNICO VALOR
                            linea = NULL;
                        }
                        else if(lineaux == linea && lineaux->ant == NULL){ //SER EL PRIMER VALOR
                            linea = lineaux->sig;
                            lineasiguiente->ant = NULL;
                            lineaux->sig = NULL;
                        }
                        else if(lineaux->sig == NULL){ // SER EL ULTIMO VALOR
                            lineaanterior->sig = NULL;
                            lineaux->ant = NULL;
                        }
                        else{ // SER UN VALOR DE EN MEDIO

                            lineaanterior->sig = lineaux->sig; //lineasiguiente
                            lineasiguiente->ant = lineaux->ant; // lineanterior
                        }
                        
                        //FREE

                        for(i=0; i<numcampos; i++){
                            free(lineaux->valores[i]);
                        }

                        free(lineaux->valores);
                        free(lineaux);

                    }

                    lineaux = lineasiguiente;

                }

                return linea;
            }
            else if(strcmp(simbolo, "<") == 0){
                while(lineaux != NULL){

                    lineasiguiente = lineaux->sig;
                    lineaanterior = lineaux->ant;

                    if(Fecha_a_numero(valor) > Fecha_a_numero(lineaux->valores[posicion])){

                        if(lineaux < linea && lineaux->sig == NULL){ //SER EL UNICO VALOR
                            linea = NULL;
                        }
                        else if(lineaux == linea && lineaux->ant == NULL){ //SER EL PRIMER VALOR
                            linea = lineaux->sig;
                            lineasiguiente->ant = NULL;
                            lineaux->sig = NULL;
                        }
                        else if(lineaux->sig == NULL){ // SER EL ULTIMO VALOR
                            lineaanterior->sig = NULL;
                            lineaux->ant = NULL;
                        }
                        else{ // SER UN VALOR DE EN MEDIO

                            lineaanterior->sig = lineaux->sig; //lineasiguiente
                            lineasiguiente->ant = lineaux->ant; // lineanterior
                        }
                        
                        //FREE

                        for(i=0; i<numcampos; i++){
                            free(lineaux->valores[i]);
                        }

                        free(lineaux->valores);
                        free(lineaux);

                    }

                    lineaux = lineasiguiente;

                }

                return linea;
        }
            else{
                printf("ERROR: operador introducido no reconocido");
            }
        }
        else if(tipo == TEXT){
            if(strcmp(simbolo, "=") == 0){
                while(lineaux != NULL){
                    lineasiguiente = lineaux->sig;
                    lineaanterior = lineaux->ant;

                    if(strcmp(valor, lineaux->valores[posicion]) == 0){
                        if(lineaux == linea && lineaux->sig == NULL){ 
                            linea = NULL;
                        }
                        else if(lineaux == linea && lineaux->ant == NULL){
                            linea = lineaux->sig;
                            lineasiguiente->ant = NULL;
                            lineaux->ant = NULL;
                        }
                        else{
                            lineaanterior->sig = lineaux->sig;
                            lineasiguiente->ant = lineaux->ant;
                        }

                        for(i=0; i < numcampos ; i++){
                            free(lineaux->valores[i]);
                        }

                        free(lineaux->valores);
                        free(lineaux);

                    }

                    lineaux = lineasiguiente;
                }

                return linea;
            }
            else if(strcmp(simbolo, ">") == 0){

                while(lineaux != NULL){
                    lineasiguiente = lineaux->sig;
                    lineaanterior = lineaux->ant;

                    if(strcmp(valor, lineaux->valores[posicion]) > 0){
                        if(lineaux == linea && lineaux->sig == NULL){ 
                            linea = NULL;
                        }
                        else if(lineaux == linea && lineaux->ant == NULL){
                            linea = lineaux->sig;
                            lineasiguiente->ant = NULL;
                            lineaux->ant = NULL;
                        }
                        else{
                            lineaanterior->sig = lineaux->sig;
                            lineasiguiente->ant = lineaux->ant;
                        }

                        for(i=0; i < numcampos ; i++){
                            free(lineaux->valores[i]);
                        }

                        free(lineaux->valores);
                        free(lineaux);

                    }

                    lineaux = lineasiguiente;
                }

                return linea;
            }
            else if(strcmp(simbolo, "<") == 0){
                while(lineaux != NULL){
                    lineasiguiente = lineaux->sig;
                    lineaanterior = lineaux->ant;

                    if(strcmp(valor, lineaux->valores[posicion]) < 0){
                        if(lineaux == linea && lineaux->sig == NULL){ 
                            linea = NULL;
                        }
                        else if(lineaux == linea && lineaux->ant == NULL){
                            linea = lineaux->sig;
                            lineasiguiente->ant = NULL;
                            lineaux->ant = NULL;
                        }
                        else{
                            lineaanterior->sig = lineaux->sig;
                            lineasiguiente->ant = lineaux->ant;
                        }

                        for(i=0; i < numcampos ; i++){
                            free(lineaux->valores[i]);
                        }

                        free(lineaux->valores);
                        free(lineaux);

                    }

                    lineaux = lineasiguiente;
                }

                return linea;
            }
            else{
                printf("ERROR: operador introducido no reconocido");
            }
        }
        else if(tipo == EMAIL){
            if(strcmp(simbolo, "=") == 0){
                while(lineaux != NULL){
                    lineasiguiente = lineaux->sig;
                    lineaanterior = lineaux->ant;

                    if(strcmp(valor, lineaux->valores[posicion]) == 0){
                        if(lineaux == linea && lineaux->sig == NULL){ 
                            linea = NULL;
                        }
                        else if(lineaux == linea && lineaux->ant == NULL){
                            linea = lineaux->sig;
                            lineasiguiente->ant = NULL;
                            lineaux->ant = NULL;
                        }
                        else{
                            lineaanterior->sig = lineaux->sig;
                            lineasiguiente->ant = lineaux->ant;
                        }

                        for(i=0; i < numcampos ; i++){
                            free(lineaux->valores[i]);
                        }

                        free(lineaux->valores);
                        free(lineaux);

                    }

                    lineaux = lineasiguiente;
                }

                return linea;
            }
            else if(strcmp(simbolo, ">") == 0){
                while(lineaux != NULL){
                    lineasiguiente = lineaux->sig;
                    lineaanterior = lineaux->ant;

                    if(strcmp(valor, lineaux->valores[posicion]) > 0){
                        if(lineaux == linea && lineaux->sig == NULL){ 
                            linea = NULL;
                        }
                        else if(lineaux == linea && lineaux->ant == NULL){
                            linea = lineaux->sig;
                            lineasiguiente->ant = NULL;
                            lineaux->ant = NULL;
                        }
                        else{
                            lineaanterior->sig = lineaux->sig;
                            lineasiguiente->ant = lineaux->ant;
                        }

                        for(i=0; i < numcampos ; i++){
                            free(lineaux->valores[i]);
                        }

                        free(lineaux->valores);
                        free(lineaux);

                    }

                    lineaux = lineasiguiente;
                }

                return linea;
            }
            else if(strcmp(simbolo, "<") < 0){
                while(lineaux != NULL){
                    lineasiguiente = lineaux->sig;
                    lineaanterior = lineaux->ant;

                    if(strcmp(valor, lineaux->valores[posicion]) < 0){
                        if(lineaux == linea && lineaux->sig == NULL){ 
                            linea = NULL;
                        }
                        else if(lineaux == linea && lineaux->ant == NULL){
                            linea = lineaux->sig;
                            lineasiguiente->ant = NULL;
                            lineaux->ant = NULL;
                        }
                        else{
                            lineaanterior->sig = lineaux->sig;
                            lineasiguiente->ant = lineaux->ant;
                        }

                        for(i=0; i < numcampos ; i++){
                            free(lineaux->valores[i]);
                        }

                        free(lineaux->valores);
                        free(lineaux);

                    }

                    lineaux = lineasiguiente;
                }

                return linea;
            }
            else{
                printf("ERROR: operador introducido no reconocido");
            }
        }
        else{
            printf("ERROR: tipo de dato no reconocido");
        }
    }   
}

/*------------------------ ENERO ---------------------------*/

TABLE *borrar_tabla(TABLE *LaGranTabla, char *tabla_borradora){
    int i;
    TABLE *tabla_aux = NULL, *tabla_siguiente = NULL, *tabla_anterior = NULL;

    tabla_aux = buscar_tabla(tabla_borradora, LaGranTabla);

    tabla_siguiente = tabla_aux->sig;
    tabla_anterior = tabla_aux->ant;

    if(tabla_aux == LaGranTabla && tabla_aux->sig == NULL){

        LaGranTabla = NULL;

    }
    else if (tabla_aux == LaGranTabla && tabla_aux->ant == NULL){

        LaGranTabla = tabla_aux->sig;
        tabla_siguiente->ant = NULL;;
        tabla_aux->ant = NULL;
    }
    else if(tabla_aux->sig == NULL){

        tabla_anterior->sig = NULL;
        tabla_aux->ant = NULL;
    }
    else{
        tabla_anterior->sig = tabla_aux->sig;
        tabla_siguiente->ant = tabla_aux->ant;
    }

    for(i=0; i<tabla_aux->numCampos; i++){
        free(tabla_aux->campos[i]);
    }

    free(tabla_aux->campos);
    free(tabla_aux->tipos);
    free(tabla_aux);

    return LaGranTabla;


}

TABLE *seleccionar_tablaBD(char *nombre_tabla, char *bd_origen, char *bd_destino, TABLE *LaGranTabla){

    TABLE *LaGranTablaAux = NULL, *tabla_aux = NULL, *tabla_aux2 = NULL;
    ROW *LaGranLinea = NULL;

    LaGranTablaAux = cargarTablas(bd_origen);
    mostrar_tablas(LaGranTablaAux);

    tabla_aux = buscar_tabla(nombre_tabla, LaGranTablaAux);
    tabla_aux2 = inicializar_tabla(tabla_aux->numCampos, tabla_aux->nombre, tabla_aux->campos, tabla_aux->tipos);

    LaGranLinea = cargar_linea(bd_origen, nombre_tabla, tabla_aux->numCampos, tabla_aux->tipos);

    if(LaGranTabla == NULL){
        LaGranTabla = tabla_aux2;
    }
    else{
        insertar_tabla(LaGranTabla, tabla_aux2);
    }

    crear_tabla_tab(LaGranTabla, bd_destino, nombre_tabla);
    actualizar_lineas(bd_destino, LaGranLinea, tabla_aux2);

    return LaGranTabla;

}

/*
int validar_entero(char *cadena){
    
    int i;

    if(cadena[0] == '+'){
        i = 1;
    }
    else{
        i=0;
    }

    if(cadena[0] == '-'){
        return 0;
    }

    if(strlen(cadena)==1 && i == 1){ // caso de que solo escribe + o -
        return 0;
    }

    if(strlen(cadena) == 0){
        return 0;
    }

    if(i == 1 && strlen(cadena) == 2 && cadena[1] == '.'){ //caso de +. o -.
        return 0;
    }
    if(strlen(cadena) == 1 && i == 0 && cadena[0] == '.'){ //caso de .
        return 0;
    }

    for(i; i<strlen(cadena); i++){
        
        if(cadena[i]<'0' || cadena[i]>'9'){ // en el caso de que no sea un numero la posicion i
            
            return 0;
        }

    return 1; // todo ha salido bn
    }
}
void imprimirxcampos(ROW *LaGranLinea, int posicion, int numcampos){

    ROW *linea = LaGranLinea;

    int i, contador = 1;

    if(linea == NULL){
        printf("Se ha producido un error\n");

    }
    else{
        while(linea != NULL){

            if(contador <= posicion){
                printf("%d - ", contador);

                for(i=0; i<numcampos-1; i++){
                    printf("%s, ", linea->valores[i]);
                }

                printf("%s \n", linea->valores[numcampos-1]);

                contador++;
                linea = linea->sig;

            }
            else{
                break;
            }       
        }
    }   
}


int validarfechaAMD(char *fecha){// y -

    int i, d, m ,a;

    if(strlen(fecha) != 10){ // 
        return 0;
    }

    for(i=0; i<10 ; i++){
        if(i != 4 || i != 7){
            if(fecha[i] < 0 || fecha[i] > 9){
                printf("ERROR: caracter invalido");
                return 0;
            }
        }
    }

    if(fecha[4] == '/' && fecha[7] == '/' || fecha[4] == '-' && fecha[7] == '-'){
        //Signos bien
    }
    else{
        printf("ERROR: caracter invalido, solo se admite / y -");
        return 0;
    }

    d=(fecha[8]-'0')*10 +(fecha[9]-'0');
    m=(fecha[5]-'0')*10 +(fecha[6]-'0');
    a=(fecha[0]-'0')*1000 +(fecha[1]-'0')*100+(fecha[2]-'0')*10+ (fecha[3]-'0'); 

    if(d<1 || m<1 || a<1000 || d>31 || m>12 || a>9999){
     
        return 0;
    }
    else if((m == 4 || m == 6 || m == 9 || m == 11) && d>30){
  
        return 0;
    }
    else if( m == 2 && a%4 == 0 && d>29){ // año bisiesto

        return 0;
    }
    else if(m == 2 && a%4!= 0 && d>28 && a%100!= 0 || a%400 == 0){ // año no bisiesto
        return 0;
    }

    return 1;

}

ROW *RenombrarLineaValorDeseado(int numCampos, ROW *Big_Row, TYPE tipo, char *valor, char *valor_nuevo, char *simbolo, int posicion)
{
	int i, j = 1;
    
	ROW *linea_auxiliar = Big_Row;
	ROW *linea_siguiente = NULL; 
	ROW *linea_anterior = NULL;

    if(Big_Row == NULL)
	{
        printf("No se han encontrado datos\n");
    }
	else
	{
		if(tipo == NUM)
		{
			if(strcmp(simbolo, "=")==0)
			{
				while(linea_auxiliar != NULL)
				{
					linea_anterior = linea_auxiliar->ant;
                    linea_siguiente = linea_auxiliar->sig;
					
					if(atof(valor) == atof(linea_auxiliar->valores[posicion]))
					{
						if(validardecimal(valor_nuevo)==1)
						{
							linea_auxiliar->valores[posicion] = valor_nuevo; 
						}
						else
						{
                            printf("El nuevo valor no es un numero\n");
                        }
					}
					
					linea_auxiliar = linea_siguiente;
					
				}
				
				return Big_Row; 
			}
			else if(strcmp(simbolo, "<")==0)
			{
				while(linea_auxiliar != NULL)
				{
					linea_anterior = linea_auxiliar->ant;
                    linea_siguiente = linea_auxiliar->sig;
						
					if(atof(valor) > atof(linea_auxiliar->valores[posicion]))
					{
						if(validardecimal(valor_nuevo)==1)
						{
							linea_auxiliar->valores[posicion] = valor_nuevo; 
						}
						else
						{
                            printf("El nuevo valor no es un numero\n");
                        }
					}
					
					linea_auxiliar = linea_siguiente;
					
				}
				
				return Big_Row; 
			}
			else if(strcmp(simbolo, ">")==0)
			{
				while(linea_auxiliar != NULL)
				{
					linea_anterior = linea_auxiliar->ant;
                    linea_siguiente = linea_auxiliar->sig;
					
					if(atof(valor) < atof(linea_auxiliar->valores[posicion]))
					{
						if(validardecimal(valor_nuevo)==1)
						{
							linea_auxiliar->valores[posicion] = valor_nuevo; 
						}
						else
						{
                            printf("El nuevo valor no es un numero\n");
                        }
					}
					
					linea_auxiliar = linea_siguiente;
					
				}
				
				return Big_Row; 
			}
			
			else
			{
				printf("ERROR de simbolos.\n"); 
			}
		}
	}
}


//
int renombrarbd(char *dbactual, char *dbnuevo){

   
    int ret = rename(dbactual, dbnuevo);

    printf("%s , %s\n ret: %d", dbactual, dbnuevo, ret);
	
    return ret;
}

void borrar_meta(char *db){

    char aux_ruta[100] = "";

                strcpy(aux_ruta, db);
                strcat(aux_ruta, "\\");
                strcat(aux_ruta, "meta");
                strcat(aux_ruta, ".db");
                remove(aux_ruta);
}

void borrar_directorio (char *db){
    char path[200];
    char ruta[100]="";
    char bar[10]="\\";

    if (getcwd(path, 200) == NULL) {
        
    }else{
    
    }

    strcat(path,bar);
    strcat(path,db);

    if(rmdir(path)==0){
        
    }else {
        printf("Se ha producido un error\n");
        
    }

}

void borrar_ficheros(char *db,TABLE *LaGranTabla){

    LaGranTabla=cargarTablas(db);
    char aux_ruta2[100] = "";
    while (LaGranTabla != NULL)
    {
        strcpy(aux_ruta2,db);
        strcat(aux_ruta2, "\\");
        strcat(aux_ruta2, LaGranTabla->nombre);
        strcat(aux_ruta2, ".tab");


        remove(aux_ruta2);

        // Borrar la tabla
        LaGranTabla = borrar_tabla(LaGranTabla, LaGranTabla->nombre);
    }
}
//


void UnirTablas (char *nombre_tabla1, char *nombre_tabla2, char *nombre_bd, TABLE *GranTabla)
{
	TABLE *TablaAuxiliar = GranTabla; 
	TABLE *tabla1, *tabla2; 
	
	ROW *aux1, *aux2, *aux3; 
	
	tabla1 = buscar_tabla(nombre_tabla1, GranTabla);
	tabla2 = buscar_tabla(nombre_tabla2, GranTabla);
	
	aux1 = cargar_linea(nombre_bd, nombre_tabla1, tabla1->numCampos, tabla1->tipos);
	aux2 = cargar_linea(nombre_bd, nombre_tabla2, tabla2->numCampos, tabla2->tipos);
	aux3 = aux2; 
	
	
	int i,j,k,p,x,y,z=0; 
	
	
	for(i=0; i<tabla1->numCampos; i++)
	{
		for(j=0; j<tabla2->numCampos; j++)
		{
			if(strcmp(tabla1->campos[i], tabla2->campos[j]) == 0 && tabla1->tipos[i] == tabla2->tipos[j])
			{
				z++;
				x = i; 
				y = j; 
			}
		}
	}
	if(z != 1)
	{
		printf("ERROR\n");
		return; 
	}
	
	
	while(aux1 != NULL)
	{
		while(aux2 != NULL)
		{
			if(strcmp(aux1->valores[x], aux2->valores[y]) == 0)
			{
				for(p=0; p<tabla1->numCampos; p++)
				{
					printf("%s, ", aux1->valores[p]);
				}
				for(k=0; k<tabla2->numCampos; k++)
				{
					if(strcmp(aux1->valores[x], aux2->valores[k]) != 0)
					{
						printf("%s, ", aux2->valores[k]);
					}
					
				}
				printf("\n");
			}
			
			aux2 = aux2->sig;
			
			
		}
		
		aux2 = aux3;
		aux1 = aux1->sig; 
		
		
	}
	
	
}

void joinTablas(char *nombredb, char *nombretablaA, char *nombretablaB, TABLE *LaTabla){ // Guardar tabla y escribir en meta
    TABLE *aux = LaTabla;
    TABLE *tablaA = NULL; 
    TABLE *tablaB = NULL; 
    ROW *lineaA = NULL;
    ROW *lineaB = NULL; 
    ROW *auxlineaB = NULL; 
    ROW *auxlineaA = NULL; 

    int i = 0, j = 0; 
    int auxi = 0, auxj = 0;
    int campos_iguales = 0;  

    int ncampos = 0; 
    char **valoresjoin = malloc(sizeof(char*)*ncampos);
    int ncampostablaB = 0; 
    char nombretablajoin[200] = ""; 
    
    ROW *LalineaJoin = NULL;
    ROW *auxLinea = NULL;
    char **nombre = malloc(sizeof(char*)*(ncampos)); //reservamos memoria para el array de columnas de la tabla (solo reservamos los campos); 
    TYPE *tipos = malloc(sizeof(TYPE*)*(ncampos));//Reservamos los tipos
    tablaA = buscar_tabla(nombretablaA, aux);
    tablaB = buscar_tabla(nombretablaB, aux);


    lineaA = cargar_linea(nombredb, nombretablaA, tablaA->numCampos, tablaA->tipos);
    lineaB = cargar_linea(nombredb, nombretablaB, tablaB->numCampos, tablaB->tipos);
    auxlineaB = lineaB;
    auxlineaA = lineaA;


    int numcamposA = tablaA->numCampos; 
    ncampos = tablaA->numCampos+(tablaB->numCampos-1);

    for(i = 0; i<tablaA->numCampos; i++){
        for(j = 0; j<tablaB->numCampos; j++){
            if(strcmp(tablaA->campos[i], tablaB->campos[j]) == 0 && tablaA->tipos[i] == tablaB->tipos[j]){
                auxi = i; 
                auxj = j; 
                campos_iguales++;
                

            }
        }
    }

    if(campos_iguales != 1){
        printf("Error de campos\n");
        return; 
    }     
    numcamposA = tablaA->numCampos;    
    for(int i = 0; i<tablaA->numCampos; i++){
        nombre[i] = tablaA->campos[i];
    } 
    for(int i = 0; i<tablaB->numCampos; i++){
        if(strcmp(tablaA->campos[auxi], tablaB->campos[i]) == 0){
            continue; 
        }
        nombre[numcamposA] = tablaB->campos[i];
        numcamposA++;
    }
    for(int i = 0; i<tablaA->numCampos; i++){
        tipos[i] = tablaA->tipos[i];
    } 
    for(int i = 0; i<tablaB->numCampos; i++){
        if(strcmp(tablaA->campos[auxi], tablaB->campos[i]) == 0){
            continue; 
        }
        tipos[numcamposA] = tablaB->tipos[i];
        numcamposA++;

    }
    

    strcat(nombretablajoin, tablaA->nombre);
    strcat(nombretablajoin, tablaB->nombre);

    TABLE *tablajoin = inicializar_tabla(ncampos, nombretablajoin, nombre, tipos);

    insertar_tabla(LaTabla, tablajoin); 
    crear_tabla_tab(LaTabla, nombredb, tablajoin->nombre);
    
    lineaA = auxlineaA; 
    lineaB = auxlineaB; 

    while(lineaA != NULL){

        while(lineaB != NULL){
            if(strcmp(lineaA->valores[auxi], lineaB->valores[auxj]) == 0){
                for(int k = 0; k<tablaA->numCampos; k++){
                    printf("%s, ", lineaA->valores[k]);  
                    valoresjoin[k] = lineaA->valores[k];                    
                }
                for(int p = 0; p<tablaB->numCampos; p++){                    
                    if(strcmp(lineaA->valores[auxi], lineaB->valores[p]) != 0){                        
                        printf("%s,  ", lineaB->valores[p]);   
                        numcamposA = tablaA->numCampos;                         
                        valoresjoin[numcamposA] = lineaB->valores[p];
                        numcamposA++;
                        LalineaJoin = cargar_linea(nombredb, nombretablajoin, ncampos, tablajoin->tipos);
                        auxLinea = inicializar_linea(valoresjoin); 

                        if(LalineaJoin == NULL){                            
                            LalineaJoin = auxLinea;                    
                            actualizar_lineas(nombredb, LalineaJoin, tablajoin);    
                        }
                        else{ 
                            insertar_ultima_linea(LalineaJoin, auxLinea);                      
                            actualizar_lineas(nombredb, LalineaJoin, tablajoin);
                        }                        
                    }                    
                }
            }
            lineaB = lineaB->sig; 
        }
        lineaB = auxlineaB;
        lineaA= lineaA->sig; 
    }  
    
    
}

void ordenar_tablasASC(TABLE *tabla){
    TABLE *i = NULL, *j = NULL;

    TABLE *tabla_aux = tabla;

        for(i=tabla; i != NULL; i = i->sig){
            for(j=i; j != NULL; j = j->sig){
                
                if(strcmp(i->nombre, j->nombre) > 0){
                    
                    char aux[100];

                    strcpy(aux, i->nombre);
                    strcpy(i->nombre, j->nombre);
                    strcpy(j->nombre, aux);
                   
                }
            }
        }
    
}

void ordenar_tablasDES(TABLE *tabla){
    TABLE *i = NULL, *j = NULL, *aux = NULL;

    TABLE *tabla_aux = tabla;

    for(i = tabla; i != NULL; i = i->sig){
        for(j=i; j != NULL; j = j->sig){
                
            if(strcmp(i->nombre, j->nombre) < 0){
                    
                char aux[100];

                strcpy(aux, i->nombre);
                strcpy(i->nombre, j->nombre);
                strcpy(j->nombre, aux);
                   
            }
        }
    }
}

void imprimirxveces(ROW *LaGranLinea, int numcampos, int veces){

    ROW *linea = LaGranLinea;

    int i, contador = 1;

    if(linea == NULL){
        printf("Se ha producido un error\n");

    }
    else{
        while(contador <= veces){

            printf("%d - ", contador);

            for(i=0; i<numcampos-1; i++){
                printf("%s, ", linea->valores[i]);
            }

            printf("%s \n", linea->valores[numcampos-1]);

            contador++;
            linea = linea->sig;
      
        }
    }   
}

void imprmirMAX(TABLE *tabla_aux, ROW *LaGranLinea, int numcampos, int orden_campo){
    
    ROW *i, *j;

    char MAX[100];

    strcpy(MAX, LaGranLinea->valores[orden_campo]);

    if(tabla_aux->tipos[orden_campo] == NUM){
        for(i=LaGranLinea; i != NULL; i = i->sig){
                
            if(atof(i->valores[orden_campo]) > atof(MAX)){
                    
                strcpy(MAX, i->valores[orden_campo]);
            }
        }
    }
    if(tabla_aux->tipos[orden_campo] == DATE){
        for(i=LaGranLinea; i != NULL; i = i->sig){
                
            if(Fecha_a_numero(i->valores[orden_campo]) > Fecha_a_numero(MAX)){
                    
                strcpy(MAX, i->valores[orden_campo]);
            }
        }
    }
    if(tabla_aux->tipos[orden_campo] == EMAIL){
        for(i=LaGranLinea; i != NULL; i = i->sig){
                
            if(strcmp(i->valores[orden_campo], MAX) > 0){
                    
                strcpy(MAX, i->valores[orden_campo]);
            }
        }
    }
    if(tabla_aux->tipos[orden_campo] == TEXT){
        for(i=LaGranLinea; i != NULL; i = i->sig){
                
            if(strcmp(i->valores[orden_campo], MAX) > 0){
                    
                strcpy(MAX, i->valores[orden_campo]);
            }
        }
    }

    printf("MAX = %s\n", MAX);

}

void imprmirMIN(TABLE *tabla_aux, ROW *LaGranLinea, int numcampos, int orden_campo){
    
    ROW *i, *j;

    char MIN[100];

    strcpy(MIN, LaGranLinea->valores[orden_campo]);

    if(tabla_aux->tipos[orden_campo] == NUM){
        for(i=LaGranLinea; i != NULL; i = i->sig){
                
            if(atof(i->valores[orden_campo]) < atof(MIN)){
                    
                strcpy(MIN, i->valores[orden_campo]);
            }
        }
    }
    if(tabla_aux->tipos[orden_campo] == DATE){
        for(i=LaGranLinea; i != NULL; i = i->sig){
                
            if(Fecha_a_numero(i->valores[orden_campo]) < Fecha_a_numero(MIN)){
                    
                strcpy(MIN, i->valores[orden_campo]);
            }
        }
    }
    if(tabla_aux->tipos[orden_campo] == EMAIL){
        for(i=LaGranLinea; i != NULL; i = i->sig){
                
            if(strcmp(i->valores[orden_campo], MIN) < 0){
                    
                strcpy(MIN, i->valores[orden_campo]);
            }
        }
    }
    if(tabla_aux->tipos[orden_campo] == TEXT){
        for(i=LaGranLinea; i != NULL; i = i->sig){
                
            if(strcmp(i->valores[orden_campo], MIN) < 0){
                    
                strcpy(MIN, i->valores[orden_campo]);
            }
        }
    }

    printf("MIN = %s\n", MIN);

}

TABLE *alter_campos(TABLE *LaGranTabla, char *campo1, char *campo2, TYPE tipo1, TYPE tipo2, char *nombre_tabla, char *nombre_bd){

    TABLE *tabla_aux = NULL;
    int i = 0;
    tabla_aux = buscar_tabla(nombre_tabla, LaGranTabla);
    ROW *linea = NULL;
    linea = cargar_linea(nombre_bd, nombre_tabla, tabla_aux->numCampos, tabla_aux->tipos);

    for(i ; i<tabla_aux->numCampos ; i++){

        if(strcmp(campo1, tabla_aux->campos[i]) == 0){

            tabla_aux->campos[i] = strdup(campo2);
            tabla_aux->tipos[i] = tipo2;
        }

    }

    liberar_memoria_lineas(linea, tabla_aux->numCampos);
    linea = NULL;
    actualizar_lineas(nombre_bd, linea, tabla_aux);


    return LaGranTabla;

}

int contarLineas(ROW *Lalinea){
    ROW *aux = NULL; 
    aux = Lalinea; 
    int contador = 0; 

    while(aux != NULL){
        contador++; 
        aux = aux->sig; 
    }

    return contador; 
}

//Sin contador
void gruopby(ROW *Lalinea, TABLE *tablaaux, int posicion){

    int nlineas = contarLineas(Lalinea); 
    char **valores = malloc(sizeof(char *) * (nlineas));

    ROW *aux1 = NULL; 
    aux1 = Lalinea; 

    int primera = 0;
    int narray = 0; 
    int entra = 0; 

    
    while(aux1 != NULL){
        if(primera == 0){
            valores[primera] = strdup(aux1->valores[posicion]);  
            printf("%s\n", valores[primera]);
            primera++;
            narray = primera; 
        }
        else{
            for(int i = 0; i<narray; i++){
                if(strcmp(valores[i], aux1->valores[posicion]) == 0){
                    entra++; 
                }
                
            }    
            if(entra == 0){
                valores[primera] = strdup(aux1->valores[posicion]);
                printf("%s\n", valores[primera]);
                primera++;                 
            }
            entra = 0;
            narray = primera;         
        }        
        aux1 = aux1->sig; 
    }
}
//Con contador
void gruopby1(ROW *Lalinea, TABLE *tablaaux, int posicion){

    int nlineas = contarLineas(Lalinea); 
    char **valores = malloc(sizeof(char *) * (nlineas));
    int *numero = (int *)malloc(sizeof(int) * (nlineas));

    ROW *aux1 = NULL; 
    aux1 = Lalinea; 

    int primera = 0;
    int narray = 0; 
    int entra = 0; 

    int contador = 0; 

    
    while(aux1 != NULL){
        if(primera == 0){
            valores[primera] = strdup(aux1->valores[posicion]);  
            contador++; 
            numero[primera] = contador;
            //printf("%s\n", valores[primera]);
            primera++;
            narray = primera; 
        }
        else{
            for(int i = 0; i<narray; i++){
                if(strcmp(valores[i], aux1->valores[posicion]) == 0){
                    contador = numero[i]; 
                    contador++; 
                    numero[i]= contador; 

                    entra++; 
                }
                
            }    
            if(entra == 0){
                contador = 1;
                valores[primera] = strdup(aux1->valores[posicion]);
                numero[primera] = contador;                
                //printf("%s\n", valores[primera]);
                primera++;                 
            }
            entra = 0;
            narray = primera;         
        }        
        aux1 = aux1->sig; 
    }

    for(int j = 0; j<narray; j++){
        printf("%s - %d\n", valores[j], numero[j]);
    }
}




*/