N_32 factorial(N_32 n)
{
    N_32 value = 1;

    for(; n; --n)
        value *= n;

    return value;
}


N_32 C(N_32 n, N_32 k)
{
    return factorial(n)/( factorial(k) * factorial(n-k) );
}
