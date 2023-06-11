/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:23:24 by mvisca            #+#    #+#             */
/*   Updated: 2023/06/11 12:10:16 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_free(char *ptr)
{
	free(ptr);
	ptr = NULL;
	return (NULL);
}

static char	*gnl_read(int fd, char *raw)
{
	int		bread;
	char	*buffer;

	bread = 1;
	// crea el buffer + 1 para evitar desbordamientos
	buffer = (char *) ft_calloc (sizeof(char), (BUFFER_SIZE + 1));
	if (!buffer)
		return (gnl_free(raw));
	// mientras el buffer tiene algo (bread) y hay un nl en el file
	while (bread > 0 && !ft_strchr(raw, NL))
	{
		bread = read (fd, buffer, BUFFER_SIZE);	
		if (bread == -1)
		{
			free(buffer);
			if (raw)
				free(raw);
			return (NULL);
		}
		buffer[bread] = 0;
		raw = ft_strjoinfree(raw, buffer);
	}
	free (buffer);
	return (raw);
}

char	*gnl_extract(char *raw)
{
	int		i;
	int		j;
	int		end;
	char	*line;
	
	if (!raw || !raw[0])
		return (NULL);
	// guarda la posicion del NL
	end = ft_strlenc(raw, NL);
	// si el end indica NL agrego un caracter antes de alojar
	if (raw[end] == NL)
		end++;
	// aloja memoria set a NULL ppara el total de la string hasta NL incluido o hasta \0
	line = (char *) ft_calloc (sizeof(char), (end + 1));
	if (!line)
		return (NULL);
	i = 0;
	j = 0;
	// copio raw de 0 hasta la ubiciacion de 
	while (raw[i] && raw[j] != NL)
		line[i++] = raw[j++];
	if (raw[j] == NL)
		line[i++] = NL;
	// termina en NULL pero ya esta null por el calloc, testear y quitar despues
	line[i] = 0;
	return (line);
}

char	*gnl_shift(char *raw)
{
	char	*new_raw;
	int		i;
	int 	len;

	len = ft_strlenc(raw, NL);
	// len es la posicion del proximi nl en raw, si no hay nl es la posicion '\0'
	// este if:
		// observa si len ha encontrado nl o el fin de raw
		// si es el fin de raw, libera raw y devuelve NULL
		// en este punto, raw en GNL es tambien null
		// en la siguiente llamada a GNL se ejecutara igualmente, y termiara por read 0
		// esta funcion no interviene directamente en la finalizacion de la ejecucion
	if (!raw[len])
	{
		free(raw);
		return (NULL);
	}
	// crea un buffer null para alojar el fragmento de raw posterior a nl
	// toma el largo total de raw (largo total raw - largo de str hasta nl, + 1) 
	// el largo del ft_calloc es el largo de la string restante despues de nl
	new_raw = (char *) ft_calloc (sizeof(char), (ft_strlenc(raw, 0) - len + 1));
	if (!new_raw)
	{
		free(raw);
		return (NULL);
	}
	len++;
	// posiciona len en el primer caracter despues de nl
	i = 0;
	// este while recorre raw y copia en new raw
	while (raw[len])
		new_raw[i++] = raw[len++];
	// esta no es necesaria, ya que se hizo el buffer con ft_calloc, revisar despues
	new_raw[i] = 0;
	// se libera raw antes de salir, new_raw sera recibido por raw en el GNL
	free(raw);
	return (new_raw);
}

char	*get_next_line(int fd)
{
	static char	*raw = NULL;
	char		*line;

	// este if:
		// descarta file descriptor negativo
		// buffer cero que no lee nada
	if (fd < 0 || BUFFER_SIZE < 1)
	{
		// libera raw, podria tener datos de llamadas anteriores, por lo tanto seria invalido
		// el calor de buffer size no cambiara entre dos llamadas de una misma instancia, pero si puede cambiar fd
		free (raw);		
		return (NULL);
	}
	// este if:
		// captura no hay raw (1ra pasada) hay raw con '\n' (pasadas intermedias) 
		// deja pasar hay raw sin '\n' (ultima pasada)
	if (!raw || (!ft_strchr(raw, '\n')))
		raw = gnl_read(fd, raw); 
	// cuando el read devuelve 0 se ha acabado el file y retorna NULL
	// esto termina la ejecucion, el programa termina en la llamada que no lee nada
	// el programa no termina en la llamada que devuelve la ultima linea terminada en '\0'
	if (!raw)
		return (NULL);
	// extrae line de raw, puede ser '\0' o '\n' terminated
	line = gnl_extract(raw);
	if (!line)
	{
		// si no hay line es que encontro en line el primer char como '\0'
		// debe inicar validando que el primer char no sea '\-' para ejecutar
		// limpiara raw porque ya no habra siguientes ejecuciones para esta sesion
		free(raw);
		raw = NULL;
		return (NULL);
	}
	// acondiciona el raw para la siguiente llamada a la funcion
	raw = gnl_shift(raw);
	return (line);
}
