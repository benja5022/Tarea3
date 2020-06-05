/**
 MIT License

 Copyright (c) 2018 Matias Barrientos.

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#ifndef Map_h
#define Map_h

typedef struct Map Map;

/**
 @typedef
 La función compara dos objetos del tipo que definio el usuario.

 @param key1 Primero parametro.
 @param key2 Segundo parametro.
 @return retorna 3 valores con respecto a la comparacion realizada.
 1: p1 es mayor que p2.
 0: p1 es igual a p2.
 -1: p1 es menor que p2.
 */
typedef int (* MapCompareCallBack)(const void * key1, const void * key2);

/**
 Crea un nuevo puntero de tipo Map.

 @param compare Funcion comparar.
 @return Puntero al nuevo tipo de Map.
 */
Map * createMap(MapCompareCallBack compare);

/**
 Inserta un dato con clave en el Map.

 @param map Puntero al Map.
 @param key Puntero a la llave del dato.
 @param value Puntero al dato.
 */
void insertMap(Map * map, const void * key, const void * value);

/**
 Elimina un nodo del Map con la llave, no libera memoria del dato guardado.

 @param map Puntero al Map.
 @param key Puntero a la llave del dato.
 @return Puntero al dato eliminado del Map.
 */
void * eraseMap(Map * map, const void * key);

/**
 La cantidad de datos ingresados al Map.

 @param map Puntero al Map.
 @return Cantidad de datos.
 */
long MapCount(Map * map);

/**
 Prueba si el Map está vacio.

 @param map Puntero al Map.
 @return 1 (true) si y solo si el Map no contiene elementos; 0 (false) lo contrario.
 */
int emptyMap(Map * map);

/**
 Busca un dato en el Map con la llave.

 @param map Puntero al Map.
 @param key Puntero a la llave del dato.
 @return Puntero al dato.
 */
void * searchMap(Map * map, const void * key);

/**
 Retorna el primer elemento

 @param map Puntero al Map.
 @return Puntero al dato.
 */
void * firstMap(Map * map);

/**
 Retorna el siguiente elemento

 @param map Puntero al Map.
 @return Puntero al dato.
 */
void * nextMap(Map * map);

/**
 Elimina todos los nodos del Map, no libera memoria de los datos guardados en el Map.
 @param map Puntero a la struct Map.
 */
void removeAllMap(Map * map);

#endif /* Map_h */
