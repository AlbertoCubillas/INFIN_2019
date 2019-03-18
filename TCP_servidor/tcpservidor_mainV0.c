/***************************************************************************
                          main.c  -  server
                             -------------------
    begin                : lun feb  4 15:30:41 CET 2002
    copyright            : (C) 2002 by A. Moreno
    email                : amoreno@euss.es
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
#include <string.h>

#define SERVER_PORT_NUM		5001
#define SERVER_MAX_CONNECTIONS	4

#define REQUEST_MSG_SIZE	1024


/************************
*
*
* tcpServidor
*
*
*/
int menu = 0;
int main(int argc, char *argv[])
{
	struct sockaddr_in	serverAddr;
	struct sockaddr_in	clientAddr;
	int			sockAddrSize;
	int			sFd;
	int			newFd;
	int			nRead;
	int 		temp1;
	int 		temp2;
	int 		NumMues;
	int 		result;
	int 		codigoretorno = 0;
	char 		readpalabra[256];
	char		writepalabra[256];
	char		buffer[256];
	char		missatge[] ="((2)(0,23.3)(10,23.3))";

	/*Preparar l'adreça local*/
	sockAddrSize=sizeof(struct sockaddr_in);
	bzero ((char *)&serverAddr, sockAddrSize); //Posar l'estructura a zero
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT_NUM);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	/*Crear un socket*/
	sFd=socket(AF_INET, SOCK_STREAM, 0);
	
	/*Nominalitzar el socket*/
	result = bind(sFd, (struct sockaddr *) &serverAddr, sockAddrSize);
	
	/*Crear una cua per les peticions de connexió*/
	result = listen(sFd, SERVER_MAX_CONNECTIONS);
	
	/*Bucle s'acceptació de connexions*/
	while(1){
		printf("\nServidor esperant connexions\n");

		/*Esperar conexió. sFd: socket pare, newFd: socket fill*/
		newFd=accept(sFd, (struct sockaddr *) &clientAddr, &sockAddrSize);
		printf("Connexión acceptada del client: adreça %s, port %d\n",	inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

		/*Rebre*/
		result = read(newFd, buffer, 256);
		printf("Missatge rebut del client(bytes %d): %s\n",	result, buffer);
		
//-------------------------------------------------------------------------------------------------------------
		//Leer lo que envia el cliente, por el buffer.
		strcpy(readpalabra,buffer);		//Se copia lo que hay en el buffer a palabra.	
			switch (readpalabra[0])		//SE va mirando caracter por caracter lo que envia el cliente.
			{
				case '(':
					switch(readpalabra[1])
					{
							case 'M':
									switch (readpalabra[2])
									{
										case '0':
										//printf("%c",palabra[2]);
												temp1 = readpalabra[3] - '0';
												temp2 = readpalabra[4] - '0';	
												printf("%d",temp1);
												printf("%d",temp2);
												NumMues = readpalabra[5] - '0';
													switch (readpalabra[6])
													{
														case ')':
														codigoretorno = 0;
														break;
													}	
										break;
										case '1':
										//printf("%c",palabra[2]);
												temp1 = readpalabra[3] - '0';  //El valores de tiempo se convierte en numero entero.
												temp2 = readpalabra[4] - '0';  //El valores de tiempo se convierte en numero entero.
												if (temp1>2)
												{
													codigoretorno = 2;
													break;
												}
												//printf("%d",temp1);
												//printf("%d",temp2);
												NumMues = readpalabra[5] - '0'; // El valor de numero de muestra para hacer la mediana se convierte a numero entero.
													switch (readpalabra[6])
													{
														case ')':
														codigoretorno = 0;
														
														break;
														default:
														codigoretorno = 2;
														break;
													}	
										break;	
										default:
										codigoretorno = 2;
										break;
									}
							
							break;
							case 'U':
									switch (readpalabra[2]){
										case ')':
										codigoretorno = 0;
										break;
														default:
														codigoretorno = 2;
														break;
													}
							break;
							
							case 'X':
									switch (readpalabra[2]){
										case ')':
										codigoretorno = 0;
										break;
														default:
														codigoretorno = 2;
														break;
													}
							break;
							
							case 'Y':
									switch (readpalabra[2]){
										case ')':
										codigoretorno = 0;
										break;
														default:
														codigoretorno = 2;
														break;
													}
							break;
							
							case 'R':
									switch (readpalabra[2]){
										case ')':
										codigoretorno = 0;
										break;
														default:
														codigoretorno = 2;
														break;
													}
							break;
							
							case 'B':
									switch (readpalabra[2]){
										case ')':
										codigoretorno = 0;
										break;
														default:
														codigoretorno = 2;
														break;
													}
							break;
						
						break;			
				break;
					default:
					codigoretorno = 1;
					break;
					}	
			default:
					codigoretorno = 1;
					break;
			}		
			
//-----------------------------------------------------------------------------------------
//git add (nom ficher.c)
//git commit -m "mensaje"
// git push


	
		/*Enviar*/
		strcpy(buffer,missatge); //Copiar missatge a buffer
		result = write(newFd, buffer, strlen(buffer)+1); //+1 per enviar el 0 final de cadena
		printf("Missatge enviat a client(bytes %d): %s\n",	result, missatge);
		
		
		/*Tancar el socket fill*/
		
		result = close(newFd);
	}
	
}



