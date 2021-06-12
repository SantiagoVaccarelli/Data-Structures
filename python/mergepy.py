def merge():
    with open("archivo1.csv", "r") as archivo1,open ("archivo2.csv", "r") as archivo2, open ("archivofinal.csv", "w") as archivo_final:
        while archivo1 or archivo2:
            a1 = archivo1.readline()
            a2 = archivo2.readline()
            if a1 > a2:
                archivo_final.write(a1)
                a1 = archivo1.readline()
            else:
                archivo_final.write(a2)
                a2 = archivo2.readline()


