## updating platformio 
# pio platform update
# pio pkg update

## building and uploading
pio run -t clean
# pio run -t stlink-reset
pio run
pio run -t upload