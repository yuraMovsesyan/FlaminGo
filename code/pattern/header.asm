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
