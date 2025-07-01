# Pipex

Pipex es un programa en C que simula el comportamiento de la construcción de un pipeline en Unix: `< infile cmd1 | cmd2 > outfile`.

## Descripción
El objetivo de Pipex es abrir un archivo de entrada (`infile`), ejecutar el primer comando (`cmd1`) leyendo de dicho archivo, pasar la salida a través de un pipe como entrada al segundo comando (`cmd2`) y finalmente redirigir la salida de este al archivo de salida (`outfile`).

## Requisitos
- Sistema Unix/Linux
- Compilador GCC
- Biblioteca Libft (ya incluida en el proyecto)
- Valgrind (opcional, para pruebas de memoria)

## Estructura del proyecto
```
Pipex/
├── Libft/         # Implementación de utilidades (split, calloc, cadena, etc.)
├── src/           # Código fuente de Pipex
│   ├── main.c     # Punto de entrada y manejo principal del programa
│   ├── utils.c    # Utilidades, gestión de memoria y rutas
│   ├── split.c    # Función ft_split para separar cadenas
│   ├── cmd.c      # Ejecución de comandos y manejo de pipes
│   └── open_close.c # Gestión de archivos
├── infile         # Archivo de prueba de entrada
├── Makefile       # Reglas para compilar y limpiar
└── pipex.h        # Definiciones y prototipos
```

## Compilación
En la carpeta raíz del proyecto:
```bash
make            # Compilación normal
make re         # Recompilación completa
```

## Uso básico
```bash
./pipex infile "cmd1 [args...]" "cmd2 [args...]" outfile
```
- `infile`: ruta al archivo de entrada
- `cmd1`: primer comando con sus argumentos (entre comillas)
- `cmd2`: segundo comando con sus argumentos (entre comillas)
- `outfile`: ruta al archivo de salida

### Ejemplo
```bash
./pipex infile "grep hola" "wc -l" outfile  # Cuenta líneas que contienen "hola"
./pipex infile "cat" "wc -l" outfile        # Cuenta total de líneas
```

## Tests y Depuración

### Tests Automatizados
El proyecto incluye un script completo de pruebas (`run_tests.sh`) que verifica:
- Funcionamiento básico de pipes
- Manejo de errores
- Gestión de archivos
- Casos límite

Para ejecutar los tests:
```bash
chmod +x run_tests.sh  # Solo la primera vez
./run_tests.sh
```

### Pruebas con Valgrind
Valgrind es una herramienta esencial para detectar fugas de memoria y otros problemas relacionados.

Para ejecutar Pipex con Valgrind:
```bash
# Comprobación básica de fugas
valgrind ./pipex infile "cmd1" "cmd2" outfile

# Análisis detallado de memoria
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./pipex infile "cmd1" "cmd2" outfile
```

Opciones importantes de Valgrind:
- `--leak-check=full`: Detección detallada de fugas
- `--show-leak-kinds=all`: Muestra todos los tipos de fugas
- `--track-origins=yes`: Muestra el origen de los valores no inicializados

### Interpretación de resultados de Valgrind
- **HEAP SUMMARY**: Resumen del uso de memoria
- **definitely lost**: Fugas de memoria confirmadas
- **indirectly lost**: Fugas por pérdida de referencias
- **possibly lost**: Posibles fugas
- **still reachable**: Memoria aún accesible
- **ERROR SUMMARY**: Resumen total de errores

## Manejo de errores
El programa incluye verificaciones exhaustivas:
- Validación de argumentos (exactamente 5)
- Comprobación de permisos de archivos
- Verificación de comandos existentes
- Control de errores en operaciones del sistema

## Limpieza
Para limpiar los archivos generados:
```bash
make clean     # Elimina archivos objeto
make fclean    # Elimina objetos y ejecutable
```

## Solución de problemas comunes
1. **Comando no encontrado**
   - Verifica que el comando existe en el sistema
   - Comprueba los permisos del ejecutable

2. **Errores de archivo**
   - Verifica permisos de lectura/escritura
   - Comprueba que las rutas sean correctas

3. **Fugas de memoria**
   - Usa Valgrind para identificar el origen
   - Verifica que todos los recursos se liberan correctamente

## Notas de implementación
- Gestión cuidadosa de memoria con liberación de recursos
- Manejo robusto de errores con mensajes informativos
- Implementación eficiente de pipes y procesos hijo
- Limpieza apropiada en caso de errores


