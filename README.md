# proyecto-so-2

Preguntas a Valeria con respuestas:


 - La primera es el archivo de entrada, como es la estructura del archivo de entrada     que nos va a proporcionar para el problema 1? Sin eso no podemos avanzar         mucho, por lo menos en mi equipo

   ya publiqué un ejemplo en módulo 7, en 2do. proyecto 




- La segunda es, los registros para el marco de página son de 8 bits siempre?

  Si 




 - Cuando se refiere a que el mapeo es igual (1-1,2-2 y asi..) es porque no se debe hacer ninguna conversión como lo vimos en clase?
 
  Es el mapeo inicial de la tabla de página. Es configurar la tabla de páginas para que arranque con unos valores válidos. 
  
  
  
  

 - Dice que las paginas van de 1 a 16, es decir, que puede haber una sola página como puede haber 16, ahora, la cantidad de bits del registro de entrada define la cantidad de paginas a trabajar? 
 
Las páginas virtuales van de 1 a 6, las físicas van de 1 a 6. La cantidad de bits del registro de entrada son las peticiones de páginas virtuales. Si el número de marcos de página es 4, entonces cada petición consta de máximo 4 páginas virtuales.




 
  - por ejemplo, en el enunciado salen distintos registros por tiempo de reloj para saber cuales paginas van a ser referenciadas y reescritas, pero esos registros son siempre de 6 bits, al igual que la cantidad de paginas. No se si me explico bien

No, son 6 bits si hay 6 marcos de página, si hay 3 marcos de página, serán 3 bits. Y como lo vamos a poner en decimal, máximo son 3 peticiones. 





- Si hay un fallo de pagina porque la pagina no existe, se elimina la pagina que     tenga menor NÚMERO DE REGISTRO  NO MENOR MARCO DE PÁGINA marco de pagina no? Se elimina esa y por cual la sustituyo?

Ses sustiuye por el marco de página que tenga menor número en los registros. Como está en el ejemplo. 




- La unica manera de que haya un fallo de pagina es que el indice no exista? 

Si. Que en la tabla de páginas diga que no está mapeada a un marco de página. 


