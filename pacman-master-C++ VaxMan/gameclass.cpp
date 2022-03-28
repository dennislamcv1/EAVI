#include "gameclass.h"
// CHANGES THROUGHOUT THE MODULE

int     GameLoop::ft_check_file_inp(std::string str)
{
  int i;

  i = 0;
  while (str[i])
  {
    if (str[i] < '0' || str[i] > '4')
      return (1);
    i++;
  }
  return (0);
}

GameLoop::~GameLoop()
{
  delete scene;
  delete view;
  delete pacman;
  delete timer_pacman;
  for (int i = 0; i < size_x; i++)
  {
    for (int j = 0; j < size_y; j++)
    {
      delete map_pix[i];
      delete map_int[i];
    }
  }
  delete[]map_pix;
  delete[]map_int;

  // CHANGE delete
  delete timer_double_ghosts;
  for (int i = 0; i < 128; i++)
  {
    delete blinkys[i];
    delete timer_blinkys[i];
    delete pinkys[i];
    delete timer_pinkys[i];
    delete inkys[i];
    delete timer_inkys[i];
    delete clydes[i];
    delete timer_clydes[i];
  }
  // CHANGE end

}

void    GameLoop::ft_roll_game()
{
  timer_pacman = new QTimer();
  QObject::connect(timer_pacman, SIGNAL(timeout()), pacman, SLOT(ft_move()));
  timer_pacman->start(300);

  timer_double_ghosts = new QTimer();  // CHANGE - special timer for doubling the ghosts event
  QObject::connect(timer_double_ghosts, SIGNAL(timeout()), this, SLOT(ghostDoubling()));
  timer_double_ghosts->start(30000);   // CHANGE - every 30 second survived ghosts are doubled
  
  ft_set_is_game_lost(false);

  // CHANGE - setup all slots excluding the ones in 0 position to NULL and assign slots in 0 position to corresponding individual objects
  timer_blinkys[0] = new QTimer();
  //blinkys[0] = new Blinky(scene, map_int, pacman);
  QObject::connect(timer_blinkys[0], SIGNAL(timeout()), blinkys[0], SLOT(ft_move_ghost()));
  QObject::connect(blinkys[0], SIGNAL(ghostDiedSignal()), this, SLOT(ghostDied()));
  timer_blinkys[0]->start(400);

  timer_pinkys[0] = new QTimer();
  //pinkys[0]   = pinky;
  QObject::connect(timer_pinkys[0], SIGNAL(timeout()), pinkys[0], SLOT(ft_move_ghost()));
  QObject::connect(pinkys[0], SIGNAL(ghostDiedSignal()), this, SLOT(ghostDied()));
  timer_pinkys[0]->start(400);

  timer_inkys[0] = new QTimer();
  //inkys[0]    = inkys[0];
  QObject::connect(timer_inkys[0], SIGNAL(timeout()), inkys[0], SLOT(ft_move_ghost()));
  QObject::connect(inkys[0], SIGNAL(ghostDiedSignal()), this, SLOT(ghostDied()));
  timer_inkys[0]->start(400);

  timer_clydes[0] = new QTimer();
  //clydes[0]   = clydes[0];
  QObject::connect(timer_clydes[0], SIGNAL(timeout()), clydes[0], SLOT(ft_move_ghost()));
  QObject::connect(clydes[0], SIGNAL(ghostDiedSignal()), this, SLOT(ghostDied()));
  timer_clydes[0]->start(400);

  for (int i = 1; i < 128; i++)
  {
    blinkys[i] = NULL;
    timer_blinkys[i] = NULL;
    pinkys[i] = NULL;
    timer_pinkys[i] = NULL;
    inkys[i] = NULL;
    timer_inkys[i] = NULL;
    clydes[i] = NULL;
    timer_clydes[i] = NULL;
  }
  // CHANGE end
}

void    GameLoop::ft_create_map()
{
  for (int i = 0; i < size_x; i++)
  {
    for (int j = 0; j < size_y; j++)
    {
      if (map_int[i][j] == 1)
      {
        map_pix[i][j].setPixmap(QPixmap(":/pics/greystone.png"));
        map_pix[i][j].setPos(j * 32, i * 32);
        scene->addItem(&(map_pix[i][j]));
      }
      if (map_int[i][j] == 3)
      {
        map_pix[i][j].setPixmap(QPixmap(":/pics/ball.png"));
        map_pix[i][j].setPos(j * 32, i * 32);
        scene->addItem(&(map_pix[i][j]));
      }
      if (map_int[i][j] == 4)
      {
        map_pix[i][j].setPixmap(QPixmap(":/pics/energizer.png"));
        map_pix[i][j].setPos(j * 32, i * 32);
        scene->addItem(&(map_pix[i][j]));
      }
    }
  }
}

void GameLoop::ft_set_is_game_lost(bool isLost)
{
  gameIsLost = isLost;
  if (pacman != nullptr)
  {
    pacman->ft_set_is_game_lost(isLost);
  }
}

