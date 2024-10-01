#include <raylib.h>

class Ball
{
    /* public attributes */
    public:
        float x;
        float y;
        int speed_x;
        int speed_y;
        int radius;
        Color color;
        int player_score;
        int cpu_score;
    
    /* public methods */
    void Draw()
    {
        DrawCircle(x, y, radius, color);
    }

    void Update()
    {
        x += speed_x;
        y += speed_y;

        if( (y + radius >= GetScreenHeight()) || (y - radius <= 0) )
        {
            speed_y *= -1;
        }

        if( (x + radius >= GetScreenWidth()) || (x - radius <= 0) )
        {
            speed_x *= -1;
        }

        if(x + radius >= GetScreenWidth())
        {
            cpu_score++;
        }
        else if(x - radius <= 0)
        {
            player_score++;
        }
    }
};