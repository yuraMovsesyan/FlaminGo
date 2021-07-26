
push NULL
                call [ExitProcess]

                ;type function for string copy
                proc StringCopy uses esi edi ecx,str1,str2,len

                          mov esi,[str1]
                          mov edi,[str2]
                          mov ecx,[len]
                          rep movsb
                          ret
                 endp

section '.idata' import data readable

        library kernel, 'kernel32.dll',\
                msvcrt, 'msvcrt.dll'

        import kernel,\
               SetConsoleOutputCP,'SetConsoleOutputCP',\
               SetConsoleCP,'SetConsoleCP',\
               ExitProcess, 'ExitProcess'

        import msvcrt,\
               printf, 'printf',\
               getch, '_getch',\
               scanf, 'scanf'