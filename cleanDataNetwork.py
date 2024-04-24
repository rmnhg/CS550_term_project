import subprocess
import matplotlib.pyplot as plt

def cut_str(string, start, end):
    return string.split(start)[1].split(end)[0]

def get_speed(array, env, size):
    for element in array:
        if element['env'] == env and element['size'] == size:
            return element['speed']
    return None

result1 = subprocess.Popen('grep -R "Downloaded file of " logs | sort', shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
stdout1, stderr1 = result1.communicate()

result2 = subprocess.Popen('grep -R "Downloaded file of " docker_files/logs | sort', shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
stdout2, stderr2 = result2.communicate()

print("Processing logs...")
values = []
for stdout in [stdout1, stdout2]:
    for line in stdout.decode().split('\n'):
        if "sec" in line:
            seconds = float(cut_str(line, " in ", " seconds"))
            env = cut_str(line, "MiBps) in the ", " environment.")
            speed = float(cut_str(line, " or ", " MiBps)"))
            size = int(float(cut_str(line, "bytes (", " MiBs)")))

            values.append({'time': seconds, 'env': env, 'speed': speed, 'size': size})

# For each file size we save the speed in the correct array
file_sizes = ['16', '32', '64', '128', '256']

download_speed_docker = []
download_speed_virtines = []
download_speed_normal = []
for env in ['normal', 'virtines', 'docker']:
    for size in file_sizes:
        if env == "normal":
            download_speed_normal.append(get_speed(values, env, int(size)))
        elif env == "virtines":
            download_speed_virtines.append(get_speed(values, env, int(size)))
        elif env == "docker":
            download_speed_docker.append(get_speed(values, env, int(size)))


# Create the plots and save them
print("Creating plots...")
plt.figure(figsize=(8, 6))
plt.plot(file_sizes, download_speed_normal, marker='o', label='Normal environment')
plt.plot(file_sizes, download_speed_virtines, marker='o', label='Virtines environment')
plt.plot(file_sizes, download_speed_docker, marker='o', label='Docker environment')
plt.xlabel("File size (MiB)")
plt.ylabel("Download Speed (MiB/sec)")
plt.title("Download Speed vs File size")
plt.legend()
plt.grid(True)
path = "download_speeds.png"
plt.savefig(path)
print(f"Figure saved at {path}!")