void    GameLoop::ft_write_line_map(int *map, std::string str)
{
  for (int i = 0; i < size_y; i++)
    map[i] = str[i] - '0';
}
GameLoop::GameLoop(char *file_name)
{
  std::ifstream   input;
  std::string     temp;
  int             nb;

  map_int = new int *[size_x];
  map_pix = new QGraphicsPixmapItem *[size_x];
  for (int i = 0; i < size_x; i++)
  {
    map_int[i] = new int[size_y];
    map_pix[i] = new QGraphicsPixmapItem[size_y];
  }

  input.open(file_name);
  if (input.is_open())
  {
    nb = 0;
    while (std::getline(input, temp))
    {
      if (temp.length() != size_y)
      {
        std::cout << "File error.\n";
        exit(0);
      }
      if (ft_check_file_inp(temp))
      {
        std::cout << "File error.\n";
        exit(0);
      }
      ft_write_line_map(map_int[nb], temp);
      nb++;
    }
    if (nb != size_x)
    {
      std::cout << "File error.\n";
      exit(0);
    }
    input.close();
  }
  else
  {
    std::cout << "File missing: " << file_name << ".\n";
    exit(0);
  }
  scene = new QGraphicsScene();
  view = new QGraphicsView();
  this->setScene(scene);
  ft_create_map();
  this->setStyleSheet("background-color:black;");
  pacman = new PacMan(map_int, map_pix, scene);
  pacman->setFlag(QGraphicsPixmapItem::ItemIsFocusable);
  pacman->setFocus();
  blinkys[0] = new Blinky(scene, map_int, pacman);
  pinkys[0] = new Pinky(scene, map_int, pacman);
  clydes[0] = new Clyde(scene, map_int, pacman);
  inkys[0] = new Inky(scene, map_int, pacman);
  //blinkys[0]->ft_set_friends(pinkys[0], clydes[0], inkys[0]);
  //pinkys[0]->ft_set_friends(blinkys[0], clydes[0], inkys[0]);
  //clydes[0]->ft_set_friends(blinkys[0], pinkys[0], inkys[0]);
  //inkys[0]->ft_set_friends(blinkys[0], pinkys[0], clydes[0]);
}

// CHANGE - double the number of survived ghosts
void    GameLoop::ghostDoubling()
{
  int nBlinkys = 0;
  int nPinkys = 0;
  int nInkys = 0;
  int nClydes = 0;
  for (int i = 0; i < 128; i++)
  {
    if (blinkys[i] != NULL && !blinkys[i]->GetIsDead())
      nBlinkys++;
    if (pinkys[i] != NULL && !pinkys[i]->GetIsDead())
      nPinkys++;
    if (inkys[i] != NULL && !inkys[i]->GetIsDead())
      nInkys++;
    if (clydes[i] != NULL && !clydes[i]->GetIsDead())
      nClydes++;
  }
  //std::cout << "Total number of ghosts: " << nBlinkys + nPinkys + nInkys + nClydes << "\n";
  if (nBlinkys > 64 || nPinkys > 64 || nInkys > 64 || nClydes > 64 || (nBlinkys + nPinkys + nInkys + nClydes) > 128)
  {
    ft_set_is_game_lost(true);
  }
  else
  {
    auto nBlinkysLeft = nBlinkys;
    auto nPinkysLeft = nPinkys;
    auto nInkysLeft = nInkys;
    auto nClydesLeft = nClydes;
    for (int i = 0; i < 128; i++)
    {
      if (nBlinkysLeft <= 0)
        break;
      if (blinkys[i] == NULL || blinkys[i]->GetIsDead())
      {
        if (timer_blinkys[i] != NULL)
        {
          timer_blinkys[i]->stop();
        }

        timer_blinkys[i] = new QTimer();
        blinkys[i] = new Blinky(scene, map_int, pacman);
        QObject::connect(timer_blinkys[i], SIGNAL(timeout()), blinkys[i], SLOT(ft_move_ghost()));
        QObject::connect(blinkys[i], SIGNAL(ghostDiedSignal()), this, SLOT(ghostDied()));
        timer_blinkys[i]->start(400);
        nBlinkysLeft--;
      }
    }
    for (int i = 0; i < 128; i++)
    {
      if (nPinkysLeft <= 0)
        break;
      if (pinkys[i] == NULL || pinkys[i]->GetIsDead())
      {
        if (timer_pinkys[i] != NULL)
        {
          timer_pinkys[i]->stop();
        }

        timer_pinkys[i] = new QTimer();
        pinkys[i] = new Pinky(scene, map_int, pacman);
        QObject::connect(timer_pinkys[i], SIGNAL(timeout()), pinkys[i], SLOT(ft_move_ghost()));
        QObject::connect(pinkys[i], SIGNAL(ghostDiedSignal()), this, SLOT(ghostDied()));
        timer_pinkys[i]->start(400);
        nPinkysLeft--;
      }
    }
    for (int i = 0; i < 128; i++)
    {
      if (nInkysLeft <= 0)
        break;
      if (inkys[i] == NULL || inkys[i]->GetIsDead())
      {
        if (timer_inkys[i] != NULL)
        {
          timer_inkys[i]->stop();
        }

        timer_inkys[i] = new QTimer();
        inkys[i] = new Inky(scene, map_int, pacman);
        QObject::connect(timer_inkys[i], SIGNAL(timeout()), inkys[i], SLOT(ft_move_ghost()));
        QObject::connect(inkys[i], SIGNAL(ghostDiedSignal()), this, SLOT(ghostDied()));
        timer_inkys[i]->start(400);
        nInkysLeft--;
      }
    }
    for (int i = 0; i < 128; i++)
    {
      if (nClydesLeft <= 0)
        break;
      if (clydes[i] == NULL || clydes[i]->GetIsDead())
      {
        if (timer_clydes[i] != NULL)
        {
          timer_clydes[i]->stop();
        }

        timer_clydes[i] = new QTimer();
        clydes[i] = new Clyde(scene, map_int, pacman);
        QObject::connect(timer_clydes[i], SIGNAL(timeout()), clydes[i], SLOT(ft_move_ghost()));
        QObject::connect(clydes[i], SIGNAL(ghostDiedSignal()), this, SLOT(ghostDied()));
        timer_clydes[i]->start(400);
        nClydesLeft--;
      }
    }
  }
  // CHANGE end
}

void GameLoop::ghostDied()
{
  // Notification when a ghost deleted
}
