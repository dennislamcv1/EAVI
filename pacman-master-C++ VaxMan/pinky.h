#ifndef PINKY_H
#define PINKY_H

#include "ghost.h"
#include "blinky.h"
#include "clyde.h"
#include "inky.h"

class       Blinky;
class       Clyde;
class       Inky;

class       Pinky : public Ghost
{
private:
    Blinky  *blinky;
    Clyde   *clyde;
    Inky    *inky;
    Q_OBJECT
public:
    void    ft_set_default();
    void    ft_calculate_point();
    void    ft_find_pacman();
    void    ft_set_friends(Blinky *bl, Clyde *cl, Inky *ink);
    void    ft_find_path();
            Pinky(QGraphicsScene *sc, int **map, PacMan *pc);
public slots:
    void    ft_move_ghost();
};

#endif // PINKY_H
