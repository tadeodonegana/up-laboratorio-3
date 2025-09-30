ipcs -m      # ver segmentos de memoria
ipcs -s      # ver semáforos

# Elimina por ID lo que veas tuyo y relacionado:
ipcrm -m <shmid>
ipcrm -s <semid>

# Alternativa por clave (si tu ipcrm lo soporta):
# ipcrm -M 0x<clave_hex>   # memoria
# ipcrm -S 0x<clave_hex>   # semáforo