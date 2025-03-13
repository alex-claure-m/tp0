#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

		// Usando el logger creado previamente
		// Escribi: "Hola! Soy un log"
	log_info(logger,"hola soy un bot");


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	ip = config_get_string_value(config, "ip");
	puerto = config_get_string_value(config,"puerto");
	valor = config_get_string_value(config,"valor");


	// Loggeamos el valor de config
	log_info(logger,"el valor del ip: %s , del puerto %s y el valor", ip,puerto,valor);

	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor,conexion); // recorda que el enviar_mensaje toma un valor y el socket al cual enviar
	//otra cosa, el cliente es el que abre la conexion, por eso tiene que pasarle ademas, la coenxion
	// el socket , solo responde, asi que si tiene que neivar un mensaje, no tiene que abrir una nueva conexion
	// mas bien deberia usar la conexion del cual le llega!

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío

	// dice que se debe leer y logear hasta recibir un string -> while
	while(strcmp(leido,"\0")!=0){ // strcmp compara el 1er caracter con el 2do: 
	// si no son guales -> false (es lo mismo que decir !=0 )
	//entonces entra por aca!
	log_info(logger, "%s", leido);
	//libero lo que leo
	free(leido);
	//al final de cada while tengo que leer de nuevo!
	leido = readline(">");
	}

	// ¡No te olvides de liberar las lineas antes de regresar!
	free(leido);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	paquete = crear_paquete(); // falto la creacion 

	leido = readline("> "); // lo mismo, debo leer y de ahi agregar a paquete
	// Leemos y esta vez agregamos las lineas al paquete
	while(leido != '\0'){
		agregar_a_paquete(paquete,leido, strlen(leido) + 1);
		free(leido);
		leido = readline("> "); // Leer una nueva línea	
	}

 	// Enviar el paquete a través de la conexión
    enviar_paquete(paquete, conexion);
	
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	free(leido);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
