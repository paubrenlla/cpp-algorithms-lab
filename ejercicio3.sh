#!/bin/bash

# Compilar el programa
g++ -std=c++11 -o ejercicio3 ejercicio3.cpp

# Lista de archivos de entrada y salida esperada
inputs=("5_3.in.txt" "10_3.in.txt" "100_10.in.txt" "200_30.in.txt" "1000_10.in.txt" "10000_100.in.txt" "100000_300.in.txt" "1000000_1000.in.txt")
outputs=("5_3.out.txt" "10_3.out.txt" "100_10.out.txt" "200_30.out.txt" "1000_10.out.txt" "10000_100.out.txt" "100000_300.out.txt" "1000000_1000.out.txt")

# Directorio de pruebas
test_dir="tests/ejercicio3"
output_dir="tests/ejercicio3Outs"

# Crear el directorio de salida si no existe
mkdir -p "$output_dir"

# Ejecutar las pruebas y comparar salidas
for i in ${!inputs[@]}; do
    input="${test_dir}/${inputs[$i]}"
    expected_output="${test_dir}/${outputs[$i]}"
    actual_output="${output_dir}/${inputs[$i]%.in.txt}.myout.txt"

    # Ejecutar el programa con la entrada
    ./ejercicio3 < "$input" > "$actual_output"

    # Comparar la salida actual con la esperada y contar diferencias
    diff_count=$(diff -y --suppress-common-lines "$actual_output" "$expected_output" | wc -l)
    
    # Mostrar el resultado
    echo "Prueba ${inputs[$i]}: ${diff_count} diferencias"
done
