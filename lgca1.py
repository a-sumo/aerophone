import taichi as ti
import numpy as np
import time
# Define the lattice dimensions and number of particles
DIM = 256
NUM_PARTICLES = 6

ti.init(arch=ti.cuda)  # Use CUDA backend

# Initialize the lattice using Taichi fields
grid_lgca = ti.field(dtype=ti.i32, shape=(DIM, DIM, NUM_PARTICLES))
grid_lgca.from_numpy(np.random.randint(0, 2, (DIM, DIM, NUM_PARTICLES)))

@ti.func
def collide(x, y, z):
    total_particles = 0
    for p in ti.static(range(NUM_PARTICLES)):
        total_particles += grid_lgca[x, y, p]
    if total_particles > 3:
        for p in ti.static(range(NUM_PARTICLES)):
            grid_lgca[x, y, p] = 1 - grid_lgca[x, y, p]

@ti.kernel
def collide_kernel():
    for I in ti.grouped(grid_lgca):
        collide(I[0], I[1], I[2])

@ti.kernel
def propagate_kernel():
    for x, y in ti.ndrange(DIM, DIM):
        # Right
        grid_lgca[x, (y + 1) % DIM, 0] = grid_lgca[x, y, 0]
        # Upper right
        grid_lgca[(x + 1) % DIM, (y + 1) % DIM, 1] = grid_lgca[x, y, 1]
        # Upper
        grid_lgca[(x + 1) % DIM, y, 2] = grid_lgca[x, y, 2]
        # Upper left
        grid_lgca[(x + 1) % DIM, (y - 1) % DIM, 3] = grid_lgca[x, y, 3]
        # Left
        grid_lgca[x, (y - 1) % DIM, 4] = grid_lgca[x, y, 4]
        # Lower left
        grid_lgca[(x - 1) % DIM, y, 5] = grid_lgca[x, y, 5]



# Benchmark the Taichi version for 1,000 updates
start_time = time.time()

for _ in range(1000):
    collide_kernel()
    propagate_kernel()

end_time = time.time()

# Calculate the update rate
duration_taichi = end_time - start_time
update_rate_taichi = 1000 / duration_taichi
update_rate_taichi
print(f'Taichi update rate: {update_rate_taichi:.2f} updates per second')
