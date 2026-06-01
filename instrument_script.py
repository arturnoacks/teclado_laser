import re
import json

with open("instrumentos.txt", "r", encoding="utf-8") as f:
    texto = f.read()

# captura linhas que começam com número
padrao = re.compile(r'^\s*(\d+)\s+(.+?)\s*$', re.MULTILINE)

instrumentos = {}

for numero, nome in padrao.findall(texto):
    instrumentos[int(numero)] = nome.strip()

with open("instrumentos.json", "w", encoding="utf-8") as f:
    json.dump(instrumentos, f, ensure_ascii=False, indent=4)

print(json.dumps(instrumentos, ensure_ascii=False, indent=4))