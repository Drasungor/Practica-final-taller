# Practica-final-taller

Aclaración: en algunos finales pregunta qué indica cada línea, en algunos casos pregunta por la línea (por ejemplo) "int "(*c)[3];", en los primeros finales que hicimos pusimos que era un array de punteros a funciones, pero está mal, para que fuera así tendría que ser "int (*c[3])();". La primera líneaen realidad indica que c es un puntero a un array (no un array, un puntero a un array), o sea que para inicializarlo tendría que hacerse algo como:

int a[3];

int (*c)[3] = &a;

Y para acceder a algún valor de a desde c:

(*c)[indice];
