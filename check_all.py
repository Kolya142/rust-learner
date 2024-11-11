import os
import json

tasks = json.load(open("tasks.json"))
o_ = 0

for task in tasks:
    tn = task["tn"]
    if os.path.exists(f'./results/res_{tn}.txt') and "✅" in open(f'./results/res_{tn}.txt').read():
        continue
    o_ += 1
    with open("./current_task.txt", 'w') as f:
        f.write(tn)
    os.system(f'./check > ./results/res_{tn}.txt')
    with open(f'./results/res_{tn}.txt') as f:
        d = f.read()
        print(d)
        if "❌" in d:
            print(f'opening vscode for {tn}')
            os.system(f'code ./tasks/{tn}/app')
            break
        
if o_ == 0 or o_ == len(tasks):
    print("all tasks completed, now you officional rust junior!✅")