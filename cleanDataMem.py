import subprocess
import matplotlib.pyplot as plt

def cut_str(string, start, end):
    return string.split(start)[1].split(end)[0]

def get_speed(array, env, type, size):
    for element in array:
        if element['env'] == env and element['type'] == type and element['size'] == size:
            return element['speed']
    return None

result1 = subprocess.Popen('grep -R "memory variable of" logs | sort', shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
stdout1, stderr1 = result1.communicate()

result2 = subprocess.Popen('grep -R "memory variable of" docker_files/logs | sort', shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
stdout2, stderr2 = result2.communicate()

print("Processing logs...")
values = []
for stdout in [stdout1, stdout2]:
    for line in stdout.decode().split('\n'):
        if "sec" in line:
            seconds = float(cut_str(line, " in ", " seconds"))
            env = cut_str(line, ") in ", " env!")
            speed = float(cut_str(line, "seconds (", " MiB/sec)"))
            size = cut_str(line, "memory variable of ", " MiB")
            type = "read" if "read" in line else "write" if "written" in line else "unknown"

            values.append({'time': seconds, 'env': env, 'speed': speed, 'size': size, 'type': type})

# For each memory size we save the speed in the correct array
memory_var_sizes = ['16', '32', '64', '128', '256']

read_speed_docker = []
read_speed_virtines = []
read_speed_normal = []

write_speed_docker = []
write_speed_virtines = []
write_speed_normal = []
for env in ['normal', 'virtines', 'docker']:
    for type in ['read', 'write']:
        for size in memory_var_sizes:
            if env == "normal":
                if type == "read":
                    read_speed_normal.append(get_speed(values, env, type, size))
                else:
                    write_speed_normal.append(get_speed(values, env, type, size))
            elif env == "virtines":
                if type == "read":
                    read_speed_virtines.append(get_speed(values, env, type, size))
                else:
                    write_speed_virtines.append(get_speed(values, env, type, size))
            elif env == "docker":
                if type == "read":
                    read_speed_docker.append(get_speed(values, env, type, size))
                else:
                    write_speed_docker.append(get_speed(values, env, type, size))

# Create the plots and save them
print("Creating plots...")
for type in ['read', 'write']:
    plt.figure(figsize=(8, 6))
    plt.plot(memory_var_sizes, write_speed_normal if type == "write" else read_speed_normal, marker='o', label='Normal environment')
    plt.plot(memory_var_sizes, write_speed_virtines if type == "write" else read_speed_virtines, marker='o', label='Virtines environment')
    plt.plot(memory_var_sizes, write_speed_docker if type == "write" else read_speed_docker, marker='o', label='Docker environment')
    plt.xlabel("Memory variable size (MiB)")
    plt.ylabel("Read Speed" if type == "read" else "Write Speed")
    plt.title("Speed vs File size")
    plt.legend()
    plt.grid(True)
    path = "mem_read_speeds.png" if type == "read" else "mem_write_speeds.png"
    plt.savefig(path)
    print(f"Figure saved at {path}!")