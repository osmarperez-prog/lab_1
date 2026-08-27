x = int(input("¿Cuántos números desea ingresar?: "))
numeros = []
for i in range(x):
    numero = int(input("Ingrese un número: "))    
    if numero not in numeros:
        numeros.append(numero)
print("Valores únicos:", numeros)
