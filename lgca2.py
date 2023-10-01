import taichi as ti
import numpy as np
import time

# Define the lattice dimensions and number of particles
DIM = 256
NUM_PARTICLES = 6

# use vulkan 
ti.init(arch=ti.vulkan)  # Use Vulkan backend

# Initialize the lattice using Taichi fields
grid_lgca = ti.field(dtype=ti.i32, shape=(DIM, DIM, NUM_PARTICLES))
grid_lgca.from_numpy(np.random.randint(0, 2, (DIM, DIM, NUM_PARTICLES)))

# Look-up table for collisions
collision_table = ti.field(dtype=ti.i32, shape=(2, 2, 2, 2, 2, 2, NUM_PARTICLES))

@ti.kernel
def init_collision_table():
    for states in ti.grouped(collision_table):
        total = 0
        for i in ti.static(range(NUM_PARTICLES)):
            total += states[i]
        if total > 3:
            for p in ti.static(range(NUM_PARTICLES)):
                collision_table[states[0], states[1], states[2], states[3], states[4], states[5], p] = 1 - states[p]
        else:
            for p in ti.static(range(NUM_PARTICLES)):
                collision_table[states[0], states[1], states[2], states[3], states[4], states[5], p] = states[p]


init_collision_table()

@ti.kernel
def update_kernel():
    for x, y in ti.ndrange(DIM, DIM):
        states = ti.Vector([grid_lgca[x, y, p] for p in ti.static(range(NUM_PARTICLES))])
        
        # Collide
        for p in ti.static(range(NUM_PARTICLES)):
            grid_lgca[x, y, p] = collision_table[states[0], states[1], states[2], states[3], states[4], states[5], p]
        
        # Propagate
        grid_lgca[x, (y + 1) % DIM, 0] = grid_lgca[x, y, 0]
        grid_lgca[(x + 1) % DIM, (y + 1) % DIM, 1] = grid_lgca[x, y, 1]
        grid_lgca[(x + 1) % DIM, y, 2] = grid_lgca[x, y, 2]
        grid_lgca[(x + 1) % DIM, (y - 1) % DIM, 3] = grid_lgca[x, y, 3]
        grid_lgca[x, (y - 1) % DIM, 4] = grid_lgca[x, y, 4]
        grid_lgca[(x - 1) % DIM, y, 5] = grid_lgca[x, y, 5]

# Benchmark the Taichi version for 1,000 updates
start_time = time.time()

for _ in range(1000):
    update_kernel()

end_time = time.time()

# Calculate the update rate
duration_taichi = end_time - start_time
update_rate_taichi = 1000 / duration_taichi
print(f'Taichi update rate: {update_rate_taichi:.2f} updates per second')

gui = ti.GUI('LGCA Visualization', (DIM, DIM))

while True:
    for _ in range(10):  # Update 10 times for smoother visualization
        update_kernel()
    visualization = np.zeros((DIM, DIM, 3), dtype=np.uint8)
    for p in range(NUM_PARTICLES):
        visualization += grid_lgca.to_numpy()[:, :, p].reshape(DIM, DIM, 1) * 255
    gui.set_image(visualization)
    gui.show()