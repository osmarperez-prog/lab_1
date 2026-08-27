n = int(input("¿Cuántos números desea sumar?: "))

suma = 0

for i in range(n):
    numero = float(input("Ingrese un número: "))
    suma = suma + numero

print("La suma total es:", suma)
