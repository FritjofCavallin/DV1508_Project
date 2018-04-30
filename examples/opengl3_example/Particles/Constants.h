#pragma once

/* Current fixed time step in simulation...*/
const float EMIT_STEP = 0.016f;
const float MAX_DURATION = 100.f;

// Default duration of an empty particle
const static float PARTICLE_DEFAULT_DUR = 5.f;

// Maximum number of particles emitted for a specific timeline
const static size_t PARTICLES_EMITTED_MAX = 1000;