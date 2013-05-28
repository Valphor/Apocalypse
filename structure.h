typedef struct Unite Unite;
typedef struct Caracteristique Caracteristique;
typedef struct Building Building;
typedef struct Rect Rect;


struct Caracteristique
{
    int vie;
    int puissance;
    int armure;
};

struct Unite
{
    SDL_Rect position;
    Caracteristique carac;
    char type;
};

struct Building
{
    SDL_Rect position;
    Caracteristique carac;
    char type;
};

struct Global
{
    Unite unite;
    Building building;
};
