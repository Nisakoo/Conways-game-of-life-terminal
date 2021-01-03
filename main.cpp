#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

int** generateMap(int sw, int sh)
{
  int **map = new int*[sh];

  // Generate map
  for(int y = 0;y < sh;y++)
  {
    map[y] = new int[sw];
    for(int x = 0;x < sw;x++)
    {
      map[y][x] = rand() % 2;
    }
  }

  return map;
}

int** updateMap(int **map, int sw, int sh)
{
  int **new_map = new int*[sh];
  int checking_zone[8][2] = {{-1, 1}, {0, 1}, {1, 1}, {-1, 0}, {1, 0}, {-1, -1}, {0, -1}, {1, -1}};

  for(int y = 0;y < sh;y++)
  {
    new_map[y] = new int[sw];
    for(int x = 0;x < sw;x++)
    {
      int neighborhoods = 0;

      for(int cell = 0;cell < 8;cell++)
      {
        int new_x = x + checking_zone[cell][0];
        int new_y = y + checking_zone[cell][1];

        if(!((new_x < 0 || new_y < 0) || (new_x >= sw || new_y >= sh)))
        {
          if(map[new_y][new_x] == 1)
          {
            neighborhoods++;
          }
        }
      }

      if(map[y][x] == 1)
      {
        new_map[y][x] = neighborhoods == 2 || neighborhoods == 3?1:0;
      }
      else
      {
        new_map[y][x] = neighborhoods == 3?1:0;
      }
    }
  }

  return new_map;
}

void updateConsole(int **map, int sw, int sh)
{
  // Clear console
  system("clear");

  // Colored output
  printf("\033[32m");

  // Draw top border
  for(int i = 0; i < sw*2+4;i++)
  {
    printf("-");
  }

  printf("\n");

  // Draw map
  for(int y = 0; y < sh;y++)
  {
    for(int x = 0; x < sw;x++)
    {
      if(map[y][x] == 1)
      {
        if(x == 0)
        {
          printf("| # ");
        }
        else
        {
          printf("# ");
        }
      }
      else
      {
        if(x == 0)
        {
          printf("|   ");
        }
        else
        {
          printf("  ");
        }
      }
    }
    printf(" |\n");
  }

  // Draw bottom border
  for(int i = 0; i < sw*2+4;i++)
  {
    printf("-");
  }

  printf("\n");
}

int main(int argc, char *argv[])
{
  int screen_width = 48;int screen_height = 32;

  unsigned long int seed = time(NULL);
  srand(seed);

  int** map = generateMap(screen_width, screen_height);

  unsigned long int iterations = 1;

  while(true)
  {
    this_thread::sleep_for(chrono::milliseconds(100));

    updateConsole(map, screen_width, screen_height);
    // Some information
    printf("SEED:%lu | ITERATIONS:%lu", seed, iterations);
    printf("\n");

    map = updateMap(map, screen_width, screen_height);

    iterations++;
  }

  return 0;
}
