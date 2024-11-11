import os
import json

tasks = json.load(open("tasks.json"))

for task in tasks:
    tn = task["tn"]
    i = task["i"].replace('\\n', '\n')
    o = task["o"].replace('\\n', '\n')
    if os.path.exists(f'./tasks/{tn}'):
        continue
    os.mkdir(f'./tasks/{tn}')
    os.mkdir(f'./tasks/{tn}/data')
    os.mkdir(f'./tasks/{tn}/app')
    os.system(f'cd ./tasks/{tn}/app; cargo init; cd ../../..')
    with open(f'./tasks/{tn}/data/input.txt', 'w') as f:
        f.write(i)
    with open(f'./tasks/{tn}/data/output.txt', 'w') as f:
        f.write(o)