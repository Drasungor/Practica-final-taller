#ifndef _COMPLEJO_H_
#define _COMPLEJO_H_

typedef struct complejo {
	int parte_real;
	int parte_imaginaria;
} complejo_t;


void complejo_init(complejo_t* complejo, int parte_real, int parte_imaginaria);

complejo_t complejo_sumar(const complejo_t* comp1, const complejo_t* comp2);

complejo_t complejo_restar(const complejo_t* comp1, const complejo_t* comp2);

void complejo_release(complejo_t* complejo);

#endif
