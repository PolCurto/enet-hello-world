# 1. Imagen base con herramientas de compilación C++ en Linux
FROM ubuntu:22.04 AS builder

# Evitar preguntas interactivas durante la instalación
ENV DEBIAN_FRONTEND=noninteractive

# Instalar compilador, CMake y dependencias necesarias
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    g++ \
    && rm -rf /var/lib/apt/lists/*

# Crear carpeta de trabajo
WORKDIR /app

# Copiar el código fuente del proyecto al contenedor
COPY . .

# Configurar y compilar el proyecto en modo Release
RUN cmake -B build -DCMAKE_BUILD_TYPE=Release
RUN cmake --build build --target GameServer

# 2. Etapa de ejecución (Imagen final hiper ligera)
FROM ubuntu:22.04

WORKDIR /app

# Copiar solo el ejecutable compilado desde la etapa anterior
COPY --from=builder /app/build/GameServer .

# Exponer el puerto UDP de tu servidor ENet (cambia '4545' si usas otro)
EXPOSE 4545/udp

# Comando por defecto al arrancar el contenedor
CMD ["./GameServer"]