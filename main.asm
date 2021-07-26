
stdcall StringCopy,"a=", write, 2
push write
call[printf]
stdcall StringCopy, '', write, 2

push a
call[scanf]

stdcall StringCopy,"b = ", write, 4
push write
call[printf]
stdcall StringCopy, '', write, 4

push b
call[scanf]


mov eax, a
mov c, eax


mov eax, b
add c, eax

stdcall StringCopy,"a + b = ", write, 8
push write
call[printf]
stdcall StringCopy, '', write, 8

push c
call[printf]

push endl
call[printf]

stdcall StringCopy,"a-b = ", write, 6
push write
call[printf]
stdcall StringCopy, '', write, 6


mov eax, a
mov ebx, b
sub eax, ebx
push eax
call[printf]

push endl
call[printf]

stdcall StringCopy,"a * b = ", write, 8
push write
call[printf]
stdcall StringCopy, '', write, 8


mov eax, a
mov ebx, b
imul eax, ebx
push eax
call[printf]

push endl
call[printf]

stdcall StringCopy,"a", write, 1
push write
call[printf]
stdcall StringCopy, '', write, 1

stdcall StringCopy," / b", write, 4
push write
call[printf]
stdcall StringCopy, '', write, 4

stdcall StringCopy," = ", write, 3
push write
call[printf]
stdcall StringCopy, '', write, 3


mov eax, a
mov ebx, b
idiv eax, ebx
push eax
call[printf]

push endl
call[printf]


mov eax, a
mov c, eax


mov eax, b
add c, eax


mov eax, a
mov c, eax


mov eax, b
add c, eax


mov eax, a
mov c, eax


mov eax, b
add c, eax
