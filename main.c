#include <raylib.h>

// particle object containing position, velocity, and type

typedef struct
{
	float x;
	float y;
	float vx;
	float vy;
	int type;
} Particle;

int main(void)
{
	// defines the number of particles in the simulation as a global final variable
	#define NUM_PARTICLES 1000

	// This array holds the particle objects.
	Particle particles[NUM_PARTICLES];

	// I need to initialized the particles
	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		particles[i] = (Particle){
			.x = GetRandomValue(0, 1000),
			.y = GetRandomValue(0, 800),
			.vx = 0.0f,
			.vy = 0.0f,
			.type = GetRandomValue(0, 3)};
	}

	// Initializing raylib window
	InitWindow(1000, 800, "simulation");

	// Sets the target fps -- if not set it will run as fast as it can
	SetTargetFPS(1000);

	Color backgroundColor = {253, 240, 213, 255};
	Color niceBlue = {0, 47, 73, 255};

	// Allows window to be closed
	while (!WindowShouldClose())
	{
		BeginDrawing();

		EndDrawing();
	}

	return 0;
}
