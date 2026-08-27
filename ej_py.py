n = int(input("Cantidad de numeros para sumar: "))
suma = 0
for i in range(n):
    num = float(input("Ingresar numero para sumar: "))
    suma += num
print("Total:", suma)

numero = input("Numero para invertir: ")
numero_invertido = numero[::-1]
print("Invertido:", numero_invertido)

nombre = input("Nombre: ")
edad = input("Edad: ")
profesion = input("Profesion: ")
print("Hola " + nombre + " Tienes " + edad + " años y eres " + profesion + ".")

x = int(input("Cantidad de numeros: "))
numeros = []
for i in range(x):
    valor = float(input("Ingresar numero: "))
    numeros.append(valor)

unicos = list(set(numeros))
print("Los valores unicos son:", unicos)
