void init_moteur()
{

}

void close_moteur()
{

}

int main(int argc, char const *argv[])
{
    int erreur;
    init_moteur();
    do
    {
        erreur = menu_ouverture();
    } while (erreur != 0);
    close_moteur();
    return 0;
}