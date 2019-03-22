


/***************************************************************************
                          exemple_menu_consola.c
                             -------------------
    begin                : 2012
    copyright            : (C) 2010 by A. Moreno
    email                : amoreno@euss.cat
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


#define REQUEST_MSG_SIZE	1024
#define REPLY_MSG_SIZE		500
#define SERVER_PORT_NUM		5001


/************************
*
*
* ImprimirMenu
*
*
*/
void ImprimirMenu(void)
{
	printf("\n\nMenu:\n");
	printf("--------------------\n");
	printf("1: Demanar la última mitjana\n");
	printf("2: Demanar el valor màxim\n");
	printf("3: Demanar el valor mínim\n");
	printf("4: Resetejar el màxim i el mínim\n");
	printf("5: Demanar comptador\n");
	printf("6: Posar en marxa i parar adquisició\n");
	printf("7: Sortir\n");
	printf("--------------------\n");
}


/************************
*
*
* main
*
*
*/
int main(int argc, char *argv[])                                                               
{                                                                          
	char input,selector1;
	struct sockaddr_in	serverAddr;
	char	    serverName[] = "127.0.0.1"; //AdreÃ§a IP on està  el servidor
	int			sockAddrSize;
	int			sFd;
	int			mlen;
	int 		result;
	char		buffer[256];
	char		missatge1[1] = {'U'};
	char		missatge2[1] = {'X'};
	char		missatge3[1] = {'Y'};
	char		missatge4[1] = {'R'};
	char		missatge5[1] = {'B'};
	char		missatge6[6] = '{','M','0','0','0','0','}';
	
	/*Crear el socket*/
	sFd=socket(AF_INET,SOCK_STREAM,0);

	/*Construir l'adreÃ§a*/
	sockAddrSize = sizeof(struct sockaddr_in);
	bzero ((char *)&serverAddr, sockAddrSize); //Posar l'estructura a zero
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons (SERVER_PORT_NUM);
	serverAddr.sin_addr.s_addr = inet_addr(serverName);

	/*ConexiÃ³*/
	result = connect (sFd, (struct sockaddr *) &serverAddr, sockAddrSize);
	
	
	
	if (result < 0)
	{
		printf("Error en establir la connexió\n");
		exit(-1);
	}
	printf("\nConnexiÃ³ establerta amb el servidor: adreça %s, port %d\n",	inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));

	ImprimirMenu();                             
	input = getchar();
	
	

	while (input != '8')
	{
		switch (input)
		{
			case '1':
				printf("S'ha seleccionat: Demanar la última mitjana\n");
				
				/*Enviar*/
				strcpy(buffer,missatge1); //Copiar missatge a buffer
				result = write(sFd, buffer, strlen(buffer));
				printf("Missatge enviat a servidor(bytes %d): %s\n",	result, missatge1);
				/*Rebre*/
				result = read(sFd, buffer, 256);
				printf("Missatge rebut del servidor(bytes %d): %s\n",	result, buffer);
				
				switch (buffer[3]){				
					case '0':
					printf("Informació rebuda correctament\n");
					break;					
					case '1':
					printf("Error tipus 1\n");
					break;					
					case '2':					
					printf("Error tipus 2\n");
					break;}
					
				switch (buffer[3]){				
					case '0':
					printf("Informació rebuda correctament\n");
					break;					
					case '1':
					printf("Error tipus 1\n");
					break;					
					case '2':					
					printf("Error tipus 2\n");
					break;}
					
				ImprimirMenu();                             
				break;                        
			case '2':
				printf("S'ha seleccionat: Demanar el valor màxim\n");
					
				/*Enviar*/
				strcpy(buffer,missatge2); //Copiar missatge a buffer
				result = write(sFd, buffer, strlen(buffer));
				printf("Missatge enviat a servidor(bytes %d): %s\n",	result, missatge2);
				/*Rebre*/
				result = read(sFd, buffer, 256);
				printf("Missatge rebut del servidor(bytes %d): %s\n",	result, buffer);
								
				                            
				break;
			case '3':
				printf("S'ha seleccionat: Demanar el valor mínim\n");
				
				/*Enviar*/
				strcpy(buffer,missatge3); //Copiar missatge a buffer
				result = write(sFd, buffer, strlen(buffer));
				printf("Missatge enviat a servidor(bytes %d): %s\n",	result, missatge3);
				/*Rebre*/
				result = read(sFd, buffer, 256);
				printf("Missatge rebut del servidor(bytes %d): %s\n",	result, buffer);	
				
				ImprimirMenu();                             
				break;
			case '4':
				printf("S'ha seleccionat: Resetejar el màxim i el mínim\n");
				
				/*Enviar*/
				strcpy(buffer,missatge4); //Copiar missatge a buffer
				result = write(sFd, buffer, strlen(buffer));
				printf("Missatge enviat a servidor(bytes %d): %s\n",	result, missatge4);
				/*Rebre*/
				result = read(sFd, buffer, 256);
				printf("Missatge rebut del servidor(bytes %d): %s\n",	result, buffer);
				
				ImprimirMenu();  
				break;			
			case '5':
				printf("S'ha seleccionat: Demanar el comptador\n");
				
				/*Enviar*/
				strcpy(buffer,missatge5); //Copiar missatge a buffer
				result = write(sFd, buffer, strlen(buffer));
				printf("Missatge enviat a servidor(bytes %d): %s\n",	result, missatge5);
				/*Rebre*/
				result = read(sFd, buffer, 256);
				printf("Missatge rebut del servidor(bytes %d): %s\n",	result, buffer);
				
				ImprimirMenu();  
				break;
			case '6':
				printf("S'ha seleccionat: Posar en marxa o aturar l'adquisició\n");
				ImprimirMenu();  
				printf("\n a. Posta en marxa\n b. Parar adquisició\n c. Tornar al menú\n");
				scanf("%s",&selector1);
					case 'a':
						printf("S'ha seleccionat: Posta en marxa\n");
						missatge6= '{','M','0','0','0','0','}';
						
						printf("Introduïr temps d'enregistrament 1 (0, 1 o 2)\n");						
						scanf("%s\n", &missatge6[3]);
						
						printf("Introduïr temps d'enregistrament 2 (0 a 9)\n");	
						scanf("%s\n", &missatge6[4]);
						
						printf("Introduïr núm. mostres mitjana (1 a 9)\n");
						scanf("%s\n", &missatge6[5]);
						
						ImprimirMenu(); 
						break;
					case 'b':
						printf("S'ha seleccionat: Parar adquisició\n");
						missatge6= '{','M','0','0','0','0','}';
						ImprimirMenu(); 
						break;	
					case 'c':
						printf("S'ha seleccionat: Tornar al menú\n");	
						ImprimirMenu(); 
						break;
						
				/*Enviar*/
				strcpy(buffer,missatge6); //Copiar missatge a buffer
				result = write(sFd, buffer, strlen(buffer));
				printf("Missatge enviat a servidor(bytes %d): %s\n",	result, missatge6);
				/*Rebre*/
				result = read(sFd, buffer, 256);
				printf("Missatge rebut del servidor(bytes %d): %s\n",	result, buffer);
			
				switch (buffer[3]){				
					case '0':
					printf("Informació rebuda correctament\n");
					break;					
					case '1':
					printf("Error tipus 1\n");
					break;					
					case '2':					
					printf("Error tipus 2\n");
					break;}
					
			case '7':
				printf("S'ha seleccionat: Sortir\n");
				
				/*Tancar el socket*/
				close(sFd);
				break;
				
			case 0x0a: //Això és per enviar els 0x0a (line feed) que s'envia quan li donem al Enter
				break;
			default:
				printf("Opcion incorrecta\n");	
				printf("He leido 0x%hhx \n",input);
				printf("Vuelve a seleccionar una opción del menú\n");
				break;
		}

		input = getchar();

	}
	
	return 0;
}


