
int hacerPositivo(int i) {
    if (i < 0)
    {
        return i * -1;
    }
    return i;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int potencia(int base, int exponente) 
{
    int resultado = 1;
    for (int i = 0; i < exponente; ++i) {
        resultado *= base;
    }
    return resultado;
}