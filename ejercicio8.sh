#!/bin/bash

# Compilar el programa
g++ -std=c++11 -o ejercicio8 ejercicio8.cpp

# Lista de archivos de entrada y salida esperada
inputs=("10.in.txt" "100.in.txt" "1000.in.txt" "10000.in.txt" "100000.in.txt" "1000000.in.txt")
outputs=("10.out.txt" "100.out.txt" "1000.out.txt" "10000.out.txt" "100000.out.txt" "1000000.out.txt")

# Directorio de pruebas
test_dir="tests/ejercicio8"
output_dir="tests/ejercicio8Outs"

# Crear el directorio de salida si no existe
mkdir -p "$output_dir"

# Ejecutar las pruebas y comparar salidas
for i in ${!inputs[@]}; do
    input="${test_dir}/${inputs[$i]}"
    expected_output="${test_dir}/${outputs[$i]}"
    actual_output="${output_dir}/${inputs[$i]%.in.txt}.myout.txt"

    # Ejecutar el programa con la entrada
    ./ejercicio8 < "$input" > "$actual_output"

    # Comparar la salida actual con la esperada y contar diferencias
    diff_count=$(diff -y --suppress-common-lines "$actual_output" "$expected_output" | wc -l)
    
    # Mostrar el resultado
    echo "Prueba ${inputs[$i]}: ${diff_count} diferencias"
done
