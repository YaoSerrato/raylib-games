/* Conway's Game of Life
    1. underpopulation: any live cell with fewer than two live neighbours dies.
    3. stasis: any live cell with two or three live neighbours lives, unchanged, to the next generation.
    2. overpopulation: any live cell with more than three live neighbours dies.
    4. reproduction: any dead cell with exactly three live neighbours will come to life.
*/

#include <iostream>
#include "main.h"
#include "simulation.hpp"

#define     CELL_SIZE               (5)
#define     WINDOW_WIDTH            (1500)
#define     WINDOW_HEIGHT           (900)
#define     FRAMES_PER_SECOND_MAX   (12)
#define     FRAMES_PER_SECOND_MIN   (5)
#define     COLOR_BACKGROUND        CLITERAL(Color){29, 29, 29, 255}

int main()
{
    Simulation simulation(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);
    int simulatioFPS = FRAMES_PER_SECOND_MAX;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Conway's Game Of Life");
    SetTargetFPS(simulatioFPS);

    // simulation loop
    while (!WindowShouldClose())
    {
        // event handling
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePosition = GetMousePosition();
            int row = mousePosition.y / CELL_SIZE;
            int col = mousePosition.x / CELL_SIZE;
            simulation.simulationToggleGridCell(row, col);
        }
        else
        {
        }


        if(IsKeyPressed(KEY_ENTER))
        {
            simulation.simulationStart();
            SetWindowTitle("Simulation is running...");
        }
        else if(IsKeyPressed(KEY_SPACE))
        {
            simulation.simulationStop();
            SetWindowTitle("Simulation is paused.");
        }
        else if(IsKeyPressed(KEY_F))
        {
            // increase speed of simulation
            if(simulatioFPS < FRAMES_PER_SECOND_MAX)
            {
                simulatioFPS += 1;
            }
            else
            {
                // the limit has been reached
            }
            SetTargetFPS(simulatioFPS);
        }
        else if(IsKeyPressed(KEY_S))
        {
            // decrease speed of simulation
            if(simulatioFPS > FRAMES_PER_SECOND_MIN)
            {
                simulatioFPS -= 1;
            }
            else
            {
                // the limit has been reached
            }
            SetTargetFPS(simulatioFPS);
        }
        else if(IsKeyPressed(KEY_R))
        {
            simulation.simulationSetInitialStateRandom();
        }
        else if(IsKeyPressed(KEY_C))
        {
            simulation.simulationClearGrid();
        }
        else
        {
            // another key different than ENTER or SPACE was pressed
        }

        // updating state
        simulation.simulationUpdate();

        // drawing objects
        BeginDrawing();
        ClearBackground(COLOR_BACKGROUND);

        simulation.simulationDraw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}