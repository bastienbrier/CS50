//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// paddle height and width
#define PADDLE_H 8
#define PADDLE_W 60

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // initiate ball velocity
    double velocity_x = drand48() + 0.5;
    double velocity_y = drand48() + 2.5;
    
    // sets the scoreboard to 0
    updateScoreboard(window, label, points);
    
    // wait for click to begin the game
    waitForClick();
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // make the paddle move
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - PADDLE_W / 2;
                
                // stops the paddle if it touches the left wall
                if (x <= 0)
                {
                    setLocation(paddle, 0, HEIGHT - 50);
                }
                // stops the paddle if it touches the right wall
                else if (x >= WIDTH - PADDLE_W)
                {
                    setLocation(paddle, WIDTH - PADDLE_W, HEIGHT - 50); 
                }
                else
                {
                    setLocation (paddle, x, HEIGHT - 50);
                }
            }
        }
        
        // move ball
        move(ball, velocity_x, velocity_y);
        
        // bounces if the ball touches the right wall
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            velocity_x = -velocity_x;
        }
        
        // bounces if the ball touches the left wall
        else if (getX(ball) <= 0)
        {
            velocity_x = -velocity_x;
        }
        
        // bounces if the ball touches the upper wall
        else if (getY(ball) <= 0)
        {
            velocity_y = -velocity_y;
        }
        
        // disappears and creates new ball if the ball touches the bottom wall
        else if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives--;
            if (lives > 0)
            {
                waitForClick();
                removeGWindow(window, ball);
                ball = initBall(window);
            }
            else if (lives == 0)
            {
                setColor(label, "RED");
                setColor(ball, "RED");
            }
        }
        
        GObject object = detectCollision(window, ball);
        if (object != NULL)
        {
            // bounces if the ball touches the paddle
            if (object == paddle)
            {
                velocity_y = -velocity_y;
                // changes the color when contact for 20ms
                setColor(paddle, "LIGHT_GRAY");
                pause(20);
                setColor(paddle, "BLACK");
            }
            
            // bounces if the ball touches a brick and removes it
            // adds a point, retires a brickk
            else if (object != paddle && strcmp(getType(object), "GRect") == 0)
            {
                removeGWindow(window, object);
                velocity_y = -velocity_y;
                points++;
                bricks--;
                updateScoreboard(window, label, points);
                if (points == 50)
                {
                    setColor(label, "GREEN");
                }
            }
        }

        pause(10);
    }
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // initializes the bricks
    for (int i = 0; i < ROWS; i++)
    {
        // colors of the bricks
        string Colors[] = {"RED", "ORANGE", "YELLOW", "GREEN", "CYAN"};
        
        for (int j = 0; j < COLS; j++)
        {
            GRect brick = newGRect(5 + 39.5 * j, 50 + 14 * i, 34.5, 10);
            setFilled(brick, true);
            setColor(brick, Colors[i]);
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH / 2 - RADIUS, HEIGHT / 2 - RADIUS, RADIUS * 2, RADIUS * 2);
    setFilled(ball, true);
    setColor(ball, "BLACK");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(WIDTH / 2 - PADDLE_W / 2, HEIGHT - 50, PADDLE_W, PADDLE_H);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
 
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel(""); 
    setFont(label, "SansSerif-44");
    setColor(label, "LIGHT_GRAY");
    add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
