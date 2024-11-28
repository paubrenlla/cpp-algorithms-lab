#!/bin/bash

# Compilar el programa
g++ -std=c++11 -o ejercicio10 ejercicio10.cpp

# Lista de archivos de entrada y salida esperada
inputs=("2.in.txt" "3.in.txt" "4.in.txt" "5.in.txt" "6.in.txt")
outputs=("2.out.txt" "3.out.txt" "4.out.txt" "5.out.txt" "6.out.txt")

# Directorio de pruebas
test_dir="tests/ejercicio10"
output_dir="tests/ejercicio10Outs"

# Crear el directorio de salida si no existe
mkdir -p "$output_dir"

# Ejecutar las pruebas y comparar salidas
for i in ${!inputs[@]}; do
    input="${test_dir}/${inputs[$i]}"
    expected_output="${test_dir}/${outputs[$i]}"
    actual_output="${output_dir}/${inputs[$i]%.in.txt}.myout.txt"

    # Ejecutar el programa con la entrada
    ./ejercicio10 < "$input" > "$actual_output"

    # Comparar la salida actual con la esperada y contar diferencias
    diff_count=$(diff -y --suppress-common-lines "$actual_output" "$expected_output" | wc -l)
    
    # Mostrar el resultado
    echo "Prueba ${inputs[$i]}: ${diff_count} diferencias"
done
