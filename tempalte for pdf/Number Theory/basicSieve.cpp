bool comp[N+10];
void sieve()
{
    comp[1] = 1;
    for(int i=2;i*i<=N;i++)
    {
        if(!comp[i])
        {
            for(int j=i*2;j<=N;j+=i)
            {
                comp[j] = 1;

            }
        }
    }
}