#include "Serializable.h"

#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

class Jugador: public Serializable
{
public:
    Jugador(const char * _n, int16_t _x, int16_t _y):pos_x(_x), pos_y(_y)
    {
        strncpy(name, _n, 80);
    };

    virtual ~Jugador(){};

    void to_bin()
    {
        alloc_data(sizeof(char) * MAX_NAME + sizeof(int16_t) * 2); //name + pos_x + pos_y
        char* tmp = _data + sizeof(int32_t);
        memcpy(tmp, (void*)name,sizeof(char) * MAX_NAME);
        tmp += sizeof(char) * MAX_NAME;
        memcpy(tmp, &pos_x,sizeof(int16_t));
        tmp += sizeof(int16_t); 
        memcpy(tmp, &pos_y,sizeof(int16_t));
    }

    int from_bin(char * data)
    {
        //
        return 0;
    }


public:

    static const size_t MAX_NAME = 80;
    char name[MAX_NAME];

    int16_t pos_x;
    int16_t pos_y;
};

int main(int argc, char **argv)
{
    Jugador one_r("-", 0, 0);
    Jugador one_w("Player_ONE", 123, 987);

    //Serializar y escribir one_w en un fichero
    //Leer el fichero en un buffer y "deserializar" en one_r
    //Mostrar el contenido one_r

    int file = open("one_w.txt", O_RDWR | O_TRUNC | O_CREAT);

    if(file < 0) return -1;

    one_w.to_bin(); //serialize player

    write(file, one_w.data(), one_w.size());

    close(file);

    return 0;
}
