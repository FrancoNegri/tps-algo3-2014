for i in 2 3 4 7
	do
		sed -n 2~2p resultados$i.txt > tiempo$i
		sed -n 1~2p resultados$i.txt > respuesta$i
	done

	paste tiempo2 tiempo3 tiempo4 tiempo7 > tiempos
	paste respuesta2 respuesta3 respuesta4 respuesta7 > respuestas