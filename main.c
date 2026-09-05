#include <limits.h>
#include <math.h>
#include <raylib.h>

// particle object containing position, velocity, and type

// Some fun colors
const Color pal_red_orange = {0xF9, 0x41, 0x44, 0xFF};
const Color pal_orange_red = {0xF3, 0x72, 0x2C, 0xFF};
const Color pal_orange = {0xF8, 0x96, 0x1E, 0xFF};
const Color pal_coral = {0xF9, 0x84, 0x4A, 0xFF};
const Color pal_yellow = {0xF9, 0xC7, 0x4F, 0xFF};

const Color pal_light_green = {0x90, 0xBE, 0x6D, 0xFF};
const Color pal_teal = {0x43, 0xAA, 0x8B, 0xFF};
const Color pal_dark_teal = {0x4D, 0x90, 0x8E, 0xFF};
const Color pal_slate_blue = {0x57, 0x75, 0x90, 0xFF};
const Color pal_ocean_blue = {0x27, 0x7D, 0xA1, 0xFF};

typedef struct {
  float x;
  float y;
  float vx;
  float vy;
  int type;
  int mass;
} Particle;

int main(void) {
// defines the number of particles in the simulation as a global final variable
#define NUM_PARTICLES 100
#define PARTICLE_SIZE 3.0f
#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 1000

  // This array holds the particle objects.
  Particle particles[NUM_PARTICLES];

  // I need to initialized the particles
  for (int i = 0; i < NUM_PARTICLES; i++) {
    int type = GetRandomValue(0, 3);
    particles[i] = (Particle){
        .x = GetRandomValue(0 + PARTICLE_SIZE, WINDOW_WIDTH - PARTICLE_SIZE),
        .y = GetRandomValue(0 + PARTICLE_SIZE, WINDOW_HEIGHT - PARTICLE_SIZE),
        .vx = GetRandomValue(-5, 5),
        .vy = GetRandomValue(-5, 5),
        .type = type,
        .mass = 4 - type};
  }

  // Initializing raylib window
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "simulation");

  // Sets the target fps -- if not set it will run as fast as it can
  SetTargetFPS(60);

  Color particleColors[4] = {pal_ocean_blue, pal_light_green, pal_yellow,
                             pal_red_orange};

  // Main Window Loop
  while (!WindowShouldClose()) {

    // LOGIC PASS

    // Loops through every particle and updates its position and velocity also
    // accounting for collisions. ---- O(N^2)
    for (int i = 0; i < NUM_PARTICLES; i++) {

      Particle *p = &particles[i];

      // updates the position
      p->x = p->x + p->vx;
      p->y = p->y + p->vy;
    }
    for (int i = 0; i < NUM_PARTICLES; i++) {
      Particle *p = &particles[i];

      // Loops through every particle and checks for collisions
      for (int j = i + 1; j < NUM_PARTICLES; j++) {
        Particle *p2 = &particles[j];

        float closeDistance =
            PARTICLE_SIZE +
            10.0f; // I will use this later for forces calculations
        bool isClose = (fabsf(p->x - p2->x) < closeDistance) &&
                       (fabsf(p->y - p2->y) < closeDistance);

        if (i != j) { // If a collision is possible/they are
                      // different particles
          if (isClose) {

            bool isCollision = (fabsf(p->x - p2->x) < PARTICLE_SIZE) &&
                               (fabsf(p->y - p2->y) < PARTICLE_SIZE);
            if (isCollision) {

              float vi = p->vx;
              float v2i = p2->vx;
              p->vx = ((p->mass - p2->mass) * vi + (2 * p2->mass * v2i)) /
                      (p->mass + p2->mass);
              p2->vx = ((p2->mass - p->mass) * v2i + (2 * p->mass * vi)) /
                       (p2->mass + p->mass);

              vi = p->vy;

              v2i = p2->vy;
              p->vy = ((p->mass - p2->mass) * vi + (2 * p2->mass * v2i)) /
                      (p->mass + p2->mass);
              p2->vy = ((p2->mass - p->mass) * v2i + (2 * p->mass * vi)) /
                       (p2->mass + p->mass);
            }
          }
        }
      }

      // Toroidal Space, a space that wraps around itself. If a particle were to
      // pass into the border it would instantly teleport to the other side

      // CHANGE -- NOW THEY WILL BOUNCE OFF THE WALLS
      if (p->x < 0 + PARTICLE_SIZE) {
        p->x += PARTICLE_SIZE;
        p->vx *= -1;
      }
      if (p->x > WINDOW_WIDTH - PARTICLE_SIZE) {
        p->x -= PARTICLE_SIZE;
        p->vx *= -1;
      }
      if (p->y < 0 + PARTICLE_SIZE) {
        p->y += PARTICLE_SIZE;
        p->vy *= -1;
      }
      if (p->y > WINDOW_HEIGHT - PARTICLE_SIZE) {
        p->y -= PARTICLE_SIZE;
        p->vy *= -1;
      }
    }

    // update velocities with a drag coefiecent of 0.9
    // p->vx = p->vx * 0.95f;
    // p->vy = p->vy * 0.95f;

    // RENDER PASS
    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(20, 20);

    // Draws every particle in the array as circles with radius 1. ---- O(N)
    // complexity
    for (int i = 0; i < NUM_PARTICLES; i++) {
      Particle *p = &particles[i];

      DrawRectangle(p->x, p->y, 2 * PARTICLE_SIZE, 2 * PARTICLE_SIZE,
                    particleColors[p->type]);
    }
    EndDrawing();
  }

  return 0;
}
