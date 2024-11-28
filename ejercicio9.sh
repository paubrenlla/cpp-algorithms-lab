#!/bin/bash

# Compilar el programa
g++ -std=c++11 -o ejercicio9 ejercicio9.cpp

# Lista de archivos de entrada y salida esperada
inputs=("15.in.txt" "25.in.txt" "50.in.txt" "75.in.txt" "100.in.txt" "1000.in.txt")
outputs=("15.out.txt" "25.out.txt" "50.out.txt" "75.out.txt" "100.out.txt" "1000.out.txt")

# Directorio de pruebas
test_dir="tests/ejercicio9"
output_dir="tests/ejercicio9Outs"

# Crear el directorio de salida si no existe
mkdir -p "$output_dir"

# Ejecutar las pruebas y comparar salidas
for i in ${!inputs[@]}; do
    input="${test_dir}/${inputs[$i]}"
    expected_output="${test_dir}/${outputs[$i]}"
    actual_output="${output_dir}/${inputs[$i]%.in.txt}.myout.txt"

    # Ejecutar el programa con la entrada
    ./ejercicio9 < "$input" > "$actual_output"

    # Comparar la salida actual con la esperada y contar diferencias
    diff_count=$(diff -y --suppress-common-lines "$actual_output" "$expected_output" | wc -l)
    
    # Mostrar el resultado
    echo "Prueba ${inputs[$i]}: ${diff_count} diferencias"
done
