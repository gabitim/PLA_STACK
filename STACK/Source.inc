COORD STRUCT
	x		WORD ?
	y		WORD ?
COORD ENDS

SMALL_RECT STRUCT
	Left	WORD ?
	Top		WORD ?
	Right	WORD ?
	Bottom	WORD ?
SMALL_RECT ENDS

CONSOLE_SCREEN_BUFFER_INFO STRUCT
	dwSize				COORD <>
	dwCursorPosition	COORD <>
	wAttributes			WORD ?
	srWindow			SMALL_RECT <>
	dwMaximumWindowSize	COORD <>
CONSOLE_SCREEN_BUFFER_INFO ENDS

MOUSE_EVENT_RECORD STRUCT
	dwMousePosition		COORD <>
	dwButtonState		DWORD ?
	dwControlKeyState	DWORD ?
	dwEventFlags		DWORD ?
MOUSE_EVENT_RECORD ENDS

KEY_EVENT_RECORD STRUCT
	bKeyDown			BOOL ?		; in Win32/64 BOOL = DWORD
	wRepeatCount		WORD ?
	wVirtualKeyCode		WORD ?
	wVirtualScanCode	WORD ?
	UNION
		UnicodeChar		WORD ?
		AsciiChar		BYTE ?
	ENDS
	dwControlKeyState DWORD ?
KEY_EVENT_RECORD ENDS

WINDOW_BUFFER_SIZE_RECORD STRUCT
	dwSize			COORD <>
WINDOW_BUFFER_SIZE_RECORD ENDS

MENU_EVENT_RECORD STRUCT
	dwCommandId		DWORD ?
MENU_EVENT_RECORD ENDS

FOCUS_EVENT_RECORD STRUCT
	bSetFocus		BOOL ?		; in Win32/64 BOOL = DWORD
FOCUS_EVENT_RECORD ENDS

INPUT_RECORD STRUCT 
  EventType             WORD ?
  two_byte_alignment    WORD ?
  UNION
    KeyEvent                KEY_EVENT_RECORD            <>
    MouseEvent              MOUSE_EVENT_RECORD          <>
    WindowBufferSizeEvent   WINDOW_BUFFER_SIZE_RECORD   <>
    MenuEvent               MENU_EVENT_RECORD           <>
    FocusEvent              FOCUS_EVENT_RECORD          <>
  ENDS 
INPUT_RECORD ENDS 

printf MACRO format:REQ, args:VARARG
	fn vc_printf, cfm$(format), args
	EXITM <>
ENDM

scanf MACRO format:REQ, args:VARARG
	fn vc_scanf, cfm$(format), args
	EXITM <>
ENDM

textcolor MACRO attr:REQ
	fn SetConsoleTextAttribute, StdOutput, attr
	EXITM <>
ENDM

input MACRO prompt
	IFNB <prompt>
		conout prompt
	ENDIF
	fn StdIn, addr buffer, 260
	EXITM <>
ENDM

malloc MACRO size:REQ
	invoke HeapAlloc, rv(GetProcessHeap), 0, size
	EXITM <rax>
ENDM
  
free MACRO memory:REQ
	invoke HeapFree, rv(GetProcessHeap), 0, memory
	EXITM <>
ENDM

strlen MACRO src:REQ
	invoke StrLen, src
	EXITM <rax>
ENDM

strcpy MACRO dest:REQ, src:REQ
	invoke StrCopy, dest, src
	EXITM <>
ENDM

strcmp MACRO src1:REQ, src2:REQ
	invoke StrCmp, src1, src2
	EXITM <>
ENDM

strconcat MACRO dest:REQ, src1:REQ, src2:REQ
	invoke StrConcat, dest, src1, src2
	EXITM <>
ENDM


cls MACRO
	call ClearScreen
	EXITM <>
ENDM

gotoxy MACRO @x:REQ, @y:REQ
	mov  ecx, StdOutput
	mov  dx, @y
	shl  edx, 16
	mov  dx, @x
	call SetConsoleCursorPosition
	EXITM <>
ENDM
