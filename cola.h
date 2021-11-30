#define MAX_COLA 10  // Capacidad máxima de la cola

struct struct_cola
{
    int datos[MAX_COLA + 1];  // Necesito un espacio más
    int inicio; // Me indica el inicio de la cola, y es de donde voy a sacar los datos
    int fin; // Me indica el fin de la cola y es donde voy a metar los datos
};

typedef struct struct_cola Cola;  // Queues, FIFO

void inicializaCola(Cola *c);
int colaVacia(Cola c); // Regresar 1 si la cola está vacía y un 0 sin no
int colaLlena(Cola c);  // Regresar 1 si la cola está llena y 0 si no 
int tieneDatos(Cola c);  // Regresar 1 si la cola tiene datos y 0 si no

void ponDato(Cola *c, int dato); // enqueue encolar 
int sacaDato(Cola *c);

int sacaDato(Cola *c)
{
    int dato = 0;

    if(tieneDatos(*c))
    {
        dato = c->datos[c->inicio];
        c->inicio = (c->inicio + 1) % (MAX_COLA + 1);
        // 0 -> MAX ok | MAX + 1 -> 0
    }

    return dato;
}

void ponDato(Cola *c, int dato)
{
    if(!colaLlena(*c))
    {
        c->datos[c->fin] = dato;
        c->fin = (c->fin + 1) % (MAX_COLA + 1);
        //c->fin++; // 0 -> N -> ok | N + 1 -> 0
    }
}

int tieneDatos(Cola c)
{
    return !colaVacia(c);
}

int colaLlena(Cola c)
{
    int llena = 0;

    if((c.fin == MAX_COLA && c.inicio == 0) || // Cuando los indices están en los extremos
        (c.fin == c.inicio - 1))  // Aquí va la condición que me dice que la cola está llena
    {
        llena = 1;
    }
    return llena;
}

int colaVacia(Cola c)
{
    int vacia = 0;

    if(c.inicio == c.fin) // Los indices están en el mismo lugar
    {
        vacia = 1;
    }

    return vacia;
}

// Inicializamos los indices inicio y fin en 0. Si están en el mismo lugar
// la cola no tiene datos

void inicializaCola(Cola *c)
{
    c->inicio = 0;
    c->fin = 0;
}