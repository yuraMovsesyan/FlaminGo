
stdcall StringCopy,"Hello World-1", write, 14
push write
call[printf]
stdcall StringCopy, '', write, 14

push p
call[getch]
