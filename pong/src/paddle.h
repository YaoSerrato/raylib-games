#include <raylib.h>

class Paddle
{
    protected:
        /* protected methods */
        void LimitMovement()
        {
            if(y <= 0)
            {
                y = 0;
            }

            if(y + height >= GetScreenHeight())
            {
                y = GetScreenHeight() - height;
            }
        }

    public:
        /* public attributes */
        float x;
        float y;
        float width;
        float height;
        int speed;
        Color color;
    
        /* public methods */
        void Draw()
        {
            DrawRectangle(x, y, width, height, color);
        }

        void Update()
        {
            if(IsKeyDown(KEY_UP))
            {
                y -= speed;
            }
            else if( IsKeyDown(KEY_DOWN))
            {
                y += speed;
            }

            LimitMovement();
        }
};

/* CPUPaddle class inherits from Paddle class */
class CPUPaddle: public Paddle
{
    public:

        /* public methods */
        void Update(int ball_y)     // method overriding
        {
            if( y + height/2 > ball_y)
            {
                y -= speed;
            }
            
            if( y + height/2 <= ball_y)
            {
                y += speed;
            }

            LimitMovement();
        }
};