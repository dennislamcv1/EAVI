#ifndef GAMECLASS_H
#define GAMECLASS_H

#include <fstream>
#include <string>
#include <ctime>
#include <random>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <QTimer>
#include <QTimerEvent>  // CHANGE timer is needed for ghost doubling event see https://doc.qt.io/qt-5/qtimerevent.html#QTimerEvent
#include <QObject>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "pacman.h"
#include "ghost.h"
#include "blinky.h"
#include "pinky.h"
#include "clyde.h"
#include "inky.h"

class   GameLoop : public QGraphicsView
{
// CHANGE	
  Q_OBJECT
private:
    QGraphicsScene                          *scene = nullptr;
    QGraphicsView                           *view = nullptr;
    QGraphicsPixmapItem                     **map_pix = nullptr;
    PacMan                                  *pacman = nullptr;
//    Blinky                                  *blinky;
//    Pinky                                   *pinky;
//    Clyde                                   *clyde;
//    Inky                                    *inky;
    int                                     **map_int;
    QTimer                                  *timer_pacman = nullptr;
    bool gameIsLost = false;        // CHANGE variable responsible for game termination

    QTimer                                  *timer_double_ghosts = nullptr;    // CHANGE - timer for doubling gosts

    Blinky                                  *blinkys[128];  // CHANGE - add room for multiple ghosts, at most 128 when the game is over
    Pinky                                   *pinkys[128];   // CHANGE - add room for multiple ghosts, at most 128 when the game is over
    Inky                                    *inkys[128];    // CHANGE - add room for multiple ghosts, at most 128 when the game is over
    Clyde                                   *clydes[128];   // CHANGE - add room for multiple ghosts, at most 128 when the game is over

    QTimer                                  *timer_blinkys[128];
    QTimer                                  *timer_pinkys[128];
    QTimer                                  *timer_inkys[128];
    QTimer                                  *timer_clydes[128];

// CHANGE end
public:
                                            GameLoop(char *file_name);
                                            ~GameLoop();
    void                                    ft_write_line_map(int *map, std::string str);
    void                                    ft_roll_game();
    void                                    ft_create_map();
    int                                     ft_check_file_inp(std::string str);
// CHANGE	

    void ft_set_is_game_lost(bool isLost);
public slots:
    void                                    ghostDoubling();  // CHANGE ghost doubling function 
    void                                    ghostDied();

// CHANGE end
};

#endif // GAMECLASS_H
