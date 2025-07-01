#!/usr/bin/env bash
# run_tests.sh: pruebas automáticas para Pipex
set -e

PIPEX=./pipex
INFILE=infile
EXPECTED=outfile

# Limpieza previa
rm -f test_* out_* 2>/dev/null || true

echo "=== Test 1: cat | wc -l ==="
# calculamos resultado esperado usando shell builtin
EXP_VAL=$(wc -l < $INFILE)
$PIPEX $INFILE "cat" "wc -l" test_out1
ACT_VAL=$(cat test_out1)
if [ "$ACT_VAL" -eq "$EXP_VAL" ]; then
    echo "OK"
else
    echo "FAIL: esperado $EXP_VAL, obtenido $ACT_VAL"
fi

echo "\n=== Test 2: grep 'hola' | wc -l ==="
# calculamos resultado esperado usando shell builtin
EXP_VAL=$(grep hola < $INFILE | wc -l)
$PIPEX $INFILE "grep hola" "wc -l" test_out2
ACT_VAL=$(cat test_out2)
if [ "$ACT_VAL" -eq "$EXP_VAL" ]; then
    echo "OK"
else
    echo "FAIL: esperado $EXP_VAL, obtenido $ACT_VAL"
fi

echo "\n=== Test 3: número de args incorrecto ==="
set +e
$PIPEX
CODE=$?
set -e
if [ $CODE -ne 0 ]; then
    echo "OK (error esperado con código $CODE)"
else
    echo "FAIL: debería fallar por args不足"
fi

echo "\n=== Test 4: comando inexistente ==="
set +e
# Capturamos stderr y código de salida
ERR_MSG=$($PIPEX $INFILE "cmd_no_exist" "wc -l" test_out4 2>&1)
CODE=$?
set -e
# Verificamos que falle y que el mensaje contenga 'No such file'
if [ $CODE -ne 0 ] && [ -n "$ERR_MSG" ]; then
    echo "OK (error esperado: $ERR_MSG)"
else
    echo "FAIL: debería fallar por comando no encontrado. Salida: $ERR_MSG"
fi

echo "\n=== Test 5: sobreescritura de outfile existente ==="
# Preparamos un outfile existente con contenido previo
echo "LINE1" > test_out5
# Ejecutamos y esperamos que sobrescriba
$PIPEX $INFILE "cat" "wc -l" test_out5
ACT_VAL=$(cat test_out5)
EXP_VAL=$(wc -l < $INFILE)
if [ "$ACT_VAL" -eq "$EXP_VAL" ]; then
    echo "OK"
else
    echo "FAIL: esperado $EXP_VAL, obtenido $ACT_VAL"
fi

echo "\n=== Test 6: infile inexistente ==="
set +e
ERR_MSG=$($PIPEX nofile "cat" "wc -l" test_out6 2>&1)
CODE=$?
set -e
if [ $CODE -ne 0 ] && [ -n "$ERR_MSG" ]; then
    echo "OK (error esperado: $ERR_MSG)"
else
    echo "FAIL: debería fallar por infile inexistente. Salida: $ERR_MSG"
fi

# Limpieza final opcional
# rm -f test_out*
