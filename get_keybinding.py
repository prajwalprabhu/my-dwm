from os import system
keys = []
modkeys={}
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
        modkeys[name[2]]=name[3]
                
    if fi >= 0 and "};" in name:
        ei = i
        break
for i in range(fi+1, ei):
    if "//" not in data[i]:
        keys.append(data[i])
print(modkeys)
for i in keys:
    i.replace(modkeys[2],modkeys[3])


with open("keys.txt", "+w") as f:
    for i in keys:
        i = i+"\n"
        f.write(i)
system("$EDITOR keys.txt")
