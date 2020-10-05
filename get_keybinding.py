from os import system
keys = []
i = 0
done = False
fi = -1
with open("config.def.h") as f:
    data = f.read()
    data = data.split("\n")
for i, name in enumerate(data):
    if "keys[]" in name:
        fi = i
    if "#define" in name and "Mask" in name:
        keys.append(name)
    if fi >= 0 and "};" in name:
        ei = i
        break
for i in range(fi+1, ei):
    if "//" not in data[i]:
        keys.append(data[i])
with open("keys.txt", "+w") as f:
    for i in keys:
        i = i+"\n"
        f.write(i)
system("$EDITOR keys.txt")
