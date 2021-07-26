format PE console

entry start

include '..\fasm\INCLUDE\win32ax.inc'
include '..\fasm\INCLUDE\ENCODING\WIN1251.inc'

section '.data' data readable writable

formatStr db '%s', 0
formatNum db '%d', 0
write rb 360
endl db 10, 13, 0
NULL = 0
_aIf rd 2
_bIf rd 2
p rd 10

section '.code' code readable executable

        start:

                invoke  SetConsoleOutputCP,1251
                invoke  SetConsoleCP,1251

stdcall StringCopy,"Hello World-1", write, 14
push write
call[printf]
stdcall StringCopy, '', write, 14

push p
call[getch]

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
