#!/bin/bash

# Compilar el programa
g++ -std=c++11 -o ejercicio5 ejercicio5.cpp

# Lista de archivos de entrada y salida esperada
inputs=("5.in.txt" "10.in.txt" "20.in.txt" "30.in.txt" "40.in.txt" "50.in.txt" "100.in.txt")
outputs=("5.out.txt" "10.out.txt" "20.out.txt" "30.out.txt" "40.out.txt" "50.out.txt" "100.out.txt")

# Directorio de pruebas
test_dir="tests/ejercicio5"
output_dir="tests/ejercicio5Outs"

# Crear el directorio de salida si no existe
mkdir -p "$output_dir"

# Ejecutar las pruebas y comparar salidas
for i in ${!inputs[@]}; do
    input="${test_dir}/${inputs[$i]}"
    expected_output="${test_dir}/${outputs[$i]}"
    actual_output="${output_dir}/${inputs[$i]%.in.txt}.myout.txt"

    # Ejecutar el programa con la entrada
    ./ejercicio5 < "$input" > "$actual_output"

    # Comparar la salida actual con la esperada y contar diferencias
    diff_count=$(diff -y --suppress-common-lines "$actual_output" "$expected_output" | wc -l)
    
    # Mostrar el resultado
    echo "Prueba ${inputs[$i]}: ${diff_count} diferencias"
done
